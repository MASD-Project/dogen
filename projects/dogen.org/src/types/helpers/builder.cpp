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
#include "dogen.org/types/helpers/node.hpp"
#include "dogen.org/types/helpers/builder.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::org::helpers::node>& lhs,
const boost::shared_ptr<dogen::org::helpers::node>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::org::helpers {

builder::builder(const boost::shared_ptr<dogen::org::helpers::node>& root_)
    : root__(root_) { }

void builder::swap(builder& other) noexcept {
    using std::swap;
    swap(root__, other.root__);
}

bool builder::operator==(const builder& rhs) const {
    return root__ == rhs.root__;
}

builder& builder::operator=(builder other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::org::helpers::node>& builder::root_() const {
    return root__;
}

boost::shared_ptr<dogen::org::helpers::node>& builder::root_() {
    return root__;
}

void builder::root_(const boost::shared_ptr<dogen::org::helpers::node>& v) {
    root__ = v;
}

void builder::root_(const boost::shared_ptr<dogen::org::helpers::node>&& v) {
    root__ = std::move(v);
}

}
