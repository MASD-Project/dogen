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
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/utility/io/optional_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/generalization_expander.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.generalization_expander"));

const std::string parent_not_found("Could not find parent: ");

}

namespace dogen {
namespace yarn {

inline bool operator<(const name& lhs, const name& rhs) {
    return lhs.id() < rhs.id();
}

std::unordered_set<std::string>
generalization_expander::obtain_parent_ids(const intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining parent ids.";
    std::unordered_set<std::string> r;
    for (const auto& pair : im.objects()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

        const auto& o(pair.second);
        if (!o.parent())
            continue;

        r.insert(o.parent()->id());
    }
    BOOST_LOG_SEV(lg, debug) << "Finished obtaining parent ids: " << r;
    return r;
}

void generalization_expander::populate_properties_up_the_generalization_tree(
    const yarn::name& leaf, intermediate_model& im, yarn::object& o) const {

    // FIXME: massive hack. must not add leaves for services.
    const auto uds(object_types::user_defined_service);
    const bool skip_leaf(o.object_type() == uds);
    if (skip_leaf) {
        BOOST_LOG_SEV(lg, debug) << "Filtering out leaves for type: "
                                 << o.name().id();
    }

    /*
     * Add the leaf to all nodes of the tree except for the leaf node
     * itself.
     */
    if (!o.is_leaf() && !skip_leaf)
        o.leaves().push_back(leaf);

    /*
     * If we do not have a parent we have reached the top of the
     * generalisation tree.
     */
    if (!o.parent()) {
        if (skip_leaf)
            return;

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

    const auto pid(o.parent()->id());
    auto j(im.objects().find(pid));
    if (j == im.objects().end()) {
        BOOST_LOG_SEV(lg, error) << parent_not_found << pid;
        BOOST_THROW_EXCEPTION(expansion_error(parent_not_found + pid));
    }

    auto& parent(j->second);
    populate_properties_up_the_generalization_tree(leaf, im, parent);

    /*
     * If our parent does not have a parent then it is our root
     * parent.
     */
    if (!parent.parent()) {
        o.root_parent(parent.name());
        o.is_root_parent_visitable(parent.is_visitable());
    } else {
        /*
         * On all other cases, inherit the root parent properties for
         * our direct parent; these would have been populated from the
         * root parent as per above.
         */
        o.root_parent(parent.root_parent());
        o.is_root_parent_visitable(parent.is_root_parent_visitable());
    }
}

void generalization_expander::populate_generalizable_properties(
    const std::unordered_set<std::string>& parent_ids,
    intermediate_model& im) const {

    for (auto& pair : im.objects()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

        /*
         * We are a child if we have a parent.
         */
         auto& o(pair.second);
         o.is_child(!!o.parent());

         /*
          * We are a parent if someone else declared us as their parent.
          */
         const auto i(parent_ids.find(id));
         o.is_parent(i != parent_ids.end());

         // FIXME: for now until we handle final properly.
         o.is_final(!o.is_parent());

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

         populate_properties_up_the_generalization_tree(o.name(), im, o);
    }
}

void generalization_expander::sort_leaves(intermediate_model& im) const {
    for (auto& pair : im.objects()) {
        auto& o(pair.second);
        o.leaves().sort();
    }
}

void generalization_expander::expand(intermediate_model& im) const {
    const auto parent_ids(obtain_parent_ids(im));
    populate_generalizable_properties(parent_ids, im);
    sort_leaves(im);
}

} }
