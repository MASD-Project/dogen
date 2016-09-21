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
#include "dogen/formatters/types/file_configuration_workflow.hpp"

namespace dogen {
namespace formatters {

file_configuration_workflow::file_configuration_workflow(
    const dynamic::repository& drp,
    const repository& rp)
    : annotations_factory_(drp), configuration_factory_(rp) { }

file_configuration_workflow::file_configuration_workflow(
    const dynamic::repository& drp, const repository& rp,
    const dynamic::object& fallback)
    : annotations_factory_(drp),
      configuration_factory_(rp, annotations_factory_.make(fallback)) { }

file_configuration file_configuration_workflow::
execute(const std::string& modeline_name) const {
    const auto fa = file_annotations();
    return configuration_factory_.make(modeline_name, fa);
}

file_configuration file_configuration_workflow::execute(
    const std::string& modeline_name, const dynamic::object& o) const {
    const auto fa(annotations_factory_.make(o));
    return configuration_factory_.make(modeline_name, fa);
}

} }
