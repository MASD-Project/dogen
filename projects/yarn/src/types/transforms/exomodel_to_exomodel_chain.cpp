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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/meta_model/exomodel.hpp"
#include "dogen/yarn/types/helpers/scoped_transform_probing.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/meta_naming_transform.hpp"
#include "dogen/yarn/types/transforms/exomodel_generation_chain.hpp"
#include "dogen/yarn/types/transforms/exomodel_to_exomodel_chain.hpp"

namespace {

const std::string transform_id("yarn.transforms.exomodel_to_exomodel_chain");
using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string transform_not_supported("Cannot transform into: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

boost::tuple<exomodel_transform_interface&, exomodel_transform_interface&>
exomodel_to_exomodel_chain::obtain_transforms(
    const boost::filesystem::path& src_path,
    const boost::filesystem::path& dst_path) {
    /*
     * Start by ensuring the registrar is in a good place.
     */
    using namespace yarn::transforms;
    auto& rg(exomodel_generation_chain::registrar());
    rg.validate();

    /*
     * Now ensure we have the required support for the two
     * transformations we intend to do. If not, there is no point
     * continuing.
     */
    auto& t0(rg.transform_for_model(src_path));
    const auto tt0(t0.transform_types());
    if (tt0 != exomodel_transform_types::bidirectional &&
        tt0 != exomodel_transform_types::unidirectional_from) {
        const auto gs(src_path.generic_string());
        BOOST_LOG_SEV(lg, error) << transform_not_supported << gs;
        BOOST_THROW_EXCEPTION(
            transformation_error(transform_not_supported + gs));
    }

    auto& t1(rg.transform_for_model(dst_path));
    const auto tt1(t1.transform_types());
    if (tt1 != exomodel_transform_types::bidirectional &&
        tt1 != exomodel_transform_types::unidirectional_to) {
        const auto gs(dst_path.generic_string());
        BOOST_LOG_SEV(lg, error) << transform_not_supported << gs;
        BOOST_THROW_EXCEPTION(
            transformation_error(transform_not_supported + gs));
    }

    return boost::tie(t0, t1);
}

void exomodel_to_exomodel_chain::
transform(const transforms::context& ctx,
    const boost::filesystem::path& src_path,
    const boost::filesystem::path& dst_path) {
    helpers::scoped_chain_probing stp(lg, "exomodel to exomodel chain",
        transform_id, ctx.prober());

    /*
     * Obtain a tuple containing the source and destination
     * transforms.
     */
    BOOST_LOG_SEV(lg, info) << " Transforming: " << src_path.generic_string()
                            << " to: " << dst_path.generic_string();
    auto tuple(obtain_transforms(src_path, dst_path));
    auto src(tuple.get<0>().transform(ctx, src_path));

    /*
     * Transform the exomodel to the requested representation.
     */
    tuple.get<1>().transform(ctx, src, dst_path);
}

} } }
