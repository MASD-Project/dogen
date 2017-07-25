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
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/annotations/types/type_repository_factory.hpp"
#include "dogen/annotations/types/archetype_location_repository_factory.hpp"
#include "dogen/formatters/types/repository_factory.hpp"
#include "dogen/yarn/types/transforms/context_factory.hpp"
#include "dogen/yarn/types/transforms/code_generation_chain.hpp"
#include "dogen/yarn/types/helpers/mapping_set_repository_factory.hpp"
#include "dogen/yarn/types/transforms/context_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.transforms.context_factory"));

}

namespace dogen {
namespace yarn {
namespace transforms {

context context_factory::make(const options::knitting_options& o) {
    BOOST_LOG_SEV(lg, debug) << "Creating the context.";

    const auto data_dir(utility::filesystem::data_files_directory());
    const auto data_dirs(std::vector<boost::filesystem::path>{ data_dir });

    annotations::archetype_location_repository_factory alrpf;
    const auto& rg = code_generation_chain::registrar();
    const auto alrp(alrpf.make(rg.archetype_locations()));

    helpers::mapping_set_repository_factory msrpf;
    const auto msrp(msrpf.make(data_dirs));

    annotations::type_repository_factory atrpf;
    const auto atrp(atrpf.make(alrp, data_dirs));

    formatters::repository_factory frpf;
    const auto frp(frpf.make(data_dirs));
    const auto& albmt(rg.archetype_locations_by_meta_type());
    const context r(data_dirs, o, albmt, alrp, atrp, msrp, frp);

    BOOST_LOG_SEV(lg, debug) << "Created the context.";
    return r;
}

} } }
