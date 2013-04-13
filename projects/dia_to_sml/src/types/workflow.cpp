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
#include "dogen/dia/types/diagram.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/dia_to_sml/types/workflow.hpp"

namespace dogen {
namespace dia_to_sml {

workflow::~workflow() noexcept { }

sml::model workflow::execute(const dia::diagram& /*diagram*/,
    const std::string& /*model_name*/,
    const std::string& /*external_package_path*/,
    bool /*is_target*/, bool /*verbose*/) {
    sml::model r;

    return r;
}

} }
