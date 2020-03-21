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
#include "dogen.m2t.cpp/types/formattables/locator_facet_configuration.hpp"

namespace dogen::m2t::cpp::formattables {

locator_facet_configuration::locator_facet_configuration(
    const std::string& directory,
    const std::string& postfix)
    : directory_(directory),
      postfix_(postfix) { }

void locator_facet_configuration::swap(locator_facet_configuration& other) noexcept {
    using std::swap;
    swap(directory_, other.directory_);
    swap(postfix_, other.postfix_);
}

bool locator_facet_configuration::operator==(const locator_facet_configuration& rhs) const {
    return directory_ == rhs.directory_ &&
        postfix_ == rhs.postfix_;
}

locator_facet_configuration& locator_facet_configuration::operator=(locator_facet_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& locator_facet_configuration::directory() const {
    return directory_;
}

std::string& locator_facet_configuration::directory() {
    return directory_;
}

void locator_facet_configuration::directory(const std::string& v) {
    directory_ = v;
}

void locator_facet_configuration::directory(const std::string&& v) {
    directory_ = std::move(v);
}

const std::string& locator_facet_configuration::postfix() const {
    return postfix_;
}

std::string& locator_facet_configuration::postfix() {
    return postfix_;
}

void locator_facet_configuration::postfix(const std::string& v) {
    postfix_ = v;
}

void locator_facet_configuration::postfix(const std::string&& v) {
    postfix_ = std::move(v);
}

}
