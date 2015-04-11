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
#include "dogen/stitch/types/mixed_content_block.hpp"

namespace dogen {
namespace stitch {

mixed_content_block::mixed_content_block(const std::list<boost::variant<std::string, dogen::stitch::mixed_content_line> >& content)
    : content_(content) { }

void mixed_content_block::swap(mixed_content_block& other) noexcept {
    using std::swap;
    swap(content_, other.content_);
}

bool mixed_content_block::operator==(const mixed_content_block& rhs) const {
    return content_ == rhs.content_;
}

mixed_content_block& mixed_content_block::operator=(mixed_content_block other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<boost::variant<std::string, dogen::stitch::mixed_content_line> >& mixed_content_block::content() const {
    return content_;
}

std::list<boost::variant<std::string, dogen::stitch::mixed_content_line> >& mixed_content_block::content() {
    return content_;
}

void mixed_content_block::content(const std::list<boost::variant<std::string, dogen::stitch::mixed_content_line> >& v) {
    content_ = v;
}

void mixed_content_block::content(const std::list<boost::variant<std::string, dogen::stitch::mixed_content_line> >&& v) {
    content_ = std::move(v);
}

} }