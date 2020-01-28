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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.variability/types/helpers/enum_mapper.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.assets/io/meta_model/location_io.hpp"
#include "dogen.assets/types/helpers/name_builder.hpp"
#include "dogen.assets/types/helpers/name_factory.hpp"
#include "dogen.assets/types/helpers/string_processor.hpp"
#include "dogen.engine/types/helpers/stereotypes_helper.hpp"
#include "dogen.engine/types/helpers/adaptation_exception.hpp"
#include "dogen.engine/types/helpers/adapter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("engine.helpers.adapter"));

const std::string member_variable_postfix("_");
const std::string short_form_attr_name("short_form");
const std::string long_form_attr_name("long_form");
const std::string add_date_time_attr_name("add_date_time");
const std::string add_dogen_version_attr_name("add_dogen_version");
const std::string add_model_to_text_transform_details_attr_name(
    "add_model_to_text_transform_details");
const std::string add_warning_attr_name("add_warning");
const std::string add_message_attr_name("message");
const std::string add_origin_sha1_hash_attr_name("add_origin_sha1_hash");
const std::string true_value("true");
const std::string false_value("false");

const std::string empty_string("String is empty but expected value.");
const std::string non_empty_string(
    "String is not empty but did not expect value: ");
const std::string enumerator_with_type("Enumerators cannot have a type: ");
const std::string unsupported_attribute("Attribute is not supported: ");
const std::string unsupported_value("Unsupported attribute value: ");

}

