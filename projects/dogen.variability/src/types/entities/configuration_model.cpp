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
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/configuration_model.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::entities::configuration>& lhs,
const boost::shared_ptr<dogen::variability::entities::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::variability::entities {

configuration_model::configuration_model(
    const boost::shared_ptr<dogen::variability::entities::configuration>& global,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::variability::entities::configuration> >& local)
    : global_(global),
      local_(local) { }

void configuration_model::swap(configuration_model& other) noexcept {
    using std::swap;
    swap(global_, other.global_);
    swap(local_, other.local_);
}

bool configuration_model::operator==(const configuration_model& rhs) const {
    return global_ == rhs.global_ &&
        local_ == rhs.local_;
}

configuration_model& configuration_model::operator=(configuration_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::variability::entities::configuration>& configuration_model::global() const {
    return global_;
}

boost::shared_ptr<dogen::variability::entities::configuration>& configuration_model::global() {
    return global_;
}

void configuration_model::global(const boost::shared_ptr<dogen::variability::entities::configuration>& v) {
    global_ = v;
}

void configuration_model::global(const boost::shared_ptr<dogen::variability::entities::configuration>&& v) {
    global_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::variability::entities::configuration> >& configuration_model::local() const {
    return local_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::variability::entities::configuration> >& configuration_model::local() {
    return local_;
}

void configuration_model::local(const std::unordered_map<std::string, boost::shared_ptr<dogen::variability::entities::configuration> >& v) {
    local_ = v;
}

void configuration_model::local(const std::unordered_map<std::string, boost::shared_ptr<dogen::variability::entities::configuration> >&& v) {
    local_ = std::move(v);
}

}
