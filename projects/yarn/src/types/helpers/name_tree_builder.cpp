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
#include "dogen/yarn/types/helpers/node.hpp"
#include "dogen/yarn/types/helpers/name_tree_builder.hpp"

namespace std {

inline bool operator==(const std::shared_ptr<dogen::yarn::helpers::node>& lhs,
const std::shared_ptr<dogen::yarn::helpers::node>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace yarn {
namespace helpers {

name_tree_builder::name_tree_builder(
    const std::unordered_set<std::string>& top_level_modules_,
    const dogen::yarn::location& model_location_,
    const std::list<std::string>& names,
    const std::shared_ptr<dogen::yarn::helpers::node>& root,
    const std::shared_ptr<dogen::yarn::helpers::node>& current)
    : top_level_modules__(top_level_modules_),
      model_location__(model_location_),
      names_(names),
      root_(root),
      current_(current) { }

void name_tree_builder::swap(name_tree_builder& other) noexcept {
    using std::swap;
    swap(top_level_modules__, other.top_level_modules__);
    swap(model_location__, other.model_location__);
    swap(names_, other.names_);
    swap(root_, other.root_);
    swap(current_, other.current_);
}

bool name_tree_builder::operator==(const name_tree_builder& rhs) const {
    return top_level_modules__ == rhs.top_level_modules__ &&
        model_location__ == rhs.model_location__ &&
        names_ == rhs.names_ &&
        root_ == rhs.root_ &&
        current_ == rhs.current_;
}

name_tree_builder& name_tree_builder::operator=(name_tree_builder other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_set<std::string>& name_tree_builder::top_level_modules_() const {
    return top_level_modules__;
}

std::unordered_set<std::string>& name_tree_builder::top_level_modules_() {
    return top_level_modules__;
}

void name_tree_builder::top_level_modules_(const std::unordered_set<std::string>& v) {
    top_level_modules__ = v;
}

void name_tree_builder::top_level_modules_(const std::unordered_set<std::string>&& v) {
    top_level_modules__ = std::move(v);
}

const dogen::yarn::location& name_tree_builder::model_location_() const {
    return model_location__;
}

dogen::yarn::location& name_tree_builder::model_location_() {
    return model_location__;
}

void name_tree_builder::model_location_(const dogen::yarn::location& v) {
    model_location__ = v;
}

void name_tree_builder::model_location_(const dogen::yarn::location&& v) {
    model_location__ = std::move(v);
}

const std::list<std::string>& name_tree_builder::names() const {
    return names_;
}

std::list<std::string>& name_tree_builder::names() {
    return names_;
}

void name_tree_builder::names(const std::list<std::string>& v) {
    names_ = v;
}

void name_tree_builder::names(const std::list<std::string>&& v) {
    names_ = std::move(v);
}

const std::shared_ptr<dogen::yarn::helpers::node>& name_tree_builder::root() const {
    return root_;
}

std::shared_ptr<dogen::yarn::helpers::node>& name_tree_builder::root() {
    return root_;
}

void name_tree_builder::root(const std::shared_ptr<dogen::yarn::helpers::node>& v) {
    root_ = v;
}

void name_tree_builder::root(const std::shared_ptr<dogen::yarn::helpers::node>&& v) {
    root_ = std::move(v);
}

const std::shared_ptr<dogen::yarn::helpers::node>& name_tree_builder::current() const {
    return current_;
}

std::shared_ptr<dogen::yarn::helpers::node>& name_tree_builder::current() {
    return current_;
}

void name_tree_builder::current(const std::shared_ptr<dogen::yarn::helpers::node>& v) {
    current_ = v;
}

void name_tree_builder::current(const std::shared_ptr<dogen::yarn::helpers::node>&& v) {
    current_ = std::move(v);
}

} } }
