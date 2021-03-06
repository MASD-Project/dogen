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
#include <boost/graph/depth_first_search.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.dia/types/transforms/string_to_diagram_transform.hpp"
#include "dogen.dia/io/entities/diagram_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.codec/io/entities/model_io.hpp"
#include "dogen.codec/io/entities/artefact_io.hpp"
#include "dogen.codec/types/transforms/transformation_error.hpp"
#include "dogen.codec/types/helpers/builder.hpp"
#include "dogen.codec/types/helpers/visitor.hpp"
#include "dogen.codec/types/helpers/grapher.hpp"
#include "dogen.codec/types/entities/comment.hpp"
#include "dogen.codec/types/helpers/dia_to_codec_projector.hpp"
#include "dogen.codec/types/transforms/dia_artefact_to_model_transform.hpp"

namespace {

const std::string
transform_id("codec.transforms.dia_artefact_to_model_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string uml_large_package("UML - LargePackage");
const std::string uml_class("UML - Class");
const std::string uml_generalization("UML - Generalization");
const std::string uml_association("UML - Association");
const std::string uml_note("UML - Note");
const std::string uml_message("UML - Message");
const std::string uml_realization("UML - Realizes");

const std::string no_uml_type("No UML type.");

}

namespace dogen::codec::transforms {

bool dia_artefact_to_model_transform::
is_not_relevant(const entities::object& po) {
    const auto ot(po.object_type());
    const bool is_relevant(
        ot == uml_large_package || ot == uml_generalization ||
        ot == uml_class ||  ot == uml_note);

    return !is_relevant;
}

void dia_artefact_to_model_transform::
validate(const std::list<entities::object>& os) {
    for (const auto& po : os) {
        /*
         * All objects must have a valid UML type.
         */
        if (po.object_type().empty()) {
            BOOST_LOG_SEV(lg, error) << no_uml_type;
            BOOST_THROW_EXCEPTION(transformation_error(no_uml_type));
        }
    }
}

std::list<entities::object> dia_artefact_to_model_transform::
obtain_objects(const dogen::dia::entities::diagram& d) {
    BOOST_LOG_SEV(lg, debug) << "Converting diagram into processed objects.";

    /*
     * Convert the original dia diagram into a list of dia objects
     * reading for processing.
     */
    auto r(helpers::dia_to_codec_projector::project(d));

    /*
     * Sanity check the processed objects to make sure they are valid.
     */
    validate(r);

    /*
     * Remove all the non-relevant process objects.
     */
    boost::range::remove_erase_if(r, is_not_relevant);

    BOOST_LOG_SEV(lg, debug) << "Converted diagram into processed objects.";
    return r;
}

codec::entities::model dia_artefact_to_model_transform::
obtain_model(const std::string& name, const std::list<entities::object>& os) {
    BOOST_LOG_SEV(lg, debug) << "Generating codec model.";

    /*
     * Create a dependency graph of the objects, and a map of children
     * to their respective parents.
     */
    helpers::grapher g;
    g.generate(os);

    /*
     * Go through the dependency graph and build a codec model from
     * it.
     */
    helpers::builder b(g.parent_id_to_child_ids());
    helpers::visitor v(b);
    boost::depth_first_search(g.graph(), boost::visitor(v));
    auto r(b.build());
    r.name().simple(name);

    BOOST_LOG_SEV(lg, debug) << "Generated codec model.";
    return r;
}

entities::model dia_artefact_to_model_transform::
apply(const transforms::context& ctx, const entities::artefact& a) {
    const auto fn(a.path().filename().stem().generic_string());
    tracing::scoped_transform_tracer stp(lg, "dia artefact to model",
        transform_id, fn, *ctx.tracer(), a);

    BOOST_LOG_SEV(lg, debug) << "Processing Dia diagram.";
    using dogen::dia::transforms::string_to_diagram_transform;
    const auto d(string_to_diagram_transform::apply(ctx.tracer(), a.content()));

    BOOST_LOG_SEV(lg, debug) << "Processed Dia diagram.";

    const auto os(obtain_objects(d));
    const auto r(obtain_model(fn, os));

    stp.end_transform(r);
    return r;
}

}
