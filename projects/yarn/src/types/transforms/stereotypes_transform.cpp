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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/resolver.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/orm_object_properties.hpp"
#include "dogen/yarn/types/orm_primitive_properties.hpp"
#include "dogen/yarn/types/transforms/stereotypes_transform.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.transforms.stereotypes_transform"));

const std::string stereotype_visitor("visitable");
const std::string stereotype_fluent("fluent");
const std::string stereotype_immutable("immutable");
const std::string stereotype_orm_object("orm object");
const std::string stereotype_orm_value("orm value");
const std::string stereotype_exception("exception");
const std::string stereotype_enumeration("enumeration");
const std::string stereotype_handcrafted("handcrafted");
const std::string stereotype_cpp_helper_formatter("C++ Helper Formatter");
const std::string stereotype_cpp_artefact_formatter("C++ Artefact Formatter");
const std::string stereotype_csharp_helper_formatter("C# Helper Formatter");
const std::string stereotype_csharp_artefact_formatter("C# Artefact Formatter");

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
const std::string invalid_primitive_properties(
    "Primitive cannot have a stereotype of 'orm_object': ");
const std::string invalid_stereotypes("Stereotypes are not valid: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

bool stereotypes_transform::
is_stereotype_handled_externally(const std::string& s) {
    return
        s == stereotype_exception ||
        s == stereotype_enumeration ||
        s == stereotype_handcrafted ||
        s == stereotype_cpp_helper_formatter ||
        s == stereotype_cpp_artefact_formatter ||
        s == stereotype_csharp_helper_formatter ||
        s == stereotype_csharp_artefact_formatter;
}

std::unordered_map<location, std::list<name> > stereotypes_transform::
bucket_leaves_by_location(const std::list<name>& leaves) {
    std::unordered_map<location, std::list<name> >  r;
    for (const auto& l : leaves)
        r[l.location()].push_back(l);

    return r;
}

visitor stereotypes_transform::create_visitor(const object& o, const location& l,
    const origin_types ot, const std::list<name>& leaves) {
    name_builder b;
    b.simple_name(o.name().simple() + "_" + visitor_name);
    b.location(l);

    const auto n(b.build());
    BOOST_LOG_SEV(lg, debug) << "Creating visitor: " << n.id();

    visitor r;
    r.name(n);
    r.origin_type(ot);
    r.documentation(visitor_doc + o.name().simple());

    if (leaves.empty()) {
        BOOST_LOG_SEV(lg, error) << no_visitees << n.id();
        BOOST_THROW_EXCEPTION(transformation_error(no_visitees + n.id()));
    }

    for (const auto& l : leaves)
        r.visits().push_back(l);

    BOOST_LOG_SEV(lg, debug) << "Created visitor: " << n.id();
    return r;
}

void stereotypes_transform::
update_visited_leaves(const std::list<name>& leaves, const visitor_details& vd,
    intermediate_model& m) {
    BOOST_LOG_SEV(lg, debug) << "Updating leaves for: " << vd.base.id();

    for (const auto& l : leaves) {
        auto i(m.objects().find(l.id()));
        if (i == m.objects().end()) {
            BOOST_LOG_SEV(lg, error) << leaf_not_found << l.id();
            BOOST_THROW_EXCEPTION(transformation_error(leaf_not_found + l.id()));
        }

        auto& o(i->second);
        o.is_visitation_leaf(true);
        o.base_visitor(vd.base);
        o.derived_visitor(vd.derived);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished updating leaves.";
}

void stereotypes_transform::
add_visitor_to_model(const visitor& v, intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Adding visitor: " << v.name().id();

    const auto pair(std::make_pair(v.name().id(), v));
    const auto i(im.visitors().insert(pair));
    if (!i.second) {
        const auto id(v.name().id());
        BOOST_LOG_SEV(lg, error) << duplicate_name << id;
        BOOST_THROW_EXCEPTION(transformation_error(duplicate_name + id));
    }
    BOOST_LOG_SEV(lg, debug) << "Added visitor: " << v.name().id();
}

void stereotypes_transform::
expand_visitable(object& o, intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Expanding visitable for: " << o.name().id();

    /*
     * The visitable stereotype can only be applied to the root of
     * an inheritance tree - it's an error otherwise.
     */
    const auto id(o.name().id());
    if (o.is_child()) {
        BOOST_LOG_SEV(lg, error) << visitable_child << id;
        BOOST_THROW_EXCEPTION(transformation_error(visitable_child + id));
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
        BOOST_THROW_EXCEPTION(transformation_error(zero_leaves + id));
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
        BOOST_THROW_EXCEPTION(transformation_error(leaves_not_found + id));
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
     * Preserve the origin type from the root object and generate the
     * visitor base.
     */
    const auto bv(create_visitor(o, loc, o.origin_type(), bvl));
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
         * We are now, possibly, in models other than the model of the
         * root parent. So, if we are generating a visitor for the
         * target model, we must ensure we set the origin type
         * correctly or else it will not come out. Note though that we
         * are setting the origin type to the visitable object, unless
         * the leaf belongs to the target model; whilst not strictly
         * correct, this approximation works in practice because we
         * can only be either a reference model or the target model as
         * proxy models do not contribute visitable types.
         */
        const auto& dv_location(pair.first);
        const auto immm(im.name().location().model_modules());
        const bool in_target_model(immm == dv_location.model_modules());
        const auto ot(in_target_model ? origin_types::target : o.origin_type());

        /*
         * Generate the derived visitor and update its leaves.
         */
        const auto& bl(pair.second);
        auto dv(create_visitor(o, dv_location, ot, bl));
        const auto dvn(dv.name());
        dv.parent(bvn);
        update_visited_leaves(bl, visitor_details(bvn, dvn), im);
        add_visitor_to_model(dv, im);
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting visitor.";
}

bool stereotypes_transform::try_expand_concept(
    const std::string& s, object& o, const intermediate_model& im) {

    resolver rs;
    const auto on(rs.try_resolve_concept_name(o.name(), s, im));
    if (!on)
        return false;

    o.modeled_concepts().push_back(*on);
    return true;
}

void stereotypes_transform::expand(object& o, intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Expanding stereotypes for: " << o.name().id();
    if (o.stereotypes().empty()) {
        BOOST_LOG_SEV(lg, debug) << "No stereotypes found.";
        return;
    }

    BOOST_LOG_SEV(lg, debug) << "Original: " << o.stereotypes();
    std::vector<std::string> unknown_stereotypes;
    std::vector<std::string> external_stereotypes;
    for (const auto s : o.stereotypes()) {
        if (is_stereotype_handled_externally(s)) {
            external_stereotypes.push_back(s);
            continue;
        } else if (s == stereotype_visitor)
            expand_visitable(o, im);
        else if (s == stereotype_fluent)
            o.is_fluent(true);
        else if (s == stereotype_immutable)
            o.is_immutable(true);
        else if (s == stereotype_orm_object) {
            orm_object_properties cfg;
            cfg.generate_mapping(true);
            o.orm_properties(cfg);
        } else if (s == stereotype_orm_value) {
            orm_object_properties cfg;
            cfg.generate_mapping(true);
            cfg.is_value(true);
            o.orm_properties(cfg);
        } else {
            const bool is_concept(try_expand_concept(s, o, im));
            if (!is_concept)
                unknown_stereotypes.push_back(s);
        }
    }

    /*
     * If there are any stereotypes we do not know about, throw an
     * error. This way the user can figure out if its trying to use a
     * concept but it has not been found or if its trying to use an
     * unsupported feature.
     */
    if (!unknown_stereotypes.empty()) {
        const auto s(boost::lexical_cast<std::string>(unknown_stereotypes));
        BOOST_LOG_SEV(lg, error) << invalid_stereotypes << s;
        BOOST_THROW_EXCEPTION(transformation_error(invalid_stereotypes + s));
    }

    o.stereotypes(external_stereotypes);
}

void stereotypes_transform::expand(primitive& p) {
    const auto id(p.name().id());
    BOOST_LOG_SEV(lg, debug) << "Expanding stereotypes for: " << id;
    if (p.stereotypes().empty()) {
        BOOST_LOG_SEV(lg, debug) << "No stereotypes found.";
        return;
    }

    BOOST_LOG_SEV(lg, debug) << "Original: " << p.stereotypes();
    std::vector<std::string> unknown_stereotypes;
    for (const auto s : p.stereotypes()) {
        if (s == stereotype_immutable)
            p.is_immutable(true);
        else if (s == stereotype_orm_value) {
            orm_primitive_properties cfg;
            cfg.generate_mapping(true);
            p.orm_properties(cfg);
        } else if (s == stereotype_orm_object) {
            BOOST_LOG_SEV(lg, error) << invalid_primitive_properties << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(invalid_primitive_properties + id));
        } else
            unknown_stereotypes.push_back(s);
    }

    if (!unknown_stereotypes.empty()) {
        const auto s(boost::lexical_cast<std::string>(unknown_stereotypes));
        BOOST_LOG_SEV(lg, error) << invalid_stereotypes << s;
        BOOST_THROW_EXCEPTION(transformation_error(invalid_stereotypes + s));
    }

    BOOST_LOG_SEV(lg, debug) << "Unknown: " << p.stereotypes();
}

void stereotypes_transform::transform(intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Expanding stereotypes for: " << im.name().id();

    for (auto& pair : im.objects())
        expand(pair.second, im);

    for (auto& pair : im.primitives())
        expand(pair.second);

    BOOST_LOG_SEV(lg, debug) << "Finished expanding stereotypes.";
}

} } }
