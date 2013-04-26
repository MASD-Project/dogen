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
#include "dogen/sml/types/string_table.hpp"

namespace dogen {
namespace sml {

string_table::string_table(
    const dogen::sml::qname& name,
    const std::string& documentation,
    const std::list<dogen::sml::entry>& entries)
    : name_(name),
      documentation_(documentation),
      entries_(entries) { }

void string_table::swap(string_table& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(documentation_, other.documentation_);
    swap(entries_, other.entries_);
}

bool string_table::operator==(const string_table& rhs) const {
    return name_ == rhs.name_ &&
        documentation_ == rhs.documentation_ &&
        entries_ == rhs.entries_;
}

string_table& string_table::operator=(string_table other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::sml::qname& string_table::name() const {
    return name_;
}

dogen::sml::qname& string_table::name() {
    return name_;
}

void string_table::name(const dogen::sml::qname& v) {
    name_ = v;
}

void string_table::name(const dogen::sml::qname&& v) {
    name_ = std::move(v);
}

const std::string& string_table::documentation() const {
    return documentation_;
}

std::string& string_table::documentation() {
    return documentation_;
}

void string_table::documentation(const std::string& v) {
    documentation_ = v;
}

void string_table::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::list<dogen::sml::entry>& string_table::entries() const {
    return entries_;
}

std::list<dogen::sml::entry>& string_table::entries() {
    return entries_;
}

void string_table::entries(const std::list<dogen::sml::entry>& v) {
    entries_ = v;
}

void string_table::entries(const std::list<dogen::sml::entry>&& v) {
    entries_ = std::move(v);
}

} }