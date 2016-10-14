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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/stereotypes_expander.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("yarn.stereotypes_expander"));

const std::string stereotype_visitor("visitable");
const std::string visitor_name("visitor");
const std::string visitor_argument_name("v");
const std::string visitor_doc("Visitor for ");
const std::string visit_operation_doc("Accept visits for type ");
const std::string duplicate_name(
    "Attempt to add object with a name that already exists in model: ");
const std::string zero_leaves("Type marked as visitable but has no leaves: ");
const std::string leaf_not_found("Could not find leaf object: ");
const std::string leaves_not_found("Could not find leaves for: ");
const std::string no_visitees("Visitor is not visiting any types: ");
const std::string visitable_child("Children cannot be marked as visitable: ");

}

namespace dogen {
namespace yarn {

std::unordered_map<location, std::list<name> > stereotypes_expander::
bucket_leaves_by_location(const std::list<name>& leaves) const {
    std::unordered_map<location, std::list<name> >  r;
    for (const auto& l : leaves)
        r[l.location()].push_back(l);

    return r;
}

visitor stereotypes_expander::create_visitor(const object& o, const location& l,
    const generation_types gt, const std::list<name>& leaves) const {
    name_builder b;
    b.simple_name(o.name().simple() + "_" + visitor_name);
    b.location(l);

    const auto n(b.build());
    BOOST_LOG_SEV(lg, debug) << "Creating visitor: " << n.id();

    visitor r;
    r.name(n);
    r.generation_type(gt);
    r.origin_type(o.origin_type());
    r.documentation(visitor_doc + o.name().simple());

    if (leaves.empty()) {
        BOOST_LOG_SEV(lg, error) << no_visitees << n.id();
        BOOST_THROW_EXCEPTION(expansion_error(no_visitees + n.id()));
    }

    for (const auto& l : leaves)
        r.visits().push_back(l);

    BOOST_LOG_SEV(lg, debug) << "Created visitor: " << n.id();
    return r;
}

void stereotypes_expander::
update_visited_leaves(const std::list<name>& leaves, const visitor_details& vd,
    intermediate_model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Updating leaves for: " << vd.base.id();

    for (const auto& l : leaves) {
        auto i(m.objects().find(l.id()));
        if (i == m.objects().end()) {
            BOOST_LOG_SEV(lg, error) << leaf_not_found << l.id();
            BOOST_THROW_EXCEPTION(expansion_error(leaf_not_found + l.id()));
        }

        auto& o(i->second);
        o.is_visitation_leaf(true);
        o.base_visitor(vd.base);
        o.derived_visitor(vd.derived);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished updating leaves.";
}

void stereotypes_expander::
add_visitor_to_model(const visitor& v, intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Adding visitor: " << v.name().id();

    const auto pair(std::make_pair(v.name().id(), v));
    const auto i(im.visitors().insert(pair));
    if (!i.second) {
        const auto id(v.name().id());
        BOOST_LOG_SEV(lg, error) << duplicate_name << id;
        BOOST_THROW_EXCEPTION(expansion_error(duplicate_name + id));
    }
    BOOST_LOG_SEV(lg, debug) << "Added visitor: " << v.name().id();
}

void stereotypes_expander::
expand_visitable(object& o, intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Expanding visitable for: " << o.name().id();

    /*
     * The visitable stereotype can only be applied to the root of
     * an inheritance tree - it's an error otherwise.
     */
    const auto id(o.name().id());
    if (o.is_child()) {
        BOOST_LOG_SEV(lg, error) << visitable_child << id;
        BOOST_THROW_EXCEPTION(expansion_error(visitable_child + id));
    }

    BOOST_LOG_SEV(lg, debug) << "Found visitation root: " << o.name().id();

    /*
     * Visitable types must have at least one leaf. We probably
     * should relax this in light of cross model visitation
     * support, but we'll leave it for now until there is a use
     * case. This means its not possible to mark a type as
     * visitable in one model and have all of its leaves on
     * different models.
     */
    if (o.leaves().empty()) {
        BOOST_LOG_SEV(lg, error) << zero_leaves << id;
        BOOST_THROW_EXCEPTION(expansion_error(zero_leaves + id));
    }

    /*
     * We need to organise the leaves by location. In truth, we
     * are trying to organise the leaves by model really, as there
     * is an assumption that we do not have multiple leaves in
     * different modules for the same model. But it should still
     * work if we do, we just end up generating multiple visitors
     * - one per module.
     *
     * Additional (crazy) limitation: we must have leaves on the
     * same location as the root parent.
     */
    auto bucketed_leaves(bucket_leaves_by_location(o.leaves()));
    auto j(bucketed_leaves.find(o.name().location()));
    if (j == bucketed_leaves.end()) {
        const auto id(o.name().id());
        BOOST_LOG_SEV(lg, error) << leaves_not_found << id;
        BOOST_THROW_EXCEPTION(expansion_error(leaves_not_found + id));
    }

    BOOST_LOG_SEV(lg, debug) << "Found bucketed leaves. Total: "
                             << j->second.size();

    /*
     * Now we need to create the base visitor. This always maps
     * to the root parent of the inheritance tree.
     */
    const auto& bvl(j->second);
    const auto& loc(o.name().location());

    /*
     * Preserve the generation type from the root object and
     * generate the visitor base.
     */
    auto gt(o.generation_type());
    const auto bv(create_visitor(o, loc, gt, bvl));
    const auto bvn(bv.name());
    o.is_visitation_root(true);
    o.base_visitor(bvn);
    update_visited_leaves(bvl, visitor_details(bvn), im);
    add_visitor_to_model(bv, im);

    /*
     * If there is only one bucket of leaves then that refers to
     * the parent visitor, which we've already processed so there
     * is nothing else to do.
     */
    if (bucketed_leaves.size() == 1)
        return;

    /*
     * There are other buckets, so first we need to remove the
     * bucket we've already processed.
     */
    bucketed_leaves.erase(j->first);

    /*
     * Now we need to create the descendant visitors, one per
     * bucket.
     */
    for (const auto& pair : bucketed_leaves) {
        /*
         * We are now (possibly) in different models other than
         * the model of the root parent. So, if we are generating
         * a visitor for the target model, we must ensure we set
         * the generation type correctly or else it will not come
         * out.
         */
        const auto& dv_location(pair.first);
        gt = generation_types::no_generation;
        const auto immm(im.name().location().model_modules());
        const bool in_target_model(immm == dv_location.model_modules());
        if (in_target_model)
            gt = generation_types::full_generation;

        /*
         * Generate the visitor derived and update its leaves.
         */
        const auto& bl(pair.second);
        auto dv(create_visitor(o, dv_location, gt, bl));
        const auto dvn(dv.name());
        dv.parent(bvn);
        update_visited_leaves(bl, visitor_details(bvn, dvn), im);
        add_visitor_to_model(dv, im);
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting visitor.";
}

void stereotypes_expander::expand(object& o, intermediate_model& im) const {
    for (const auto s : o.stereotypes()) {
        if (s == stereotype_visitor)
            expand_visitable(o, im);
    }
}

void stereotypes_expander::expand(intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Expanding stereotypes for: " << im.name().id();

    for (auto& pair : im.objects())
        expand(pair.second, im);

    BOOST_LOG_SEV(lg, debug) << "Finished expanding stereotypes";
}

} }
