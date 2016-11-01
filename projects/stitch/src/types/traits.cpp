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
#include "dogen/stitch/types/traits.hpp"

namespace dogen {
namespace stitch {

std::string traits::model_name() {
    static std::string r("stitch");
    return r;
}

std::string traits::stream_variable_name() {
    static std::string r("stitch.stream_variable_name");
    return r;
}

std::string traits::relative_output_directory() {
    static std::string r("stitch.relative_output_directory");
    return r;
}

std::string traits::inclusion_dependency() {
    static std::string r("stitch.inclusion_dependency");
    return r;
}

std::string traits::containing_namespaces() {
    static std::string r("stitch.containing_namespaces");
    return r;
}

std::string traits::wale_template() {
    static std::string r("stitch.wale_template");
    return r;
}

} }
