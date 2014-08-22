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
#include "dogen/test_models/stereotypes/types/identity_pod_unversioned_key.hpp"

namespace dogen {
namespace test_models {
namespace stereotypes {

identity_pod_unversioned_key::identity_pod_unversioned_key(const dogen::test_models::stereotypes::value& prop_0)
    : prop_0_(prop_0) { }

void identity_pod_unversioned_key::swap(identity_pod_unversioned_key& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool identity_pod_unversioned_key::operator==(const identity_pod_unversioned_key& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

identity_pod_unversioned_key& identity_pod_unversioned_key::operator=(identity_pod_unversioned_key other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::stereotypes::value& identity_pod_unversioned_key::prop_0() const {
    return prop_0_;
}

dogen::test_models::stereotypes::value& identity_pod_unversioned_key::prop_0() {
    return prop_0_;
}

void identity_pod_unversioned_key::prop_0(const dogen::test_models::stereotypes::value& v) {
    prop_0_ = v;
}

void identity_pod_unversioned_key::prop_0(const dogen::test_models::stereotypes::value&& v) {
    prop_0_ = std::move(v);
}

} } }