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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.org/types/entities/drawer_type.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.org/io/entities/drawer_type_io.hpp"
#include "dogen.org/types/transforms/string_to_document_transform.hpp"
#include "dogen.codec/io/entities/model_io.hpp"
#include "dogen.codec/io/entities/artefact_io.hpp"
#include "dogen.codec/types/transforms/transformation_error.hpp"
#include "dogen.codec/types/transforms/org_artefact_to_model_transform.hpp"

namespace {

const std::string
transform_id("codec.transforms.org_artefact_to_model_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string unexpected_number_of_drawers(
    "Unexpected number of drawers: ");
const std::string unexpected_drawer_type("Unexpected drawer type: ");
const std::string invalid_property("Property is missing key or value.");

}

namespace dogen::codec::transforms {

using identification::entities::tagged_value;
using org::entities::drawer_type;

std::list<tagged_value> org_artefact_to_model_transform::
read_tagged_values(const std::list<org::entities::drawer>& drawers) {
    /*
     * Org models are expected to have exactly one property
     * drawer. Ensure that's the case and read its contents.
     */
    const auto sz(drawers.size());
    if (sz != 1) {
        BOOST_LOG_SEV(lg, error) << unexpected_number_of_drawers << sz;
        BOOST_THROW_EXCEPTION(
            transformation_error(unexpected_number_of_drawers +
                boost::lexical_cast<std::string>(sz)));
    }

    const auto& drawer(drawers.front());
    if (drawer.type() != drawer_type::property_drawer) {
        BOOST_LOG_SEV(lg, error) << unexpected_drawer_type << drawer.type();
        BOOST_THROW_EXCEPTION(
            transformation_error(unexpected_drawer_type +
                boost::lexical_cast<std::string>(drawer.type())));
    }

    std::list<tagged_value> r;
    for (const auto& dc : drawer.contents()) {
        /*
         * Properties are expected to have both key and value.
         */
        if (dc.key().empty() || dc.value().empty()) {
            BOOST_LOG_SEV(lg, error) << invalid_property << "Key: '"
                                     << dc.key() << "' Value: '"
                                     << dc.value() << "'";
            BOOST_THROW_EXCEPTION(
                transformation_error(invalid_property));
        }

        tagged_value tv;
        tv.tag(dc.key());
        tv.value(dc.value());
        r.push_back(tv);
    }
    return r;
}

entities::model org_artefact_to_model_transform::
apply(const transforms::context& ctx, const entities::artefact& a) {
    const auto fn(a.path().filename().stem().generic_string());
    const auto t(ctx.tracer());
    tracing::scoped_transform_tracer stp(lg, "org artefact to model",
        transform_id, fn, *t, a);

    BOOST_LOG_SEV(lg, debug) << "Processing org-mode document.";
    using org::transforms::string_to_document_transform;
    const auto doc(string_to_document_transform::apply(t, a.content()));

    BOOST_LOG_SEV(lg, debug) << "Processed org-mode document.";
    entities::model r;
    r.tagged_values(read_tagged_values(doc.drawers()));

    stp.end_transform(r);
    return r;
}

}
