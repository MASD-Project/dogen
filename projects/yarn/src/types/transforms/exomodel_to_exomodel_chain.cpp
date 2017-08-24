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
#include "dogen/yarn/types/helpers/model_sorter.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/exomodel_generation_chain.hpp"
#include "dogen/yarn/types/transforms/exomodel_to_exomodel_chain.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.transforms.exomodel_to_exomodel_chain"));

const std::string transform_not_supported("Cannot transform into: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

void exomodel_to_exomodel_chain::
transform(const boost::filesystem::path& src_path,
    const boost::filesystem::path& dst_path) {
    BOOST_LOG_SEV(lg, info) << "Transforming: " << src_path.generic_string()
                            << " to: " << dst_path.generic_string();

    using namespace yarn::transforms;
    auto& rg(exomodel_generation_chain::registrar());
    rg.validate();

    const auto src_model_identifier(src_path.string());
    auto& t0(rg.transform_for_model(src_model_identifier));
    const auto st0(t0.supported_transforms());
    if (st0 != exomodel_transform_types::bidirectional &&
        st0 != exomodel_transform_types::unidirectional_from) {
        BOOST_LOG_SEV(lg, error) << transform_not_supported
                                 << src_model_identifier;
        BOOST_THROW_EXCEPTION(transformation_error(
                transform_not_supported + src_model_identifier));
    }

    const auto dst_model_identifier(dst_path.string());
    auto& t1(rg.transform_for_model(dst_model_identifier));
    const auto st1(t1.supported_transforms());
    if (st1 != exomodel_transform_types::bidirectional &&
        st1 != exomodel_transform_types::unidirectional_to) {
        BOOST_LOG_SEV(lg, error) << transform_not_supported
                                 << dst_model_identifier;
        BOOST_THROW_EXCEPTION(transformation_error(
                transform_not_supported + dst_model_identifier));
    }

    auto src(t0.transform(src_path));
    yarn::helpers::model_sorter::sort(src);
    t1.transform(src, dst_path);

    BOOST_LOG_SEV(lg, info) << "Transformation done.";
}

} } }
