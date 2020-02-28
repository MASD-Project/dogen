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
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.assets/io/meta_model/name_io.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/types/helpers/resolver.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/helpers/name_builder.hpp"
#include "dogen.assets/types/features/generalization.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/transforms/generalization_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.generalization_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string parent_not_found("Could not find parent: ");
const std::string incompatible_is_final(
    "Attempt to force is final on a type with children: ");
const std::string parent_name_conflict(
    "Parent name is defined in both meta-data and structure of model: ");

}

namespace dogen::assets::meta_model {

inline bool operator<(const name& lhs, const name& rhs) {
    return lhs.qualified().dot() < rhs.qualified().dot();
}

}

namespace dogen::assets::transforms {

std::unordered_set<std::string> generalization_transform::
update_and_collect_parent_ids(const helpers::indices& idx,
    const variability::meta_model::feature_model& fm, meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Updating and collecting parent ids.";

    using helpers::resolver;
    std::unordered_set<std::string> r;
    using features::generalization;
    const auto fg(generalization::make_feature_group(fm));
    for (auto& pair : m.structural_elements().objects()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, trace) << "Processing type: " << id;

        /*
         * Obtain the static configuration from the meta-data.
         */
        auto& o(*pair.second);
        const auto scfg(generalization::make_static_configuration(fg, o));

        /*
         * Populate "is final requested" directly, as per user
         * input. Note that we cannot actually compute the flag's
         * ultimate state at this point, and hence why two fields are
         * needed: one to signify that the user requested the class to
         * be final and another to determine that the class is really
         * final.
         */
        o.is_final_requested(scfg.is_final);

        /*
         * Now handle parenting information in meta-data. If no parent
         * was set in the meta-data then there is nothing to do.
         */
        if (!scfg.parent.empty()) {
            BOOST_LOG_SEV(lg, trace) << "Parent: " << scfg.parent;

            /*
             * If we've already have a parent name, this means there
             * are now two conflicting sources of parenting
             * information, so we need to bomb out.
             */
            BOOST_LOG_SEV(lg, trace) << "Parents: " << o.parents();
            if (!o.parents().empty()) {
                const auto& n(o.name().qualified().dot());
                BOOST_LOG_SEV(lg, error) << parent_name_conflict << n;
                BOOST_THROW_EXCEPTION(
                    transformation_error(parent_name_conflict + n));
            }

            /*
             * Convert the string obtained via meta-data into a assets
             * name and set it as our parent name.
             */
            const auto pn(helpers::name_builder::build(scfg.parent));
            o.parents().push_back(pn);
        }

        /*
         * If we still have no parents, then there is nothing to do.
         */
        if (o.parents().empty()) {
            BOOST_LOG_SEV(lg, trace) << "Type has no parents.";
            continue;
        }

        /*
         * Resolve the parent names. This is required because they may
         * have been supplied via meta-data, and as such, may be
         * incomplete. We can't wait for the resolution step proper
         * because there is a circular dependency: resolution needs
         * stereotype expansion and streotype expansion needs
         * generalisation (as it handles visitors, which need leaves,
         * etc), which in turn needs resolution. So, in order to break
         * the cycle, we resolve here.
         *
         * Note that we are also gathering the parent names after
         * resolution.
         */
        std::list<meta_model::name> resolved_parents;
        for (const auto& pn : o.parents()) {
            const auto resolved_pn(resolver::resolve(m, idx, o.name(), pn));
            resolved_parents.push_back(resolved_pn);

            const auto& pid(resolved_pn.qualified().dot());
            BOOST_LOG_SEV(lg, trace) << "Resolved parent: " << pid;
            r.insert(pid);
        }

        o.parents(resolved_parents);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished updating and collecting parent ids: "
                             << r;
    return r;
}

void generalization_transform::walk_up_generalization_tree(
    const meta_model::name &leaf, meta_model::model& m,
    meta_model::structural::object& o) {

    BOOST_LOG_SEV(lg, trace) << "Updating leaves for: "
                             << o.name().qualified().dot()
                             << " Leaf: " << leaf.qualified().dot();

    /*
     * Add the leaf to all nodes of the tree except for the leaf node
     * itself. The leaf node is the last child of a branch of
     * inheritance.
     */
    if (!o.is_leaf()) {
        o.leaves().push_back(leaf);
        BOOST_LOG_SEV(lg, trace) << "Added leaf to object.";
    }

    /*
     * If we do not have any parents, we have reached the top of the
     * generalisation tree. The top of the tree is the top-most class
     * in an inheritance graph (the root parent).
     */
    if (o.parents().empty()) {
        /*
         * If the leaf name belongs to the target model, add it to the
         * model's list of leaves. Ignore non-target leaves.
         */
        const auto& ll(leaf.location());
        const auto& ml(m.name().location());
        if (ll.model_modules() == ml.model_modules()) {
            m.leaves().insert(leaf);
            BOOST_LOG_SEV(lg, trace) << "Added leaf to model.";
        } else
            BOOST_LOG_SEV(lg, trace) << "Ignoring non-target leaf.";

        return;
    }

    /*
     * Now we climb up the inheritance graph.
     */
    for (const auto& pn : o.parents()) {
        const auto& pid(pn.qualified().dot());
        BOOST_LOG_SEV(lg, trace) << "Processing parent: " << pid;

        /*
         * Parents must exist or else the model is inconsistent.
         */
        auto i(m.structural_elements().objects().find(pid));
        if (i == m.structural_elements().objects().end()) {
            BOOST_LOG_SEV(lg, error) << parent_not_found << pid;
            BOOST_THROW_EXCEPTION(transformation_error(parent_not_found + pid));
        }

        auto& parent(*i->second);
        walk_up_generalization_tree(leaf, m, parent);

        if (parent.parents().empty()) {
            /*
             * If our parent does not have a parent, then it is our
             * root parent.
             */
            BOOST_LOG_SEV(lg, trace) << "Found root parent directly: "
                                     << parent.name().qualified().dot();
            o.root_parents().push_back(parent.name());
        } else {
            /*
             * On all other cases, inherit the root parents property
             * from our direct parent; these would have been populated
             * from the root parent as per above.
             */
            for (const auto& rp : parent.root_parents()) {
                BOOST_LOG_SEV(lg, trace) << "Found root parent indirectly: "
                                         << rp.qualified().dot();
                o.root_parents().push_back(rp);
            }
        }
    }
}

void generalization_transform::populate_generalizable_properties(
    const std::unordered_set<std::string>& parent_ids, meta_model::model& m) {

    for (auto& pair : m.structural_elements().objects()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, trace) << "Processing type: " << id;

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
         if (o.is_final_requested()) {
           /*
            * We can't have a final class if we already know it is a
            * parent.
            */
             if (*o.is_final_requested() && o.is_parent()) {
                 BOOST_LOG_SEV(lg, error) << incompatible_is_final << id;
                 BOOST_THROW_EXCEPTION(
                     transformation_error(incompatible_is_final + id));
             }
             o.is_final(*o.is_final_requested());
         } else {
             /*
              * By default we setup all childless types and leaf types
              * as final, unless the user tells us otherwise.
              */
             o.is_final(!o.is_parent());
         }

         /*
          * We are in an inheritance (generalisation) relationship if
          * we are either a parent or a child or both.
          */
         o.in_inheritance_relationship(o.is_parent() || o.is_child());

         /*
          * We are a leaf if we are not a parent but we are a child.
          */
         o.is_leaf(!o.is_parent() && o.is_child());
         if (!o.is_leaf()) {
             BOOST_LOG_SEV(lg, trace) << "Non-leaf type, processing finished.";
             continue;
         }

         walk_up_generalization_tree(o.name(), m, o);
    }
}

void generalization_transform::sort_leaves(meta_model::model& m) {
    for (auto& pair : m.structural_elements().objects()) {
        auto& o(*pair.second);
        o.leaves().sort();
    }
}

void generalization_transform::apply(const context& ctx,
    const helpers::indices& idx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "generalization transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& fm(*ctx.feature_model());
    const auto parent_ids(update_and_collect_parent_ids(idx, fm, m));
    populate_generalizable_properties(parent_ids, m);
    sort_leaves(m);

    stp.end_transform(m);
}

}
