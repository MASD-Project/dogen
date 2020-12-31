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
#include <ostream>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.variability/types/helpers/enum_mapper.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/logical_location_io.hpp"
#include "dogen.identification/types/helpers/logical_name_builder.hpp"
#include "dogen.identification/types/helpers/logical_name_factory.hpp"
#include "dogen.orchestration/types/helpers/projection_error.hpp"
#include "dogen.logical/types/helpers/stereotypes_helper.hpp"
#include "dogen.orchestration/types/helpers/codec_to_logical_projector.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("orchestration.helpers.codec_to_logical_projector"));

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
const std::string external_modules_path_contribution_name(
    "external_modules_path_contribution");
const std::string model_modules_path_contribution_name(
    "model_modules_path_contribution");
const std::string facet_path_contribution_name("facet_path_contribution");
const std::string internal_modules_path_contribution_name(
    "internal_modules_path_contribution");
const std::string requires_relative_path_name("requires_relative_path");
const std::string file_extension_name("file_extension");
const std::string directory_name_name("directory_name");

const std::string path_contribution_none("none");
const std::string path_contribution_as_directories("as_directories");
const std::string path_contribution_as_path_components("as_path_components");

const std::string content_attr_name("content");
const std::string stitch_template_content_attr_name("stitch_template_content");

const std::string empty_string("String is empty but expected value.");
const std::string non_empty_string(
    "String is not empty but did not expect value: ");
const std::string non_empty_attributes("Element does not support attributes: ");
const std::string enumerator_with_type("Enumerators cannot have a type: ");
const std::string unsupported_attribute("Attribute is not supported: ");
const std::string unsupported_value("Unsupported attribute value: ");

/**
 * The notion of "container" for this particular flag refers to
 * meta-model elements that can contain other meta-model elements
 * (e.g. namespaces), not of objects that can contain other objects,
 * hence why is_container is always false.
 */
const bool is_meta_container(true);
const bool not_meta_container(false);

}

