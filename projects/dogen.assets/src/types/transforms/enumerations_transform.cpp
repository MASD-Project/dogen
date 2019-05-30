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
#include <ostream>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.assets/lexical_cast/meta_model/technical_space_lc.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/types/traits.hpp"
#include "dogen.assets/types/features/enumeration.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/meta_model/structural/builtin.hpp"
#include "dogen.assets/types/meta_model/structural/enumeration.hpp"
#include "dogen.assets/types/meta_model/structural/enumeration.hpp"
#include "dogen.assets/types/helpers/name_factory.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/transforms/enumerations_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.enumerations_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string csharp_invalid("Invalid");
const std::string cpp_invalid("invalid");

const std::string unsupported_technical_space(
    "Invalid or unsupported technical space: ");
const std::string too_many_defaults(
    "Model has more than one default enumeration: ");
const std::string missing_default(
    "Model does not have a default enumeration type: ");

}

namespace dogen::assets::transforms {

enumerations_transform::enumeration_feature_group
enumerations_transform::make_enumeration_feature_group(
    const variability::meta_model::feature_model& fm) {
    BOOST_LOG_SEV(lg, debug) << "Creating enumeration feature group.";

    enumeration_feature_group r;
    const variability::helpers::feature_selector s(fm);

    using en = traits::enumeration;
    const auto uidue(en::use_implementation_defined_underlying_element());
    r.use_implementation_defined_underlying_element =
        s.get_by_name(uidue);

    const auto uidev(en::use_implementation_defined_enumerator_values());
    r.use_implementation_defined_enumerator_values =
        s.get_by_name(uidev);

    const auto aie(en::add_invalid_enumerator());
    r.add_invalid_enumerator = s.get_by_name(aie);

    BOOST_LOG_SEV(lg, debug) << "Created enumeration feature group.";
    return r;
}

enumerations_transform::enumerator_feature_group
enumerations_transform::make_enumerator_feature_group(
    const variability::meta_model::feature_model& fm) {
    BOOST_LOG_SEV(lg, debug) << "Creating enumerator feature group.";

    enumerator_feature_group r;
    const variability::helpers::feature_selector s(fm);
    r.value = s.get_by_name(traits::enumerator::value());

    BOOST_LOG_SEV(lg, debug) << "Created enumerator feature group.";
    return r;
}

enumerations_transform::feature_group enumerations_transform::
make_feature_group(const variability::meta_model::feature_model& fm) {
    BOOST_LOG_SEV(lg, debug) << "Creating feature group.";

    feature_group r;
    r.enumeration = make_enumeration_feature_group(fm);
    r.enumerator = make_enumerator_feature_group(fm);

    BOOST_LOG_SEV(lg, debug) << "Created feature group.";
    return r;
}

void enumerations_transform::
populate_from_configuration(const enumeration_feature_group& fg,
    meta_model::structural::enumeration& e) {

    const auto& cfg(*e.configuration());
    const variability::helpers::configuration_selector s(cfg);
    const auto uidue(fg.use_implementation_defined_underlying_element);
    e.use_implementation_defined_underlying_element(
        s.get_boolean_content_or_default(uidue));

    const auto uidev(fg.use_implementation_defined_enumerator_values);
    e.use_implementation_defined_enumerator_values(
        s.get_boolean_content_or_default(uidev));

    const auto aie(fg.add_invalid_enumerator);
    e.add_invalid_enumerator(s.get_boolean_content_or_default(aie));
}

void enumerations_transform::populate_from_configuration(
    const enumerator_feature_group& fg, meta_model::structural::enumerator& e) {
    const auto& cfg(*e.configuration());
    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.value)) {
        e.value(s.get_text_content(fg.value));
        BOOST_LOG_SEV(lg, debug) << "Read enumerator value: " << e.value();
    }
}

