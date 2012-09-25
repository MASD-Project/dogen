/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
