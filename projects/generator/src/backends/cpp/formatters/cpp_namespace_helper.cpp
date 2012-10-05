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
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"

namespace {

const std::string empty;

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

namespace_helper::namespace_helper(std::ostream& stream,
    const std::list<std::string>& namespaces)
    : stream_(stream), namespace_formatter_(stream), namespaces_(namespaces) {

    if (namespaces_.empty()) {
        namespace_formatter_.format_start(empty);
        return;
    }

    for (auto ns : namespaces_)
        namespace_formatter_.format_start(ns);
}

namespace_helper::~namespace_helper() {
    if (namespaces_.empty()) {
        namespace_formatter_.format_end();
        return;
    }

    bool first(true);
    for (auto ns : namespaces_) {
        if (!first)
            stream_ << " ";
        namespace_formatter_.format_end();
        first = false;
    }
}

} } } } }
