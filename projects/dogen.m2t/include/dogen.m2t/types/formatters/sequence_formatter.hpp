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
#ifndef DOGEN_M2T_TYPES_FORMATTERS_SEQUENCE_FORMATTER_HPP
#define DOGEN_M2T_TYPES_FORMATTERS_SEQUENCE_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.m2t/types/formatters/infix_configuration.hpp"

namespace dogen::m2t::formatters {

/**
 * @brief Helper to format sequences.
 */
class sequence_formatter {
public:
    template <typename SequenceSize>
    explicit sequence_formatter(const SequenceSize sequence_size)
        : position_(0),
          sequence_size_(static_cast<unsigned int>(sequence_size)),
          element_separator_(",") {}

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
     *
     * @param skip if true, moves to the next position and returns an
     * empty string. If false, returns the postfix for the current
     * position and moves to the next position.
     */
    std::string postfix(const bool skip = false) const;

public:
    /**
     * @brief Returns the current position.
     */
    unsigned int current_position() const;

    /**
     * @brief Logs the current state of the formatter to the log.
     */
    void log_current_state() const;

public:
    /**
     * @brief Sets the value of the element separator. By default it
     * is a comma.
     */
    void element_separator(const std::string& s);

    /**
     * @brief Moves to the next position.
     */
    void next();

    /**
     * @brief Resets the position and configurations.
     */
    /**@{*/
    void reset();
    template <typename SequenceSize>
    void reset(const SequenceSize sequence_size) {
        sequence_size_ = static_cast<unsigned int>(sequence_size);
        reset();
    }
    /**@}*/

private:
    unsigned int position_;
    unsigned int sequence_size_;
    std::string element_separator_;
    infix_configuration prefix_configuration_;
    infix_configuration postfix_configuration_;
};

}

#endif
