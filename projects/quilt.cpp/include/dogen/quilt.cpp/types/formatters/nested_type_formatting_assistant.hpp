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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_NESTED_TYPE_FORMATTING_ASSISTANT_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_NESTED_TYPE_FORMATTING_ASSISTANT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <ostream>
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/quilt.cpp/types/properties/nested_type_info.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

/**
 * @brief Provides a number of utilities to formatters that generate
 * helper methods for nested types.
 */
class nested_type_formatting_assistant final {
public:
    explicit nested_type_formatting_assistant(std::ostream& s);

public:
    /**
     * @brief Returns a scoped namespace formatter.
     */
    dogen::formatters::cpp::scoped_namespace_formatter
    make_scoped_namespace_formatter(const std::list<std::string>& ns);

private:
    /**
     * @brief Returns true if type requires quoting.
     */
    bool requires_quoting(const properties::nested_type_info& t) const;

    /**
     * @brief Returns true if type requires generic string call.
     */
    bool requires_generic_string(const properties::nested_type_info& t) const;

    /**
     * @brief Returns true if type requires tidying up call.
     */
    bool requires_tidying_up(const properties::nested_type_info& t) const;

public:
    /**
     * @brief Returns true if the type can be hashed without requiring a
     * helper method.
     */
    static bool requires_hashing_helper_method(
        const properties::nested_type_info& t);

public:
    /**
     * @brief Returns the correct streaming invocation for the
     * supplied type.
     */
    std::string streaming_for_type(const properties::nested_type_info& t,
        const std::string& s) const;

public:
    /**
     * @brief Returns the stream that is currently being populated.
     */
    std::ostream& stream();

private:
    std::ostream& stream_;
};

} } } }

#endif
