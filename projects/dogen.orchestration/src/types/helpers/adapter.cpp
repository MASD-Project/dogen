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
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.logical/io/entities/location_io.hpp"
#include "dogen.logical/types/helpers/name_builder.hpp"
#include "dogen.logical/types/helpers/name_factory.hpp"
#include "dogen.orchestration/types/helpers/adaptation_exception.hpp"
#include "dogen.orchestration/types/helpers/stereotypes_helper.hpp"
#include "dogen.orchestration/types/helpers/adapter.hpp"

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

const std::string guid_attr_name("guid");

const std::string empty_string("String is empty but expected value.");
const std::string non_empty_string(
    "String is not empty but did not expect value: ");
const std::string enumerator_with_type("Enumerators cannot have a type: ");
const std::string unsupported_attribute("Attribute is not supported: ");
const std::string unsupported_value("Unsupported attribute value: ");

}

namespace dogen::orchestration::helpers {

using logical::entities::decoration::modeline_field;
using logical::entities::decoration::modeline_group;
using logical::entities::decoration::modeline;
using logical::entities::decoration::generation_marker;
using logical::entities::decoration::licence;


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

std::list<variability::entities::potential_binding> adapter::
to_potential_binding(const std::list<std::string>& stereotypes) const {
    std::list<variability::entities::potential_binding> r;
    for (const auto& s : stereotypes) {
        variability::entities::potential_binding pb;
        pb.name(s);
        pb.realized(false);
        r.push_back(pb);
    }
    return r;
}

logical::entities::name adapter::to_name(const logical::entities::location& l,
    const std::string& n) const {
    BOOST_LOG_SEV(lg, debug) << "Location: " << l;
    /*
     * Names are expected to be delimited by the scope operator,
     * denoting internal modules.
     */
    ensure_not_empty(n);
    auto tokens(utility::string::splitter::split_scoped(n));
    using logical::helpers::name_builder;
    name_builder b;
    b.simple_name(tokens.back());
    tokens.pop_back();
    if (!tokens.empty())
        b.internal_modules(tokens);

    b.external_modules(l.external_modules());
    b.model_modules(l.model_modules());

    return b.build();
}

modeline_field
adapter::to_modeline_field(const injection::entities::attribute& ia) const {
    ensure_not_empty(ia.name());

    modeline_field r;
    r.name(ia.name());
    r.value(ia.value());
    return r;
}

logical::entities::attribute
adapter::to_attribute(const logical::entities::name& owner,
    const injection::entities::attribute& ia) const {
    ensure_not_empty(ia.name());

    logical::helpers::name_factory f;
    logical::entities::attribute r;
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

logical::entities::structural::enumerator
adapter::to_enumerator(const logical::entities::name& owner,
    const injection::entities::attribute& ia) const {
    ensure_not_empty(ia.name());

    if (!ia.type().empty()) {
        const auto t(ia.type());
        BOOST_LOG_SEV(lg, error) << enumerator_with_type << t;
        BOOST_THROW_EXCEPTION(adaptation_exception(enumerator_with_type + t));
    }

    logical::helpers::name_factory f;
    logical::entities::structural::enumerator r;
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

void adapter::populate_element(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie,
    logical::entities::element& e) const {

    /*
     * Ensure we populate the configuration before we attempt to read
     * any meta-data from it.
     */
    e.configuration(ie.configuration());
    const auto& ds(scr.dynamic_stereotypes());
    e.configuration()->profile_bindings(to_potential_binding(ds));
    e.name(to_name(l, ie.name()));
    e.configuration()->name().qualified(e.name().qualified().dot());

    /*
     * Finally, populate all other attributes.
     */
    e.origin_type(logical::entities::origin_types::not_yet_determined);
    e.documentation(ie.documentation());
    e.static_stereotypes(scr.static_stereotypes());
    e.origin_sha1_hash(ie.origin_sha1_hash());
    e.in_global_module(
        l.external_modules().empty() && l.model_modules().empty());
}

boost::shared_ptr<logical::entities::structural::object>
adapter::to_object(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming injection element to object: "
                             << ie.name();

    auto r(boost::make_shared<logical::entities::structural::object>());
    populate_element(l, scr, ie, *r);
    r->is_associative_container(ie.is_associative_container());
    r->can_be_primitive_underlier(ie.can_be_primitive_underlier());

    for (const auto& attr : ie.attributes())
        r->local_attributes().push_back(to_attribute(r->name(), attr));

    for (const auto& p : ie.parents())
        r->parents().push_back(to_name(l, p));

    return r;
}

boost::shared_ptr<logical::entities::structural::object_template>
adapter::to_object_template(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming injection element "
                             << "to object template: " << ie.name();

    auto r(boost::make_shared<logical::entities::structural::object_template>());
    populate_element(l, scr, ie, *r);

    for (const auto& attr : ie.attributes())
        r->local_attributes().push_back(to_attribute(r->name(), attr));

    for (const auto& p : ie.parents())
        r->parents().push_back(to_name(l, p));

    return r;
}

boost::shared_ptr<logical::entities::structural::exception>
adapter::to_exception(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming injection element to exception: "
                             << ie.name();

    auto r(boost::make_shared<logical::entities::structural::exception>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<logical::entities::structural::primitive>
adapter::to_primitive(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming injection element to primitive: "
                             << ie.name();

    auto r(boost::make_shared<logical::entities::structural::primitive>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<logical::entities::structural::enumeration>
adapter::to_enumeration(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming injection element to enumeration: "
                             << ie.name();

    auto r(boost::make_shared<logical::entities::structural::enumeration>());
    populate_element(l, scr, ie, *r);

    for (const auto& attr : ie.attributes())
        r->enumerators().push_back(to_enumerator(r->name(), attr));

    return r;
}

boost::shared_ptr<logical::entities::structural::module> adapter::
to_module(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming injection element to module: "
                             << ie.name();

    auto r(boost::make_shared<logical::entities::structural::module>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<logical::entities::structural::builtin>
adapter::to_builtin(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming injection element to builtin: "
                             << ie.name();

    auto r(boost::make_shared<logical::entities::structural::builtin>());
    populate_element(l, scr, ie, *r);

    r->can_be_primitive_underlier(ie.can_be_primitive_underlier());
    r->is_default_enumeration_type(ie.is_default_enumeration_type());
    r->is_floating_point(ie.is_floating_point());
    r->can_be_enumeration_underlier(ie.can_be_enumeration_underlier());

    return r;
}

boost::shared_ptr<logical::entities::structural::entry_point>
adapter::to_entry_point(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming injection element to exception: "
                             << ie.name();

    auto r(boost::make_shared<logical::entities::structural::entry_point>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<logical::entities::structural::assistant>
adapter::to_assistant(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming injection element to assistant: "
                             << ie.name();

    auto r(boost::make_shared<logical::entities::structural::assistant>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<modeline_group>
adapter::to_modeline_group(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    auto r(boost::make_shared<modeline_group>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<modeline>
adapter::to_modeline(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    auto r(boost::make_shared<modeline>());
    populate_element(l, scr, ie, *r);

    for (const auto& attr : ie.attributes())
        r->fields().push_back(to_modeline_field(attr));

    return r;
}

boost::shared_ptr<generation_marker>
adapter::to_generation_marker(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
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
adapter::to_licence(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
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

void adapter::populate_abstract_profile(const logical::entities::location& l,
    const injection::entities::element& ie,
    logical::entities::variability::abstract_profile& ap) const {
    for (const auto& p : ie.parents())
        ap.parents().push_back(to_name(l, p));
}

void adapter::populate_abstract_feature(
    const logical::entities::name& bundle_name,
    const injection::entities::attribute& ia,
    logical::entities::variability::abstract_feature& af) const {
    const auto n(ia.name());
    ensure_not_empty(n);

    logical::helpers::name_factory f;
    af.name(f.build_attribute_name(bundle_name, n));
    af.original_key(n);
    af.default_value(ia.value());
    af.unparsed_type(ia.type());
    af.documentation(ia.documentation());

    using variability::helpers::enum_mapper;
    af.value_type(enum_mapper::to_value_type(ia.type()));
    af.configuration(ia.configuration());
    af.configuration()->name().qualified(af.name().qualified().dot());
}

void adapter::populate_abstract_profile_entry(const logical::entities::name& pn,
    const injection::entities::attribute& attr,
    logical::entities::variability::abstract_profile_entry& ape) const {
    logical::helpers::name_factory f;

    const auto n(attr.name());
    ensure_not_empty(n);

    /*
     * The conventions for naming profile entries are somewhat
     * confusing. The "simple" name of a profile entry must match the
     * qualified name of the feature it is configuring, e.g.:
     *
     *     masd.generalization.parent
     *
     * The "qualified" name of the profile entry reflects its
     * position in assets space, and as such is composed of the
     * assets element that owns the profile entry (the profile):
     *
     *     dogen.cpp_artefact_transform
     *
     * Concatenated with the "simple" name, e.g.:
     *
     *     dogen.cpp_artefact_transform.masd.generalization.parent
     *
     * Whilst this may not be exactly the most aesthetically
     * pleasing approach, it is more or less compliant with the
     * conceptual model for the assets space. It also makes it
     * really easy to find out where a configuration came from,
     * when we are looking at a configuration model
     * representation.
     */
    ape.name(f.build_attribute_name(pn, n));
    ape.original_key(n);
    ape.configuration(attr.configuration());
    ape.configuration()->name().qualified(ape.name().qualified().dot());
    if (!attr.value().empty())
        ape.value().push_back(attr.value());
}

boost::shared_ptr<logical::entities::variability::profile>
adapter::to_variability_profile(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    using logical::entities::variability::profile;
    auto r(boost::make_shared<profile>());
    populate_element(l, scr, ie, *r);
    populate_abstract_profile(l, ie, *r);

    for (const auto& attr : ie.attributes()) {
        logical::entities::variability::profile_entry e;
        populate_abstract_profile_entry(r->name(), attr, e);
        r->entries().push_back(e);
    }
    return r;
}

boost::shared_ptr<logical::entities::variability::profile_template>
adapter::to_variability_profile_template(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    using logical::entities::variability::profile_template;
    auto r(boost::make_shared<profile_template>());
    populate_element(l, scr, ie, *r);
    populate_abstract_profile(l, ie, *r);

    for (const auto& attr : ie.attributes()) {
        logical::entities::variability::profile_template_entry e;
        populate_abstract_profile_entry(r->name(), attr, e);
        r->entries().push_back(e);
    }

    return r;
}

boost::shared_ptr<logical::entities::variability::feature_template_bundle>
adapter::to_variability_feature_template_bundle(
    const logical::entities::location &l,
    const stereotypes_conversion_result &scr,
    const injection::entities::element &ie) const {
    using logical::entities::variability::feature_template_bundle;
    auto r(boost::make_shared<feature_template_bundle>());
    populate_element(l, scr, ie, *r);

    for (const auto& ia : ie.attributes()) {
        logical::entities::variability::feature_template ft;
        populate_abstract_feature(r->name(), ia, ft);
        r->feature_templates().push_back(ft);
    }

    return r;
}

boost::shared_ptr<logical::entities::variability::feature_bundle>
adapter::to_variability_feature_bundle(const logical::entities::location &l,
    const stereotypes_conversion_result &scr,
    const injection::entities::element &ie) const {
    using logical::entities::variability::feature_bundle;
    auto r(boost::make_shared<feature_bundle>());
    populate_element(l, scr, ie, *r);

    for (const auto& ia : ie.attributes()) {
        logical::entities::variability::feature f;
        populate_abstract_feature(r->name(), ia, f);
        r->features().push_back(f);
    }

    return r;
}

boost::shared_ptr<
    logical::entities::variability::initializer
    >
adapter::to_variability_initializer(const logical::entities::location &l,
    const stereotypes_conversion_result &scr,
    const injection::entities::element &ie) const {
    using logical::entities::variability::initializer;
    auto r(boost::make_shared<initializer>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<logical::entities::mapping::fixed_mappable>
adapter::to_fixed_mappable(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    using logical::entities::mapping::fixed_mappable;
    auto r(boost::make_shared<fixed_mappable>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<logical::entities::mapping::extensible_mappable>
adapter::to_extensible_mappable(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    using logical::entities::mapping::extensible_mappable;
    auto r(boost::make_shared<extensible_mappable>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<logical::entities::templating::logic_less_template>
adapter::to_logic_less_template(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    using logical::entities::templating::logic_less_template;
    auto r(boost::make_shared<logic_less_template>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<logical::entities::serialization::type_registrar>
adapter::to_type_registrar(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    using logical::entities::serialization::type_registrar;
    auto r(boost::make_shared<type_registrar>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<logical::entities::visual_studio::solution>
adapter::to_visual_studio_solution(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    using logical::entities::visual_studio::solution;
    auto r(boost::make_shared<solution>());
    populate_element(l, scr, ie, *r);

    for (const auto& attr : ie.attributes()) {
        const auto n(attr.name());
        ensure_not_empty(n);

        const auto v(attr.value());
        if (n == guid_attr_name)
            r->guid(v);
        else {
            BOOST_LOG_SEV(lg, error) << unsupported_attribute << n;
            BOOST_THROW_EXCEPTION(
                adaptation_exception(unsupported_attribute + n));
        }
    }

    return r;
}

boost::shared_ptr<logical::entities::visual_studio::project>
adapter::to_visual_studio_project(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    using logical::entities::visual_studio::project;
    auto r(boost::make_shared<project>());
    populate_element(l, scr, ie, *r);

    for (const auto& attr : ie.attributes()) {
        const auto n(attr.name());
        ensure_not_empty(n);

        const auto v(attr.value());
        if (n == guid_attr_name)
            r->guid(v);
        else {
            BOOST_LOG_SEV(lg, error) << unsupported_attribute << n;
            BOOST_THROW_EXCEPTION(
                adaptation_exception(unsupported_attribute + n));
        }
    }

    return r;
}

boost::shared_ptr<logical::entities::visual_studio::msbuild_targets>
adapter::to_visual_studio_msbuild_targets(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    using logical::entities::visual_studio::msbuild_targets;
    auto r(boost::make_shared<msbuild_targets>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<logical::entities::orm::common_odb_options>
adapter::to_orm_common_odb_options(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    using logical::entities::orm::common_odb_options;
    auto r(boost::make_shared<common_odb_options>());
    populate_element(l, scr, ie, *r);
    return r;
}

boost::shared_ptr<logical::entities::build::cmakelists>
adapter::to_build_cmakelists(const logical::entities::location& l,
    const stereotypes_conversion_result& scr,
    const injection::entities::element& ie) const {
    using logical::entities::build::cmakelists;
    auto r(boost::make_shared<cmakelists>());
    populate_element(l, scr, ie, *r);
    return r;
}

}
