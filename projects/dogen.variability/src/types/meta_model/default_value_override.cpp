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
#include "dogen.variability/types/meta_model/value.hpp"
#include "dogen.variability/types/meta_model/default_value_override.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::meta_model::value>& lhs,
const boost::shared_ptr<dogen::variability::meta_model::value>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::variability::meta_model {

default_value_override::default_value_override(
    const std::string& key,
    const boost::shared_ptr<dogen::variability::meta_model::value>& value)
    : key_(key),
      value_(value) { }

void default_value_override::swap(default_value_override& other) noexcept {
    using std::swap;
    swap(key_, other.key_);
    swap(value_, other.value_);
}

bool default_value_override::operator==(const default_value_override& rhs) const {
    return key_ == rhs.key_ &&
        value_ == rhs.value_;
}

default_value_override& default_value_override::operator=(default_value_override other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& default_value_override::key() const {
    return key_;
}

std::string& default_value_override::key() {
    return key_;
}

void default_value_override::key(const std::string& v) {
    key_ = v;
}

void default_value_override::key(const std::string&& v) {
    key_ = std::move(v);
}

const boost::shared_ptr<dogen::variability::meta_model::value>& default_value_override::value() const {
    return value_;
}

boost::shared_ptr<dogen::variability::meta_model::value>& default_value_override::value() {
    return value_;
}

void default_value_override::value(const boost::shared_ptr<dogen::variability::meta_model::value>& v) {
    value_ = v;
}

void default_value_override::value(const boost::shared_ptr<dogen::variability::meta_model::value>&& v) {
    value_ = std::move(v);
}

}
