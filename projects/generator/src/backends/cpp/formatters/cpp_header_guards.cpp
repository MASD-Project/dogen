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
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"

namespace {

const std::string ifndef("#ifndef ");
const std::string define("#define ");
const std::string endif("#endif");

const std::string msvc_line_1("#if defined(_MSC_VER) && (_MSC_VER >= 1200)");
const std::string msvc_line_2("#pragma once");
const std::string msvc_line_3("#endif");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

header_guards::header_guards(std::ostream& stream)
    : stream_(stream) { }

void header_guards::format_start(std::string guard_name) {
    stream_ << ifndef << guard_name;
    stream_ << std::endl << define << guard_name;

    stream_ << std::endl << std::endl
            << msvc_line_1 << std::endl
            << msvc_line_2 << std::endl
            << msvc_line_3 << std::endl;
}

void header_guards::format_end() {
    stream_ << endif << std::endl;
}

} } } } }
