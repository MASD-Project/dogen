/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/dia/types/composite.hpp"
#include "dogen/dia/types/attribute.hpp"
#include "dogen/dia_to_sml/types/traits.hpp"
#include "dogen/dia_to_sml/types/transformation_error.hpp"
#include "dogen/dia_to_sml/io/object_types_io.hpp"
#include "dogen/dia_to_sml/types/processed_object.hpp"
#include "dogen/dia_to_sml/io/processed_object_io.hpp"
#include "dogen/dia_to_sml/io/context_io.hpp"
#include "dogen/dia_to_sml/types/validator.hpp"
#include "dogen/dia_to_sml/types/transformer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.transformer"));

const std::string empty;
const std::string unsigned_int("unsigned int");
const std::string empty_dia_object_name("Dia object name is empty");
const std::string empty_package_id("Supplied package id is empty");
const std::string original_parent_not_found("Object has no original parent: ");
const std::string parent_not_found("Object has a parent but its not defined: ");
const std::string empty_parent_container(
    "Object has an entry in child to parent container but its empty: ");
const std::string missing_module_for_qname("Missing module for qname: ");
const std::string missing_qname_for_id("Missing QName for dia object ID: ");
const std::string type_attribute_expected(
    "Could not find type attribute. ID: ");
const std::string invalid_type_string(
    "String provided with type did not parse into SML qnames: ");
const std::string object_has_invalid_type("Invalid dia type: ");
const std::string invalid_stereotype_in_graph("Invalid stereotype: ");
const std::string immutabilty_with_inheritance(
    "Immutability not supported with inheritance: ");
const std::string multiple_inheritance(
    "Child has more than one parent, but multiple inheritance not supported:");

}

namespace dogen {
namespace dia_to_sml {

transformer::transformer(const dynamic::schema::workflow& w, context& c)
    : context_(c),
      identifier_parser_(new sml::identifier_parser(c.top_level_module_names(),
              c.model().name().external_module_path(),
              c.model().name().model_name())),
      schema_workflow_(w) {

    BOOST_LOG_SEV(lg, debug) << "Initial context: " << context_;
}

void transformer::
update_model_references(const sml::nested_qname& nqn) {
    const auto mn(nqn.type().model_name());
    const bool is_primitives_model(mn.empty());
    const bool is_current_model(mn != context_.model().name().model_name());

    if (!is_primitives_model && is_current_model) {
        sml::qname qn;
        qn.model_name(mn);
        const auto p(std::make_pair(qn, sml::origin_types::unknown));
        context_.model().references().insert(p);

        BOOST_LOG_SEV(lg, debug) << "Adding model dependency: "
                                 << mn << ". Current model: "
                                 << context_.model().name().model_name();
    }

    for (const auto c : nqn.children())
        update_model_references(c);
}

void transformer::require_is_transformable(const processed_object& po) const {
    if (!is_transformable(po)) {
        const auto type(boost::lexical_cast<std::string>(po.object_type()));
        BOOST_LOG_SEV(lg, error) << object_has_invalid_type << type;
        BOOST_THROW_EXCEPTION(
            transformation_error(object_has_invalid_type + type));
    }
}

sml::generation_types transformer::generation_type(const profile& p) const {
    using sml::generation_types;
    if (!context_.model().is_target())
        return generation_types::no_generation;

    if (p.is_non_generatable() || p.is_service() || p.is_factory() ||
        p.is_repository())
        return generation_types::partial_generation;

    return generation_types::full_generation;
}

sml::qname transformer::to_qname(const std::string& n) const {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }

    sml::qname r;
    r.model_name(context_.model().name().model_name());
    r.external_module_path(context_.model().name().external_module_path());
    r.simple_name(n);

