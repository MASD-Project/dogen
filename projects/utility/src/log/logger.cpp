/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/utility/log/logger.hpp"

namespace dogen {
namespace utility {
namespace log {

logger logger_factory(std::string component_name) {
    using namespace boost::log;
    return logger(keywords::channel = component_name);
}

} } }
