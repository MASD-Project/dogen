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
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/types/element.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::element>& lhs,
const boost::shared_ptr<dogen::yarn::element>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace yarn {

model::model(
    const dogen::yarn::name& name,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >& elements,
    const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& references,
    const std::unordered_set<dogen::yarn::name>& leaves,
    const dogen::yarn::module& root_module)
    : name_(name),
      elements_(elements),
      references_(references),
      leaves_(leaves),
      root_module_(root_module) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(elements_, other.elements_);
    swap(references_, other.references_);
    swap(leaves_, other.leaves_);
    swap(root_module_, other.root_module_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        elements_ == rhs.elements_ &&
        references_ == rhs.references_ &&
        leaves_ == rhs.leaves_ &&
        root_module_ == rhs.root_module_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::yarn::name& model::name() const {
    return name_;
}

dogen::yarn::name& model::name() {
    return name_;
}

void model::name(const dogen::yarn::name& v) {
    name_ = v;
}

void model::name(const dogen::yarn::name&& v) {
    name_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >& model::elements() const {
    return elements_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >& model::elements() {
    return elements_;
}

void model::elements(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >& v) {
    elements_ = v;
}

void model::elements(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >&& v) {
    elements_ = std::move(v);
}

const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& model::references() const {
    return references_;
}

std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& model::references() {
    return references_;
}

void model::references(const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& v) {
    references_ = v;
}

void model::references(const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>&& v) {
    references_ = std::move(v);
}

const std::unordered_set<dogen::yarn::name>& model::leaves() const {
    return leaves_;
}

std::unordered_set<dogen::yarn::name>& model::leaves() {
    return leaves_;
}

void model::leaves(const std::unordered_set<dogen::yarn::name>& v) {
    leaves_ = v;
}

void model::leaves(const std::unordered_set<dogen::yarn::name>&& v) {
    leaves_ = std::move(v);
}

const dogen::yarn::module& model::root_module() const {
    return root_module_;
}

dogen::yarn::module& model::root_module() {
    return root_module_;
}

void model::root_module(const dogen::yarn::module& v) {
    root_module_ = v;
}

void model::root_module(const dogen::yarn::module&& v) {
    root_module_ = std::move(v);
}

} }
