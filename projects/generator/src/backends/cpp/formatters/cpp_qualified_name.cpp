/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"

namespace {

const std::string separator("::");
}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

cpp_qualified_name::cpp_qualified_name(std::ostream& stream)
    : stream_(stream) { }

void cpp_qualified_name::format(view_models::class_view_model vm) {
    for(auto n : vm.namespaces())
        stream_ << n << separator;
    stream_ << vm.name();
}

} } } } }
