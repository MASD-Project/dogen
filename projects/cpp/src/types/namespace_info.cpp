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
#include "dogen/cpp/types/namespace_info.hpp"

namespace dogen {
namespace cpp {

namespace_info::namespace_info(
    const std::list<std::string>& namespaces,
    const std::string& documentation)
    : namespaces_(namespaces),
      documentation_(documentation) { }

void namespace_info::swap(namespace_info& other) noexcept {
    using std::swap;
    swap(namespaces_, other.namespaces_);
    swap(documentation_, other.documentation_);
}

bool namespace_info::operator==(const namespace_info& rhs) const {
    return namespaces_ == rhs.namespaces_ &&
        documentation_ == rhs.documentation_;
}

namespace_info& namespace_info::operator=(namespace_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& namespace_info::namespaces() const {
    return namespaces_;
}

std::list<std::string>& namespace_info::namespaces() {
    return namespaces_;
}

void namespace_info::namespaces(const std::list<std::string>& v) {
    namespaces_ = v;
}

void namespace_info::namespaces(const std::list<std::string>&& v) {
    namespaces_ = std::move(v);
}

const std::string& namespace_info::documentation() const {
    return documentation_;
}

std::string& namespace_info::documentation() {
    return documentation_;
}

void namespace_info::documentation(const std::string& v) {
    documentation_ = v;
}

void namespace_info::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

} }