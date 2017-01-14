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
#include "dogen/upsilon/types/type_information_entry.hpp"

namespace dogen {
namespace upsilon {

type_information_entry::type_information_entry(type_information_entry&& rhs)
    : name_(std::move(rhs.name_)),
      pof_id_(std::move(rhs.pof_id_)),
      file_path_(std::move(rhs.file_path_)) { }

type_information_entry::type_information_entry(
    const std::string& name,
    const std::string& pof_id,
    const boost::filesystem::path& file_path)
    : name_(name),
      pof_id_(pof_id),
      file_path_(file_path) { }

void type_information_entry::swap(type_information_entry& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(pof_id_, other.pof_id_);
    swap(file_path_, other.file_path_);
}

bool type_information_entry::operator==(const type_information_entry& rhs) const {
    return name_ == rhs.name_ &&
        pof_id_ == rhs.pof_id_ &&
        file_path_ == rhs.file_path_;
}

type_information_entry& type_information_entry::operator=(type_information_entry other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& type_information_entry::name() const {
    return name_;
}

std::string& type_information_entry::name() {
    return name_;
}

void type_information_entry::name(const std::string& v) {
    name_ = v;
}

void type_information_entry::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& type_information_entry::pof_id() const {
    return pof_id_;
}

std::string& type_information_entry::pof_id() {
    return pof_id_;
}

void type_information_entry::pof_id(const std::string& v) {
    pof_id_ = v;
}

void type_information_entry::pof_id(const std::string&& v) {
    pof_id_ = std::move(v);
}

const boost::filesystem::path& type_information_entry::file_path() const {
    return file_path_;
}

boost::filesystem::path& type_information_entry::file_path() {
    return file_path_;
}

void type_information_entry::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void type_information_entry::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

} }
