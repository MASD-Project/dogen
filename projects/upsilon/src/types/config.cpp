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
#include "dogen/upsilon/types/config.hpp"

namespace dogen {
namespace upsilon {

config::config(config&& rhs)
    : directory_(std::move(rhs.directory_)),
      schema_refs_(std::move(rhs.schema_refs_)),
      outputs_(std::move(rhs.outputs_)),
      file_name_(std::move(rhs.file_name_)) { }

config::config(
    const dogen::upsilon::directory& directory,
    const std::vector<dogen::upsilon::schema_ref>& schema_refs,
    const std::vector<dogen::upsilon::output>& outputs,
    const boost::filesystem::path& file_name)
    : directory_(directory),
      schema_refs_(schema_refs),
      outputs_(outputs),
      file_name_(file_name) { }

void config::swap(config& other) noexcept {
    using std::swap;
    swap(directory_, other.directory_);
    swap(schema_refs_, other.schema_refs_);
    swap(outputs_, other.outputs_);
    swap(file_name_, other.file_name_);
}

bool config::operator==(const config& rhs) const {
    return directory_ == rhs.directory_ &&
        schema_refs_ == rhs.schema_refs_ &&
        outputs_ == rhs.outputs_ &&
        file_name_ == rhs.file_name_;
}

config& config::operator=(config other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::upsilon::directory& config::directory() const {
    return directory_;
}

dogen::upsilon::directory& config::directory() {
    return directory_;
}

void config::directory(const dogen::upsilon::directory& v) {
    directory_ = v;
}

void config::directory(const dogen::upsilon::directory&& v) {
    directory_ = std::move(v);
}

const std::vector<dogen::upsilon::schema_ref>& config::schema_refs() const {
    return schema_refs_;
}

std::vector<dogen::upsilon::schema_ref>& config::schema_refs() {
    return schema_refs_;
}

void config::schema_refs(const std::vector<dogen::upsilon::schema_ref>& v) {
    schema_refs_ = v;
}

void config::schema_refs(const std::vector<dogen::upsilon::schema_ref>&& v) {
    schema_refs_ = std::move(v);
}

const std::vector<dogen::upsilon::output>& config::outputs() const {
    return outputs_;
}

std::vector<dogen::upsilon::output>& config::outputs() {
    return outputs_;
}

void config::outputs(const std::vector<dogen::upsilon::output>& v) {
    outputs_ = v;
}

void config::outputs(const std::vector<dogen::upsilon::output>&& v) {
    outputs_ = std::move(v);
}

const boost::filesystem::path& config::file_name() const {
    return file_name_;
}

boost::filesystem::path& config::file_name() {
    return file_name_;
}

void config::file_name(const boost::filesystem::path& v) {
    file_name_ = v;
}

void config::file_name(const boost::filesystem::path&& v) {
    file_name_ = std::move(v);
}

} }
