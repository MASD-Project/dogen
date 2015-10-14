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
#include "dogen/formatters/types/traits.hpp"

namespace dogen {
namespace formatters {

std::string traits::copyright_notices() {
    static std::string r("copyright_notice");
    return r;
}

std::string traits::licence_name() {
    static std::string r("licence_name");
    return r;
}

std::string traits::modeline_group_name() {
    static std::string r("modeline_group_name");
    return r;
}

std::string traits::generate_preamble() {
    static std::string r("generate_preamble");
    return r;
}

std::string traits::code_generation_marker::add_date_time() {
    static std::string r("code_generation_marker.add_date_time");
    return r;
}

std::string traits::code_generation_marker::add_warning() {
    static std::string r("code_generation_marker.add_warning");
    return r;
}

std::string traits::code_generation_marker::message() {
    static std::string r("code_generation_marker.message");
    return r;
}

} }
