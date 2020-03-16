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
#include "dogen.logical/types/meta_model/orm/odb_options.hpp"

namespace dogen::logical::meta_model::orm {

odb_options::odb_options(
    const std::string& epilogue,
    const std::list<std::string>& include_regexes,
    const std::string& header_guard_prefix)
    : epilogue_(epilogue),
      include_regexes_(include_regexes),
      header_guard_prefix_(header_guard_prefix) { }

void odb_options::swap(odb_options& other) noexcept {
    using std::swap;
    swap(epilogue_, other.epilogue_);
    swap(include_regexes_, other.include_regexes_);
    swap(header_guard_prefix_, other.header_guard_prefix_);
}

bool odb_options::operator==(const odb_options& rhs) const {
    return epilogue_ == rhs.epilogue_ &&
        include_regexes_ == rhs.include_regexes_ &&
        header_guard_prefix_ == rhs.header_guard_prefix_;
}

odb_options& odb_options::operator=(odb_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& odb_options::epilogue() const {
    return epilogue_;
}

std::string& odb_options::epilogue() {
    return epilogue_;
}

void odb_options::epilogue(const std::string& v) {
    epilogue_ = v;
}

void odb_options::epilogue(const std::string&& v) {
    epilogue_ = std::move(v);
}

const std::list<std::string>& odb_options::include_regexes() const {
    return include_regexes_;
}

std::list<std::string>& odb_options::include_regexes() {
    return include_regexes_;
}

void odb_options::include_regexes(const std::list<std::string>& v) {
    include_regexes_ = v;
}

void odb_options::include_regexes(const std::list<std::string>&& v) {
    include_regexes_ = std::move(v);
}

const std::string& odb_options::header_guard_prefix() const {
    return header_guard_prefix_;
}

std::string& odb_options::header_guard_prefix() {
    return header_guard_prefix_;
}

void odb_options::header_guard_prefix(const std::string& v) {
    header_guard_prefix_ = v;
}

void odb_options::header_guard_prefix(const std::string&& v) {
    header_guard_prefix_ = std::move(v);
}

}
