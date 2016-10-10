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
#ifndef DOGEN_FORMATTERS_TEST_MOCK_DECORATION_PROPERTIES_FACTORY_HPP
#define DOGEN_FORMATTERS_TEST_MOCK_DECORATION_PROPERTIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen/formatters/types/licence.hpp"
#include "dogen/formatters/types/modeline.hpp"
#include "dogen/formatters/types/modeline_locations.hpp"
#include "dogen/formatters/types/decoration_properties.hpp"

namespace dogen {
namespace formatters {
namespace test {

class mock_decoration_properties_factory {
public:
    /**
     * @brief Generates a mode line.
     */
    modeline make_modeline(const modeline_locations l) const;

    /**
     * @brief Generates a licence.
     */
    licence make_licence(const bool is_empty = false,
        const bool is_multiline = false) const;

    /**
     * @brief Generates includes.
     */
    std::list<std::string> make_includes(const bool is_empty = false) const;

    /**
     * @brief Generates a code generation marker.
     */
    std::string make_marker(const bool is_empty = false) const;

    /**
     * @brief Generates a header guard.
     */
    std::string make_header_guard(const bool is_empty = false) const;

    /**
     * @brief Creates the decoration properties.
     *
     * If called without parameters, creates decoration
     * properties with sensible defaults.
     */
    decoration_properties make_decoration_properties(
        const modeline_locations ml = modeline_locations::top,
        const bool use_multiline_licence = false,
        const bool use_empty_licence = false,
        const bool use_empty_marker = false) const;

    /**
     * @brief Creates empty decoration properties.
     */
    decoration_properties make_empty_decoration_properties() const;
};

} } }

#endif
