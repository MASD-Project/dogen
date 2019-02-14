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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/io/meta_model/languages_io.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/model_to_text_model_chain.hpp"

namespace {

const std::string transform_id("masd.transforms.model_to_text_model_chain");
using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string unsupported_language(
    "Could not find transform for language: ");
const std::string disabled_transform(
    "Transform for requested language is disabled: ");

}

namespace masd::dogen::coding::transforms {

std::shared_ptr<model_to_text_model_transform_registrar>
model_to_text_model_chain::registrar_;
model_to_text_model_transform_registrar&
model_to_text_model_chain::registrar() {
    if (!registrar_) {
        registrar_ = std::make_shared<
            model_to_text_model_transform_registrar>();
    }

    return *registrar_;
}

void model_to_text_model_chain::
merge(meta_model::text_model&& src, meta_model::text_model& dst) {
    dst.artefacts().splice(dst.artefacts().end(), src.artefacts());
    dst.managed_directories().splice(dst.managed_directories().end(),
        src.managed_directories());
}

meta_model::text_model model_to_text_model_chain::
transform(const context& ctx, const meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Transforming model: " << m.name().id();

    /*
     * No point in proceeding if the model has not types to
     * transform to text.
     */
    if (!m.has_generatable_types()) {
        BOOST_LOG_SEV(lg, warn) << "No generatable types found.";
        return meta_model::text_model();
    }

    /*
     * Look for the required model to text transfrom. If none is
     * available, throw to let the user know it requested an
     * unsupported transformation.
     */
    const auto ol(m.output_language());
    BOOST_LOG_SEV(lg, debug) << "Looking for a transform for language: " << ol;
    const auto ptr(registrar().transform_for_language(ol));
    if (!ptr) {
        const auto s(boost::lexical_cast<std::string>(ol));
        BOOST_LOG_SEV(lg, error) << unsupported_language << s;
        BOOST_THROW_EXCEPTION(transformation_error(unsupported_language + s));
    }

    const auto& t(*ptr);
    const auto id(t.id());
    BOOST_LOG_SEV(lg, debug) << "Found transform: " << id;

    /*
     * Ensure the transform for the requested language is marked as
     * enabled. If it is disabled, the user has requested conflicting
     * options - output on language X but disable backend for language
     * X - so we need to throw to let it know.
     */
    const auto& ek(m.extraction_properties().enabled_backends());
    const auto is_enabled(ek.find(id) != ek.end());
    if (!is_enabled) {
        BOOST_LOG_SEV(lg, error) << disabled_transform << t.id();
        BOOST_THROW_EXCEPTION(transformation_error(disabled_transform + id));
    }

    /*
     * Generate artefacts for all elements in model.
     */
    const bool ekd(m.extraction_properties().enable_backend_directories());
    auto r(t.transform(ctx, ekd, m));
    BOOST_LOG_SEV(lg, debug) << "Generated files for : " << id
                             << ". Total files: "
                             << std::distance(r.artefacts().begin(),
                                 r.artefacts().end());

    BOOST_LOG_SEV(lg, debug) << "Transformed model.";
    return r;
}

meta_model::text_model model_to_text_model_chain::
transform(const context& ctx, const std::list<meta_model::model>& models) {
    tracing::scoped_chain_tracer stp(lg, "code generation chain",
        transform_id, ctx.tracer());

    BOOST_LOG_SEV(lg, debug) << "Transforming models: " << models.size();

    meta_model::text_model r;
    for (const auto& m : models)
        merge(transform(ctx, m), r);

    return r;
}

}
