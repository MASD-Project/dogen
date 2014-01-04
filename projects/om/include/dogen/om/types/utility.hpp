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
#ifndef DOGEN_OM_TYPES_UTILITY_HPP
#define DOGEN_OM_TYPES_UTILITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <iosfwd>
#include "dogen/om/types/padding_types.hpp"

namespace dogen {
namespace om {

class utility {
public:
    utility() = delete;
    utility(const utility&) = delete;
    ~utility() = default;
    utility(utility&&) = default;
    utility& operator=(const utility&) = delete;

public:
    utility(std::ostream& stream);

private:
    /**
     * @brief Perform the required padding before content, if any.
     */
    void handle_padding_before(const padding_types padding);

    /**
     * @brief Perform the required padding after content, if any.
     */
    void handle_padding_after(const padding_types padding);

public:
    /**
     * @brief C++ access specifiers, followed by ':'.
     */
    /**@{*/
    void public_access_specifier(
        const padding_types padding = padding_types::new_line,
        const bool reset_management = false);
    void protected_access_specifier(
        const padding_types padding = padding_types::new_line,
        const bool reset_management = false);
    void private_access_specifier(
        const padding_types padding = padding_types::new_line,
        const bool reset_management = false);
    /**@}*/

    /**
     * @brief Open a C++ scope.
     */
    void open_scope(const padding_types padding = padding_types::none);

    /**
     * @brief Close a C++ scope.
     */
    void close_scope(const padding_types padding = padding_types::none);

    /**
     * @brief Add a number of blank lines.
     *
     * @param is_managed If true, the managed blank lines manipulator
     * will be inserted into the stream.
     * @param how_many determines how many blank lines to add.
     */
    void blank_line(const bool is_managed = false,
        const unsigned int how_many = 1);

    /**
     * @brief Adds a single, managed blank line.
     *
     * Equivalent to calling blank_line(true, 1);
     */
    void managed_blank_line();

    /**
     * @brief Formats the input as a member variable.
     */
    std::string as_member_variable(const std::string& property_name) const;

    /**
     * @brief Formats the input as a getter of a property.
     */
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
};

} }

#endif
