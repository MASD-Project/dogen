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
#include "dogen/config/types/sql_settings.hpp"

namespace dogen {
namespace config {

sql_settings::sql_settings()
    : verbose_(static_cast<bool>(0)),
      disable_backend_(static_cast<bool>(0)),
      create_schema_(static_cast<bool>(0)) { }

sql_settings::sql_settings(
    const bool verbose,
    const bool disable_backend,
    const bool create_schema,
    const std::string& schema_name)
    : verbose_(verbose),
      disable_backend_(disable_backend),
      create_schema_(create_schema),
      schema_name_(schema_name) { }

void sql_settings::swap(sql_settings& other) noexcept {
    using std::swap;
    swap(verbose_, other.verbose_);
    swap(disable_backend_, other.disable_backend_);
    swap(create_schema_, other.create_schema_);
    swap(schema_name_, other.schema_name_);
}

bool sql_settings::operator==(const sql_settings& rhs) const {
    return verbose_ == rhs.verbose_ &&
        disable_backend_ == rhs.disable_backend_ &&
        create_schema_ == rhs.create_schema_ &&
        schema_name_ == rhs.schema_name_;
}

sql_settings& sql_settings::operator=(sql_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool sql_settings::verbose() const {
    return verbose_;
}

void sql_settings::verbose(const bool v) {
    verbose_ = v;
}

bool sql_settings::disable_backend() const {
    return disable_backend_;
}

void sql_settings::disable_backend(const bool v) {
    disable_backend_ = v;
}

bool sql_settings::create_schema() const {
    return create_schema_;
}

void sql_settings::create_schema(const bool v) {
    create_schema_ = v;
}

const std::string& sql_settings::schema_name() const {
    return schema_name_;
}

std::string& sql_settings::schema_name() {
    return schema_name_;
}

void sql_settings::schema_name(const std::string& v) {
    schema_name_ = v;
}

void sql_settings::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

} }