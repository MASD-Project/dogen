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
#include "dogen/wale/types/text_template.hpp"

namespace dogen {
namespace wale {

text_template::text_template(
    const dogen::wale::properties& properties,
    const std::string& content)
    : properties_(properties),
      content_(content) { }

void text_template::swap(text_template& other) noexcept {
    using std::swap;
    swap(properties_, other.properties_);
    swap(content_, other.content_);
}

bool text_template::operator==(const text_template& rhs) const {
    return properties_ == rhs.properties_ &&
        content_ == rhs.content_;
}

text_template& text_template::operator=(text_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::wale::properties& text_template::properties() const {
    return properties_;
}

dogen::wale::properties& text_template::properties() {
    return properties_;
}

void text_template::properties(const dogen::wale::properties& v) {
    properties_ = v;
}

void text_template::properties(const dogen::wale::properties&& v) {
    properties_ = std::move(v);
}

const std::string& text_template::content() const {
    return content_;
}

std::string& text_template::content() {
    return content_;
}

void text_template::content(const std::string& v) {
    content_ = v;
}

void text_template::content(const std::string&& v) {
    content_ = std::move(v);
}

} }
