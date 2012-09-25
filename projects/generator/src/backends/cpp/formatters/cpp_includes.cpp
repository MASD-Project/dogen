/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"

namespace {

const std::string include("#include ");
const std::string open_system("<");
const std::string close_system(">");
const std::string open_user("\"");
const std::string close_user("\"");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

cpp_includes::cpp_includes(std::ostream& stream) : stream_(stream) {}

void cpp_includes::format(std::list<std::string> value, bool is_system) {
    value.sort();
    for (auto i : value) {
        stream_ << include << (is_system ? open_system : open_user)
                << i
                << (is_system ? close_system : close_user)
                << std::endl;
    }
}

} } } } }
