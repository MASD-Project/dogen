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
#include "dogen/yarn/types/mapping_value.hpp"

namespace dogen {
namespace yarn {

mapping_value::mapping_value(
    const dogen::yarn::name& default_name,
    const std::list<dogen::yarn::name>& aliases)
    : default_name_(default_name),
      aliases_(aliases) { }

void mapping_value::swap(mapping_value& other) noexcept {
    using std::swap;
    swap(default_name_, other.default_name_);
    swap(aliases_, other.aliases_);
}

bool mapping_value::operator==(const mapping_value& rhs) const {
    return default_name_ == rhs.default_name_ &&
        aliases_ == rhs.aliases_;
}

mapping_value& mapping_value::operator=(mapping_value other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::yarn::name& mapping_value::default_name() const {
    return default_name_;
}

dogen::yarn::name& mapping_value::default_name() {
    return default_name_;
}

void mapping_value::default_name(const dogen::yarn::name& v) {
    default_name_ = v;
}

void mapping_value::default_name(const dogen::yarn::name&& v) {
    default_name_ = std::move(v);
}

const std::list<dogen::yarn::name>& mapping_value::aliases() const {
    return aliases_;
}

std::list<dogen::yarn::name>& mapping_value::aliases() {
    return aliases_;
}

void mapping_value::aliases(const std::list<dogen::yarn::name>& v) {
    aliases_ = v;
}

void mapping_value::aliases(const std::list<dogen::yarn::name>&& v) {
    aliases_ = std::move(v);
}

} }
