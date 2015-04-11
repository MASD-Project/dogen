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
#include "dogen/stitch/types/scriptlet_block.hpp"

namespace dogen {
namespace stitch {

scriptlet_block::scriptlet_block(const std::list<std::string>& content)
    : content_(content) { }

void scriptlet_block::swap(scriptlet_block& other) noexcept {
    using std::swap;
    swap(content_, other.content_);
}

bool scriptlet_block::operator==(const scriptlet_block& rhs) const {
    return content_ == rhs.content_;
}

scriptlet_block& scriptlet_block::operator=(scriptlet_block other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& scriptlet_block::content() const {
    return content_;
}

std::list<std::string>& scriptlet_block::content() {
    return content_;
}

void scriptlet_block::content(const std::list<std::string>& v) {
    content_ = v;
}

void scriptlet_block::content(const std::list<std::string>&& v) {
    content_ = std::move(v);
}

} }