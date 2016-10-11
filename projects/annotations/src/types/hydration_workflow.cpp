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
#include "dogen/utility/io/set_io.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/annotations/types/json_hydrator.hpp"
#include "dogen/annotations/types/hydration_workflow.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("annotations.hydration_workflow"));

}

namespace dogen {
namespace annotations {

std::list<field_definition> hydration_workflow::
hydrate(const std::forward_list<boost::filesystem::path>& dirs) const {
    BOOST_LOG_SEV(lg, info) << "Finding all files in: " << dirs;
    const auto files(dogen::utility::filesystem::find_files(dirs));
    BOOST_LOG_SEV(lg, info) << "Files found: " << files;

    json_hydrator jh;
    std::list<field_definition> r;
    for (const auto& f : files) {
        auto fds(jh.hydrate(f));
        r.splice(r.end(), fds);
    }
    BOOST_LOG_SEV(lg, info) << "Finished hydrating all files.";
    return r;
}

} }
