/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/throw_exception.hpp>
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/utility/io/optional_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/resolver.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/generalization_expander.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.generalization_expander"));

const std::string parent_not_found("Could not find parent: ");
const std::string incompatible_is_final(
    "Attempt to force is final on a type with children: ");

}

namespace dogen {
namespace yarn {

inline bool operator<(const name& lhs, const name& rhs) {
    return lhs.id() < rhs.id();
}

generalization_expander::type_group generalization_expander::make_type_group(
    const annotations::type_repository& atrp) const {

    type_group r;
    const annotations::type_repository_selector s(atrp);
    r.is_final = s.select_type_by_name(traits::generalization::is_final());
    return r;
}

boost::optional<bool>
generalization_expander::make_is_final(const type_group& tg,
    const annotations::annotation& a) const {
    const annotations::entry_selector s(a);

    if (s.has_entry(tg.is_final))
        return s.get_boolean_content(tg.is_final);

    return boost::optional<bool>();
}

std::unordered_set<std::string>
generalization_expander::update_and_collect_parent_ids(const indices& idx,
    intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Updating and collecting parent ids.";

    resolver rs;
    std::unordered_set<std::string> r;
    for (auto& pair : im.objects()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

        auto& o(pair.second);
        if (o.parents().empty())
            continue;

        /*
         * Resolve the parent names. This is required because they may
         * have been supplied via meta-data, and as such, be
         * incomplete. We can't wait for the resolution step proper
         * because there is a circular dependency: resolution needs
         * streotype expansion and streotype expansion needs
         * generalization, which needs resolution. So we must resolve
         * here.
         */
        std::list<name> resolved_parents;
        for (const auto& pn : o.parents()) {
            const auto resolved_pn(rs.resolve(im, idx, o.name(), pn));
            r.insert(resolved_pn.id());
            resolved_parents.push_back(resolved_pn);
        }

        o.parents(resolved_parents);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished updating and collecting parent ids: "
                             << r;
    return r;
}

void generalization_expander::populate_properties_up_the_generalization_tree(
    const type_group& tg, const yarn::name& leaf,
    intermediate_model& im, yarn::object& o) const {

    /*
     * Add the leaf to all nodes of the tree except for the leaf node
     * itself.
     */
    if (!o.is_leaf())
        o.leaves().push_back(leaf);

    /*
     * If we do not have any parents, we have reached the top of the
     * generalisation tree.
     */
    if (o.parents().empty()) {
        /*
         * If the leaf name belongs to the target model, add it to
         * the model's list of leaves. Ignore non-target leaves.
         */
        const auto& ll(leaf.location());
        const auto& ml(im.name().location());
        if (ll.model_modules() == ml.model_modules())
            im.leaves().insert(leaf);

        return;
    }

    for (const auto& pn : o.parents()) {
        auto i(im.objects().find(pn.id()));
        if (i == im.objects().end()) {
            BOOST_LOG_SEV(lg, error) << parent_not_found << pn.id();
            BOOST_THROW_EXCEPTION(expansion_error(parent_not_found + pn.id()));
        }

        auto& parent(i->second);
        populate_properties_up_the_generalization_tree(tg, leaf, im, parent);

        if (parent.parents().empty()) {
            /*
             * If our parent does not have a parent, then it is our
             * root parent.
             */
            o.root_parents().push_back(parent.name());
        } else {
            /*
             * On all other cases, inherit the root parents property
             * from our direct parent; these would have been populated
             * from the root parent as per above.
             */
            for (const auto& rp : parent.root_parents())
                o.root_parents().push_back(rp);
        }
    }
}

void generalization_expander::
populate_generalizable_properties(const type_group& tg,
    const std::unordered_set<std::string>& parent_ids,
    intermediate_model& im) const {

    for (auto& pair : im.objects()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

        auto& o(pair.second);

        /*
         * We are a child if we have at least one parent.
         */
        o.is_child(!o.parents().empty());

         /*
          * We are a parent if someone else declared us as their parent.
          */
         const auto i(parent_ids.find(id));
         o.is_parent(i != parent_ids.end());

         /*
          * Parents are always abstract.
          */
         o.is_abstract(o.is_parent());

         /*
          * Handle the case where the user decided to override final.
          */
         const auto is_final(make_is_final(tg, o.annotation()));
         if (is_final) {
             if (*is_final && o.is_parent()) {
                 BOOST_LOG_SEV(lg, error) << incompatible_is_final << id;
                 BOOST_THROW_EXCEPTION(
                     expansion_error(incompatible_is_final + id));
             }
             o.is_final(*is_final);
         } else {
             /*
              * By default we setup all childless types and leaf types
              * as final, unless the user tells us otherwise.
              */
             o.is_final(!o.is_parent());
         }

         /*
          * We are in an inheritance (generalisation) relationship if
          * we are either a parent or a child (or both).
          */
         o.in_inheritance_relationship(o.is_parent() || o.is_child());

         /*
          * We are a leaf if we are not a parent but we are a child.
          */
         o.is_leaf(!o.is_parent() && o.is_child());

         if (!o.is_leaf())
             continue;

         populate_properties_up_the_generalization_tree(tg, o.name(), im, o);
    }
}

void generalization_expander::sort_leaves(intermediate_model& im) const {
    for (auto& pair : im.objects()) {
        auto& o(pair.second);
        o.leaves().sort();
    }
}

void generalization_expander::
expand(const annotations::type_repository& atrp, const indices& idx,
    intermediate_model& im) const {
    const auto parent_ids(update_and_collect_parent_ids(idx, im));

    const auto tg(make_type_group(atrp));
    populate_generalizable_properties(tg, parent_ids, im);
    sort_leaves(im);
}

} }
