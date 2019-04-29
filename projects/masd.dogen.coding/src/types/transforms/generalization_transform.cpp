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
#include "masd.dogen.utility/types/io/unordered_set_io.hpp"
#include "masd.dogen.utility/types/io/optional_io.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/io/meta_model/name_io.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/helpers/resolver.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/generalization_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.generalization_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string parent_not_found("Could not find parent: ");
const std::string incompatible_is_final(
    "Attempt to force is final on a type with children: ");

}

namespace masd::dogen::coding::meta_model {

inline bool operator<(const name& lhs, const name& rhs) {
    return lhs.qualified().dot() < rhs.qualified().dot();
}

}

namespace masd::dogen::coding::transforms {

generalization_transform::feature_group
generalization_transform::make_feature_group(
    const variability::meta_model::feature_model& fm) {

    feature_group r;
    const variability::helpers::feature_selector s(fm);
    r.is_final = s.get_by_name(traits::generalization::is_final());
    return r;
}

boost::optional<bool>
generalization_transform::make_is_final(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);

    if (s.has_configuration_point(fg.is_final))
        return s.get_boolean_content(fg.is_final);

    return boost::optional<bool>();
}

std::unordered_set<std::string>
generalization_transform::update_and_collect_parent_ids(
    const helpers::indices& idx, meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Updating and collecting parent ids.";

    using helpers::resolver;
    std::unordered_set<std::string> r;
    for (auto& pair : m.objects()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

        auto& o(*pair.second);
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
        std::list<meta_model::name> resolved_parents;
        for (const auto& pn : o.parents()) {
            const auto resolved_pn(resolver::resolve(m, idx, o.name(), pn));
            r.insert(resolved_pn.qualified().dot());
            resolved_parents.push_back(resolved_pn);
        }

        o.parents(resolved_parents);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished updating and collecting parent ids: "
                             << r;
    return r;
}

void generalization_transform::populate_properties_up_the_generalization_tree(
    const feature_group& fg, const meta_model::name& leaf,
    meta_model::model& em, meta_model::object& o) {

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
        const auto& ml(em.name().location());
        if (ll.model_modules() == ml.model_modules())
            em.leaves().insert(leaf);

        return;
    }

    for (const auto& pn : o.parents()) {
        auto i(em.objects().find(pn.qualified().dot()));
        if (i == em.objects().end()) {
            BOOST_LOG_SEV(lg, error) << parent_not_found
                                     << pn.qualified().dot();
            BOOST_THROW_EXCEPTION(
                transformation_error(parent_not_found + pn.qualified().dot()));
        }

        auto& parent(*i->second);
        populate_properties_up_the_generalization_tree(fg, leaf, em, parent);

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

void generalization_transform::
populate_generalizable_properties(const feature_group& fg,
    const std::unordered_set<std::string>& parent_ids, meta_model::model& m) {

    for (auto& pair : m.objects()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

        auto& o(*pair.second);

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
         const auto is_final(make_is_final(fg, *o.configuration()));
         if (is_final) {
             if (*is_final && o.is_parent()) {
                 BOOST_LOG_SEV(lg, error) << incompatible_is_final << id;
                 BOOST_THROW_EXCEPTION(
                     transformation_error(incompatible_is_final + id));
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

         populate_properties_up_the_generalization_tree(fg, o.name(), m, o);
    }
}

void generalization_transform::sort_leaves(meta_model::model& m) {
    for (auto& pair : m.objects()) {
        auto& o(*pair.second);
        o.leaves().sort();
    }
}

void generalization_transform::apply(const context& ctx,
    const helpers::indices& idx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "generalization transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto parent_ids(update_and_collect_parent_ids(idx, m));
    const auto fg(make_feature_group(*ctx.feature_model()));
    populate_generalizable_properties(fg, parent_ids, m);
    sort_leaves(m);

    stp.end_transform(m);
}

}