namespace dogen::orchestration::helpers {

using identification::entities::logical_id;
using identification::entities::logical_name;
using identification::entities::logical_location;
using identification::helpers::logical_name_factory;
using identification::helpers::logical_name_builder;
using logical::entities::stereotypes;
using logical::entities::decoration::modeline_field;
using logical::entities::decoration::modeline_group;
using logical::entities::decoration::modeline;
using logical::entities::decoration::generation_marker;
using logical::entities::decoration::licence;

bool str_to_bool(const std::string& s) {
    if (s == true_value) return true;
    if (s == false_value) return false;
    BOOST_LOG_SEV(lg, error) << unsupported_value << s;
    BOOST_THROW_EXCEPTION(projection_error(unsupported_value + s));
}

void codec_to_logical_projector::ensure_not_empty(const std::string& s) const {
    if (!s.empty())
        return;

    BOOST_LOG_SEV(lg, error) << empty_string;
    BOOST_THROW_EXCEPTION(projection_error(empty_string));
}

void codec_to_logical_projector::
ensure_not_empty(const logical_id& element_id, const std::string& s) const {
    if (!s.empty())
        return;

    std::ostringstream os;
    os << empty_string << " Element: " << element_id;

    const std::string msg(os.str());
    BOOST_LOG_SEV(lg, error) << msg;
    BOOST_THROW_EXCEPTION(projection_error(msg));
}

void codec_to_logical_projector::ensure_not_empty(const logical_id& element_id,
    const identification::entities::name& n) const {
    ensure_not_empty(element_id, n.simple());
    ensure_not_empty(element_id, n.qualified());
}

void codec_to_logical_projector::
ensure_empty(const logical_id& element_id, const std::string& s) const {
    if (s.empty())
        return;

    std::ostringstream os;
    os << non_empty_string << "'" << s << "' Element: " << element_id;

    const std::string msg(os.str());
    BOOST_LOG_SEV(lg, error) << msg;
    BOOST_THROW_EXCEPTION(projection_error(msg));
}

void codec_to_logical_projector::ensure_empty(const logical_id& element_id,
    const std::list<codec::entities::attribute>& cattrs) const {
    if (cattrs.empty())
        return;

    std::ostringstream os;
    os << non_empty_attributes << element_id;

    const std::string msg(os.str());
    BOOST_LOG_SEV(lg, error) << msg;
    BOOST_THROW_EXCEPTION(projection_error(msg));
}

std::list<variability::entities::potential_binding>
codec_to_logical_projector::to_potential_binding(
    const std::list<identification::entities::stereotype>& sts) const {
    std::list<variability::entities::potential_binding> r;
    for (const auto& st : sts) {
        variability::entities::potential_binding pb;
        pb.name(st.value());
        pb.realized(false);
        r.push_back(pb);
    }
    return r;
}

logical_name codec_to_logical_projector::
to_name(const std::string& n, const bool is_container) const {
    ensure_not_empty(n);

    /*
     * Names are expected to be delimited by the scope operator,
     * denoting internal modules. The head of the list is the simple
     * name, and the remaining are the internal modules.
     */
    auto tokens(utility::string::splitter::split_scoped(n));
    logical_name_builder b;
    b.is_container(is_container);
    b.simple_name(tokens.back());

    tokens.pop_back();
    if (!tokens.empty())
        b.internal_modules(tokens);

    return b.build();
}

logical_name codec_to_logical_projector::to_name(const logical_location& l,
    const std::string& n, const bool is_container) const {
    ensure_not_empty(n);
    BOOST_LOG_SEV(lg, debug) << "Location: " << l;

    /*
     * Names are expected to be delimited by the scope operator,
     * denoting internal modules. The head of the list is the simple
     * name, and the remaining are the internal modules.
     */
    auto tokens(utility::string::splitter::split_scoped(n));
    logical_name_builder b;
    b.is_container(is_container);
    b.simple_name(tokens.back());

    tokens.pop_back();
    if (!tokens.empty())
        b.internal_modules(tokens);

    /*
     * Copy the remaining properties from the location.
     */
    b.external_modules(l.external_modules());
    b.model_modules(l.model_modules());

    return b.build();
}

modeline_field
codec_to_logical_projector::to_modeline_field(const logical_name& owner,
    const codec::entities::attribute& cattr) const {
    ensure_not_empty(owner.id(), cattr.name());

    modeline_field r;
    r.name(cattr.name().simple());
    r.value(cattr.value());
    return r;
}

logical::entities::attribute
codec_to_logical_projector::to_attribute(const logical_name& owner,
    const codec::entities::attribute& cattr) const {
    BOOST_LOG_SEV(lg, debug) << "Reading attribute for: " << owner.id().value();
    ensure_not_empty(owner.id(), cattr.name());

    BOOST_LOG_SEV(lg, debug) << "Attribute: " << cattr.name().simple();

    logical_name_factory f;
    logical::entities::attribute r;
    r.name(f.build_attribute_name(owner, cattr.name().simple()));
    r.member_variable_name(r.name().simple() + member_variable_postfix);
    r.getter_setter_name(r.name().simple());

    r.unparsed_type(cattr.type());
    r.documentation(cattr.comment().documentation());

    r.configuration(cattr.configuration());
    r.configuration()->name().qualified(r.name().qualified().dot());

    logical::helpers::stereotypes_helper h;
    const auto sts(h.from_primitives(cattr.stereotypes()));
    const auto& ds(sts.dynamic_stereotypes());
    r.configuration()->profile_bindings(to_potential_binding(ds));

    return r;
}

logical::entities::structural::enumerator
codec_to_logical_projector::to_enumerator(const logical_name& owner,
    const codec::entities::attribute& cattr) const {
    ensure_not_empty(owner.id(), cattr.name());

    if (!cattr.type().empty()) {
        const auto t(cattr.type());
        BOOST_LOG_SEV(lg, error) << enumerator_with_type << t;
        BOOST_THROW_EXCEPTION(projection_error(enumerator_with_type + t));
    }

    logical_name_factory f;
    logical::entities::structural::enumerator r;
    r.name(f.build_attribute_name(owner, cattr.name().simple()));
    r.documentation(cattr.comment().documentation());

    r.configuration(cattr.configuration());
    r.configuration()->name().qualified(r.name().qualified().dot());

    logical::helpers::stereotypes_helper h;
    const auto sts(h.from_primitives(cattr.stereotypes()));
    const auto& ds(sts.dynamic_stereotypes());
    r.configuration()->profile_bindings(to_potential_binding(ds));

    return r;
}

void codec_to_logical_projector::populate_element(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce,
    const bool is_container, logical::entities::element& e) const {
    /*
     * Ensure we populate the configuration before we attempt to read
     * any meta-data from it. We take the dynamic stereotypes and
     * populate the potential bindings with it; these are stereotypes
     * that are not well-known so its likely they are referring to
     * profiles. Subsequent transforms in the logical model will
     * confirm if these potential bindings are actual bindings.
     */
    e.configuration(ce.configuration());
    const auto& ds(sts.dynamic_stereotypes());
    e.configuration()->profile_bindings(to_potential_binding(ds));
    e.name(to_name(l, ce.name().qualified(), is_container));
    e.configuration()->name().qualified(e.name().qualified().dot());

    /*
     * Next populate the static stereotypes. Note that we are not
     * populating the dynamic stereotypes at the element level here,
     * though we did do them for the configuration above. This is
     * because for elements they require more complex transforms,
     * which are done in the logical model chains.
     */
    e.stereotypes().static_stereotypes(sts.static_stereotypes());

    /*
     * Finally, populate all other attributes.
     */
    const auto& em(l.external_modules());
    const auto& mm(l.model_modules());
    e.in_global_module(em.empty() && mm.empty());
    e.provenance(ce.provenance());
    e.documentation(ce.comment().documentation());
}

boost::shared_ptr<logical::entities::structural::object>
codec_to_logical_projector::to_object(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming codec element to object: "
                             << ce.name().qualified();

    auto r(boost::make_shared<logical::entities::structural::object>());
    populate_element(l, sts, ce, not_meta_container, *r);

    r->is_associative_container(ce.is_associative_container());
    r->can_be_primitive_underlier(ce.can_be_primitive_underlier());

    for (const auto& attr : ce.attributes())
        r->local_attributes().push_back(to_attribute(r->name(), attr));

    for (const auto& p : ce.parents())
        r->parents().push_back(to_name(l, p, not_meta_container));

    return r;
}

boost::shared_ptr<logical::entities::structural::object_template>
codec_to_logical_projector::to_object_template(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming codec element "
                             << "to object template: " << ce.name().qualified();

    using logical::entities::structural::object_template;
    auto r(boost::make_shared<object_template>());
    populate_element(l, sts, ce, not_meta_container, *r);

    for (const auto& cattr : ce.attributes())
        r->local_attributes().push_back(to_attribute(r->name(), cattr));

    for (const auto& cp : ce.parents())
        r->parents().push_back(to_name(l, cp, false/*is_container*/));

    return r;
}

boost::shared_ptr<logical::entities::structural::exception>
codec_to_logical_projector::to_exception(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming codec element to exception: "
                             << ce.name().qualified();

    auto r(boost::make_shared<logical::entities::structural::exception>());
    populate_element(l, sts, ce, not_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<logical::entities::structural::primitive>
codec_to_logical_projector::to_primitive(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming codec element to primitive: "
                             << ce.name().qualified();

    auto r(boost::make_shared<logical::entities::structural::primitive>());
    populate_element(l, sts, ce, not_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<logical::entities::structural::enumeration>
codec_to_logical_projector::to_enumeration(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming codec element to enumeration: "
                             << ce.name().qualified();

    auto r(boost::make_shared<logical::entities::structural::enumeration>());
    populate_element(l, sts, ce, not_meta_container, *r);

    for (const auto& attr : ce.attributes())
        r->enumerators().push_back(to_enumerator(r->name(), attr));

    return r;
}

boost::shared_ptr<logical::entities::structural::module>
codec_to_logical_projector::to_module(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming codec element to module: "
                             << ce.name().qualified();

    auto r(boost::make_shared<logical::entities::structural::module>());
    populate_element(l, sts, ce, is_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<logical::entities::structural::builtin>
codec_to_logical_projector::to_builtin(const logical_location& l,
    const stereotypes& sts,
    const codec::entities::element& ce) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming codec element to builtin: "
                             << ce.name().qualified();

    auto r(boost::make_shared<logical::entities::structural::builtin>());
    populate_element(l, sts, ce, not_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());

    r->can_be_primitive_underlier(ce.can_be_primitive_underlier());
    r->is_default_enumeration_type(ce.is_default_enumeration_type());
    r->is_floating_point(ce.is_floating_point());
    r->can_be_enumeration_underlier(ce.can_be_enumeration_underlier());

    return r;
}

boost::shared_ptr<logical::entities::structural::entry_point>
codec_to_logical_projector::to_entry_point(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming codec element to exception: "
                             << ce.name().qualified();

    auto r(boost::make_shared<logical::entities::structural::entry_point>());
    populate_element(l, sts, ce, not_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<logical::entities::structural::assistant>
codec_to_logical_projector::to_assistant(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming codec element to assistant: "
                             << ce.name().qualified();

    auto r(boost::make_shared<logical::entities::structural::assistant>());
    populate_element(l, sts, ce, not_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<modeline_group>
codec_to_logical_projector::to_modeline_group(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    auto r(boost::make_shared<modeline_group>());
    populate_element(l, sts, ce, is_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<modeline>
codec_to_logical_projector::to_modeline(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    auto r(boost::make_shared<modeline>());
    populate_element(l, sts, ce, not_meta_container, *r);

    for (const auto& cattr : ce.attributes())
        r->fields().push_back(to_modeline_field(r->name(), cattr));

    return r;
}

boost::shared_ptr<generation_marker>
codec_to_logical_projector::to_generation_marker(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    auto r(boost::make_shared<generation_marker>());
    populate_element(l, sts, ce, not_meta_container, *r);

    for (const auto& cattr : ce.attributes()) {
        ensure_not_empty(r->name().id(), cattr.name());
        const auto n(cattr.name().simple());

        const auto t(cattr.type());
        ensure_empty(r->name().id(), t);

        const auto v(cattr.value());
        if (n == add_date_time_attr_name)
            r->add_date_time(str_to_bool(v));
        else if (n == add_dogen_version_attr_name)
            r->add_dogen_version(str_to_bool(v));
        else if (n == add_model_to_text_transform_details_attr_name)
            r->add_model_to_text_transform_details(str_to_bool(v));
        else if (n == add_warning_attr_name)
            r->add_warning(str_to_bool(v));
        else if (n == add_message_attr_name)
            r->message(cattr.comment().documentation());
        else if (n == add_origin_sha1_hash_attr_name)
            r->add_origin_sha1_hash(str_to_bool(v));
        else {
            BOOST_LOG_SEV(lg, error) << unsupported_attribute << n;
            BOOST_THROW_EXCEPTION(
                projection_error(unsupported_attribute + n));
        }
    }

    return r;
}

boost::shared_ptr<licence>
codec_to_logical_projector::to_licence(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    auto r(boost::make_shared<licence>());
    populate_element(l, sts, ce, not_meta_container, *r);

    for (const auto& cattr : ce.attributes()) {
        ensure_not_empty(r->name().id(), cattr.name());

        const auto n(cattr.name().simple());
        ensure_not_empty(r->name().id(), n);

        if (n == short_form_attr_name)
            r->short_form(cattr.comment().documentation());
        else if (n == long_form_attr_name)
            r->long_form(cattr.comment().documentation());
        else {
            BOOST_LOG_SEV(lg, error) << unsupported_attribute << n;
            BOOST_THROW_EXCEPTION(projection_error(unsupported_attribute + n));
        }
    }

    return r;
}

void codec_to_logical_projector::populate_abstract_profile(
    const logical_location& l, const codec::entities::element& ce,
    logical::entities::variability::abstract_profile& ap) const {
    for (const auto& p : ce.parents())
        ap.parents().push_back(to_name(l, p, not_meta_container));
}

void codec_to_logical_projector::populate_abstract_feature(
    const logical_name& bundle_name, const codec::entities::attribute& cattr,
    logical::entities::variability::abstract_feature& af) const {
    ensure_not_empty(bundle_name.id(), cattr.name());
    const auto n(cattr.name().simple());

    logical_name_factory f;
    af.name(f.build_attribute_name(bundle_name, n));
    af.original_key(n);
    af.default_value(cattr.value());
    af.unparsed_type(cattr.type());
    af.documentation(cattr.comment().documentation());

    using variability::helpers::enum_mapper;
    af.value_type(enum_mapper::to_value_type(cattr.type()));
    af.configuration(cattr.configuration());
    af.configuration()->name().qualified(af.name().qualified().dot());
}

void codec_to_logical_projector::
populate_abstract_profile_entry(const logical_name& pn,
    const codec::entities::attribute& cattr,
    logical::entities::variability::abstract_profile_entry& ape) const {
    ensure_not_empty(pn.id(), cattr.name());

    logical_name_factory f;
    const auto n(cattr.name().simple());

    /*
     * The conventions for naming profile entries are somewhat
     * confusing. The "qualified" name of a profile entry must match
     * the qualified name of the feature it is configuring, e.g.:
     *
     *     masd.generalization.parent
     *
     * The "qualified" name of the profile entry reflects its position
     * in logical space, and as such is composed of the logical
     * element that owns the profile entry (the profile):
     *
     *     dogen.cpp_artefact_transform
     *
     * Concatenated with the qualified name, e.g.:
     *
     *     dogen.cpp_artefact_transform.masd.generalization.parent
     *
     * Whilst this may not be exactly the most aesthetically
     * pleasing approach, it is more or less compliant with the
     * conceptual model for the logical space. It also makes it
     * really easy to find out where a configuration came from,
     * when we are looking at a configuration model
     * representation.
     */
    ape.name(f.build_attribute_name(pn, n));
    ape.original_key(n);
    ape.configuration(cattr.configuration());
    ape.configuration()->name().qualified(ape.name().qualified().dot());
    if (!cattr.value().empty())
        ape.value().push_back(cattr.value());
}

boost::shared_ptr<logical::entities::variability::profile>
codec_to_logical_projector::to_variability_profile(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::variability::profile;
    auto r(boost::make_shared<profile>());
    populate_element(l, sts, ce, not_meta_container, *r);
    populate_abstract_profile(l, ce, *r);

    for (const auto& cattr : ce.attributes()) {
        logical::entities::variability::profile_entry e;
        populate_abstract_profile_entry(r->name(), cattr, e);
        r->entries().push_back(e);
    }
    return r;
}

boost::shared_ptr<logical::entities::variability::profile_template>
codec_to_logical_projector::to_variability_profile_template(
    const logical_location& l, const stereotypes& sts,
    const codec::entities::element& ce) const {
    using logical::entities::variability::profile_template;
    auto r(boost::make_shared<profile_template>());
    populate_element(l, sts, ce, not_meta_container, *r);
    populate_abstract_profile(l, ce, *r);

    for (const auto& cattr : ce.attributes()) {
        logical::entities::variability::profile_template_entry e;
        populate_abstract_profile_entry(r->name(), cattr, e);
        r->entries().push_back(e);
    }

    return r;
}

boost::shared_ptr<logical::entities::variability::feature_template_bundle>
codec_to_logical_projector::to_variability_feature_template_bundle(
    const logical_location& l, const stereotypes& sts,
    const codec::entities::element& ce) const {
    using logical::entities::variability::feature_template_bundle;
    auto r(boost::make_shared<feature_template_bundle>());
    populate_element(l, sts, ce, not_meta_container, *r);

    for (const auto& cattr : ce.attributes()) {
        logical::entities::variability::feature_template ft;
        populate_abstract_feature(r->name(), cattr, ft);
        r->feature_templates().push_back(ft);
    }

    return r;
}

boost::shared_ptr<logical::entities::variability::feature_bundle>
codec_to_logical_projector::to_variability_feature_bundle(
    const logical_location& l, const stereotypes& sts,
    const codec::entities::element& ce) const {
    using logical::entities::variability::feature_bundle;
    auto r(boost::make_shared<feature_bundle>());
    populate_element(l, sts, ce, not_meta_container, *r);

    for (const auto& cattr : ce.attributes()) {
        logical::entities::variability::feature f;
        populate_abstract_feature(r->name(), cattr, f);
        r->features().push_back(f);
    }

    return r;
}

boost::shared_ptr<logical::entities::variability::initializer>
codec_to_logical_projector::
to_variability_initializer(const logical_location& l,
    const stereotypes& sts, const codec::entities::element &ce) const {
    using logical::entities::variability::initializer;
    auto r(boost::make_shared<initializer>());
    populate_element(l, sts, ce, not_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<logical::entities::mapping::fixed_mappable>
codec_to_logical_projector::to_fixed_mappable(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::mapping::fixed_mappable;
    auto r(boost::make_shared<fixed_mappable>());
    populate_element(l, sts, ce, not_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<logical::entities::mapping::extensible_mappable>
codec_to_logical_projector::to_extensible_mappable(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::mapping::extensible_mappable;
    auto r(boost::make_shared<extensible_mappable>());
    populate_element(l, sts, ce, not_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<logical::entities::templating::logic_less_template>
codec_to_logical_projector::to_logic_less_template(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::templating::logic_less_template;
    auto r(boost::make_shared<logic_less_template>());
    populate_element(l, sts, ce, not_meta_container, *r);

    for (const auto& cattr : ce.attributes()) {
        ensure_not_empty(r->name().id(), cattr.name());
        const auto n(cattr.name().simple());

        if (n == content_attr_name)
            r->content(cattr.comment().documentation());
        else {
            BOOST_LOG_SEV(lg, error) << unsupported_attribute << n;
            BOOST_THROW_EXCEPTION(
                projection_error(unsupported_attribute + n));
        }
    }

    return r;
}

boost::shared_ptr<logical::entities::serialization::type_registrar>
codec_to_logical_projector::to_type_registrar(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::serialization::type_registrar;
    auto r(boost::make_shared<type_registrar>());
    populate_element(l, sts, ce, not_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<logical::entities::visual_studio::solution>
codec_to_logical_projector::to_visual_studio_solution(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::visual_studio::solution;
    auto r(boost::make_shared<solution>());
    populate_element(l, sts, ce, not_meta_container, *r);

    for (const auto& cattr : ce.attributes()) {
        ensure_not_empty(r->name().id(), cattr.name());
        const auto n(cattr.name().simple());

        const auto v(cattr.value());
        if (n == guid_attr_name)
            r->guid(v);
        else {
            BOOST_LOG_SEV(lg, error) << unsupported_attribute << n;
            BOOST_THROW_EXCEPTION(
                projection_error(unsupported_attribute + n));
        }
    }

    return r;
}

boost::shared_ptr<logical::entities::visual_studio::project>
codec_to_logical_projector::to_visual_studio_project(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::visual_studio::project;
    auto r(boost::make_shared<project>());
    populate_element(l, sts, ce, not_meta_container, *r);

    for (const auto& cattr : ce.attributes()) {
        ensure_not_empty(r->name().id(), cattr.name());
        const auto n(cattr.name().simple());

        const auto v(cattr.value());
        if (n == guid_attr_name)
            r->guid(v);
        else {
            BOOST_LOG_SEV(lg, error) << unsupported_attribute << n;
            BOOST_THROW_EXCEPTION(
                projection_error(unsupported_attribute + n));
        }
    }

    return r;
}

boost::shared_ptr<logical::entities::visual_studio::msbuild_targets>
codec_to_logical_projector::
to_visual_studio_msbuild_targets(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::visual_studio::msbuild_targets;
    auto r(boost::make_shared<msbuild_targets>());
    populate_element(l, sts, ce, not_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<logical::entities::orm::common_odb_options>
codec_to_logical_projector::to_orm_common_odb_options(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::orm::common_odb_options;
    auto r(boost::make_shared<common_odb_options>());
    populate_element(l, sts, ce, not_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<logical::entities::build::cmakelists>
codec_to_logical_projector::to_build_cmakelists(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::build::cmakelists;
    auto r(boost::make_shared<cmakelists>());
    populate_element(l, sts, ce, not_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<logical::entities::physical::backend>
codec_to_logical_projector::to_physical_backend(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::physical::backend;
    auto r(boost::make_shared<backend>());
    populate_element(l, sts, ce, is_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<logical::entities::physical::facet>
codec_to_logical_projector::to_physical_facet(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::physical::facet;
    auto r(boost::make_shared<facet>());
    populate_element(l, sts, ce, is_meta_container, *r);
    ensure_empty(r->name().id(), ce.attributes());
    return r;
}

boost::shared_ptr<logical::entities::physical::archetype>
codec_to_logical_projector::to_physical_archetype(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::physical::archetype;
    auto r(boost::make_shared<archetype>());
    populate_element(l, sts, ce, not_meta_container, *r);

    for (const auto& cattr : ce.attributes()) {
        const auto id(r->name().id());
        ensure_not_empty(id, cattr.name());
        const auto n(cattr.name().simple());

        if (n != stitch_template_content_attr_name) {
            BOOST_LOG_SEV(lg, error) << unsupported_attribute << n;
            BOOST_THROW_EXCEPTION(
                projection_error(unsupported_attribute + n));
        }

        auto& tt(r->text_templating());
        tt.stitch_template_content(cattr.comment().documentation());
        tt.configuration(cattr.configuration());

        auto& cfg(*tt.configuration());
        cfg.name().qualified(r->name().qualified().dot());

        logical::helpers::stereotypes_helper h;
        const auto sts(h.from_primitives(cattr.stereotypes()));
        const auto& ds(sts.dynamic_stereotypes());
        cfg.profile_bindings(to_potential_binding(ds));
    }

    return r;
}

boost::shared_ptr<logical::entities::physical::archetype_kind>
codec_to_logical_projector::to_physical_archetype_kind(
    const logical_location& l, const stereotypes& sts,
    const codec::entities::element& ce) const {
    using logical::entities::physical::archetype_kind;
    auto r(boost::make_shared<archetype_kind>());
    populate_element(l, sts, ce, not_meta_container, *r);

    for (const auto& cattr : ce.attributes()) {
        ensure_not_empty(r->name().id(), cattr.name());
        const auto n(cattr.name().simple());

        const auto v(cattr.value());
        if (n == file_extension_name)
            r->file_extension(v);
        else {
            BOOST_LOG_SEV(lg, error) << unsupported_attribute << n;
            BOOST_THROW_EXCEPTION(
                projection_error(unsupported_attribute + n));
        }
    }

    return r;
}

boost::shared_ptr<logical::entities::physical::part>
codec_to_logical_projector::to_physical_part(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::physical::part;
    auto r(boost::make_shared<part>());
    populate_element(l, sts, ce, not_meta_container, *r);

    const std::string path_contribution_none("none");
    const std::string path_contribution_as_directories("as_directories");
    const std::string
        path_contribution_as_path_components("as_path_components");

    const auto is_valid_path_contribution([&](const std::string& s) {
            const bool is_valid(s == path_contribution_none ||
                s == path_contribution_as_directories ||
                s == path_contribution_as_path_components);

            if (is_valid)
                return;

            BOOST_LOG_SEV(lg, error) << unsupported_value << s;
            BOOST_THROW_EXCEPTION(projection_error(unsupported_value + s));
        });

    const auto id(r->name().id());
    for (const auto& cattr : ce.attributes()) {
        ensure_not_empty(r->name().id(), cattr.name());
        const auto n(cattr.name().simple());

        const auto t(cattr.type());
        ensure_empty(id, t);

        const auto v(cattr.value());
        if (n == external_modules_path_contribution_name) {
            ensure_not_empty(id, v);
            is_valid_path_contribution(v);
            r->external_modules_path_contribution(v);
        } else if (n == model_modules_path_contribution_name) {
            ensure_not_empty(id, v);
            is_valid_path_contribution(v);
            r->model_modules_path_contribution(v);
        } else if (n == facet_path_contribution_name) {
            ensure_not_empty(id, v);
            is_valid_path_contribution(v);
            r->facet_path_contribution(v);
        } else if (n == internal_modules_path_contribution_name) {
            ensure_not_empty(id, v);
            is_valid_path_contribution(v);
            r->internal_modules_path_contribution(v);
        } else if (n == requires_relative_path_name) {
            ensure_not_empty(id, v);
            r->requires_relative_path(str_to_bool(v));
        } else if (n == directory_name_name) {
            /*
             * Part may have an empty directory, for now.
             */
            r->directory_name(v);
        } else {
            BOOST_LOG_SEV(lg, error) << unsupported_attribute << n;
            BOOST_THROW_EXCEPTION(
                projection_error(unsupported_attribute + n));
        }
    }

    return r;
}

boost::shared_ptr<logical::entities::physical::helper>
codec_to_logical_projector::to_physical_helper(const logical_location& l,
    const stereotypes& sts, const codec::entities::element& ce) const {
    using logical::entities::physical::helper;
    auto r(boost::make_shared<helper>());
    populate_element(l, sts, ce, not_meta_container, *r);

    const auto id(r->name().id());
    for (const auto& cattr : ce.attributes()) {
        ensure_not_empty(r->name().id(), cattr.name());
        const auto n(cattr.name().simple());

        const auto t(cattr.type());
        ensure_empty(id, t);

        const auto id(r->name().id());
        ensure_not_empty(id, n);

        if (n != stitch_template_content_attr_name) {
            BOOST_LOG_SEV(lg, error) << unsupported_attribute << n;
            BOOST_THROW_EXCEPTION(
                projection_error(unsupported_attribute + n));
        }

        auto& tt(r->text_templating());
        tt.stitch_template_content(cattr.comment().documentation());
        tt.configuration(cattr.configuration());

        auto& cfg(*tt.configuration());
        cfg.name().qualified(r->name().qualified().dot());

        logical::helpers::stereotypes_helper h;
        const auto sts(h.from_primitives(cattr.stereotypes()));
        const auto& ds(sts.dynamic_stereotypes());
        cfg.profile_bindings(to_potential_binding(ds));
    }

    return r;
}

}
