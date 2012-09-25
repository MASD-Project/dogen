/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <sstream>
#include <ostream>
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

cpp_namespace::cpp_namespace(std::ostream& stream)
    : stream_(stream) { }

void cpp_namespace::format_start(std::string name) {
    stream_ << "namespace";
    if (name.empty())
        stream_ << " {";
    else
        stream_ << " " << name << " {";
    stream_ << std::endl;
}

void cpp_namespace::format_end() {
    stream_ << "}"; // no std::endl by design
}

} } } } }