namespace dogen::engine::helpers {

using assets::meta_model::decoration::modeline_field;
using assets::meta_model::decoration::modeline_group;
using assets::meta_model::decoration::modeline;
using assets::meta_model::decoration::generation_marker;
using assets::meta_model::decoration::licence;


void adapter::ensure_not_empty(const std::string& s) const {
    if (s.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_string;
        BOOST_THROW_EXCEPTION(adaptation_exception(empty_string));
    }
}

void adapter::ensure_empty(const std::string& s) const {
    if (s.empty()) {
        BOOST_LOG_SEV(lg, error) << non_empty_string << s;
        BOOST_THROW_EXCEPTION(adaptation_exception(non_empty_string + s));
    }
}

std::list<variability::meta_model::potential_binding> adapter::
to_potential_binding(const std::list<std::string>& stereotypes) const {
    std::list<variability::meta_model::potential_binding> r;
    for (const auto& s : stereotypes) {
        variability::meta_model::potential_binding pb;
        pb.name(s);
        pb.realized(false);
        r.push_back(pb);
    }
    return r;
}

assets::meta_model::name adapter::to_name(const assets::meta_model::location& l,
    const std::string& n) const {
    BOOST_LOG_SEV(lg, debug) << "Location: " << l;
    /*
     * Names are expected to be delimited by the scope operator,
     * denoting internal modules.
     */
    ensure_not_empty(n);
    auto tokens(utility::string::splitter::split_scoped(n));
    assets::helpers::name_builder b;
    b.simple_name(tokens.back());
    tokens.pop_back();
    if (!tokens.empty())
        b.internal_modules(tokens);

    b.external_modules(l.external_modules());
    b.model_modules(l.model_modules());

    return b.build();
}

modeline_field
adapter::to_modeline_field(const injection::meta_model::attribute& ia) const {
    ensure_not_empty(ia.name());

    modeline_field r;
    r.name(ia.name());
    r.value(ia.value());
    return r;
}

assets::meta_model::attribute
adapter::to_attribute(const assets::meta_model::name& owner,
    const injection::meta_model::attribute& ia) const {
    ensure_not_empty(ia.name());

    assets::helpers::name_factory f;
    assets::meta_model::attribute r;
    r.name(f.build_attribute_name(owner, ia.name()));
    r.member_variable_name(r.name().simple() + member_variable_postfix);
    r.getter_setter_name(r.name().simple());

    r.unparsed_type(ia.type());
    r.documentation(ia.documentation());

    r.configuration(ia.configuration());
    r.configuration()->name().qualified(r.name().qualified().dot());

    helpers::stereotypes_helper h;
    const auto scr(h.from_string(ia.stereotypes()));
    const auto& ds(scr.dynamic_stereotypes());
    r.configuration()->profile_bindings(to_potential_binding(ds));

    return r;
}

assets::meta_model::structural::enumerator
adapter::to_enumerator(const assets::meta_model::name& owner,
    const injection::meta_model::attribute& ia) const {
    ensure_not_empty(ia.name());

    if (!ia.type().empty()) {
        const auto t(ia.type());
        BOOST_LOG_SEV(lg, error) << enumerator_with_type << t;
        BOOST_THROW_EXCEPTION(adaptation_exception(enumerator_with_type + t));
    }

    assets::helpers::name_factory f;
    assets::meta_model::structural::enumerator r;
    r.name(f.build_attribute_name(owner, ia.name()));
    r.documentation(ia.documentation());

    r.configuration(ia.configuration());
    r.configuration()->name().qualified(r.name().qualified().dot());

    helpers::stereotypes_helper h;
    const auto scr(h.from_string(ia.stereotypes()));
    const auto& ds(scr.dynamic_stereotypes());
    r.configuration()->profile_bindings(to_potential_binding(ds));

    return r;
}

void adapter::populate_element(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie,
    assets::meta_model::element& e) const {
    e.name(to_name(l, ie.name()));
    e.origin_type(assets::meta_model::origin_types::not_yet_determined);
    e.documentation(ie.documentation());
    e.static_stereotypes(scr.static_stereotypes());

    e.origin_element_id(ie.origin_element_id());
    e.origin_sha1_hash(ie.origin_sha1_hash());

    e.configuration(ie.configuration());
    e.configuration()->name().qualified(e.name().qualified().dot());

    const auto& ds(scr.dynamic_stereotypes());
    e.configuration()->profile_bindings(to_potential_binding(ds));

    e.in_global_module(
        l.external_modules().empty() && l.model_modules().empty());
}

boost::shared_ptr<assets::meta_model::structural::object>
adapter::to_object(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to object: "
                             << ie.name();

    auto r(boost::make_shared<assets::meta_model::structural::object>());
    populate_element(l, scr, ie, *r);
    r->is_associative_container(ie.is_associative_container());
    r->can_be_primitive_underlier(ie.can_be_primitive_underlier());

    for (const auto& attr : ie.attributes())
        r->local_attributes().push_back(to_attribute(r->name(), attr));

    for (const auto& p : ie.parents())
        r->parents().push_back(to_name(l, p));

    return r;
}

boost::shared_ptr<assets::meta_model::structural::object_template>
adapter::to_object_template(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element "
                             << "to object template: " << ie.name();

    auto r(boost::make_shared<assets::meta_model::structural::object_template>());
    populate_element(l, scr, ie, *r);

    for (const auto& attr : ie.attributes())
        r->local_attributes().push_back(to_attribute(r->name(), attr));

    for (const auto& p : ie.parents())
        r->parents().push_back(to_name(l, p));

    return r;
}

boost::shared_ptr<assets::meta_model::structural::exception>
adapter::to_exception(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to exception: "
                             << ie.name();

    auto r(boost::make_shared<assets::meta_model::structural::exception>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<assets::meta_model::structural::primitive>
adapter::to_primitive(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to primitive: "
                             << ie.name();

    auto r(boost::make_shared<assets::meta_model::structural::primitive>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<assets::meta_model::structural::enumeration>
adapter::to_enumeration(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to enumeration: "
                             << ie.name();

    auto r(boost::make_shared<assets::meta_model::structural::enumeration>());
    populate_element(l, scr, ie, *r);

    for (const auto& attr : ie.attributes())
        r->enumerators().push_back(to_enumerator(r->name(), attr));

    return r;
}

boost::shared_ptr<assets::meta_model::structural::module> adapter::
to_module(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to module: "
                             << ie.name();

    auto r(boost::make_shared<assets::meta_model::structural::module>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<assets::meta_model::structural::builtin>
adapter::to_builtin(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to builtin: "
                             << ie.name();

    auto r(boost::make_shared<assets::meta_model::structural::builtin>());
    populate_element(l, scr, ie, *r);

    r->can_be_primitive_underlier(ie.can_be_primitive_underlier());
    r->is_default_enumeration_type(ie.is_default_enumeration_type());
    r->is_floating_point(ie.is_floating_point());
    r->can_be_enumeration_underlier(ie.can_be_enumeration_underlier());

    return r;
}

boost::shared_ptr<modeline_group>
adapter::to_modeline_group(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    auto r(boost::make_shared<modeline_group>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<modeline>
adapter::to_modeline(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    auto r(boost::make_shared<modeline>());
    populate_element(l, scr, ie, *r);

    for (const auto& attr : ie.attributes())
        r->fields().push_back(to_modeline_field(attr));

    return r;
}

boost::shared_ptr<generation_marker>
adapter::to_generation_marker(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    auto r(boost::make_shared<generation_marker>());
    populate_element(l, scr, ie, *r);

    const auto str_to_bool(
        [](const std::string& s) {
            if (s == true_value) return true;
            if (s == false_value) return false;
            BOOST_LOG_SEV(lg, error) << unsupported_value << s;
            BOOST_THROW_EXCEPTION(adaptation_exception(unsupported_value + s));
        });

    for (const auto& attr : ie.attributes()) {
        const auto n(attr.name());
        ensure_not_empty(n);

        const auto v(attr.value());
        if (n == add_date_time_attr_name)
            r->add_date_time(str_to_bool(v));
        else if (n == add_dogen_version_attr_name)
            r->add_dogen_version(str_to_bool(v));
        else if (n == add_model_to_text_transform_details_attr_name)
            r->add_model_to_text_transform_details(str_to_bool(v));
        else if (n == add_warning_attr_name)
            r->add_warning(str_to_bool(v));
        else if (n == add_message_attr_name)
            r->message(attr.documentation());
        else if (n == add_origin_sha1_hash_attr_name)
            r->add_origin_sha1_hash(str_to_bool(v));
        else {
            BOOST_LOG_SEV(lg, error) << unsupported_attribute << n;
            BOOST_THROW_EXCEPTION(
                adaptation_exception(unsupported_attribute + n));
        }
    }

    return r;
}

boost::shared_ptr<licence>
adapter::to_licence(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    auto r(boost::make_shared<licence>());
    populate_element(l, scr, ie, *r);

    for (const auto& attr : ie.attributes()) {
        const auto n(attr.name());
        ensure_not_empty(n);

        if (n == short_form_attr_name)
            r->short_form(attr.documentation());
        else if (n == long_form_attr_name)
            r->long_form(attr.documentation());
        else {
            BOOST_LOG_SEV(lg, error) << unsupported_attribute << n;
            BOOST_THROW_EXCEPTION(
                adaptation_exception(unsupported_attribute + n));
        }
    }

    return r;
}

boost::shared_ptr<assets::meta_model::variability::profile_template>
adapter::to_variability_profile_template(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    using assets::meta_model::variability::profile_template;
    auto r(boost::make_shared<profile_template>());
    populate_element(l, scr, ie, *r);

    assets::helpers::name_factory f;
    for (const auto& p : ie.parents())
        r->parents().push_back(to_name(l, p));

    for (const auto& attr : ie.attributes()) {
        const auto n(attr.name());
        ensure_not_empty(n);

        /*
         * The conventions for naming profile entries are somewhat
         * confusing. The "simple" name of a profile entry must match
         * the qualified naem of the feature it is configuring, e.g.:
         *
         *     masd.generalization.parent
         *
         * The "qualified" name of the profile entry reflects its
         * position in assets space, and as such is composed of the
         * assets element that owns the profile entry (the profile):
         *
         *     dogen.cpp_artefact_formatter
         *
         * Concatenated with the "simple" name, e.g.:
         *
         *     dogen.cpp_artefact_formatter.masd.generalization.parent
         *
         * Whilst this may not be exactly the most aesthetically
         * pleasing approach, it is more or less compliant with the
         * conceptual model for the assets space. It also makes it
         * really easy to find out where a configuration came from,
         * when we are looking at a configuration model
         * representation.
         */
        assets::meta_model::variability::profile_template_entry e;
        e.name(f.build_attribute_name(r->name(), n));
        e.key(n);
        e.configuration(attr.configuration());
        e.configuration()->name().qualified(e.name().qualified().dot());
        e.value(attr.value());
        r->entries().push_back(e);
    }
    return r;
}

boost::shared_ptr<assets::meta_model::variability::feature_bundle>
adapter::to_variability_feature_bundle(
    const assets::meta_model::location &l,
    const stereotypes_conversion_result &scr,
    const injection::meta_model::element &ie) const {
    using assets::meta_model::variability::feature_bundle;
    auto r(boost::make_shared<feature_bundle>());
    populate_element(l, scr, ie, *r);

    using variability::helpers::enum_mapper;
    assets::helpers::name_factory f;
    assets::helpers::string_processor sp;
    for (const auto& attr : ie.attributes()) {
        const auto n(attr.name());
        ensure_not_empty(n);

        assets::meta_model::variability::feature_template ft;
        ft.name(f.build_attribute_name(r->name(), n));
        ft.key(n);
        ft.identifiable_key(sp.to_identifiable(n));
        ft.value(attr.value());
        ft.unparsed_type(attr.type());
        ft.value_type(enum_mapper::to_value_type(attr.type()));
        ft.configuration(attr.configuration());
        ft.configuration()->name().qualified(ft.name().qualified().dot());
        r->feature_templates().push_back(ft);
    }

    return r;
}

boost::shared_ptr<
    assets::meta_model::variability::feature_template_initializer
    >
adapter::to_variability_feature_template_initializer(
    const assets::meta_model::location &l,
    const stereotypes_conversion_result &scr,
    const injection::meta_model::element &ie) const {
    using assets::meta_model::variability::feature_template_initializer;
    auto r(boost::make_shared<feature_template_initializer>());
    populate_element(l, scr, ie, *r);
    return r;
}


boost::shared_ptr<assets::meta_model::mapping::fixed_mappable>
adapter::to_fixed_mappable(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    using assets::meta_model::mapping::fixed_mappable;
    auto r(boost::make_shared<fixed_mappable>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<assets::meta_model::mapping::extensible_mappable>
adapter::to_extensible_mappable(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    using assets::meta_model::mapping::extensible_mappable;
    auto r(boost::make_shared<extensible_mappable>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<assets::meta_model::templating::logic_less_template>
adapter::to_logic_less_template(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    using assets::meta_model::templating::logic_less_template;
    auto r(boost::make_shared<logic_less_template>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<assets::meta_model::serialization::type_registrar>
adapter::to_type_registrar(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    using assets::meta_model::serialization::type_registrar;
    auto r(boost::make_shared<type_registrar>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<assets::meta_model::build::visual_studio_project>
adapter::to_visual_studio_project(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    using assets::meta_model::build::visual_studio_project;
    auto r(boost::make_shared<visual_studio_project>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<assets::meta_model::build::visual_studio_solution>
adapter::to_visual_studio_solution(const assets::meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const injection::meta_model::element& ie) const {
    using assets::meta_model::build::visual_studio_solution;
    auto r(boost::make_shared<visual_studio_solution>());
    populate_element(l, scr, ie, *r);
    return r;
}

}
