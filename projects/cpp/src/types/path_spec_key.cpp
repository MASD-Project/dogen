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
#include "dogen/cpp/types/path_spec_key.hpp"

namespace dogen {
namespace cpp {

path_spec_key::path_spec_key(
    const std::string& formatter_id,
    const dogen::sml::qname& qname)
    : formatter_id_(formatter_id),
      qname_(qname) { }

void path_spec_key::swap(path_spec_key& other) noexcept {
    using std::swap;
    swap(formatter_id_, other.formatter_id_);
    swap(qname_, other.qname_);
}

bool path_spec_key::operator==(const path_spec_key& rhs) const {
    return formatter_id_ == rhs.formatter_id_ &&
        qname_ == rhs.qname_;
}

path_spec_key& path_spec_key::operator=(path_spec_key other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& path_spec_key::formatter_id() const {
    return formatter_id_;
}

std::string& path_spec_key::formatter_id() {
    return formatter_id_;
}

void path_spec_key::formatter_id(const std::string& v) {
    formatter_id_ = v;
}

void path_spec_key::formatter_id(const std::string&& v) {
    formatter_id_ = std::move(v);
}

const dogen::sml::qname& path_spec_key::qname() const {
    return qname_;
}

dogen::sml::qname& path_spec_key::qname() {
    return qname_;
}

void path_spec_key::qname(const dogen::sml::qname& v) {
    qname_ = v;
}

void path_spec_key::qname(const dogen::sml::qname&& v) {
    qname_ = std::move(v);
}

} }