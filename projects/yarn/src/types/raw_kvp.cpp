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
#include "dogen/yarn/types/raw_kvp.hpp"

namespace dogen {
namespace yarn {

raw_kvp::raw_kvp(
    const std::list<std::pair<std::string, std::string> >& element,
    const std::unordered_map<std::string, std::list<std::pair<std::string, std::string> > >& attributes)
    : element_(element),
      attributes_(attributes) { }

void raw_kvp::swap(raw_kvp& other) noexcept {
    using std::swap;
    swap(element_, other.element_);
    swap(attributes_, other.attributes_);
}

bool raw_kvp::operator==(const raw_kvp& rhs) const {
    return element_ == rhs.element_ &&
        attributes_ == rhs.attributes_;
}

raw_kvp& raw_kvp::operator=(raw_kvp other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::pair<std::string, std::string> >& raw_kvp::element() const {
    return element_;
}

std::list<std::pair<std::string, std::string> >& raw_kvp::element() {
    return element_;
}

void raw_kvp::element(const std::list<std::pair<std::string, std::string> >& v) {
    element_ = v;
}

void raw_kvp::element(const std::list<std::pair<std::string, std::string> >&& v) {
    element_ = std::move(v);
}

const std::unordered_map<std::string, std::list<std::pair<std::string, std::string> > >& raw_kvp::attributes() const {
    return attributes_;
}

std::unordered_map<std::string, std::list<std::pair<std::string, std::string> > >& raw_kvp::attributes() {
    return attributes_;
}

void raw_kvp::attributes(const std::unordered_map<std::string, std::list<std::pair<std::string, std::string> > >& v) {
    attributes_ = v;
}

void raw_kvp::attributes(const std::unordered_map<std::string, std::list<std::pair<std::string, std::string> > >&& v) {
    attributes_ = std::move(v);
}

} }
