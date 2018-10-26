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
#include "masd.dogen/types/weaving_configuration.hpp"

namespace masd::dogen {

weaving_configuration::weaving_configuration()
    : style_(static_cast<masd::dogen::weaving_style>(0)) { }

weaving_configuration::weaving_configuration(weaving_configuration&& rhs)
    : output_directory_(std::move(rhs.output_directory_)),
      style_(std::move(rhs.style_)) { }

weaving_configuration::weaving_configuration(
    const boost::filesystem::path& output_directory,
    const masd::dogen::weaving_style style)
    : output_directory_(output_directory),
      style_(style) { }

void weaving_configuration::swap(weaving_configuration& other) noexcept {
    using std::swap;
    swap(output_directory_, other.output_directory_);
    swap(style_, other.style_);
}

bool weaving_configuration::operator==(const weaving_configuration& rhs) const {
    return output_directory_ == rhs.output_directory_ &&
        style_ == rhs.style_;
}

weaving_configuration& weaving_configuration::operator=(weaving_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& weaving_configuration::output_directory() const {
    return output_directory_;
}

boost::filesystem::path& weaving_configuration::output_directory() {
    return output_directory_;
}

weaving_configuration& weaving_configuration::output_directory(const boost::filesystem::path& v) {
    output_directory_ = v;
    return *this;
}

weaving_configuration& weaving_configuration::output_directory(const boost::filesystem::path&& v) {
    output_directory_ = std::move(v);
    return *this;
}

masd::dogen::weaving_style weaving_configuration::style() const {
    return style_;
}

weaving_configuration& weaving_configuration::style(const masd::dogen::weaving_style v) {
    style_ = v;
    return *this;
}

}
