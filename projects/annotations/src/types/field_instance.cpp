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
#include "dogen/annotations/types/value.hpp"
#include "dogen/annotations/types/field_instance.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::annotations::value>& lhs,
const boost::shared_ptr<dogen::annotations::value>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace annotations {

field_instance::field_instance(const boost::shared_ptr<dogen::annotations::value>& value)
    : value_(value) { }

void field_instance::swap(field_instance& other) noexcept {
    using std::swap;
    swap(value_, other.value_);
}

bool field_instance::operator==(const field_instance& rhs) const {
    return value_ == rhs.value_;
}

field_instance& field_instance::operator=(field_instance other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::annotations::value>& field_instance::value() const {
    return value_;
}

boost::shared_ptr<dogen::annotations::value>& field_instance::value() {
    return value_;
}

void field_instance::value(const boost::shared_ptr<dogen::annotations::value>& v) {
    value_ = v;
}

void field_instance::value(const boost::shared_ptr<dogen::annotations::value>&& v) {
    value_ = std::move(v);
}

} }
