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
#include <boost/algorithm/string/join.hpp>
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.text.csharp/types/traits.hpp"
#include "dogen.text.csharp/types/formattables/workflow.hpp"
#include "dogen.text.csharp/types/transforms/workflow.hpp"
#include "dogen.text.csharp/types/model_to_text_csharp_chain.hpp"

namespace {

const std::string
transform_id("text.csharp.model_to_text_csharp_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;
const std::string dot(".");
const std::string description(
    "Generates C# code according to the MASD generative model.");

}

namespace dogen::text::csharp {

model_to_text_csharp_chain::
~model_to_text_csharp_chain() noexcept { }

formattables::model
model_to_text_csharp_chain::create_formattables_model(
    const variability::entities::feature_model& feature_model,
    const transforms::repository& frp, const text::entities::model& m) const {
    formattables::workflow fw;
    const auto& ap(m.logical().aspect_properties());
    return fw.execute(feature_model, ap, frp, m);
}

identification::entities::physical_meta_id
model_to_text_csharp_chain::id() const {
    static identification::entities::physical_meta_id r("masd.csharp");
    return r;
}

std::string model_to_text_csharp_chain::description() const {
    return ::description;
}

void model_to_text_csharp_chain::
apply(boost::shared_ptr<tracing::tracer> tracer,
    const std::unordered_map<identification::entities::logical_id,
    logical::entities::aspect_properties>& aspect_properties,
    formattables::model& fm) const {
    transforms::workflow wf;
    wf.execute(tracer, aspect_properties, fm);
}

identification::entities::technical_space
model_to_text_csharp_chain::technical_space() const {
    return identification::entities::technical_space::csharp;
}

void model_to_text_csharp_chain::apply(const text::transforms::context& ctx,
    const bool /*enable_backend_directories*/, text::entities::model& m) const {
    const auto id(m.provenance().logical_name().id());
    tracing::scoped_chain_tracer stp(lg, "C# M2T chain", transform_id,
        id.value(), *ctx.tracer());

    const auto& feature_model(*ctx.feature_model());
    const auto& frp(transforms::workflow::registrar().formatter_repository());
    const auto& ap(m.logical().aspect_properties());

    /*
     * Generate the formattables model.
     */
    auto fm(create_formattables_model(feature_model, frp, m));
    apply(ctx.tracer(), ap, fm);

    using identification::entities::physical_meta_id;
    const auto beid(physical_meta_id("masd.csharp"));
    const auto& mmp(m.physical().meta_model_properties());
    const auto i(mmp.backend_properties().find(beid));
    if (i != mmp.backend_properties().end()) {
        const auto& be(i->second);
        m.physical().managed_directories().push_back(be.file_path());
    }
}

}
