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
#include <boost/variant/get.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/pod.hpp"
#include "dogen/sml/types/service.hpp"
#include "dogen/dia/types/composite.hpp"
#include "dogen/dia/types/attribute.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/io/value_object_io.hpp"
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
const std::string identity_attribute_key("IDENTITY_ATTRIBUTE");
const std::string comment_key("COMMENT");
const std::string empty_dia_object_name("Dia object name is empty");
const std::string original_parent_not_found("Pod has no original parent: ");
const std::string parent_not_found("Object has a parent but its not defined: ");
const std::string empty_parent_container(
    "Object has an entry in child to parent container but its empty: ");
const std::string missing_module_for_id("Missing module for dia object ID: ");
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

transformer::transformer(context& c)
    : context_(c),
      identifier_parser_(
          new identifier_parser(c.top_level_module_names(),
              c.model().external_module_path(), c.model().name())),
      comments_parser_(new comments_parser()) {

    BOOST_LOG_SEV(lg, debug) << "Initial context: " << context_;
}

void transformer::
compute_model_dependencies(const sml::nested_qname& nqn) {
    // primitives model is empty
    const auto mn(nqn.type().model_name());
    if (!mn.empty() && mn != context_.model().name()) {
        sml::reference ref;
        ref.model_name(mn);
        context_.model().dependencies().insert(std::make_pair(mn, ref));
        BOOST_LOG_SEV(lg, debug) << "Adding model dependency: "
                                 << mn << ". Current model: "
                                 << context_.model().name();
    }

    for (const auto c : nqn.children())
        compute_model_dependencies(c);
}

void transformer::require_is_transformable(const processed_object& po) const {
    if (!is_transformable(po)) {
        const auto type(boost::lexical_cast<std::string>(po.object_type()));
        BOOST_LOG_SEV(lg, error) << object_has_invalid_type << type;
        BOOST_THROW_EXCEPTION(
            transformation_error(object_has_invalid_type + type));
    }
}

sml::qname transformer::transform_qname(const std::string& n,
    sml::meta_types meta_type, const std::string& pkg_id) const {

    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }

    sml::qname name;
    name.model_name(context_.model().name());
    name.meta_type(meta_type);
    name.external_module_path(context_.model().external_module_path());

    if (!pkg_id.empty()) {
        const auto i(context_.id_to_qname().find(pkg_id));
        if (i == context_.id_to_qname().end()) {
            BOOST_LOG_SEV(lg, error) << missing_qname_for_id << pkg_id;
            BOOST_THROW_EXCEPTION(transformation_error(
                    missing_qname_for_id + pkg_id));
        }

        auto j(context_.model().modules().find(i->second));
        if (j == context_.model().modules().end()) {
            BOOST_LOG_SEV(lg, error) << missing_module_for_qname
                                     << i->second.type_name();

            BOOST_THROW_EXCEPTION(
                transformation_error(missing_module_for_qname +
                    i->second.type_name()));
        }

        auto pp(j->second.name().module_path());
        pp.push_back(j->second.name().type_name());
        name.module_path(pp);
    }

    name.type_name(n);
    if (name.type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }
    return name;
}

sml::nested_qname
transformer::transform_nested_qname(const std::string& n) const {
    sml::nested_qname r(identifier_parser_->parse_qname(n));
    if (r.type().type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_type_string << n;
        BOOST_THROW_EXCEPTION(transformation_error(invalid_type_string + n));
    }
    return r;
}

sml::property transformer::
transform_property(const processed_property& p) const {
    sml::property r;
    typedef boost::shared_ptr<dia::attribute> attribute_ptr;

    r.name(p.name());
    const auto pair(comments_parser_->parse(p.comment()));
    r.documentation(pair.first);
    r.implementation_specific_parameters(pair.second);

    for (const auto pair : r.implementation_specific_parameters()) {
        if (pair.first != identity_attribute_key)
            continue;

        r.is_identity_attribute(true);
        break;
    }

    if (r.name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }
    return r;
}

sml::enumerator transformer::transform_enumerator(const processed_property& p,
    const unsigned int position) const {
    sml::enumerator r;
    typedef boost::shared_ptr<dia::attribute> attribute_ptr;

    r.name(p.name());
    const auto pair(comments_parser_->parse(p.comment()));
    r.value(boost::lexical_cast<std::string>(position));
    r.documentation(pair.first);

    if (r.name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }
    return r;
}

