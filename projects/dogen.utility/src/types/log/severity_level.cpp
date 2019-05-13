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
#include <stdexcept>
#include "dogen.utility/types/log/severity_level.hpp"
#include "dogen.utility/types/exception/invalid_enum_value.hpp"

namespace {

const std::string trace_level("trace");
const std::string debug_level("debug");
const std::string info_level("info");
const std::string warn_level("warn");
const std::string error_level("error");

}

namespace dogen::utility::log {

severity_level to_severity_level(const std::string& s) {
    if (s == trace_level)
        return severity_level::trace;
    if (s == debug_level)
        return severity_level::debug;
    if (s == info_level)
        return severity_level::info;
    if (s == warn_level)
        return severity_level::warn;
    if (s == error_level)
        return severity_level::error;

    using dogen::utility::exception::invalid_enum_value;
    BOOST_THROW_EXCEPTION(
        invalid_enum_value("Invalid or unexpected severity level: " + s));
}

}
