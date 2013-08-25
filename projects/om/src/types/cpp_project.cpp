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
#include "dogen/om/types/cpp_project.hpp"

namespace dogen {
namespace om {

cpp_project::cpp_project(cpp_project&& rhs)
    : makefiles_(std::move(rhs.makefiles_)),
      odb_options_(std::move(rhs.odb_options_)),
      cpp_files_(std::move(rhs.cpp_files_)) { }

cpp_project::cpp_project(
    const std::list<dogen::om::cmake_file>& makefiles,
    const boost::optional<dogen::om::odb_options_file>& odb_options,
    const std::list<dogen::om::cpp_file>& cpp_files)
    : makefiles_(makefiles),
      odb_options_(odb_options),
      cpp_files_(cpp_files) { }

void cpp_project::swap(cpp_project& other) noexcept {
    using std::swap;
    swap(makefiles_, other.makefiles_);
    swap(odb_options_, other.odb_options_);
    swap(cpp_files_, other.cpp_files_);
}

bool cpp_project::operator==(const cpp_project& rhs) const {
    return makefiles_ == rhs.makefiles_ &&
        odb_options_ == rhs.odb_options_ &&
        cpp_files_ == rhs.cpp_files_;
}

cpp_project& cpp_project::operator=(cpp_project other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::om::cmake_file>& cpp_project::makefiles() const {
    return makefiles_;
}

std::list<dogen::om::cmake_file>& cpp_project::makefiles() {
    return makefiles_;
}

void cpp_project::makefiles(const std::list<dogen::om::cmake_file>& v) {
    makefiles_ = v;
}

void cpp_project::makefiles(const std::list<dogen::om::cmake_file>&& v) {
    makefiles_ = std::move(v);
}

const boost::optional<dogen::om::odb_options_file>& cpp_project::odb_options() const {
    return odb_options_;
}

boost::optional<dogen::om::odb_options_file>& cpp_project::odb_options() {
    return odb_options_;
}

void cpp_project::odb_options(const boost::optional<dogen::om::odb_options_file>& v) {
    odb_options_ = v;
}

void cpp_project::odb_options(const boost::optional<dogen::om::odb_options_file>&& v) {
    odb_options_ = std::move(v);
}

const std::list<dogen::om::cpp_file>& cpp_project::cpp_files() const {
    return cpp_files_;
}

std::list<dogen::om::cpp_file>& cpp_project::cpp_files() {
    return cpp_files_;
}

void cpp_project::cpp_files(const std::list<dogen::om::cpp_file>& v) {
    cpp_files_ = v;
}

void cpp_project::cpp_files(const std::list<dogen::om::cpp_file>&& v) {
    cpp_files_ = std::move(v);
}

} }