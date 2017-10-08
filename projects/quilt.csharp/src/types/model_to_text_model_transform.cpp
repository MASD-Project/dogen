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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/helpers/scoped_transform_probing.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/quilt.csharp/types/formattables/workflow.hpp"
#include "dogen/quilt.csharp/types/formatters/workflow.hpp"
#include "dogen/quilt.csharp/types/formattables/locator.hpp"
#include "dogen/quilt.csharp/types/model_to_text_model_transform.hpp"

namespace {

const std::string transform_id(dogen::quilt::csharp::traits::backend());

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;
const std::string dot(".");

}

namespace dogen {
namespace quilt {
namespace csharp {

model_to_text_model_transform::~model_to_text_model_transform() noexcept { }

formattables::model model_to_text_model_transform::create_formattables_model(
    const annotations::type_repository& atrp,
    const annotations::annotation& ra,
    const formatters::repository& frp, const formattables::locator& l,
    const yarn::meta_model::model& m) const {
    formattables::workflow fw;
    return fw.execute(atrp, ra, frp, l, m);
}

std::string model_to_text_model_transform::id() const {
    return traits::backend();
}

std::list<dogen::formatters::artefact> model_to_text_model_transform::
format(const annotations::type_repository& /*atrp*/,
    const annotations::annotation_groups_factory& /*agf*/,
    const dogen::formatters::repository& /*drp*/,
    const formattables::model& fm) const {
    formatters::workflow wf;
    return wf.execute(fm);
}

const std::forward_list<annotations::archetype_location>&
model_to_text_model_transform::archetype_locations() const {
    const auto& rg(formatters::workflow::registrar());
    return rg.archetype_locations();
}

const std::unordered_map<std::string,
                         annotations::archetype_locations_group>&
model_to_text_model_transform::archetype_locations_by_meta_name() const {
    const auto& rg(formatters::workflow::registrar());
    return rg.archetype_locations_by_meta_name();
}

yarn::meta_model::languages model_to_text_model_transform::language() const {
    return yarn::meta_model::languages::csharp;
}

yarn::meta_model::text_model
model_to_text_model_transform::transform(const yarn::transforms::context& ctx,
    const bool enable_backend_directories,
    const yarn::meta_model::model& m) const {
    yarn::helpers::scoped_transform_probing stp(lg,
        "C# model to text transform",
        transform_id, m.name().id(), ctx.prober());

    BOOST_LOG_SEV(lg, debug) << "Started backend.";

    /*
     * Create the locator.
     */
    const auto mn(m.name());
    const auto& ra(m.root_module()->annotation());
    const auto& atrp(ctx.type_repository());
    const auto odp(ctx.transform_options().output_directory_path());
    const auto& frp(formatters::workflow::registrar().formatter_repository());
    const bool ekd(enable_backend_directories);
    const formattables::locator l(odp, atrp, frp, ra, mn, m.module_ids(), ekd);

    /*
     * Generate the formattables model.
     */
    const auto fm(create_formattables_model(atrp, ra, frp, l, m));

    /*
     * Code-generate all artefacts.
     */
    yarn::meta_model::text_model r;
    const auto& drp(ctx.formatters_repository());
    const auto& agf(ctx.groups_factory());
    r.artefacts(format(atrp, agf, drp, fm));
    r.managed_directories().push_back(l.project_path());

    BOOST_LOG_SEV(lg, debug) << "Finished backend.";
    return r;
}

} } }
