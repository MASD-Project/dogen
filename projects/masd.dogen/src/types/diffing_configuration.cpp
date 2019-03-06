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
#include "masd.dogen/types/diffing_configuration.hpp"

namespace masd::dogen {

diffing_configuration::diffing_configuration()
    : style_(static_cast<masd::dogen::diffing_style>(0)),
      report_unchanged_files_(static_cast<bool>(0)),
      destination_(static_cast<masd::dogen::diffing_destination>(0)) { }

diffing_configuration::diffing_configuration(diffing_configuration&& rhs)
    : style_(std::move(rhs.style_)),
      report_unchanged_files_(std::move(rhs.report_unchanged_files_)),
      destination_(std::move(rhs.destination_)),
      output_directory_(std::move(rhs.output_directory_)) { }

diffing_configuration::diffing_configuration(
    const masd::dogen::diffing_style style,
    const bool report_unchanged_files,
    const masd::dogen::diffing_destination destination,
    const boost::filesystem::path& output_directory)
    : style_(style),
      report_unchanged_files_(report_unchanged_files),
      destination_(destination),
      output_directory_(output_directory) { }

void diffing_configuration::swap(diffing_configuration& other) noexcept {
    using std::swap;
    swap(style_, other.style_);
    swap(report_unchanged_files_, other.report_unchanged_files_);
    swap(destination_, other.destination_);
    swap(output_directory_, other.output_directory_);
}

bool diffing_configuration::operator==(const diffing_configuration& rhs) const {
    return style_ == rhs.style_ &&
        report_unchanged_files_ == rhs.report_unchanged_files_ &&
        destination_ == rhs.destination_ &&
        output_directory_ == rhs.output_directory_;
}

diffing_configuration& diffing_configuration::operator=(diffing_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

masd::dogen::diffing_style diffing_configuration::style() const {
    return style_;
}

diffing_configuration& diffing_configuration::style(const masd::dogen::diffing_style v) {
    style_ = v;
    return *this;
}

bool diffing_configuration::report_unchanged_files() const {
    return report_unchanged_files_;
}

diffing_configuration& diffing_configuration::report_unchanged_files(const bool v) {
    report_unchanged_files_ = v;
    return *this;
}

masd::dogen::diffing_destination diffing_configuration::destination() const {
    return destination_;
}

diffing_configuration& diffing_configuration::destination(const masd::dogen::diffing_destination v) {
    destination_ = v;
    return *this;
}

const boost::filesystem::path& diffing_configuration::output_directory() const {
    return output_directory_;
}

boost::filesystem::path& diffing_configuration::output_directory() {
    return output_directory_;
}

diffing_configuration& diffing_configuration::output_directory(const boost::filesystem::path& v) {
    output_directory_ = v;
    return *this;
}

diffing_configuration& diffing_configuration::output_directory(const boost::filesystem::path&& v) {
    output_directory_ = std::move(v);
    return *this;
}

}
