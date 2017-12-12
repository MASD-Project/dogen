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
#include "dogen/test_models/boost_model/types/class_a.hpp"
#include "dogen/test_models/boost_model/types/some_service.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::test_models::boost_model::class_a>& lhs,
const boost::shared_ptr<dogen::test_models::boost_model::class_a>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace test_models {
namespace boost_model {

some_service::some_service(const boost::shared_ptr<dogen::test_models::boost_model::class_a>& prop_0)
    : prop_0_(prop_0) { }

void some_service::swap(some_service& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool some_service::operator==(const some_service& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

some_service& some_service::operator=(some_service other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::test_models::boost_model::class_a>& some_service::prop_0() const {
    return prop_0_;
}

boost::shared_ptr<dogen::test_models::boost_model::class_a>& some_service::prop_0() {
    return prop_0_;
}

void some_service::prop_0(const boost::shared_ptr<dogen::test_models::boost_model::class_a>& v) {
    prop_0_ = v;
}

void some_service::prop_0(const boost::shared_ptr<dogen::test_models::boost_model::class_a>&& v) {
    prop_0_ = std::move(v);
}

} } }
