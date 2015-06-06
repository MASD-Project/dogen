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
#ifndef DOGEN_FORMATTERS_TYPES_SEQUENCE_FORMATTER_HPP
#define DOGEN_FORMATTERS_TYPES_SEQUENCE_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/formatters/types/infix_configuration.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Helper to format sequences.
 */
class sequence_formatter {
public:
    sequence_formatter(const unsigned int sequence_size,
        const std::string& element_separator);

private:
    /**
     * @brief Returns true if we are at the first position.
     */
    bool is_first() const;

    /**
     * @brief Returns true if we are at the last position.
     */
    bool is_last() const;

    /**
     * @brief Returns true if sequence has only one element.
     */
    bool is_single() const;

    /**
     * @brief Returns the string for the current position.
     */
    std::string value_for_position(const infix_configuration& ic) const;

public:
    /**
     * @brief Configuration to use for the prefix.
     */
    infix_configuration& prefix_configuration();

    /**
     * @brief Configuration to use for the postfix.
     */

    infix_configuration& postfix_configuration();

public:
    /**
     * @brief Gets the prefix for the current position.
     */
    std::string prefix() const;

    /**
     * @brief Gets the postfix for the current position and moves to
     * the next position.
     */
    std::string postfix();

    /**
     * @brief Returns the current position.
     */
    unsigned int current_position() const;

    /**
     * @brief Resets the position and configurations.
     */
    /**@{*/
    void reset();
    void reset(const unsigned int sequence_size);
    /**@}*/

private:
    unsigned int sequence_size_;
    const std::string element_separator_;
    unsigned int position_;
    infix_configuration prefix_configuration_;
    infix_configuration postfix_configuration_;
};

} }

#endif
