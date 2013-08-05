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
#include "dogen/cpp_formatters/types/qname.hpp"

namespace {

const std::string separator("::");

template<typename T>
void format(std::ostream& s, const T& t) {
    for(auto n : t.namespaces())
        s << n << separator;
    s << t.name();
}

}

namespace dogen {
namespace cpp_formatters {

qname::qname(std::ostream& stream)
    : stream_(stream) { }

void qname::format(const cpp::parent_info& pi) {
    ::format<cpp::parent_info>(stream_, pi);
}

void qname::format(const cpp::class_info& ci) {
    ::format<cpp::class_info>(stream_, ci);
}

void qname::format(const cpp::enum_info& ei) {
    ::format<cpp::enum_info>(stream_, ei);
}

} }
