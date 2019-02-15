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
#include "masd.dogen.cli/types/weaving_configuration.hpp"

namespace masd::dogen::cli {

weaving_configuration::weaving_configuration()
    : style_(static_cast<masd::dogen::weaving_style>(0)) { }

weaving_configuration::weaving_configuration(weaving_configuration&& rhs)
    : style_(std::move(rhs.style_)),
      target_(std::move(rhs.target_)) { }

weaving_configuration::weaving_configuration(
    const masd::dogen::weaving_style style,
    const boost::filesystem::path& target)
    : style_(style),
      target_(target) { }

void weaving_configuration::swap(weaving_configuration& other) noexcept {
    using std::swap;
    swap(style_, other.style_);
    swap(target_, other.target_);
}

bool weaving_configuration::operator==(const weaving_configuration& rhs) const {
    return style_ == rhs.style_ &&
        target_ == rhs.target_;
}

weaving_configuration& weaving_configuration::operator=(weaving_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

masd::dogen::weaving_style weaving_configuration::style() const {
    return style_;
}

weaving_configuration& weaving_configuration::style(const masd::dogen::weaving_style v) {
    style_ = v;
    return *this;
}

const boost::filesystem::path& weaving_configuration::target() const {
    return target_;
}

boost::filesystem::path& weaving_configuration::target() {
    return target_;
}

weaving_configuration& weaving_configuration::target(const boost::filesystem::path& v) {
    target_ = v;
    return *this;
}

weaving_configuration& weaving_configuration::target(const boost::filesystem::path&& v) {
    target_ = std::move(v);
    return *this;
}

}
