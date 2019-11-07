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
#include <utility>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/vector_io.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.injection/types/transforms/context.hpp"
#include "dogen.injection/io/meta_model/model_io.hpp"
#include "dogen.injection/types/transforms/transformation_error.hpp"
#include "dogen.injection/types/transforms/tagged_values_overrides_transform.hpp"

namespace {

const std::string
transform_id("injector.transforms.tagged_values_overrides_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string invalid_override("Invalid variability override: ");
const std::string empty_model_name("Model name cannot be empty: ");
const std::string invalid_attribute("Attribute name requires element name: ");
const std::string duplicate_override("Duplicate variability override: ");
const std::string multiple_elements("Element name matches multiple elements: ");
const std::string multiple_attributes(
    "Attribute name matches multiple elements: ");
const std::string override_not_applied("Override could not be applied: ");

}

namespace dogen::injection::transforms {

void tagged_values_overrides_transform::
apply(const transforms::context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "configuration transform",
        transform_id, m.name(), *ctx.tracer(), m);

    /*
     * If there are no variability overrides, there is nothing to do.
     */
    const auto& vos(ctx.variability_overrides());
    if (vos.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No variability overrides found.";
        return;
    }

    BOOST_LOG_SEV(lg, trace) << "Variability overrides: "
                             << ctx.variability_overrides();

    /*
     * Convert the CSV string into a set of tokens, and match those
     * tokens to modeling elements.
     */
    std::unordered_set<std::string> processed;
    using dogen::utility::string::splitter;
    for (const auto& vo : vos) {
      /*
       * A duplicate override probably implies the user is doing
       * something wrong (typo, etc.).
       */
        const auto inserted(processed.insert(vo).second);
        if (inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_override << vo;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_override + vo));
        }

        /*
         * Split the override into tokens. We expect precisely 5
         * tokens. Some of these may or may not be empty.
         */
        auto tokens(splitter::split_csv(vo));

        if (tokens.size() != 5) {
            BOOST_LOG_SEV(lg, error) << invalid_override << vo;
            BOOST_THROW_EXCEPTION(transformation_error(invalid_override + vo));
        }

        const auto model_name(tokens.front());
        tokens.pop_front();

        /*
         * Model name must not be empty.
         */
        if (model_name.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_model_name << vo;
            BOOST_THROW_EXCEPTION(transformation_error(empty_model_name + vo));
        }

        /*
         * If the model name does not match, we can ignore the override.
         */
        if (m.name() != model_name) {
            BOOST_LOG_SEV(lg, trace) << "Override does not apply to model."
                                     << " Model: " << m.name()
                                     << " Variability override model: "
                                     <<  model_name;
            continue;
        }

        const auto element_name(tokens.front());
        tokens.pop_front();
        const auto attribute_name(tokens.front());
        tokens.pop_front();

        if (element_name.empty()) {
            /*
             * If the element name is empty then the attribute name
             * must also be empty.
             */
            if (!attribute_name.empty()) {
                BOOST_LOG_SEV(lg, error) << invalid_attribute << vo;
                BOOST_THROW_EXCEPTION(
                    transformation_error(invalid_attribute + vo));
            }

            /*
             * Apply the override apply to the model itself.
             */
            const std::pair<std::string, std::string>
                pair({ tokens.front(), tokens.back() });
            m.tagged_values().push_back(pair);
            continue;
        }

        /*
         * Locate the element for this override, which must exist.
         */
        bool found(false);
        for (auto& e : m.elements()) {
          /*
           *  Only one element is expected to match.
           */
            if (e.name() == element_name) {
                if (found) {
                    BOOST_LOG_SEV(lg, error) << multiple_elements << vo;
                    BOOST_THROW_EXCEPTION(
                        transformation_error(multiple_elements + vo));
                }
            }

            /*
             * If we have no attribute name, the override is for the
             * element itself.
             */
            if (attribute_name.empty()) {
                found = true;
                const std::pair<std::string, std::string>
                    pair({ tokens.front(), tokens.back() });
                e.tagged_values().push_back(pair);
                continue;
            }

            /*
             * Locate the attribute for this override, which must exist.
             */
            for (auto& a : e.attributes()) {
                /*
                 *  Only one element is expected to match.
                 */
                if (a.name() == attribute_name) {
                    if (found) {
                        BOOST_LOG_SEV(lg, error) << multiple_attributes << vo;
                        BOOST_THROW_EXCEPTION(
                            transformation_error(multiple_attributes + vo));
                    }
                }

                /*
                 * If we have no attribute name, the override is for the
                 * element itself.
                 */
                found = true;
                const std::pair<std::string, std::string>
                    pair({ tokens.front(), tokens.back() });
                a.tagged_values().push_back(pair);
                continue;
            }
        }

        if (!found) {
            BOOST_LOG_SEV(lg, error) << override_not_applied << vo;
            BOOST_THROW_EXCEPTION(
                transformation_error(override_not_applied + vo));
        }
    }

    stp.end_transform(m);
    BOOST_LOG_SEV(lg, debug) << "Transformed model.";
}

}
