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
#include "dogen.cli/types/dumpspecs_configuration.hpp"

namespace dogen::cli {

dumpspecs_configuration::dumpspecs_configuration()
    : style_(static_cast<dogen::reporting_style>(0)) { }

dumpspecs_configuration::dumpspecs_configuration(const dogen::reporting_style style)
    : style_(style) { }

void dumpspecs_configuration::swap(dumpspecs_configuration& other) noexcept {
    using std::swap;
    swap(style_, other.style_);
}

bool dumpspecs_configuration::operator==(const dumpspecs_configuration& rhs) const {
    return style_ == rhs.style_;
}

dumpspecs_configuration& dumpspecs_configuration::operator=(dumpspecs_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::reporting_style dumpspecs_configuration::style() const {
    return style_;
}

dumpspecs_configuration& dumpspecs_configuration::style(const dogen::reporting_style v) {
    style_ = v;
    return *this;
}

}
