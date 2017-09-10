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
#include "dogen/yarn/types/helpers/transform_metrics.hpp"
#include "dogen/yarn/types/helpers/transform_metrics_builder.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& lhs,
const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace yarn {
namespace helpers {

transform_metrics_builder::transform_metrics_builder(
    const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& root,
    const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& current_)
    : root_(root),
      current__(current_) { }

void transform_metrics_builder::swap(transform_metrics_builder& other) noexcept {
    using std::swap;
    swap(root_, other.root_);
    swap(current__, other.current__);
}

bool transform_metrics_builder::operator==(const transform_metrics_builder& rhs) const {
    return root_ == rhs.root_ &&
        current__ == rhs.current__;
}

transform_metrics_builder& transform_metrics_builder::operator=(transform_metrics_builder other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& transform_metrics_builder::root() const {
    return root_;
}

boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& transform_metrics_builder::root() {
    return root_;
}

void transform_metrics_builder::root(const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& v) {
    root_ = v;
}

void transform_metrics_builder::root(const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>&& v) {
    root_ = std::move(v);
}

const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& transform_metrics_builder::current_() const {
    return current__;
}

boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& transform_metrics_builder::current_() {
    return current__;
}

void transform_metrics_builder::current_(const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& v) {
    current__ = v;
}

void transform_metrics_builder::current_(const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>&& v) {
    current__ = std::move(v);
}

} } }
