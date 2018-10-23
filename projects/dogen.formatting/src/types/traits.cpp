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
#include "dogen.formatting/types/traits.hpp"

namespace dogen::formatting {

std::string traits::decoration::generate_decoration() {
    static std::string r("decoration.generate_decoration");
    return r;
}

std::string traits::decoration::copyright_notices() {
    static std::string r("decoration.copyright_notice");
    return r;
}

std::string traits::decoration::licence_name() {
    static std::string r("decoration.licence_name");
    return r;
}

std::string traits::decoration::modeline_group_name() {
    static std::string r("decoration.modeline_group_name");
    return r;
}

std::string traits::decoration::code_generation_marker::add_date_time() {
    static std::string r("decoration.code_generation_marker.add_date_time");
    return r;
}

std::string traits::decoration::code_generation_marker::add_warning() {
    static std::string r("decoration.code_generation_marker.add_warning");
    return r;
}

std::string traits::decoration::code_generation_marker::message() {
    static std::string r("decoration.code_generation_marker.message");
    return r;
}

}
