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
#include <set>
#include <boost/make_shared.hpp>
#include <boost/variant/get.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/dia/types/composite.hpp"
#include "dogen/yarn.dia/types/transformation_error.hpp"
#include "dogen/yarn.dia/io/object_types_io.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/io/processed_object_io.hpp"
#include "dogen/yarn.dia/io/repository_io.hpp"
#include "dogen/yarn.dia/types/validator.hpp"
#include "dogen/yarn.dia/types/transformer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.transformer"));

const std::string empty;
const std::string empty_dia_object_name("Dia object name is empty");
const std::string empty_package_id("Supplied package id is empty");
const std::string parent_not_found("Object has a parent but its not defined: ");
const std::string empty_parent_container(
    "Object has an entry in child to parent container but its empty: ");
const std::string missing_module_for_name("Missing module for name: ");
const std::string missing_name_for_id("Missing name for dia object ID: ");
const std::string type_attribute_expected(
    "Could not find type attribute. ID: ");
const std::string invalid_type_string(
    "String provided with type did not parse into Yarn names: ");
const std::string object_has_invalid_type("Invalid dia type: ");
const std::string invalid_stereotype_in_graph("Invalid stereotype: ");
const std::string immutabilty_with_inheritance(
    "Immutability not supported with inheritance: ");
const std::string multiple_inheritance(
    "Child has more than one parent, but multiple inheritance not supported:");

}

namespace dogen {
namespace yarn {
namespace dia {

transformer::transformer(const dynamic::workflow& w, const repository& rp)
    : repository_(rp), dynamic_workflow_(w) {

    BOOST_LOG_SEV(lg, debug) << "Initial repository: " << repository_;
}

yarn::generation_types transformer::generation_type(const profile& p) const {
    using yarn::generation_types;
    if (repository_.model().origin_type() != yarn::origin_types::target)
        return generation_types::no_generation;

    if (p.is_non_generatable() || p.is_service())
        return generation_types::partial_generation;

    return generation_types::full_generation;
}

yarn::name transformer::to_name(const std::string& n) const {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }

    yarn::name_factory f;
    return f.build_element_in_model(repository_.model().name(), n);
}

yarn::name transformer::to_name(const std::string& n,
    const yarn::name& module_n) const {

    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }

