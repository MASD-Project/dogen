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
#ifndef DOGEN_FORMATTERS_TYPES_CODE_GENERATION_MARKER_PROPERTY_SHEET_HPP
#define DOGEN_FORMATTERS_TYPES_CODE_GENERATION_MARKER_PROPERTY_SHEET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/formatters/serialization/code_generation_marker_property_sheet_fwd_ser.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Properties of the code generation marker associated with this file.
 */
class code_generation_marker_property_sheet final {
public:
    code_generation_marker_property_sheet(const code_generation_marker_property_sheet&) = default;
    code_generation_marker_property_sheet(code_generation_marker_property_sheet&&) = default;
    ~code_generation_marker_property_sheet() = default;

public:
    code_generation_marker_property_sheet();

public:
    code_generation_marker_property_sheet(
        const bool add_date_time,
        const bool add_warning,
        const std::string& message);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const code_generation_marker_property_sheet& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, code_generation_marker_property_sheet& v, unsigned int version);

public:
    /**
     * @brief If true, add the generation date and time to the marker.
     */
    /**@{*/
    bool add_date_time() const;
    void add_date_time(const bool v);
    /**@}*/

    /**
     * @brief If true, adds a warning not to modify code-generated files.
     */
    /**@{*/
    bool add_warning() const;
    void add_warning(const bool v);
    /**@}*/

    /**
     * @brief Message to place on all code-generated files.
     */
    /**@{*/
    const std::string& message() const;
    std::string& message();
    void message(const std::string& v);
    void message(const std::string&& v);
    /**@}*/

public:
    bool operator==(const code_generation_marker_property_sheet& rhs) const;
    bool operator!=(const code_generation_marker_property_sheet& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(code_generation_marker_property_sheet& other) noexcept;
    code_generation_marker_property_sheet& operator=(code_generation_marker_property_sheet other);

private:
    bool add_date_time_;
    bool add_warning_;
    std::string message_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatters::code_generation_marker_property_sheet& lhs,
    dogen::formatters::code_generation_marker_property_sheet& rhs) {
    lhs.swap(rhs);
}

}

#endif
