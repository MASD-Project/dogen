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
#include "dogen/cpp/types/formattables/project.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

project::project(project&& rhs)
    : files_(std::move(rhs.files_)),
      odb_options_(std::move(rhs.odb_options_)),
      src_cmakelists_(std::move(rhs.src_cmakelists_)),
      include_cmakelists_(std::move(rhs.include_cmakelists_)) { }

project::project(
    const std::list<dogen::cpp::formattables::file_info>& files,
    const dogen::cpp::formattables::odb_options_info& odb_options,
    const dogen::cpp::formattables::cmakelists_info& src_cmakelists,
    const boost::optional<dogen::cpp::formattables::cmakelists_info>& include_cmakelists)
    : files_(files),
      odb_options_(odb_options),
      src_cmakelists_(src_cmakelists),
      include_cmakelists_(include_cmakelists) { }

void project::swap(project& other) noexcept {
    using std::swap;
    swap(files_, other.files_);
    swap(odb_options_, other.odb_options_);
    swap(src_cmakelists_, other.src_cmakelists_);
    swap(include_cmakelists_, other.include_cmakelists_);
}

bool project::operator==(const project& rhs) const {
    return files_ == rhs.files_ &&
        odb_options_ == rhs.odb_options_ &&
        src_cmakelists_ == rhs.src_cmakelists_ &&
        include_cmakelists_ == rhs.include_cmakelists_;
}

project& project::operator=(project other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::cpp::formattables::file_info>& project::files() const {
    return files_;
}

std::list<dogen::cpp::formattables::file_info>& project::files() {
    return files_;
}

void project::files(const std::list<dogen::cpp::formattables::file_info>& v) {
    files_ = v;
}

void project::files(const std::list<dogen::cpp::formattables::file_info>&& v) {
    files_ = std::move(v);
}

const dogen::cpp::formattables::odb_options_info& project::odb_options() const {
    return odb_options_;
}

dogen::cpp::formattables::odb_options_info& project::odb_options() {
    return odb_options_;
}

void project::odb_options(const dogen::cpp::formattables::odb_options_info& v) {
    odb_options_ = v;
}

void project::odb_options(const dogen::cpp::formattables::odb_options_info&& v) {
    odb_options_ = std::move(v);
}

const dogen::cpp::formattables::cmakelists_info& project::src_cmakelists() const {
    return src_cmakelists_;
}

dogen::cpp::formattables::cmakelists_info& project::src_cmakelists() {
    return src_cmakelists_;
}

void project::src_cmakelists(const dogen::cpp::formattables::cmakelists_info& v) {
    src_cmakelists_ = v;
}

void project::src_cmakelists(const dogen::cpp::formattables::cmakelists_info&& v) {
    src_cmakelists_ = std::move(v);
}

const boost::optional<dogen::cpp::formattables::cmakelists_info>& project::include_cmakelists() const {
    return include_cmakelists_;
}

boost::optional<dogen::cpp::formattables::cmakelists_info>& project::include_cmakelists() {
    return include_cmakelists_;
}

void project::include_cmakelists(const boost::optional<dogen::cpp::formattables::cmakelists_info>& v) {
    include_cmakelists_ = v;
}

void project::include_cmakelists(const boost::optional<dogen::cpp::formattables::cmakelists_info>&& v) {
    include_cmakelists_ = std::move(v);
}

} } }
