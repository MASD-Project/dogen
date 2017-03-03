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
#include "dogen/yarn/types/orm_module_configuration.hpp"

namespace dogen {
namespace yarn {

orm_module_configuration::orm_module_configuration(const std::string& schema_name)
    : schema_name_(schema_name) { }

void orm_module_configuration::swap(orm_module_configuration& other) noexcept {
    using std::swap;
    swap(schema_name_, other.schema_name_);
}

bool orm_module_configuration::operator==(const orm_module_configuration& rhs) const {
    return schema_name_ == rhs.schema_name_;
}

orm_module_configuration& orm_module_configuration::operator=(orm_module_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& orm_module_configuration::schema_name() const {
    return schema_name_;
}

std::string& orm_module_configuration::schema_name() {
    return schema_name_;
}

void orm_module_configuration::schema_name(const std::string& v) {
    schema_name_ = v;
}

void orm_module_configuration::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

} }
