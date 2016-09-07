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
#include <memory>
#include <functional>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/injection_error.hpp"
#include "dogen/yarn/types/injector.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("yarn.injector"));

const std::string empty;
const std::string visitor_name("visitor");
const std::string visitor_argument_name("v");
const std::string visitor_doc("Visitor for ");
const std::string visit_operation_doc("Accept visits for type ");
const std::string global_module_doc("Module that represents the global scope.");
const std::string duplicate_name(
    "Attempt to add object with a name that already exists in model: ");
const std::string zero_leaves("Type marked as visitable but has no leaves: ");
const std::string leaf_not_found("Could not find leaf object: ");
const std::string leaves_not_found("Could not find leaves for: ");
const std::string model_already_has_global_module(
    "Found a global module in model: ");
const std::string no_visitees("Visitor is not visiting any types: ");

}

namespace dogen {
namespace yarn {

template<typename AssociativeContainerOfContainable>
inline void add_containing_module_to_non_contained_entities(
    const name& container_name, AssociativeContainerOfContainable& c) {
    for (auto& pair : c) {
        auto& s(pair.second);
        if (!s.contained_by())
            s.contained_by(container_name);
    }
}

module injector::create_global_module() const {
    module r;
    r.generation_type(generation_types::no_generation);
    r.origin_type(origin_types::system);
    r.documentation(global_module_doc);
    return r;
}

std::unordered_map<location, std::list<name> > injector::
bucket_leaves_by_location(const std::list<name>& leaves) const {
    std::unordered_map<location, std::list<name> >  r;
    for (const auto& l : leaves)
        r[l.location()].push_back(l);

    return r;
}

visitor injector::create_visitor(const object& o, const location& l,
    const generation_types gt, const std::list<name>& leaves) const {
    name_builder b;
    b.simple_name(o.name().simple() + "_" + visitor_name);
    b.location(l);

    const auto n(b.build());
    BOOST_LOG_SEV(lg, debug) << "Creating visitor: " << n.id();

    visitor r;
    r.name(n);
    r.generation_type(gt);
    r.origin_type(origin_types::system);
    r.documentation(visitor_doc + o.name().simple());

    if (leaves.empty()) {
        BOOST_LOG_SEV(lg, error) << no_visitees << n.id();
        BOOST_THROW_EXCEPTION(injection_error(no_visitees + n.id()));
    }

    for (const auto& l : leaves)
        r.visits().push_back(l);

    BOOST_LOG_SEV(lg, debug) << "Created visitor: " << n.id();
    return r;
}

void injector::
inject_visitable_by(const std::list<name>& leaves, const visitor& v,
    intermediate_model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting visitable by for: "
                             << v.name().id();

    for (const auto& l : leaves) {
        auto i(m.objects().find(l.id()));
        if (i == m.objects().end()) {
            BOOST_LOG_SEV(lg, error) << leaf_not_found << l.id();
            BOOST_THROW_EXCEPTION(injection_error(leaf_not_found + l.id()));
        }

        auto vt(visitation_types::visitation_child_parent_visitor);
        if (v.parent())
            vt = visitation_types::visitation_child_descendant_visitor;

        auto& o(i->second);
        o.visitation_type(vt);
        o.visitable_by(v.name());
    }

    BOOST_LOG_SEV(lg, debug) << "Finished injecting visitable by.";
}

void injector::
add_visitor_to_model(const visitor& v, intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Adding visitor: " << v.name().id();

    const auto pair(std::make_pair(v.name().id(), v));
    const auto i(im.visitors().insert(pair));
    if (!i.second) {
        const auto id(v.name().id());
        BOOST_LOG_SEV(lg, error) << duplicate_name << id;
        BOOST_THROW_EXCEPTION(injection_error(duplicate_name + id));
    }
    BOOST_LOG_SEV(lg, debug) << "Added visitor: " << v.name().id();
}

void injector::inject_visitors(intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Injecting visitors for: " << im.name().id();

    for (auto& pair : im.objects()) {
        auto& o(pair.second);

        /*
         * We only care about the visitation roots - e.g. the
         * top-level classes marked as visitable. All other visitation
         * statuses are set by us (other than not visitable, of
         * course).
         */
        if (o.visitation_type() != visitation_types::visitation_root)
            continue;

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
            const auto id(o.name().id());
            BOOST_LOG_SEV(lg, error) << zero_leaves << id;
            BOOST_THROW_EXCEPTION(injection_error(zero_leaves + id));
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
        auto i(bucketed_leaves.find(o.name().location()));
        if (i == bucketed_leaves.end()) {
            const auto id(o.name().id());
            BOOST_LOG_SEV(lg, error) << leaves_not_found << id;
            BOOST_THROW_EXCEPTION(injection_error(leaves_not_found + id));
        }

        BOOST_LOG_SEV(lg, debug) << "Found bucketed leaves. Total: "
                                 << i->second.size();

        /*
         * Now we need to create the parent visitor. This always maps
         * to the root parent of the inheritance tree.
         */
        const auto& pvl(i->second);
        const auto& loc(o.name().location());

        /*
         * Preserve the generation type from the root object.
         */
        auto gt(o.generation_type());
        const auto pv(create_visitor(o, loc, gt, pvl));
        o.visitable_by(pv.name());
        inject_visitable_by(pvl, pv, im);
        add_visitor_to_model(pv, im);

        /*
         * If there is only one bucket of leaves then that refers to
         * the parent visitor, which we've already processed so there
         * is nothing else to do.
         */
        if (bucketed_leaves.size() == 1)
            continue;

        /*
         * There are other buckets, so first we need to remove the
         * bucket we've already processed.
         */
        bucketed_leaves.erase(i->first);

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
            const auto& bn(pair.first);
            gt = generation_types::no_generation;
            const auto mm(im.name().location().model_modules());
            const bool in_target_model(mm == bn.model_modules());
            if (in_target_model)
                gt = generation_types::full_generation;

            const auto& bl(pair.second);
            auto dv(create_visitor(o, bn, gt, bl));
            dv.parent(pv.name());
            inject_visitable_by(bl, dv, im);
            add_visitor_to_model(dv, im);
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Done injecting visitors.";
}

void injector::inject_global_module(intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Injecting global module for: "
                             << im.name().id();

    const auto gm(create_global_module());
    const auto gmn(gm.name());
    const auto i(im.modules().find(gmn.id()));
    if (i != im.modules().end()) {
        const auto id(im.name().id());
        BOOST_LOG_SEV(lg, error) << model_already_has_global_module << id;
        BOOST_THROW_EXCEPTION(
            injection_error(model_already_has_global_module + id));
    }
    im.modules().insert(std::make_pair(gmn.id(), gm));

    add_containing_module_to_non_contained_entities(gmn, im.modules());
    add_containing_module_to_non_contained_entities(gmn, im.concepts());
    add_containing_module_to_non_contained_entities(gmn, im.primitives());
    add_containing_module_to_non_contained_entities(gmn, im.enumerations());
    add_containing_module_to_non_contained_entities(gmn, im.objects());
    add_containing_module_to_non_contained_entities(gmn, im.exceptions());
    add_containing_module_to_non_contained_entities(gmn, im.visitors());

    BOOST_LOG_SEV(lg, debug) << "Done injecting global module";
}

void injector::inject(intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Running on: " << im.name().id();

    inject_visitors(im);
    inject_global_module(im);

    BOOST_LOG_SEV(lg, debug) << "Finished running";
}

} }