    yarn::name_factory f;
    return f.build_element_in_module(module_n, n);
}

const yarn::module& transformer::module_for_name(const yarn::name& n) const {
    auto i(repository_.model().modules().find(n.id()));
    if (i == repository_.model().modules().end()) {
        const auto sn(n.simple());
        BOOST_LOG_SEV(lg, error) << missing_module_for_name << sn;
        BOOST_THROW_EXCEPTION(
            transformation_error(missing_module_for_name + sn));
    }
    return i->second;
}

const yarn::module& transformer::module_for_id(const std::string& id) const {
    if (id.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_package_id;
        BOOST_THROW_EXCEPTION(transformation_error(empty_package_id));
    }

    const auto i(repository_.id_to_name().find(id));
    if (i == repository_.id_to_name().end()) {
        BOOST_LOG_SEV(lg, error) << missing_name_for_id << id;
        BOOST_THROW_EXCEPTION(transformation_error(missing_name_for_id + id));
    }

    return module_for_name(i->second);
}

yarn::attribute transformer::to_attribute(const yarn::name& owning_element,
    const processed_attribute& a) const {
    if (a.name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }

    yarn::name_factory f;
    const auto n(f.build_attribute_name(owning_element, a.name()));

    yarn::attribute r;
    r.name(n);
    r.unparsed_type(a.type());
    r.documentation(a.comment().documentation());

    const auto& kvps(a.comment().key_value_pairs());
    const auto scope(dynamic::scope_types::property);
    r.extensions(dynamic_workflow_.execute(scope, kvps));

    return r;
}

yarn::enumerator transformer::to_enumerator(const processed_attribute& a,
    const unsigned int position) const {
    yarn::enumerator r;
    r.name(a.name());
    r.value(boost::lexical_cast<std::string>(position));
    r.documentation(a.comment().documentation());

    if (r.name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }
    return r;
}

void transformer::update_element(const processed_object& o, const profile& p,
    yarn::element& e) {

    e.generation_type(generation_type(p));
    e.origin_type(origin_types::not_yet_determined);

    const auto package_id(o.child_node_id());
    bool is_in_package(!package_id.empty());
    if (is_in_package) {
        /*
         * Create the element name taking into account the
         * packages the element is contained in.
         */
        const auto& module(module_for_id(package_id));
        e.name(to_name(o.name(), module.name()));
    } else {
        /*
         * Type is a top-level type - e.g. belongs to the
         * synthetic module for the model; do not add this
         * dependency to the name.
         */
        e.name(to_name(o.name()));
    }

    e.documentation(o.comment().documentation());

    const auto& kvps(o.comment().key_value_pairs());
    const auto scope(dynamic::scope_types::entity);
    e.extensions(dynamic_workflow_.execute(scope, kvps));
}

yarn::object
transformer::to_object(const processed_object& po, const profile& p,
    const yarn::object_types ot) {
    yarn::object o;
    update_element(po, p, o);

    o.is_fluent(p.is_fluent());
    if (p.is_visitable())
        o.stereotypes().insert(yarn::stereotypes::visitable);

    for (const auto us : p.unknown_stereotypes()) {
        // FIXME: hack to handle new stereotypes
        if (us == "formatter")
            o.stereotypes().insert(yarn::stereotypes::formatter);
        else if (us == "handcrafted")
            o.stereotypes().insert(yarn::stereotypes::handcrafted);
        else {
            const auto n(to_name(us));
            o.modeled_concepts().push_back(n);
        }
    }

    for (const auto& p : po.attributes())
        o.local_attributes().push_back(to_attribute(o.name(), p));

    const auto i(repository_.child_id_to_parent_ids().find(po.id()));
    if (i != repository_.child_id_to_parent_ids().end()) {
        if (i->second.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_parent_container << po.id();
            BOOST_THROW_EXCEPTION(
                transformation_error(empty_parent_container + po.id()));
        }

        if (i->second.size() > 1) {
            BOOST_LOG_SEV(lg, error) << multiple_inheritance << po.id();
            BOOST_THROW_EXCEPTION(
                transformation_error(multiple_inheritance + po.id()));
        }

        const auto parent_name(i->second.front());
        const auto j(repository_.id_to_name().find(parent_name));
        if (j == repository_.id_to_name().end()) {
            BOOST_LOG_SEV(lg, error) << "Object has a parent but "
                                     << " there is no Name mapping defined."
                                     << " Child ID: '" << po.id()
                                     << "' Parent ID: '" << parent_name << "'";

            BOOST_THROW_EXCEPTION(
                transformation_error(parent_not_found + po.id()));
        }

        BOOST_LOG_SEV(lg, debug) << "Setting parent for: "
                                 << o.name().id() << " as "
                                 << j->second.id();
        o.parent(j->second);
    } else {
        BOOST_LOG_SEV(lg, debug) << "Object has no parent: "
                                 << o.name().id();
    }

    o.is_immutable(p.is_immutable());
    o.object_type(ot);
    return o;
}

yarn::exception
transformer::to_exception(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is an exception: " << o.id();

    yarn::exception e;
    update_element(o, p, e);
    return e;
}

yarn::enumeration
transformer::to_enumeration(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is an enumeration: " << o.id();
    yarn::enumeration e;
    update_element(o, p, e);

    dogen::yarn::enumerator invalid;
    invalid.name("invalid");
    invalid.documentation("Represents an uninitialised enum");
    invalid.value("0");
    e.enumerators().push_back(invalid);

    std::set<std::string> enumerator_names;
    enumerator_names.insert(invalid.name());

    unsigned int pos(1);
    for (const auto& p : o.attributes()) {
        auto enumerator(to_enumerator(p, pos++));

        const auto i(enumerator_names.find(enumerator.name()));
        if (i != enumerator_names.end()) {
            BOOST_LOG_SEV(lg, error) << "Duplicate enumerator name: "
                                     << enumerator.name();
            BOOST_THROW_EXCEPTION(transformation_error(
                    "Duplicate enumerator name: " + enumerator.name()));
        }
        e.enumerators().push_back(enumerator);
        enumerator_names.insert(enumerator.name());
    }
    return e;
}

yarn::module
transformer::to_module(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is a module: " << o.id();

    yarn::module m;
    update_element(o, p, m);
    return m;
}

yarn::concept
transformer::to_concept(const processed_object& o, const profile& p) {
    yarn::concept c;
    update_element(o, p, c);

    for (const auto& prop : o.attributes())
        c.local_attributes().push_back(to_attribute(c.name(), prop));

    const auto i(repository_.child_id_to_parent_ids().find(o.id()));
    c.is_child(i != repository_.child_id_to_parent_ids().end());
    if (c.is_child()) {
        if (i->second.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_parent_container << o.id();
            BOOST_THROW_EXCEPTION(
                transformation_error(empty_parent_container + o.id()));
        }

        for (const auto& concept_id : i->second) {
            const auto j(repository_.id_to_name().find(concept_id));
            if (j == repository_.id_to_name().end()) {
                BOOST_LOG_SEV(lg, error) << "Object has a parent but "
                                         << " there is no name mapping."
                                         << " Child ID: '" << o.id()
                                         << "' Parent ID: '" << concept_id
                                         << "'";

                BOOST_THROW_EXCEPTION(
                    transformation_error(parent_not_found + o.id()));
            }
            c.refines().push_back(j->second);
        }
    }

    return c;
}

} } }