void transformer::
transform_pod(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is a pod: " << o.id();

    sml::pod pod;
    pod.category_type(sml::category_types::user_defined);

    const std::string pkg_id(o.child_node_id());
    using sml::meta_types;
    pod.name(transform_qname(o.name(), meta_types::pod, pkg_id));

    using sml::pod_types;
    pod.pod_type(pod_types::value);
    if (p.is_entity())
        pod.pod_type(pod_types::entity);
    else if (p.is_service()) // FIXME: service HACK
        pod.pod_type(pod_types::service);

    pod.is_fluent(p.is_fluent());
    pod.is_versioned(p.is_versioned());
    pod.is_visitable(p.is_visitable());
    pod.is_keyed(p.is_keyed());

    for (const auto us : p.unknown_stereotypes()) {
        const auto c(transform_qname(us, meta_types::concept, empty));
        pod.modeled_concepts().push_back(c);
    }

    using sml::generation_types;
    pod.generation_type(context_.is_target() ?
        generation_types::full_generation :
        generation_types::no_generation);

    // FIXME: service hack
    // if (context_.is_target() && p.is_non_generatable())
    if (context_.is_target() && (p.is_non_generatable() || p.is_service()))
        pod.generation_type(generation_types::partial_generation);

    const auto pair(comments_parser_->parse(o.comment()));
    pod.documentation(pair.first);
    pod.implementation_specific_parameters(pair.second);

    for (const auto& p : o.properties()) {
        auto property(transform_property(p));
        property.type_name(transform_nested_qname(p.type()));
        compute_model_dependencies(property.type_name());
        pod.properties().push_back(property);
    }

    if (pod.name().type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name + o.id();
        BOOST_THROW_EXCEPTION(
            transformation_error(empty_dia_object_name + o.id()));
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
                                 << pod.name().type_name() << " as "
                                 << j->second.type_name();
        pod.parent_name(j->second);
    } else {
        BOOST_LOG_SEV(lg, debug) << "Pod has no parent: "
                                 << pod.name().type_name();
    }

    const auto j(context_.parent_ids().find(o.id()));
    pod.is_parent(j != context_.parent_ids().end());
    context_.id_to_qname().insert(std::make_pair(o.id(), pod.name()));

    if (!pod.parent_name()) {
        context_.original_parent().insert(
            std::make_pair(pod.name(), pod.name()));
    } else {
        const auto k(context_.original_parent().find(*pod.parent_name()));
        if (k == context_.original_parent().end()) {
            BOOST_LOG_SEV(lg, error) << "Could not find the original parent of "
                                     << pod.name().type_name();

            BOOST_THROW_EXCEPTION(
                transformation_error(original_parent_not_found +
                    pod.name().type_name()));
        }
        pod.original_parent_name(k->second);
        context_.original_parent().insert(
            std::make_pair(pod.name(), k->second));
    }

    if (!pod.is_parent() && pod.parent_name() &&
        pod.generation_type() == generation_types::full_generation) {
        auto parent(pod.parent_name());
        while (parent) {
            auto k(context_.leaves().find(*parent));
            if (k == context_.leaves().end()) {
                const std::list<sml::qname> l { pod.name() };
                context_.leaves().insert(std::make_pair(*parent, l));
            } else
                k->second.push_back(pod.name());

            auto j(context_.model().pods().find(*parent));
            if (j == context_.model().pods().end()) {
                BOOST_LOG_SEV(lg, error) << "Could not find the parent of "
                                         << parent->type_name();
                BOOST_THROW_EXCEPTION(transformation_error(parent_not_found +
                        parent->type_name()));
            }
            parent = j->second.parent_name();
        }
    }

    pod.is_immutable(p.is_immutable());
    if ((pod.is_parent() || pod.parent_name()) && p.is_immutable())  {
        BOOST_LOG_SEV(lg, error) << immutabilty_with_inheritance
                                 << pod.name().type_name();

        BOOST_THROW_EXCEPTION(
            transformation_error(immutabilty_with_inheritance +
                pod.name().type_name()));
    }

    context_.model().pods().insert(std::make_pair(pod.name(), pod));
}

