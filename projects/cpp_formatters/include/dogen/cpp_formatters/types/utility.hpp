/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_FORMATTERS_TYPES_UTILITY_HPP
#define DOGEN_CPP_FORMATTERS_TYPES_UTILITY_HPP

#include <iosfwd>
#include <string>
#include "dogen/cpp_formatters/types/indenter.hpp"

namespace dogen {
namespace cpp_formatters {

class utility {
public:
    utility() = delete;
    utility(const utility&) = delete;
    ~utility() = default;
    utility(utility&&) = default;
    utility& operator=(const utility&) = delete;

public:
    utility(std::ostream& stream, indenter& indenter) :
        stream_(stream), indenter_(indenter) { }

public:
    /**
     * @brief Inserts the desired c++ access specifier.
     */
    /**@{*/
    void public_access_specifier();
    void protected_access_specifier();
    void private_access_specifier();
    /**@}*/

    void open_scope();
    void close_scope();
    void blank_line(unsigned int how_many = 1);
    std::string as_member_variable(const std::string& property_name) const;
    std::string as_getter(const std::string& property_name) const;

    /**
     * @brief Adds double quotes to original.
     *
     * Using single quotes to denote the string boundary (e.g. they
     * are not actually on the string), an original of 'a' produces
     * the output '"a"'.
     */
    std::string quote(const std::string& original) const;

    /**
     * @brief Adds escapped quotes to original.
     *
     * Using single quotes to denote the string boundary (e.g. they
     * are not actually on the string), an original of 'a' produces
     * the output '\"a\"'.
     */
    std::string quote_escaped(const std::string& original) const;

    /**
     * @brief Adds escapped quotes to original, with c++ streaming
     * syntax.
     *
     * Using single quotes to denote the string boundary (e.g. they
     * are not actually on the string), an original of 'a' produces
     * the output '<< "\"" << a << "\"""'.
     */
    std::string quote_escaped_streamed(const std::string& original) const;

private:
    std::ostream& stream_;
    indenter& indenter_;
};

} }

#endif
