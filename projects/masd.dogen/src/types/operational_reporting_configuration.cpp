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
#include "masd.dogen/types/operational_reporting_configuration.hpp"

namespace masd::dogen {

operational_reporting_configuration::operational_reporting_configuration()
    : style_(static_cast<masd::dogen::operational_reporting_style>(0)) { }

operational_reporting_configuration::operational_reporting_configuration(const masd::dogen::operational_reporting_style style)
    : style_(style) { }

void operational_reporting_configuration::swap(operational_reporting_configuration& other) noexcept {
    using std::swap;
    swap(style_, other.style_);
}

bool operational_reporting_configuration::operator==(const operational_reporting_configuration& rhs) const {
    return style_ == rhs.style_;
}

operational_reporting_configuration& operational_reporting_configuration::operator=(operational_reporting_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

masd::dogen::operational_reporting_style operational_reporting_configuration::style() const {
    return style_;
}

void operational_reporting_configuration::style(const masd::dogen::operational_reporting_style v) {
    style_ = v;
}

}
