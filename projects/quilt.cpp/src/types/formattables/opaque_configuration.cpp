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
#include "dogen/quilt.cpp/types/annotations/opaque_annotations.hpp"
#include "dogen/quilt.cpp/types/formattables/opaque_configuration.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>& lhs,
const boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

opaque_configuration::opaque_configuration(
    const boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>& top_level,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& property_level)
    : top_level_(top_level),
      property_level_(property_level) { }

void opaque_configuration::swap(opaque_configuration& other) noexcept {
    using std::swap;
    swap(top_level_, other.top_level_);
    swap(property_level_, other.property_level_);
}

bool opaque_configuration::operator==(const opaque_configuration& rhs) const {
    return top_level_ == rhs.top_level_ &&
        property_level_ == rhs.property_level_;
}

opaque_configuration& opaque_configuration::operator=(opaque_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>& opaque_configuration::top_level() const {
    return top_level_;
}

boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>& opaque_configuration::top_level() {
    return top_level_;
}

void opaque_configuration::top_level(const boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>& v) {
    top_level_ = v;
}

void opaque_configuration::top_level(const boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>&& v) {
    top_level_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& opaque_configuration::property_level() const {
    return property_level_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& opaque_configuration::property_level() {
    return property_level_;
}

void opaque_configuration::property_level(const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& v) {
    property_level_ = v;
}

void opaque_configuration::property_level(const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >&& v) {
    property_level_ = std::move(v);
}

} } } }
