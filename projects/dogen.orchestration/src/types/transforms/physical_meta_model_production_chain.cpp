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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/meta_model_io.hpp"
#include "dogen.physical/types/helpers/meta_name_builder.hpp"
#include "dogen.physical/types/helpers/meta_name_index_builder.hpp"
#include "dogen.physical/types/helpers/template_instantiation_domains_factory.hpp"
#include "dogen.text.cpp/types/transforms/transforms.hpp"
#include "dogen.text.csharp/types/transforms/transforms.hpp"
#include "dogen.physical/types/transforms/meta_model_production_chain.hpp"
#include "dogen.orchestration/types/transforms/physical_meta_model_production_chain.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.physical_meta_model_production_chain");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const bool legacy(false);

}

namespace dogen::orchestration::transforms {

boost::shared_ptr<physical::entities::meta_model>
physical_meta_model_production_chain::
apply(const physical::transforms::minimal_context& ctx, const
    text::transforms::model_to_text_technical_space_chain_registrar& rg) {
    tracing::scoped_chain_tracer stp(lg, "physical meta-model production chain",
        transform_id, "physical_meta_model", *ctx.tracer());


    const std::list<physical::entities::backend> bes {
        text::cpp::transforms::transforms_backend_chain::static_backend(),
        text::csharp::transforms::transforms_backend_chain::static_backend()
    };

    if (legacy) {
        /*
         * Create the MASD PMM. This is done here until we support
         * defining PMMs in the logical representation of the physical
         * meta-model through text transforms.
         */
        using physical::entities::meta_model;
        auto r(boost::make_shared<meta_model>());

        physical::helpers::meta_name_builder mnb;
        mnb.meta_model("masd");

        r->meta_name(mnb.build());
        r->backends(bes);

        /*
         * Legacy repository building.
         */
        physical::helpers::meta_name_index_builder b;
        for (const auto& pair : rg.transforms_by_technical_space()) {
            const auto& t(*pair.second);
            b.add(t.physical_meta_names_by_logical_meta_name());
        }

        const auto nrp(b.build());
        r->indexed_names(nrp);

        /*
         * Obtain the template instantiation domains.
         */
        using tidf = physical::helpers::template_instantiation_domains_factory;
        r->template_instantiation_domains(tidf::make(nrp.all()));

        stp.end_chain(r);
        return r;
    } else {
        using physical::transforms::meta_model_production_chain;
        const auto r(meta_model_production_chain::apply(ctx, bes));
        stp.end_chain(r);
        return r;
    }
}

}
