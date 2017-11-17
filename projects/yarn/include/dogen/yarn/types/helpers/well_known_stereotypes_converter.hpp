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
#ifndef DOGEN_YARN_TYPES_HELPERS_WELL_KNOWN_STEREOTYPES_CONVERTER_HPP
#define DOGEN_YARN_TYPES_HELPERS_WELL_KNOWN_STEREOTYPES_CONVERTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include "dogen/yarn/types/meta_model/well_known_stereotypes.hpp"
#include "dogen/yarn/types/helpers/stereotypes_conversion_result.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

/**
 * @brief Converts well-known stereotypes from and to strings.
 */
class well_known_stereotypes_converter final {
public:
    /**
     * @brief Converts a string with a single well-known stereotype
     * into its enum.
     *
     * @note The string must not have any leading or trailing spaces
     * or other artefacts and must match exactly the definition of a
     * well-known yarn stereotype, e.g. 'yarn::object', etc.
     */
    static meta_model::well_known_stereotypes from_string(const std::string& s);

public:
    /**
     * @brief Given a CSV-separated string, returns the set of
     * well-known stereotypes as well as those it does not know of.
     */
    static stereotypes_conversion_result from_csv_string(const std::string& s);

    /**
     * @brief Converts a well-known stereotype to its string representation.
     */
    static std::string to_string(const meta_model::well_known_stereotypes st);
};

} } }

#endif
