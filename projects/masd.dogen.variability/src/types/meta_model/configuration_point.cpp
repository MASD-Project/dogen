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
#include <ostream>
#include "masd.dogen.variability/io/meta_model/value_io.hpp"
#include "masd.dogen.variability/types/meta_model/value.hpp"
#include "masd.dogen.variability/io/meta_model/element_io.hpp"
#include "masd.dogen.variability/types/meta_model/configuration_point.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::variability::meta_model::value>& lhs,
const boost::shared_ptr<masd::dogen::variability::meta_model::value>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<masd::dogen::variability::meta_model::value>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace masd::dogen::variability::meta_model {

configuration_point::configuration_point(
    const masd::dogen::variability::meta_model::name& name,
    const std::string& description,
    const boost::shared_ptr<masd::dogen::variability::meta_model::value>& value)
    : masd::dogen::variability::meta_model::element(
      name,
      description),
      value_(value) { }

void configuration_point::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::variability::meta_model::configuration_point\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::variability::meta_model::element::to_stream(s);
    s << ", "
      << "\"value\": " << value_
      << " }";
}

void configuration_point::swap(configuration_point& other) noexcept {
    masd::dogen::variability::meta_model::element::swap(other);

    using std::swap;
    swap(value_, other.value_);
}

bool configuration_point::equals(const masd::dogen::variability::meta_model::element& other) const {
    const configuration_point* const p(dynamic_cast<const configuration_point* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool configuration_point::operator==(const configuration_point& rhs) const {
    return masd::dogen::variability::meta_model::element::compare(rhs) &&
        value_ == rhs.value_;
}

configuration_point& configuration_point::operator=(configuration_point other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<masd::dogen::variability::meta_model::value>& configuration_point::value() const {
    return value_;
}

boost::shared_ptr<masd::dogen::variability::meta_model::value>& configuration_point::value() {
    return value_;
}

void configuration_point::value(const boost::shared_ptr<masd::dogen::variability::meta_model::value>& v) {
    value_ = v;
}

void configuration_point::value(const boost::shared_ptr<masd::dogen::variability::meta_model::value>&& v) {
    value_ = std::move(v);
}

}
