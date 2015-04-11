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
#include <ostream>
#include "dogen/stitch/io/block_io.hpp"
#include "dogen/stitch/io/scriptlet_line_io.hpp"
#include "dogen/stitch/types/scriptlet_block.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::stitch::scriptlet_line>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace stitch {

scriptlet_block::scriptlet_block(const std::list<dogen::stitch::scriptlet_line>& content)
    : dogen::stitch::block(),
      content_(content) { }

void scriptlet_block::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::stitch::scriptlet_block\"" << ", "
      << "\"__parent_0__\": ";
    block::to_stream(s);
    s << ", "
      << "\"content\": " << content_
      << " }";
}

void scriptlet_block::swap(scriptlet_block& other) noexcept {
    block::swap(other);

    using std::swap;
    swap(content_, other.content_);
}

bool scriptlet_block::equals(const dogen::stitch::block& other) const {
    const scriptlet_block* const p(dynamic_cast<const scriptlet_block* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool scriptlet_block::operator==(const scriptlet_block& rhs) const {
    return block::compare(rhs) &&
        content_ == rhs.content_;
}

scriptlet_block& scriptlet_block::operator=(scriptlet_block other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::stitch::scriptlet_line>& scriptlet_block::content() const {
    return content_;
}

std::list<dogen::stitch::scriptlet_line>& scriptlet_block::content() {
    return content_;
}

void scriptlet_block::content(const std::list<dogen::stitch::scriptlet_line>& v) {
    content_ = v;
}

void scriptlet_block::content(const std::list<dogen::stitch::scriptlet_line>&& v) {
    content_ = std::move(v);
}

} }