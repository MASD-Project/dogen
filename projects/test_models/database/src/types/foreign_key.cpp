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
#include "dogen/test_models/database/types/foreign_key.hpp"
#include "dogen/test_models/database/types/primary_key_2.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::test_models::database::primary_key_2>& lhs,
const boost::shared_ptr<dogen::test_models::database::primary_key_2>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace test_models {
namespace database {

foreign_key::foreign_key()
    : prop_0_(static_cast<unsigned int>(0)) { }

foreign_key::foreign_key(
    const unsigned int prop_0,
    const boost::shared_ptr<dogen::test_models::database::primary_key_2>& prop_1)
    : prop_0_(prop_0),
      prop_1_(prop_1) { }

void foreign_key::swap(foreign_key& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
}

bool foreign_key::operator==(const foreign_key& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_;
}

foreign_key& foreign_key::operator=(foreign_key other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

unsigned int foreign_key::prop_0() const {
    return prop_0_;
}

void foreign_key::prop_0(const unsigned int v) {
    prop_0_ = v;
}

const boost::shared_ptr<dogen::test_models::database::primary_key_2>& foreign_key::prop_1() const {
    return prop_1_;
}

boost::shared_ptr<dogen::test_models::database::primary_key_2>& foreign_key::prop_1() {
    return prop_1_;
}

void foreign_key::prop_1(const boost::shared_ptr<dogen::test_models::database::primary_key_2>& v) {
    prop_1_ = v;
}

void foreign_key::prop_1(const boost::shared_ptr<dogen::test_models::database::primary_key_2>&& v) {
    prop_1_ = std::move(v);
}

} } }
