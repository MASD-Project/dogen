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
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/lexical_cast/entities/technical_space_lc.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/traits.hpp"
#include "dogen.logical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/helpers/name_builder.hpp"
#include "dogen.logical/types/features/enumeration.hpp"
#include "dogen.logical/types/features/enumerator.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/enumerations_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.enumerations_transform");

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

namespace dogen::logical::transforms {

namespace {

void populate_enumeration(const features::enumeration::feature_group& fg,
    const entities::name& default_underlying_element_name,
    entities::structural::enumeration& e) {

    /*
     * Create the static configuration from its dynamic counterpart
     * and populate the trivial top-level flags.
     */
    const auto scfg(features::enumeration::make_static_configuration(fg, e));
    e.use_implementation_defined_underlying_element(
        scfg.use_implementation_defined_underlying_element);

    e.use_implementation_defined_enumerator_values(
        scfg.use_implementation_defined_enumerator_values);

    e.add_invalid_enumerator(scfg.add_invalid_enumerator);

    /*
     * Now handle the underlying element. Use the name read from the
     * meta-data, if any.
     */
    if (!scfg.underlying_element.empty()) {
        /*
         * Convert the string obtained via meta-data into a logical name and
         * set it as our underlying element name.
         */
        const auto ue(helpers::name_builder::build(scfg.underlying_element));
        e.underlying_element(ue);
        return;
    }

    /*
     * Use the default element name supplied by the caller.
     */
    const auto& duen(default_underlying_element_name);
    BOOST_LOG_SEV(lg, debug) << "Using default underlying element '"
                             << duen.qualified().dot() << "'";

    e.underlying_element(duen);
}

void populate_enumerator(const features::enumerator::feature_group &fg,
                         const unsigned int position,
                         entities::structural::enumerator &e) {

  /*
   * We try to read the value from variability's configuration. If
   * its not populated we set it ourselves. Note that it is
   * validation's job to ensure the user doesn't start mixing and
   * matching, populating the value for some enumerators but not
   * others.
   */
  const auto scfg(features::enumerator::make_static_configuration(fg, e));
  if (scfg.value.empty())
    e.value(boost::lexical_cast<std::string>(position));
  else
    e.value(scfg.value);
}

}

entities::name enumerations_transform::
obtain_enumeration_default_underlying_element_name(const entities::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Obtaining default enumeration underlying "
                             << "element name for model: "
                             << m.name().qualified().dot();

    /*
     * Go through all the built-ins and find out which one was set to
     * be the default type to use for enumerations. We expect one and
     * only type to have been assigned this role.
     */
    entities::name r;
    bool found(false);
    for (const auto& pair : m.structural_elements().builtins()) {
        const auto& b(*pair.second);
        const auto& id(b.name().qualified().dot());
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

std::string
enumerations_transform::obtain_invalid_enumerator_simple_name(
    const identification::entities::technical_space ts) {
    using identification::entities::technical_space;
    switch(ts) {
    case technical_space::csharp: return csharp_invalid;
    case technical_space::cpp: return cpp_invalid;
    default: {
        const auto s(boost::lexical_cast<std::string>(ts));
        BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
        BOOST_THROW_EXCEPTION(
            transformation_error(unsupported_technical_space + s));
    } }
}

entities::structural::enumerator
enumerations_transform::make_invalid_enumerator(const entities::name& n,
    const identification::entities::technical_space ts) {
    entities::structural::enumerator r;
    r.documentation("Represents an uninitialised enum");
    r.value("0");

    helpers::name_factory nf;
    const auto sn(obtain_invalid_enumerator_simple_name(ts));
    r.name(nf.build_attribute_name(n, sn));

    using variability::entities::configuration;
    r.configuration(boost::make_shared<configuration>());

    return r;
}

void enumerations_transform::apply(const context& ctx, entities::model& m) {
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

    /*
     * Start by creating the feature groups with all features needed
     * by both enumerations and enumerators.
     */
    const auto& fm(*ctx.feature_model());
    const auto fg1(features::enumeration::make_feature_group(fm));
    const auto fg2(features::enumerator::make_feature_group(fm));

    /*
     * Now we obtain the default underlying element for all
     * enumerations in this model. This will be used, unless the
     * enumeration has decided to override it.
     */
    const auto duen(obtain_enumeration_default_underlying_element_name(m));

    /*
     * Process each enumeration and their enumerators.
     */
    const auto its(m.input_technical_space());
    for (auto& pair : m.structural_elements().enumerations()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing: " << id;

        /*
         * Read all properties for this enumeration that are stored in
         * the dynamic configuration.
         */
        auto& e(*pair.second);
        populate_enumeration(fg1, duen, e);

        /*
         * If the enumeration requested it, create a special
         * enumerator to represent the "invalid" state.
         */
        if (e.add_invalid_enumerator())
            e.enumerators().push_front(make_invalid_enumerator(e.name(), its));

        /*
         * Now process all enumerators. This is mainly concerned with
         * either reading the enumerator value from its dynamic
         * configuration, or, if not supplied, populating it from our
         * position counter.
         */
        unsigned int position(0);
        for (auto& en : e.enumerators())
            populate_enumerator(fg2, position++, en);
    }

    stp.end_transform(m);
}

}
