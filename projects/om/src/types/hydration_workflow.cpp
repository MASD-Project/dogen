/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/om/types/licence_hydrator.hpp"
#include "dogen/om/types/modeline_group_hydrator.hpp"
#include "dogen/om/types/hydration_workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("om.hydration_manager"));

}

namespace dogen {
namespace om {

std::unordered_map<std::string, modeline_group> hydration_workflow::
hydrate_modeline_groups(const std::list<boost::filesystem::path> ) {
    std::unordered_map<std::string, modeline_group> r;

    return r;
}

std::unordered_map<std::string, licence> hydration_workflow::
hydrate_licences(const std::list<boost::filesystem::path> ) {
    std::unordered_map<std::string, licence> r;

    return r;
}

} }
