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
#include "dogen/cpp/types/project.hpp"

namespace dogen {
namespace cpp {

project::project(
    const std::list<dogen::cpp::file_info>& files,
    const dogen::cpp::odb_options_info& odb_options,
    const dogen::cpp::cmakelists_info& cmakelists)
    : files_(files),
      odb_options_(odb_options),
      cmakelists_(cmakelists) { }

void project::swap(project& other) noexcept {
    using std::swap;
    swap(files_, other.files_);
    swap(odb_options_, other.odb_options_);
    swap(cmakelists_, other.cmakelists_);
}

bool project::operator==(const project& rhs) const {
    return files_ == rhs.files_ &&
        odb_options_ == rhs.odb_options_ &&
        cmakelists_ == rhs.cmakelists_;
}

project& project::operator=(project other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::cpp::file_info>& project::files() const {
    return files_;
}

std::list<dogen::cpp::file_info>& project::files() {
    return files_;
}

void project::files(const std::list<dogen::cpp::file_info>& v) {
    files_ = v;
}

void project::files(const std::list<dogen::cpp::file_info>&& v) {
    files_ = std::move(v);
}

const dogen::cpp::odb_options_info& project::odb_options() const {
    return odb_options_;
}

dogen::cpp::odb_options_info& project::odb_options() {
    return odb_options_;
}

void project::odb_options(const dogen::cpp::odb_options_info& v) {
    odb_options_ = v;
}

void project::odb_options(const dogen::cpp::odb_options_info&& v) {
    odb_options_ = std::move(v);
}

const dogen::cpp::cmakelists_info& project::cmakelists() const {
    return cmakelists_;
}

dogen::cpp::cmakelists_info& project::cmakelists() {
    return cmakelists_;
}

void project::cmakelists(const dogen::cpp::cmakelists_info& v) {
    cmakelists_ = v;
}

void project::cmakelists(const dogen::cpp::cmakelists_info&& v) {
    cmakelists_ = std::move(v);
}

} }