    return r;
}

sml::qname transformer::to_qname(const std::string& n,
    const sml::qname& module_qn) const {
    auto r(to_qname(n));
    auto pp(module_qn.module_path());
    pp.push_back(module_qn.simple_name());
    r.module_path(pp);
    return r;
}

sml::module& transformer::module_for_qname(const sml::qname& qn) {
    auto i(context_.model().modules().find(qn));
    if (i == context_.model().modules().end()) {
        const auto sn(qn.simple_name());
        BOOST_LOG_SEV(lg, error) << missing_module_for_qname << sn;
        BOOST_THROW_EXCEPTION(
            transformation_error(missing_module_for_qname + sn));
    }
    return i->second;
}

sml::module& transformer::module_for_id(const std::string& id) {
    if (id.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_package_id;
        BOOST_THROW_EXCEPTION(transformation_error(empty_package_id));
    }

    const auto i(context_.id_to_qname().find(id));
    if (i == context_.id_to_qname().end()) {
        BOOST_LOG_SEV(lg, error) << missing_qname_for_id << id;
        BOOST_THROW_EXCEPTION(transformation_error(missing_qname_for_id + id));
    }

    return module_for_qname(i->second);
}

sml::nested_qname transformer::to_nested_qname(const std::string& n) const {
    sml::nested_qname r(identifier_parser_->parse_qname(n));
    if (r.type().simple_name().empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_type_string << n;
        BOOST_THROW_EXCEPTION(transformation_error(invalid_type_string + n));
    }
    return r;
}

sml::property transformer::to_property(const processed_property& p) const {
    if (p.name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }

    sml::property r;
    r.name(p.name());
    r.type(to_nested_qname(p.type()));

    r.documentation(p.comment().documentation());

    const auto& kvps(p.comment().key_value_pairs());
    const auto scope(dynamic::schema::scope_types::property);
    r.extensions(schema_workflow_.execute(scope, kvps));

    return r;
}

sml::enumerator transformer::to_enumerator(const processed_property& p,
    const unsigned int position) const {
    sml::enumerator r;
    r.name(p.name());
    r.value(boost::lexical_cast<std::string>(position));
    r.documentation(p.comment().documentation());

    if (r.name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }
    return r;
}

void transformer::add_leaf(const sml::qname& leaf, const sml::object& ao) {
    using sml::generation_types;

    if (!ao.is_child())
        return;

    using sml::relationship_types;
    const auto i(ao.relationships().find(relationship_types::parents));
    if (i == ao.relationships().end() || i->second.empty()) {
        BOOST_LOG_SEV(lg, error) << "Object is child but has no parents "
                                 << ao.name().simple_name();

        BOOST_THROW_EXCEPTION(transformation_error(parent_not_found +
                ao.name().simple_name()));
    }

    for (const auto& parent : i->second) {
        auto k(context_.model().objects().find(parent));
        if (k == context_.model().objects().end()) {
            BOOST_LOG_SEV(lg, error) << "Could not find the parent of "
                                     << parent.simple_name();
            BOOST_THROW_EXCEPTION(transformation_error(parent_not_found +
                    parent.simple_name()));
        }
        add_leaf(leaf, k->second);
        context_.leaves()[parent].push_back(leaf);
    }
}

void transformer::
update_object(sml::object& ao, const processed_object& o, const profile& p) {

    update_element(ao, o, p);

    ao.is_fluent(p.is_fluent());
    ao.is_versioned(p.is_versioned());
    ao.is_visitable(p.is_visitable());

    for (const auto us : p.unknown_stereotypes()) {
        const auto qn(to_qname(us));
        using sml::relationship_types;
        ao.relationships()[relationship_types::modeled_concepts].push_back(qn);
    }

    for (const auto& p : o.properties()) {
        const auto property(to_property(p));
        ao.local_properties().push_back(property);
        update_model_references(property.type());
    }

    const auto i(context_.child_id_to_parent_ids().find(o.id()));
    if (i != context_.child_id_to_parent_ids().end()) {
        if (i->second.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_parent_container << o.id();
            BOOST_THROW_EXCEPTION(
                transformation_error(empty_parent_container + o.id()));
        }

        if (i->second.size() > 1) {
            BOOST_LOG_SEV(lg, error) << multiple_inheritance << o.id();
            BOOST_THROW_EXCEPTION(
                transformation_error(multiple_inheritance + o.id()));
        }

        const auto parent_name(i->second.front());
        const auto j(context_.id_to_qname().find(parent_name));
        if (j == context_.id_to_qname().end()) {
            BOOST_LOG_SEV(lg, error) << "Object has a parent but "
                                     << " there is no QName mapping defined."
                                     << " Child ID: '" << o.id()
                                     << "' Parent ID: '" << parent_name << "'";

            BOOST_THROW_EXCEPTION(
                transformation_error(parent_not_found + o.id()));
        }

        BOOST_LOG_SEV(lg, debug) << "Setting parent for: "
                                 << ao.name().simple_name() << " as "
                                 << j->second.simple_name();
        ao.is_child(true);
        using sml::relationship_types;
        ao.relationships()[relationship_types::parents].push_back(j->second);
    } else {
        BOOST_LOG_SEV(lg, debug) << "Object has no parent: "
                                 << ao.name().simple_name();
    }

    const auto j(context_.parent_ids().find(o.id()));
    ao.is_parent(j != context_.parent_ids().end());
    ao.is_final(!ao.is_parent());
    context_.id_to_qname().insert(std::make_pair(o.id(), ao.name()));

    if (!ao.is_child()) {
        ao.is_inheritance_root(ao.is_parent());
        context_.original_parent().insert(
            std::make_pair(ao.name(), ao.name()));
    } else {
        using sml::relationship_types;
        const auto k(ao.relationships().find(relationship_types::parents));
        if (k == ao.relationships().end() && k->second.empty()) {
            BOOST_LOG_SEV(lg, error) << "Object is child but has no parents "
                                     << ao.name().simple_name();

            BOOST_THROW_EXCEPTION(
                transformation_error(parent_not_found +
                    ao.name().simple_name()));
        }

        for (const auto& parent_name : k->second) {
            const auto j(context_.original_parent().find(parent_name));
            if (j == context_.original_parent().end()) {
                BOOST_LOG_SEV(lg, error)
                    << "Could not find the original parent of "
                    << ao.name().simple_name();

                BOOST_THROW_EXCEPTION(
                    transformation_error(original_parent_not_found +
                        ao.name().simple_name()));
            }
            context_.original_parent().insert(
                std::make_pair(ao.name(), j->second));
            using sml::relationship_types;
            ao.relationships()[relationship_types::original_parents].push_back(
                j->second);
        }
    }

    // FIXME: massive hack. must not add leafs for services.
    const bool is_service(ao.object_type() ==
        sml::object_types::user_defined_service);
    if (!ao.is_parent() && ao.is_child() && !is_service)
        add_leaf(ao.name(), ao);

    ao.is_immutable(p.is_immutable());
    if ((ao.is_parent() || ao.is_child()) && p.is_immutable())  {
        BOOST_LOG_SEV(lg, error) << immutabilty_with_inheritance
                                 << ao.name().simple_name();

        BOOST_THROW_EXCEPTION(
            transformation_error(immutabilty_with_inheritance +
                ao.name().simple_name()));
    }
}

void transformer::to_entity(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is an entity: " << o.id();

    sml::object e;
    update_object(e, o, p);
    e.is_aggregate_root(p.is_aggregate_root());

    for (const auto& p : e.local_properties()) {
        const dynamic::schema::field_selector fs(p.extensions());
        if (fs.has_field(traits::identity_attribute()))
            e.identity().push_back(p);
    }

    if (p.is_entity())
        e.object_type(sml::object_types::entity);
    else if (p.is_keyed_entity())
        e.object_type(sml::object_types::keyed_entity);
    context_.model().objects().insert(std::make_pair(e.name(), e));
}

void transformer::to_exception(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is an exception: " << o.id();

    sml::object vo;
    update_object(vo, o, p);
    vo.object_type(sml::object_types::exception);
    context_.model().objects().insert(std::make_pair(vo.name(), vo));
}

void transformer::to_object(const processed_object& po, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is a factory: " << po.id();

    sml::object o;
    if (p.is_factory())
        o.object_type(sml::object_types::factory);
    else if (p.is_repository())
        o.object_type(sml::object_types::repository);
    else if (p.is_service())
        o.object_type(sml::object_types::user_defined_service);

    update_object(o, po, p);
    context_.model().objects().insert(std::make_pair(o.name(), o));
}

void transformer::to_value_object(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is a value object: " << o.id();

    sml::object vo;
    update_object(vo, o, p);
    vo.object_type(sml::object_types::user_defined_value_object);
    context_.model().objects().insert(std::make_pair(vo.name(), vo));
}

void transformer::to_enumeration(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is an enumeration: " << o.id();
    sml::enumeration e;
    update_element(e, o, p);

    dogen::sml::qname qn;
    qn.simple_name(unsigned_int);
    e.underlying_type(qn);

    dogen::sml::enumerator invalid;
    invalid.name("invalid");
    invalid.documentation("Represents an uninitialised enum");
    invalid.value("0");
    e.enumerators().push_back(invalid);

    std::set<std::string> enumerator_names;
    enumerator_names.insert(invalid.name());

    unsigned int pos(1);
    for (const auto& p : o.properties()) {
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
    context_.model().enumerations().insert(std::make_pair(e.name(), e));
}

void transformer::to_module(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is a module: " << o.id();

    sml::module m;
    m.type(sml::module_types::regular);
    update_element(m, o, p);
    context_.model().modules().insert(std::make_pair(m.name(), m));
}

void transformer::from_note(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Object is a note: " << o.id()
                             << ". Note text: '"
                             << o.comment().original_content() << "'";

    if (o.comment().original_content().empty() ||
        !o.comment().applicable_to_parent_object())
        return;

    const auto& documentation(o.comment().documentation());
    const auto& kvps(o.comment().key_value_pairs());
    const sml::model& model(context_.model());
    using dynamic::schema::scope_types;
    if (o.child_node_id().empty()) {
        auto& module(module_for_qname(model.name()));
        module.documentation(documentation);

        const auto scope(scope_types::root_module);
        module.extensions(schema_workflow_.execute(scope, kvps));
        return;
    }

    sml::module& module(module_for_id(o.child_node_id()));
    module.documentation(documentation);

    const auto scope(scope_types::any_module);
    module.extensions(schema_workflow_.execute(scope, kvps));
}

void transformer::to_concept(const processed_object& o, const profile& p) {
    sml::concept c;
    update_element(c, o, p);

    for (const auto& prop : o.properties()) {
        auto property(to_property(prop));
        property.type(to_nested_qname(prop.type()));
        update_model_references(property.type());
        c.local_properties().push_back(property);
    }

    const auto i(context_.child_id_to_parent_ids().find(o.id()));
    c.is_child(i != context_.child_id_to_parent_ids().end());
    if (c.is_child()) {
        if (i->second.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_parent_container << o.id();
            BOOST_THROW_EXCEPTION(
                transformation_error(empty_parent_container + o.id()));
        }

        for (const auto& concept_id : i->second) {
            const auto j(context_.id_to_qname().find(concept_id));
            if (j == context_.id_to_qname().end()) {
                BOOST_LOG_SEV(lg, error) << "Object has a parent but "
                                         << " there is no QName mapping."
                                         << " Child ID: '" << o.id()
                                         << "' Parent ID: '" << concept_id
                                         << "'";

                BOOST_THROW_EXCEPTION(
                    transformation_error(parent_not_found + o.id()));
            }
            c.refines().push_back(j->second);
        }
    }

    const auto j(context_.parent_ids().find(o.id()));
    c.is_parent(j != context_.parent_ids().end());

    context_.model().concepts().insert(std::make_pair(c.name(), c));
}

bool transformer::is_transformable(const processed_object& o) const {
    const auto ot(o.object_type());
    return
        ot == object_types::uml_large_package ||
        ot == object_types::uml_generalization ||
        ot == object_types::uml_class ||
        ot == object_types::uml_note;
}

void  transformer::dispatch(const processed_object& o, const profile& p) {
    if (p.is_uml_large_package())
        to_module(o, p);
    else if (p.is_uml_note())
        from_note(o);
    else if (p.is_enumeration())
        to_enumeration(o, p);
    else if (p.is_concept())
        to_concept(o, p);
    else if (p.is_exception())
        to_exception(o, p);
    else if (p.is_entity() || p.is_keyed_entity())
        to_entity(o, p);
    else if (p.is_factory() || p.is_repository() || p.is_service())
        to_object(o, p);
    else
        to_value_object(o, p);
}

void transformer::transform(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Starting to transform: " << o.id();
    BOOST_LOG_SEV(lg, debug) << "Object contents: " << o;

    require_is_transformable(o);
    dispatch(o, p);

    BOOST_LOG_SEV(lg, debug) << "Transformed: " << o.id();
}

} }
