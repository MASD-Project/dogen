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
#include "dogen/dia/types/enum_parser.hpp"
#include "dogen/dia_to_sml/types/transformation_error.hpp"
#include "dogen/dia/io/stereotypes_io.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/dia_to_sml/types/object_transformer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml.object_transformer"));

const std::string empty;
const std::string dia_string("string");
const std::string dia_name("name");
const std::string dia_type("type");
const std::string dia_comment("comment");
const std::string dia_stereotype("stereotype");
const std::string dia_attributes("attributes");
const std::string dia_composite("composite");
const std::string dia_uml_attribute("umlattribute");
const std::string hash_character("#");

const std::string error_parsing_object_type("Fail to parse object type: ");
const std::string empty_dia_object_name("Dia object name is empty");
const std::string original_parent_not_found("Pod has no original parent: ");
const std::string uml_attribute_expected("UML atttribute expected");
const std::string parent_not_found("Object has a parent but its not defined: ");
const std::string missing_package_for_id("Missing package for dia object ID: ");
const std::string error_parsing_stereotype("Fail to parse stereotype: ");
const std::string name_attribute_expected("Could not find name attribute");
const std::string type_attribute_expected("Could not find type attribute");
const std::string unexpected_attribute_value_type(
    "Did not find expected attribute value type: ");
const std::string unexpected_attribute_value_size(
    "Unexpected attribute value size: ");
const std::string invalid_type_string(
    "String provided with type did not parse into SML qnames: ");
const std::string object_has_invalid_type("Invalid dia type: ");
const std::string invalid_stereotype_in_graph("Invalid stereotype: ");

template<typename AttributeValue, typename Variant>
AttributeValue
attribute_value(const Variant& v, const std::string& desc) {

    AttributeValue r;
    try {
        r = boost::get<AttributeValue>(v);
    } catch (const boost::bad_get&) {
        BOOST_LOG_SEV(lg, error) << unexpected_attribute_value_type << desc;

        using dogen::dia_to_sml::transformation_error;
        BOOST_THROW_EXCEPTION(
            transformation_error(unexpected_attribute_value_type + desc));
    }
    return r;
}

}

