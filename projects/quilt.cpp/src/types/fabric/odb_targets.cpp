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
#include "dogen/quilt.cpp/types/fabric/odb_targets.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

odb_targets::odb_targets(
    const std::string& main_target_name,
    const std::string& options_file,
    const std::list<dogen::quilt::cpp::fabric::odb_target>& targets)
    : main_target_name_(main_target_name),
      options_file_(options_file),
      targets_(targets) { }

void odb_targets::swap(odb_targets& other) noexcept {
    using std::swap;
    swap(main_target_name_, other.main_target_name_);
    swap(options_file_, other.options_file_);
    swap(targets_, other.targets_);
}

bool odb_targets::operator==(const odb_targets& rhs) const {
    return main_target_name_ == rhs.main_target_name_ &&
        options_file_ == rhs.options_file_ &&
        targets_ == rhs.targets_;
}

odb_targets& odb_targets::operator=(odb_targets other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& odb_targets::main_target_name() const {
    return main_target_name_;
}

std::string& odb_targets::main_target_name() {
    return main_target_name_;
}

void odb_targets::main_target_name(const std::string& v) {
    main_target_name_ = v;
}

void odb_targets::main_target_name(const std::string&& v) {
    main_target_name_ = std::move(v);
}

const std::string& odb_targets::options_file() const {
    return options_file_;
}

std::string& odb_targets::options_file() {
    return options_file_;
}

void odb_targets::options_file(const std::string& v) {
    options_file_ = v;
}

void odb_targets::options_file(const std::string&& v) {
    options_file_ = std::move(v);
}

const std::list<dogen::quilt::cpp::fabric::odb_target>& odb_targets::targets() const {
    return targets_;
}

std::list<dogen::quilt::cpp::fabric::odb_target>& odb_targets::targets() {
    return targets_;
}

void odb_targets::targets(const std::list<dogen::quilt::cpp::fabric::odb_target>& v) {
    targets_ = v;
}

void odb_targets::targets(const std::list<dogen::quilt::cpp::fabric::odb_target>&& v) {
    targets_ = std::move(v);
}

} } } }