void transformer::transform_enumeration(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Object is an enumeration: " << o.id();
    sml::enumeration e;

    e.generation_type(context_.is_target() ?
        sml::generation_types::full_generation :
        sml::generation_types::no_generation);

    const std::string pkg_id(o.child_node_id());
    using sml::meta_types;
    e.name(transform_qname(o.name(), meta_types::enumeration, pkg_id));
    e.documentation(o.comment());

    dogen::sml::qname qn;
    qn.type_name(unsigned_int);
    qn.meta_type(dogen::sml::meta_types::primitive);
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
        auto enumerator(transform_enumerator(p, pos++));

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

void transformer::transform_module(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Object is a module: " << o.id();

    sml::module p;
    const std::string pkg_id(o.child_node_id());
    using sml::meta_types;
    p.name(transform_qname(o.name(), meta_types::module, pkg_id));
    p.documentation(o.comment());

    if (p.name().type_name().empty()) {
        BOOST_THROW_EXCEPTION(
            transformation_error(empty_dia_object_name + o.id()));
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name + o.id();
    }

    context_.id_to_qname().insert(std::make_pair(o.id(), p.name()));
    context_.model().modules().insert(std::make_pair(p.name(), p));
}

void transformer::transform_note(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Object is a note: " << o.id()
                             << ". Note text: '" << o.text() << "'";

    if (o.text().empty())
        return;

    const auto pair(comments_parser_->parse(o.text()));
    bool has_marker(false);
    for (const auto& p : pair.second) {
        has_marker = p.first == comment_key;
        if (has_marker)
            break;
    }

    if (!has_marker)
        return;

    if (o.child_node_id().empty()) {
        context_.model().documentation(pair.first);
        context_.model().implementation_specific_parameters(pair.second);
        return;
    }

    const auto i(context_.id_to_qname().find(o.child_node_id()));
    if (i == context_.id_to_qname().end()) {
        BOOST_LOG_SEV(lg, error) << missing_module_for_id << o.child_node_id();
        BOOST_THROW_EXCEPTION(
            transformation_error(missing_module_for_id + o.child_node_id()));
    }

    auto j(context_.model().modules().find(i->second));
    if (j == context_.model().modules().end()) {
        BOOST_LOG_SEV(lg, error) << missing_module_for_qname
                                 << i->second.type_name();

        BOOST_THROW_EXCEPTION(
            transformation_error(missing_module_for_qname +
                i->second.type_name()));
    }
    j->second.documentation(pair.first);
    j->second.implementation_specific_parameters(pair.second);
}

void transformer::transform_exception(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Object is an exception: " << o.id();

    sml::value_object e;
    e.type(sml::value_types::exception);
    e.generation_type(context_.is_target() ?
        sml::generation_types::full_generation :
        sml::generation_types::no_generation);

    const std::string pkg_id(o.child_node_id());
    using sml::meta_types;
    e.name(transform_qname(o.name(), meta_types::exception, pkg_id));
    e.documentation(o.comment());
    context_.model().exceptions().insert(std::make_pair(e.name(), e));
    BOOST_LOG_SEV(lg, debug) << "Created exception: " << e;
}

void transformer::transform_concept(const processed_object& o) {
    sml::concept c;
    const std::string pkg_id(o.child_node_id());
    using sml::meta_types;
    c.name(transform_qname(o.name(), meta_types::concept, pkg_id));
    context_.id_to_qname().insert(std::make_pair(o.id(), c.name()));

    c.generation_type(context_.is_target() ?
        sml::generation_types::full_generation :
        sml::generation_types::no_generation);

    for (const auto& prop : o.properties()) {
        auto property(transform_property(prop));
        property.type_name(transform_nested_qname(prop.type()));
        compute_model_dependencies(property.type_name());
        c.properties().push_back(property);
    }

    const auto i(context_.child_id_to_parent_ids().find(o.id()));
    if (i != context_.child_id_to_parent_ids().end()) {
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

void transformer::
transform(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Starting to transform: " << o.id();
    BOOST_LOG_SEV(lg, debug) << "Object contents: " << o;

    require_is_transformable(o);

    if (p.is_uml_large_package())
        transform_module(o);
    else if (p.is_uml_note())
        transform_note(o);
    else if (p.is_enumeration())
        transform_enumeration(o);
    else if (p.is_exception())
        transform_exception(o);
    else if (p.is_concept())
        transform_concept(o);
    else
        transform_pod(o, p);

    BOOST_LOG_SEV(lg, debug) << "Transformed: " << o.id();
}

} }
