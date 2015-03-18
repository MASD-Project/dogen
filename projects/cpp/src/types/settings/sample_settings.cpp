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
#include <ostream>
#include "dogen/cpp/io/settings/special_formatter_settings_io.hpp"
#include "dogen/cpp/types/settings/sample_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

void sample_settings::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::settings::sample_settings\"" << ", "
      << "\"__parent_0__\": ";
    special_formatter_settings::to_stream(s);
    s << " }";
}

bool sample_settings::equals(const dogen::cpp::settings::special_formatter_settings& other) const {
    const sample_settings* const p(dynamic_cast<const sample_settings* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool sample_settings::operator==(const sample_settings& /*rhs*/) const {
    return true;
}

} } }