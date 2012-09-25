/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include <string>
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"

namespace  {
const std::string one_indent("    ");
}


namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

void cpp_indenter::to_stream(std::ostream& stream) const {
    for (unsigned int i(0); i < indent_level_; ++i)
        stream << one_indent;
}

std::ostream& operator<<(std::ostream& stream, cpp_indenter indenter) {
    indenter.to_stream(stream);
    return stream;
}

} } } } }
