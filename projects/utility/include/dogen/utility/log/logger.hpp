/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_LOG_LOGGER_HPP
#define DOGEN_UTILITY_LOG_LOGGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include "dogen/utility/log/severity_level.hpp"

namespace dogen {
namespace utility {
namespace log {

typedef boost::log::sources::severity_channel_logger<
    severity_level,
    std::string
    > logger;

logger logger_factory(std::string component_name);

} } }

#endif
