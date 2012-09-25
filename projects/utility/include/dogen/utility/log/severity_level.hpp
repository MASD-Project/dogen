/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_LOG_SEVERITY_LEVEL_HPP
#define DOGEN_UTILITY_LOG_SEVERITY_LEVEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ostream>
#include "dogen/utility/exception/invalid_enum_value.hpp"

namespace dogen {
namespace utility {
namespace log {

/**
 * @brief Logging severity.
 *
 * This must be a C++-03 enum due to the boost::log internals.
 */
enum severity_level {
    fine_debug,
    debug,
    info,
    warn,
    error,
    fatal
};

/**
 * @brief Inserter for severity level enum.
 *
 * Required for interoperability with boost log.
 */
template<typename CharT, typename TraitsT>
inline std::basic_ostream<CharT, TraitsT>&
operator<<(std::basic_ostream<CharT, TraitsT>& stream, severity_level level) {
    switch(level) {
    case severity_level::fine_debug: stream << "FINE_DEBUG"; break;
    case severity_level::debug: stream << "DEBUG"; break;
    case severity_level::info: stream << "INFO"; break;
    case severity_level::warn: stream << "WARN"; break;
    case severity_level::error: stream << "ERROR"; break;
    case severity_level::fatal: stream << "FATAL"; break;
    default:
        using dogen::utility::exception::invalid_enum_value;
        throw invalid_enum_value("Invalid or unexpected severity level");
        break;
    }
    return stream;
}

} } }

#endif