namespace dogen {
namespace dia_to_sml {

object_transformer::object_transformer(context* c)
    : context_(c),
      identifier_parser_(
          new sml::identifier_parser(c->top_level_packages(),
              c->external_package_path(), c->model_name())),
      comments_parser_(new sml::comments_parser()) { }

void object_transformer::
compute_model_dependencies(const sml::nested_qname& nqn) {
    // primitives model is empty
    const auto mn(nqn.type().model_name());
    if (!mn.empty() && mn != context_->model_name())
        context_->dependencies().insert(mn);

    for (const auto c : nqn.children())
        compute_model_dependencies(c);
}

std::string object_transformer::
transform_string_attribute(const dia::attribute& a) const {
    const auto values(a.values());
    if (values.size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Expected attribute to have one"
                                 << " value but found " << values.size();
        BOOST_THROW_EXCEPTION(
            transformation_error(unexpected_attribute_value_size +
                boost::lexical_cast<std::string>(values.size())));
    }

    using dia::string;
    const auto v(attribute_value<string>(values.front(), dia_string));
    std::string name(v.value());
    boost::erase_first(name, hash_character);
    boost::erase_last(name, hash_character);
    boost::trim(name);
    return name;
}

sml::qname object_transformer::transform_qname(const dogen::dia::attribute& a,
    sml::meta_types meta_type, const std::string& pkg_id) const {

    if (a.name() != dia_name) {
        BOOST_LOG_SEV(lg, error) << name_attribute_expected;
        BOOST_THROW_EXCEPTION(transformation_error(name_attribute_expected));
    }

    sml::qname name;
    name.model_name(context_->model_name());
    name.meta_type(meta_type);
    name.external_package_path(context_->external_package_path());

    if (!pkg_id.empty()) {
        const auto i(context_->packages_by_id().find(pkg_id));
        if (i == context_->packages_by_id().end()) {
            BOOST_LOG_SEV(lg, error) << missing_package_for_id << pkg_id;
            BOOST_THROW_EXCEPTION(
                transformation_error(missing_package_for_id + pkg_id));
        }
        auto pp(i->second.name().package_path());
        pp.push_back(i->second.name().type_name());
        name.package_path(pp);
    }

    name.type_name(transform_string_attribute(a));
    if (name.type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }
    return name;
}

sml::property object_transformer::
transform_property(const dia::composite& uml_attribute) {
    sml::property property;
    typedef boost::shared_ptr<dia::attribute> attribute_ptr;

    for (const attribute_ptr a : uml_attribute.value()) {
        if (a->name() == dia_name)
            property.name(transform_string_attribute(*a));
        else if (a->name() == dia_type) {
            const std::string s(transform_string_attribute(*a));
            auto nested_name(identifier_parser_->parse_qname(s));
            if (nested_name.type().type_name().empty()) {
                BOOST_LOG_SEV(lg, error) << invalid_type_string << s;
                BOOST_THROW_EXCEPTION(
                    transformation_error(invalid_type_string + s));
            }
            property.type_name(nested_name);
            compute_model_dependencies(nested_name);
        } else if (a->name() == dia_comment) {
            const std::string comment(transform_string_attribute(*a));
            const auto r(comments_parser_->parse(comment));
            property.documentation(r.first);
            property.implementation_specific_parameters(r.second);
        } else {
            BOOST_LOG_SEV(lg, warn) << "Ignoring unexpected attribute: "
                                    << a->name();
        }
    }

    if (property.name().empty()) {
        BOOST_LOG_SEV(lg, error) << "Could not find a name attribute.";
        BOOST_THROW_EXCEPTION(transformation_error(name_attribute_expected));
    }

    if (property.type_name().type().type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << "Could not find a type attribute.";
        BOOST_THROW_EXCEPTION(transformation_error(type_attribute_expected));
    }
    return property;
}

void object_transformer::transform_pod(const dia::object& o) {
    using sml::generation_types;

    sml::pod pod;
    pod.generation_type(context_->is_target() ?
        generation_types::full_generation :
        generation_types::no_generation);

    pod.category_type(sml::category_types::user_defined);
    for (auto a : o.attributes()) {
        BOOST_LOG_SEV(lg, debug) << "Found attribute: " << a.name();

        if (a.name() == dia_name) {
            const std::string pkg_id(o.child_node() ?
                o.child_node()->parent() : empty);
            using sml::meta_types;
            pod.name(transform_qname(a, meta_types::pod, pkg_id));
        } else if (a.name() == dia_stereotype) {
            const auto v(transform_string_attribute(a));

            if (v.empty()) {
                pod.pod_type(sml::pod_types::value);
                continue;
            }

            using dia::enum_parser;
            const auto st(enum_parser::parse_stereotype(v));
            using dia::stereotypes;
            if (st == stereotypes::entity)
                pod.pod_type(sml::pod_types::entity);
            else if (st == stereotypes::value)
                pod.pod_type(sml::pod_types::value);
            else if (st == stereotypes::nongeneratable) {
                pod.pod_type(sml::pod_types::value);
                if (context_->is_target())
                    pod.generation_type(generation_types::partial_generation);
            } else if (st == stereotypes::service) {
                pod.pod_type(sml::pod_types::service);
                if (context_->is_target())
                    pod.generation_type(generation_types::partial_generation);
            } else
                pod.pod_type(sml::pod_types::value);
        } else if (a.name() == dia_comment) {
            const std::string comment(transform_string_attribute(a));
            const auto r(comments_parser_->parse(comment));
            pod.documentation(r.first);
            pod.implementation_specific_parameters(r.second);
        } else if (a.name() == dia_attributes) {
            const auto values(a.values());

            if (values.empty()) {
                BOOST_LOG_SEV(lg, debug) << "Attribute is empty.";
                continue;
            }

            std::vector<sml::property> properties;
            for (auto v : values) {
                using dia::composite;
                const auto c(attribute_value<composite>(v, dia_composite));

                if (c.type() != dia_uml_attribute) {
                    BOOST_LOG_SEV(lg, error) << "Expected composite type "
                                             << " to be " << dia_uml_attribute
                                             << "but was " << c.type();
                    BOOST_THROW_EXCEPTION(
                        transformation_error(uml_attribute_expected));
                }
                BOOST_LOG_SEV(lg, debug) << "Found composite of type "
                                         << c.type();
                properties.push_back(transform_property(c));
            }
            pod.properties(properties);
        }
    }

    if (pod.name().type_name().empty()) {
        BOOST_LOG_SEV(lg, error) << name_attribute_expected + o.id();
        BOOST_THROW_EXCEPTION(
            transformation_error(name_attribute_expected + o.id()));
    }

    const auto i(context_->child_to_parent().find(o.id()));
    if (i != context_->child_to_parent().end()) {
        const auto j(context_->dia_id_to_qname().find(i->second));
        if (j == context_->dia_id_to_qname().end()) {
            BOOST_LOG_SEV(lg, error) << "Object has a parent but "
                                     << " there is no QName mapping defined."
                                     << " Child ID: '" << o.id()
                                     << "' Parent ID: '" << i->second << "'";

            BOOST_THROW_EXCEPTION(
                transformation_error(parent_not_found + o.id()));
        }
        pod.parent_name(j->second);
    }

    const auto j(context_->parent_ids().find(o.id()));
    pod.is_parent(j != context_->parent_ids().end());
    context_->dia_id_to_qname().insert(std::make_pair(o.id(), pod.name()));

    if (!pod.parent_name()) {
        context_->original_parent().insert(
            std::make_pair(pod.name(), pod.name()));
    } else {
        const auto k(context_->original_parent().find(*pod.parent_name()));
        if (k == context_->original_parent().end()) {
            BOOST_LOG_SEV(lg, error) << "Could not find the original parent of "
                                     << pod.name().type_name();

            BOOST_THROW_EXCEPTION(
                transformation_error(original_parent_not_found +
                    pod.name().type_name()));
        }
        pod.original_parent_name(k->second);
        context_->original_parent().insert(
            std::make_pair(pod.name(), k->second));
    }

    if (!pod.is_parent() && pod.parent_name() &&
        pod.generation_type() == generation_types::full_generation) {
        auto parent(pod.parent_name());
        while (parent) {
            auto k(context_->leaves().find(*parent));
            if (k == context_->leaves().end()) {
                std::list<sml::qname> l { pod.name() };
                context_->leaves().insert(std::make_pair(*parent, l));
            } else {
                k->second.push_back(pod.name());
            }

            auto j(context_->pods().find(*parent));
            if (j == context_->pods().end()) {
                BOOST_LOG_SEV(lg, error) << "Could not find the parent of "
                                         << parent->type_name();
                BOOST_THROW_EXCEPTION(transformation_error(parent_not_found +
                        parent->type_name()));
            }
            parent = j->second.parent_name();
        }
    }
    context_->pods().insert(std::make_pair(pod.name(), pod));
}

void object_transformer::
ensure_object_is_uml_class(const dia::object& o) const {
    using dia::object_types;
    object_types ot(object_types::invalid);

    try {
        using dogen::dia::enum_parser;
        ot = enum_parser::parse_object_type(o.type());
    } catch(const std::exception& e) {
        std::ostringstream s;
        s << error_parsing_object_type << "'" << o.type()
          << "'. Error: " << e.what();

        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(transformation_error(s.str()));
    }

    if (ot == object_types::uml_class)
        return;

    BOOST_LOG_SEV(lg, error) << object_has_invalid_type << o.type();
    BOOST_THROW_EXCEPTION(
        transformation_error(object_has_invalid_type + o.type()));
}

dia::stereotypes
object_transformer::stereotype_for_object(const dia::object& o) const {
    using dia::stereotypes;
    stereotypes r(stereotypes::invalid);
    for (const auto& a : o.attributes()) {
        if (a.name() != dia_stereotype)
            continue;

        using dia::stereotypes;
        const std::string s(transform_string_attribute(a));
        if (s.empty())
            return r;

        try {
            using dogen::dia::enum_parser;
            r = enum_parser::parse_stereotype(s);
        } catch(const std::exception& e) {
            std::ostringstream stream;
            stream << error_parsing_stereotype << "'" << s
                   << "'. Error: " << e.what();
            BOOST_LOG_SEV(lg, error) << stream.str();
            BOOST_THROW_EXCEPTION(transformation_error(stream.str()));
        }
        break;
    }
    return r;
}

sml::enumerator object_transformer::
transform_enumerator(const dogen::dia::composite& uml_attribute,
    const unsigned int position) const {
    dogen::sml::enumerator r;
    for (const auto a : uml_attribute.value()) {
        if (a->name() == dia_name) {
            r.name(transform_string_attribute(*a));
        } else if (a->name() == dia_comment) {
            const std::string doc(transform_string_attribute(*a));
            r.documentation(doc);
        } else {
            BOOST_LOG_SEV(lg, warn) << "Ignoring unexpected attribute: "
                                    << a->name();
        }
    }
    r.value(boost::lexical_cast<std::string>(position));
    if (r.name().empty()) {
        BOOST_LOG_SEV(lg, error) << "Could not find a name attribute.";
        BOOST_THROW_EXCEPTION(transformation_error(name_attribute_expected));
    }

    return r;
}

void object_transformer::transform_enumeration(const dia::object& o) {
    sml::enumeration e;

    e.generation_type(context_->is_target() ?
        sml::generation_types::full_generation :
        sml::generation_types::no_generation);

    for (auto a : o.attributes()) {
        BOOST_LOG_SEV(lg, debug) << "Found attribute: " << a.name();
        if (a.name() == dia_name) {
            const std::string pkg_id(o.child_node() ?
                o.child_node()->parent() : empty);
            using sml::meta_types;
            e.name(transform_qname(a, meta_types::enumeration, pkg_id));
        } else if (a.name() == dia_comment) {
            const std::string doc(transform_string_attribute(a));
            e.documentation(doc);
        } if (a.name() == dia_attributes) {
            const auto values(a.values());

            if (values.empty()) {
                BOOST_LOG_SEV(lg, debug) << "Attribute is empty.";
                continue;
            }

            dogen::sml::enumerator invalid;
            invalid.name("invalid");
            invalid.documentation("Represents an uninitialised enum");
            invalid.value("0");
            e.enumerators().push_back(invalid);

            std::set<std::string> enumerator_names;
            enumerator_names.insert(invalid.name());

            unsigned int pos(1);
            for (auto v : values) {
                using dogen::dia::composite;
                const auto c(attribute_value<composite>(v, dia_composite));

                if (c.type() != dia_uml_attribute) {
                    BOOST_LOG_SEV(lg, error) << "Expected composite type to be "
                                             << dia_uml_attribute
                                             << "but was " << c.type();
                    BOOST_THROW_EXCEPTION(
                        transformation_error(uml_attribute_expected));
                }
                BOOST_LOG_SEV(lg, debug) << "Found composite of type "
                                         << c.type();
                const auto enumerator(transform_enumerator(c, pos++));
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
        }
    }
    context_->enumerations().insert(std::make_pair(e.name(), e));
}

void object_transformer::transform(const dia::object& o) {
    ensure_object_is_uml_class(o);

    using dia::stereotypes;
    const auto st(stereotype_for_object(o));
    switch(st) {
    case stereotypes::value:
    case stereotypes::entity:
    case stereotypes::service:
        transform_pod(o); break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_stereotype_in_graph << st;
        BOOST_THROW_EXCEPTION(
            transformation_error(invalid_stereotype_in_graph +
                boost::lexical_cast<std::string>(st)));
    }
}

} }
