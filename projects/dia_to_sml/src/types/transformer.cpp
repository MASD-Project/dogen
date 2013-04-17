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
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/types/transformation_error.hpp"
#include "dogen/dia_to_sml/io/stereotypes_io.hpp"
#include "dogen/dia_to_sml/io/object_types_io.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/exception.hpp"
#include "dogen/dia_to_sml/types/processed_object.hpp"
#include "dogen/dia_to_sml/types/transformer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.transformer"));

const std::string empty;
const std::string comment_marker("COMMENT");
const std::string empty_dia_object_name("Dia object name is empty");
const std::string original_parent_not_found("Pod has no original parent: ");
const std::string parent_not_found("Object has a parent but its not defined: ");
const std::string missing_package_for_id("Missing package for dia object ID: ");
const std::string missing_package_for_qname("Missing package for qname: ");
const std::string missing_qname_for_id("Missing QName for dia object ID: ");
const std::string type_attribute_expected(
    "Could not find type attribute. ID: ");
const std::string invalid_type_string(
    "String provided with type did not parse into SML qnames: ");
const std::string object_has_invalid_type("Invalid dia type: ");
const std::string invalid_stereotype_in_graph("Invalid stereotype: ");

}

namespace dogen {
namespace dia_to_sml {

transformer::transformer(context& c)
    : context_(c),
      identifier_parser_(
          new identifier_parser(c.top_level_package_names(),
              c.model().external_package_path(), c.model().name())),
      comments_parser_(new comments_parser()) { }

transformer::~transformer() noexcept { }

void transformer::
compute_model_dependencies(const sml::nested_qname& nqn) {
    // primitives model is empty
    const auto mn(nqn.type().model_name());
    if (!mn.empty() && mn != context_.model().name()) {
        sml::reference ref;
        ref.model_name(mn);
        context_.model().dependencies().insert(std::make_pair(mn, ref));
    }

    for (const auto c : nqn.children())
        compute_model_dependencies(c);
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
    name.external_package_path(context_.model().external_package_path());

    if (!pkg_id.empty()) {
        const auto i(context_.dia_id_to_qname().find(pkg_id));
        if (i == context_.dia_id_to_qname().end()) {
            BOOST_LOG_SEV(lg, error) << missing_qname_for_id << pkg_id;
            BOOST_THROW_EXCEPTION(transformation_error(
                    missing_qname_for_id + pkg_id));
        }

        auto j(context_.model().packages().find(i->second));
        if (j == context_.model().packages().end()) {
            BOOST_LOG_SEV(lg, error) << missing_package_for_qname
                                     << i->second.type_name();

            BOOST_THROW_EXCEPTION(
                transformation_error(missing_package_for_qname +
                    i->second.type_name()));
        }

        auto pp(j->second.name().package_path());
        pp.push_back(j->second.name().type_name());
        name.package_path(pp);
    }

    name.type_name(n);
    if (name.type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }
    return name;
}

sml::property transformer::
transform_property(const processed_property& p) {
    sml::property r;
    typedef boost::shared_ptr<dia::attribute> attribute_ptr;

    r.name(p.name());
    auto nested_name(identifier_parser_->parse_qname(p.type()));
    if (nested_name.type().type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_type_string << p.type();
        BOOST_THROW_EXCEPTION(
            transformation_error(invalid_type_string + p.type()));
    }
    r.type_name(nested_name);
    compute_model_dependencies(nested_name);

    const auto pair(comments_parser_->parse(p.comment()));
    r.documentation(pair.first);
    r.implementation_specific_parameters(pair.second);

    if (r.name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }

    if (r.type_name().type().type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << "Could not find a type attribute.";
        BOOST_THROW_EXCEPTION(transformation_error(type_attribute_expected));
    }
    return r;
}

void transformer::transform_pod(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Object is a pod: " << o.id();

    using sml::generation_types;
    sml::pod pod;
    pod.generation_type(context_.is_target() ?
        generation_types::full_generation :
        generation_types::no_generation);

    pod.category_type(sml::category_types::user_defined);

    const std::string pkg_id(o.child_node_id());
    using sml::meta_types;
    pod.name(transform_qname(o.name(), meta_types::pod, pkg_id));

    switch(o.stereotype()) {
        case stereotypes::no_stereotype:
            pod.pod_type(sml::pod_types::value);
            break;
    case stereotypes::entity:
        pod.pod_type(sml::pod_types::entity);
        break;
    case stereotypes::value:
        pod.pod_type(sml::pod_types::value);
        break;
    case stereotypes::nongeneratable:
        pod.pod_type(sml::pod_types::value);
        if (context_.is_target())
            pod.generation_type(generation_types::partial_generation);
        break;
    case stereotypes::service:
        pod.pod_type(sml::pod_types::service);
        if (context_.is_target())
            pod.generation_type(generation_types::partial_generation);
        break;
    default:
        // FIXME
        pod.pod_type(sml::pod_types::value);
        break;
    }

    const auto pair(comments_parser_->parse(o.comment()));
    pod.documentation(pair.first);
    pod.implementation_specific_parameters(pair.second);

    for (const auto& p : o.properties())
        pod.properties().push_back(transform_property(p));

    if (pod.name().type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name + o.id();
        BOOST_THROW_EXCEPTION(
            transformation_error(empty_dia_object_name + o.id()));
    }

    const auto i(context_.child_to_parent().find(o.id()));
    if (i != context_.child_to_parent().end()) {
        const auto j(context_.dia_id_to_qname().find(i->second));
        if (j == context_.dia_id_to_qname().end()) {
            BOOST_LOG_SEV(lg, error) << "Object has a parent but "
                                     << " there is no QName mapping defined."
                                     << " Child ID: '" << o.id()
                                     << "' Parent ID: '" << i->second << "'";

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
    context_.dia_id_to_qname().insert(std::make_pair(o.id(), pod.name()));

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
                std::list<sml::qname> l { pod.name() };
                context_.leaves().insert(std::make_pair(*parent, l));
            } else {
                k->second.push_back(pod.name());
            }

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
    context_.model().pods().insert(std::make_pair(pod.name(), pod));
}

void transformer::
ensure_object_is_uml_class(const object_types ot) const {
    if (ot == object_types::uml_class)
        return;

    BOOST_LOG_SEV(lg, error) << object_has_invalid_type << ot;
    BOOST_THROW_EXCEPTION(
        transformation_error(object_has_invalid_type +
            boost::lexical_cast<std::string>(ot)));
}

sml::enumerator transformer::
transform_enumerator(const processed_property& p,
    const unsigned int position) const {

    dogen::sml::enumerator r;
    r.name(p.name());
    r.documentation(p.comment());
    r.value(boost::lexical_cast<std::string>(position));

    if (r.name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }
    return r;
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

    dogen::sml::enumerator invalid;
    invalid.name("invalid");
    invalid.documentation("Represents an uninitialised enum");
    invalid.value("0");
    e.enumerators().push_back(invalid);

    std::set<std::string> enumerator_names;
    enumerator_names.insert(invalid.name());

    unsigned int pos(1);
    for (const auto& p : o.properties()) {
        const auto enumerator(transform_enumerator(p, pos++));
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

void transformer::transform_package(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Object is a package: " << o.id();

    sml::package p;
    const std::string pkg_id(o.child_node_id());
    using sml::meta_types;
    p.name(transform_qname(o.name(), meta_types::package, pkg_id));
    p.documentation(o.comment());

    if (p.name().type_name().empty()) {
        BOOST_THROW_EXCEPTION(
            transformation_error(empty_dia_object_name + o.id()));
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name + o.id();
    }

    context_.dia_id_to_qname().insert(std::make_pair(o.id(), p.name()));
    context_.model().packages().insert(std::make_pair(p.name(), p));
}

void transformer::transform_note(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Object is a note: " << o.id()
                             << ". Note text: '" << o.text() << "'";

    if (o.text().empty())
        return;

    const auto pair(comments_parser_->parse(o.text()));
    bool has_marker(false);
    for (const auto& p : pair.second) {
        has_marker = p.first == comment_marker;
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

    const auto i(context_.dia_id_to_qname().find(o.child_node_id()));
    if (i == context_.dia_id_to_qname().end()) {
        BOOST_LOG_SEV(lg, error) << missing_package_for_id << o.child_node_id();
        BOOST_THROW_EXCEPTION(
            transformation_error(missing_package_for_id + o.child_node_id()));
    }

    auto j(context_.model().packages().find(i->second));
    if (j == context_.model().packages().end()) {
        BOOST_LOG_SEV(lg, error) << missing_package_for_qname
                                 << i->second.type_name();

        BOOST_THROW_EXCEPTION(
            transformation_error(missing_package_for_qname +
                i->second.type_name()));
    }
    j->second.documentation(pair.first);
    j->second.implementation_specific_parameters(pair.second);
}

void transformer::transform_exception(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Object is an exception: " << o.id();

    sml::exception e;
    e.generation_type(context_.is_target() ?
        sml::generation_types::full_generation :
        sml::generation_types::no_generation);

    const std::string pkg_id(o.child_node_id());
    using sml::meta_types;
    e.name(transform_qname(o.name(), meta_types::exception, pkg_id));
    e.documentation(o.comment());
    context_.model().exceptions().insert(std::make_pair(e.name(), e));
}

void transformer::transform(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Starting to transform: " << o.id();

    if (o.object_type() == object_types::uml_large_package) {
        transform_package(o);
        return;
    }

    if (o.object_type() == object_types::uml_note) {
        transform_note(o);
        return;
    }

    ensure_object_is_uml_class(o.object_type());
    switch(o.stereotype()) {
    case stereotypes::no_stereotype:
    case stereotypes::value:
    case stereotypes::entity:
    case stereotypes::service:
    case stereotypes::nongeneratable:
        transform_pod(o); break;
    case stereotypes::enumeration:
        transform_enumeration(o); break;
    case stereotypes::exception:
        transform_exception(o); break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_stereotype_in_graph
                                 << o.stereotype();
        BOOST_THROW_EXCEPTION(
            transformation_error(invalid_stereotype_in_graph +
                boost::lexical_cast<std::string>(o.stereotype())));
    }
    BOOST_LOG_SEV(lg, debug) << "Transformed: " << o.id();
}

} }
