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
#include "dogen.identification/types/helpers/node.hpp"
#include "dogen.identification/types/helpers/logical_name_tree_builder.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::identification::helpers::node>& lhs,
const boost::shared_ptr<dogen::identification::helpers::node>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::identification::helpers {

logical_name_tree_builder::logical_name_tree_builder(
    const std::list<std::string>& names_,
    const boost::shared_ptr<dogen::identification::helpers::node>& root_,
    const boost::shared_ptr<dogen::identification::helpers::node>& current_)
    : names__(names_),
      root__(root_),
      current__(current_) { }

void logical_name_tree_builder::swap(logical_name_tree_builder& other) noexcept {
    using std::swap;
    swap(names__, other.names__);
    swap(root__, other.root__);
    swap(current__, other.current__);
}

bool logical_name_tree_builder::operator==(const logical_name_tree_builder& rhs) const {
    return names__ == rhs.names__ &&
        root__ == rhs.root__ &&
        current__ == rhs.current__;
}

logical_name_tree_builder& logical_name_tree_builder::operator=(logical_name_tree_builder other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& logical_name_tree_builder::names_() const {
    return names__;
}

std::list<std::string>& logical_name_tree_builder::names_() {
    return names__;
}

void logical_name_tree_builder::names_(const std::list<std::string>& v) {
    names__ = v;
}

void logical_name_tree_builder::names_(const std::list<std::string>&& v) {
    names__ = std::move(v);
}

const boost::shared_ptr<dogen::identification::helpers::node>& logical_name_tree_builder::root_() const {
    return root__;
}

boost::shared_ptr<dogen::identification::helpers::node>& logical_name_tree_builder::root_() {
    return root__;
}

void logical_name_tree_builder::root_(const boost::shared_ptr<dogen::identification::helpers::node>& v) {
    root__ = v;
}

void logical_name_tree_builder::root_(const boost::shared_ptr<dogen::identification::helpers::node>&& v) {
    root__ = std::move(v);
}

const boost::shared_ptr<dogen::identification::helpers::node>& logical_name_tree_builder::current_() const {
    return current__;
}

boost::shared_ptr<dogen::identification::helpers::node>& logical_name_tree_builder::current_() {
    return current__;
}

void logical_name_tree_builder::current_(const boost::shared_ptr<dogen::identification::helpers::node>& v) {
    current__ = v;
}

void logical_name_tree_builder::current_(const boost::shared_ptr<dogen::identification::helpers::node>&& v) {
    current__ = std::move(v);
}

}
