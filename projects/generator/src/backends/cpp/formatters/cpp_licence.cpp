/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

licence::licence(std::ostream& stream)
    : stream_(stream) { }

void licence::format() {
    stream_ << "/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil;"
            << " c-basic-offset: 4 -*-" << std::endl
            << " *" << std::endl
            << " * Copyright (C) 2012 Kitanda" << std::endl
            << " *" << std::endl
            << " * This file is distributed under the Kitanda Proprietary Software" << std::endl
            << " * Licence. See doc/LICENCE.TXT for details." << std::endl
            << " *" << std::endl
            << " */" << std::endl;
}

} } } } }
