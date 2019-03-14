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
#include "masd.dogen.extraction/types/helpers/outputting_configuration.hpp"

namespace masd::dogen::extraction::helpers {

outputting_configuration::outputting_configuration()
    : force_write_(static_cast<bool>(0)),
      delete_extra_files_(static_cast<bool>(0)),
      delete_empty_directories_(static_cast<bool>(0)) { }

outputting_configuration::outputting_configuration(
    const bool force_write,
    const bool delete_extra_files,
    const std::vector<std::string>& ignore_files_matching_regex,
    const bool delete_empty_directories)
    : force_write_(force_write),
      delete_extra_files_(delete_extra_files),
      ignore_files_matching_regex_(ignore_files_matching_regex),
      delete_empty_directories_(delete_empty_directories) { }

void outputting_configuration::swap(outputting_configuration& other) noexcept {
    using std::swap;
    swap(force_write_, other.force_write_);
    swap(delete_extra_files_, other.delete_extra_files_);
    swap(ignore_files_matching_regex_, other.ignore_files_matching_regex_);
    swap(delete_empty_directories_, other.delete_empty_directories_);
}

bool outputting_configuration::operator==(const outputting_configuration& rhs) const {
    return force_write_ == rhs.force_write_ &&
        delete_extra_files_ == rhs.delete_extra_files_ &&
        ignore_files_matching_regex_ == rhs.ignore_files_matching_regex_ &&
        delete_empty_directories_ == rhs.delete_empty_directories_;
}

outputting_configuration& outputting_configuration::operator=(outputting_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool outputting_configuration::force_write() const {
    return force_write_;
}

void outputting_configuration::force_write(const bool v) {
    force_write_ = v;
}

bool outputting_configuration::delete_extra_files() const {
    return delete_extra_files_;
}

void outputting_configuration::delete_extra_files(const bool v) {
    delete_extra_files_ = v;
}

const std::vector<std::string>& outputting_configuration::ignore_files_matching_regex() const {
    return ignore_files_matching_regex_;
}

std::vector<std::string>& outputting_configuration::ignore_files_matching_regex() {
    return ignore_files_matching_regex_;
}

void outputting_configuration::ignore_files_matching_regex(const std::vector<std::string>& v) {
    ignore_files_matching_regex_ = v;
}

void outputting_configuration::ignore_files_matching_regex(const std::vector<std::string>&& v) {
    ignore_files_matching_regex_ = std::move(v);
}

bool outputting_configuration::delete_empty_directories() const {
    return delete_empty_directories_;
}

void outputting_configuration::delete_empty_directories(const bool v) {
    delete_empty_directories_ = v;
}

}