meta_model::name enumerations_transform::
obtain_enumeration_default_underlying_element_name(const meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Obtaining default enumeration underlying "
                             << "element name for model: "
                             << m.name().qualified().dot();

    meta_model::name r;
    bool found(false);
    for (const auto& pair : m.structural_elements().builtins()) {
        const auto b(*pair.second);
        const auto id(b.name().qualified().dot());
        if (b.is_default_enumeration_type()) {
            BOOST_LOG_SEV(lg, debug) << "Found default enumeration underlying "
                                     << " element name:" << id;

            if (found) {
                BOOST_LOG_SEV(lg, error) << too_many_defaults << id;
                BOOST_THROW_EXCEPTION(
                    transformation_error(too_many_defaults + id));
            }
            found = true;
            r = b.name();
        }
    }

    if (!found) {
        const auto id(m.name().qualified().dot());
        BOOST_LOG_SEV(lg, error) << missing_default << id;
        BOOST_THROW_EXCEPTION(transformation_error(missing_default + id));
    }

    BOOST_LOG_SEV(lg, debug) << "Obtained default enumeration underlying "
                             << "element name for model. ";
    return r;
}

std::string enumerations_transform::
obtain_invalid_enumerator_simple_name(const meta_model::technical_space ts) {
    switch(ts) {
    case meta_model::technical_space::csharp: return csharp_invalid;
    case meta_model::technical_space::cpp: return cpp_invalid;
    default: {
        const auto s(boost::lexical_cast<std::string>(ts));
        BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
        BOOST_THROW_EXCEPTION(
            transformation_error(unsupported_technical_space + s));
    } }
}

meta_model::structural::enumerator
enumerations_transform::make_invalid_enumerator(const meta_model::name& n,
    const meta_model::technical_space l) {
    meta_model::structural::enumerator r;
    r.documentation("Represents an uninitialised enum");
    r.value("0");

    helpers::name_factory nf;
    const auto sn(obtain_invalid_enumerator_simple_name(l));
    r.name(nf.build_attribute_name(n, sn));

    return r;
}

void enumerations_transform::expand_default_underlying_element(
    const meta_model::name& default_underlying_element_name,
    meta_model::structural::enumeration& e) {
    const auto ue(e.underlying_element());
    BOOST_LOG_SEV(lg, debug) << "Underlying type: '"
                             << ue.qualified().dot() << "'";

    if (!ue.simple().empty())
        return;

    BOOST_LOG_SEV(lg, debug) << "Defaulting enumeration to type: "
                             << default_underlying_element_name.
        qualified().dot();
    e.underlying_element(default_underlying_element_name);
}

void enumerations_transform::
expand_enumerators(const enumerator_feature_group& fg,
    const meta_model::technical_space ts,
    meta_model::structural::enumeration& e) {
    std::vector<meta_model::structural::enumerator> enumerators;

    if (e.add_invalid_enumerator()) {
        enumerators.reserve(e.enumerators().size() + 1/*invalid*/);
        enumerators.push_back(make_invalid_enumerator(e.name(), ts));
    } else
        enumerators.reserve(e.enumerators().size());

    /*
     * Update the value of each enumerator, and ensure the enumerator
     * names are unique.
     */
    unsigned int pos(e.add_invalid_enumerator() ? 1 : 0);
    for (const auto& en : e.enumerators()) {
        const auto sn(en.name().simple());

        /*
         * We try to read the value from variability's
         * configuration. If its not populated we set it
         * ourselves. Note that it is validation's job to ensure the
         * user doesn't start mixing and matching, populating the
         * value for some enumerators but not others.
         */
        auto copy(en);
        populate_from_configuration(fg, copy);

        if (copy.value().empty())
            copy.value(boost::lexical_cast<std::string>(pos));

        enumerators.push_back(copy);
        ++pos;
    }
    e.enumerators(enumerators);
}

void enumerations_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "enumerations transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * If no enumerations exist, we can just exit. This means we can
     * still support models that have no dependencies, provided they
     * do not use enumerations. Otherwise, we'd fail when searching
     * for the default underlying element name.
     */
    if (m.structural_elements().enumerations().empty())
        return;

    const auto its(m.input_technical_space());
    const auto fg(make_feature_group(*ctx.feature_model()));
    const auto duen(obtain_enumeration_default_underlying_element_name(m));

    for (auto& pair : m.structural_elements().enumerations()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Expanding: " << id;

        auto& e(*pair.second);
        populate_from_configuration(fg.enumeration, e);
        expand_default_underlying_element(duen, e);
        expand_enumerators(fg.enumerator, its, e);
    }

    stp.end_transform(m);
}

}
