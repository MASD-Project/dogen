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
#include "dogen.assets/types/helpers/decomposition_result.hpp"

namespace dogen::assets::helpers {

decomposition_result::decomposition_result(
    const std::list<std::pair<std::string, dogen::assets::meta_model::name> >& names,
    const std::list<std::pair<std::string, dogen::assets::meta_model::name> >& meta_names,
    const std::list<std::pair<std::string, dogen::assets::meta_model::name_tree> >& name_trees)
    : names_(names),
      meta_names_(meta_names),
      name_trees_(name_trees) { }

void decomposition_result::swap(decomposition_result& other) noexcept {
    using std::swap;
    swap(names_, other.names_);
    swap(meta_names_, other.meta_names_);
    swap(name_trees_, other.name_trees_);
}

bool decomposition_result::operator==(const decomposition_result& rhs) const {
    return names_ == rhs.names_ &&
        meta_names_ == rhs.meta_names_ &&
        name_trees_ == rhs.name_trees_;
}

decomposition_result& decomposition_result::operator=(decomposition_result other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::pair<std::string, dogen::assets::meta_model::name> >& decomposition_result::names() const {
    return names_;
}

std::list<std::pair<std::string, dogen::assets::meta_model::name> >& decomposition_result::names() {
    return names_;
}

void decomposition_result::names(const std::list<std::pair<std::string, dogen::assets::meta_model::name> >& v) {
    names_ = v;
}

void decomposition_result::names(const std::list<std::pair<std::string, dogen::assets::meta_model::name> >&& v) {
    names_ = std::move(v);
}

const std::list<std::pair<std::string, dogen::assets::meta_model::name> >& decomposition_result::meta_names() const {
    return meta_names_;
}

std::list<std::pair<std::string, dogen::assets::meta_model::name> >& decomposition_result::meta_names() {
    return meta_names_;
}

void decomposition_result::meta_names(const std::list<std::pair<std::string, dogen::assets::meta_model::name> >& v) {
    meta_names_ = v;
}

void decomposition_result::meta_names(const std::list<std::pair<std::string, dogen::assets::meta_model::name> >&& v) {
    meta_names_ = std::move(v);
}

const std::list<std::pair<std::string, dogen::assets::meta_model::name_tree> >& decomposition_result::name_trees() const {
    return name_trees_;
}

std::list<std::pair<std::string, dogen::assets::meta_model::name_tree> >& decomposition_result::name_trees() {
    return name_trees_;
}

void decomposition_result::name_trees(const std::list<std::pair<std::string, dogen::assets::meta_model::name_tree> >& v) {
    name_trees_ = v;
}

void decomposition_result::name_trees(const std::list<std::pair<std::string, dogen::assets::meta_model::name_tree> >&& v) {
    name_trees_ = std::move(v);
}

}
