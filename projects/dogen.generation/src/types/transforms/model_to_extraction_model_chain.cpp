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
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.assets/types/meta_model/structural/module.hpp"
#include "dogen.assets/io/meta_model/technical_space_io.hpp"
#include "dogen.extraction/io/meta_model/model_io.hpp"
#include "dogen.generation/io/meta_model/model_io.hpp"
#include "dogen.generation/types/transforms/transformation_error.hpp"
#include "dogen.generation/types/transforms/model_to_extraction_model_chain.hpp"

namespace {

const std::string transform_id(
    "generation.transforms.model_to_extraction_model_chain");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string unsupported_technical_space(
    "Could not find transform for technical space: ");
const std::string disabled_transform(
    "Transform for requested technical space is disabled: ");

}

namespace dogen::generation::transforms {

std::shared_ptr<
    model_to_extraction_model_transform_registrar>
model_to_extraction_model_chain::registrar_;
model_to_extraction_model_transform_registrar&
model_to_extraction_model_chain::registrar() {
    if (!registrar_) {
        registrar_ = std::make_shared<
            model_to_extraction_model_transform_registrar>();
    }

    return *registrar_;
}

void model_to_extraction_model_chain::
merge(extraction::meta_model::model&& src, extraction::meta_model::model& dst) {
    dst.artefacts().splice(dst.artefacts().end(), src.artefacts());
    dst.managed_directories().splice(dst.managed_directories().end(),
        src.managed_directories());
}

extraction::meta_model::model model_to_extraction_model_chain::
apply(const generation::transforms::context& ctx,
    const generation::meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Transforming model: "
                             << m.name().qualified().dot();

    /*
     * No point in proceeding if the model has not types to
     * transform to text.
     */
    if (!m.has_generatable_types()) {
        BOOST_LOG_SEV(lg, warn) << "No generatable types found.";
        return extraction::meta_model::model();
    }

    /*
     * Look for the required model extractor. If none is available,
     * throw to let the user know it requested an unsupported
     * transformation.
     */
    const auto ts(m.output_technical_space());
    BOOST_LOG_SEV(lg, debug) << "Looking for a transform for technical space: "
                             << ts;
    const auto ptr(registrar().transform_for_technical_space(ts));
    if (!ptr) {
        const auto s(boost::lexical_cast<std::string>(ts));
        BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
        BOOST_THROW_EXCEPTION(
            transformation_error(unsupported_technical_space + s));
    }

    const auto& t(*ptr);
    const auto id(t.id());
    BOOST_LOG_SEV(lg, debug) << "Found transform: " << id;

    /*
     * Ensure the transform for the requested technical space is
     * marked as enabled. If it is disabled, the user has requested
     * conflicting options - output on technical_space X but disable
     * backend for technical space X - so we need to throw to let the
     * user know.
     */
    const auto& ek(m.extraction_properties().enabled_backends());
    const auto is_enabled(ek.find(id) != ek.end());
    if (!is_enabled) {
        BOOST_LOG_SEV(lg, error) << disabled_transform << id;
        BOOST_THROW_EXCEPTION(transformation_error(disabled_transform + id));
    }

    /*
     * Generate artefacts for all elements in model.
     */
    const bool ekd(m.extraction_properties().enable_backend_directories());
    auto r(t.apply(ctx, ekd, m));
    // r.origin_element_id(m.origin_element_id());
    // r.origin_sha1_hash(m.origin_sha1_hash());

    BOOST_LOG_SEV(lg, debug) << "Generated artefacts for : " << id
                             << ". Total artefacts: " << r.artefacts().size();

    BOOST_LOG_SEV(lg, debug) << "Transformed model.";
    return r;
}

extraction::meta_model::model model_to_extraction_model_chain::
apply(const generation::transforms::context& ctx,
    const std::list<generation::meta_model::model>& ms) {
    tracing::scoped_chain_tracer stp(lg, "model to extraction model chain",
        transform_id, "FIXME", *ctx.tracer(), ms);

    BOOST_LOG_SEV(lg, debug) << "Transforming models: " << ms.size();

    extraction::meta_model::model r;
    if (ms.empty())
        return r;

    /*
     * Copy across the extraction properties. We can use any of the
     * models in the list as they must all share the same properties
     * from the original target. This will be cleaned up when we fix
     * the processing pipeline.
     */
    const auto ep(ms.front().extraction_properties());
    r.name(ms.front().name().simple());
    r.configuration(ms.front().root_module()->configuration());

    /*
     * Now transform the models into artefacts.
     */
    for (const auto& m : ms)
        merge(apply(ctx, m), r);

    stp.end_chain(r);
    return r;
}

}
