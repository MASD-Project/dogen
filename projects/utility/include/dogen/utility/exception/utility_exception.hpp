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
#ifndef DOGEN_UTILITY_EXCEPTION_EXCEPTION_HPP
#define DOGEN_UTILITY_EXCEPTION_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/exception/info.hpp>

namespace dogen {
namespace utility {

/**
 * @brief
 */
namespace exception {

/**
 * @brief base class for all exceptions within dogen.
 *
 * Exceptions should have a descriptive error message which must be
 * passed in as a string literal; any additional (variable) exception
 * information must be passed in via tags. See "Transporting of
 * Arbitrary Data to the Catch Site" in the boost::exception
 * documentation.
 */
class exception : public virtual std::exception,
                  public virtual boost::exception {
public:
    // to use BOOST_THROW_EXCEPTION we need to provide a default constructor.
    exception() { }

    /**
     * @param message Error message. Must be a string literal.
     */
    exception(const std::string& message) : message_(message) { }
    virtual ~exception() throw() { }

public:
    const char* what() const throw() { return message_.c_str(); }

private:
    const std::string message_;
};

} } }

#endif
