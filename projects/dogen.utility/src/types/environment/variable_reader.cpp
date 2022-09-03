/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <cstdlib>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/environment/environment_exception.hpp"
#include "dogen.utility/types/environment/variable_reader.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("utility.environment.variable_reader"));

const std::string empty;
const std::string environment_variable_name_empty(
    "Environment variable name is empty");
const std::string environment_variable_empty(
    "Environment variable is empty or not defined: ");

}

namespace dogen::utility::environment {

std::string variable_reader::
read_environment_variable(const std::string& n) {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Environment variable name not supplied";
        return empty;
    }

#ifdef _MSC_VER
    /*
     * First, we call getenv_s without a buffer to determine the
     * correct string length.
     */
    size_t length = 0;
    if ((getenv_s(&length, NULL, 0, n.c_str()) != 0) || (length == 0)) {
        BOOST_LOG_SEV(lg, debug) << "Environment variable is empty.";
        return empty;
    }

    /*
     * Then, we call it again to retrieve the value of the environment variable.
     * Note that 'length' already accounts for the null-terminator
     */
    std::string r(length - 1, '@');
    size_t read = 0;
    if ((getenv_s(&read, &r[0], length, n.c_str()) != 0) || (read != length)) {
        BOOST_LOG_SEV(lg, debug) << "Environment variable is empty.";
        return empty;
    }

    return r;
#else
    const char* v = std::getenv(n.c_str());
    if (v == nullptr) {
        BOOST_LOG_SEV(lg, debug) << "Environment variable is not defined.";
        return {};
    }

    const std::string r(v);
    BOOST_LOG_SEV(lg, debug) << "Read variable. Value: " << r;
    return r;
#endif
}

std::string variable_reader::
strict_read_environment_variable(const std::string& n) {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << environment_variable_name_empty;
        BOOST_THROW_EXCEPTION(
            environment_exception(environment_variable_name_empty));
    }

    const auto r(read_environment_variable(n));
    if (r.empty()) {
        BOOST_LOG_SEV(lg, error) << environment_variable_empty + n;
        BOOST_THROW_EXCEPTION(
            environment_exception(environment_variable_empty + n));
    }
    return r;
}

}
