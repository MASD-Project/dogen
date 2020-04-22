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
#ifndef DOGEN_TEMPLATING_TYPES_HELPERS_STITCH_TEMPLATE_BUILDER_HPP
#define DOGEN_TEMPLATING_TYPES_HELPERS_STITCH_TEMPLATE_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <ostream>

namespace dogen::templating::helpers {

/**
 * @brief Helper class to generate stitch templates.
 */
class stitch_template_builder final {
public:
    stitch_template_builder(std::ostream& os);

public:
    /**
     * @brief Adds a directive block to the stream.
     *
     * Directive blocks take the form of:
     *
     *     <#@ NAME = VALUE #>
     *
     * They must be at the start of the template.
     */
    void add_directive_block(const std::string& name, const std::string& value);

    /**
     * @brief Adds a variable expansion block to the stream.
     *
     * Variable expansion blocks take the form of:
     *
     *    <#$ NAME #>
     *
     * Variable name must have been defined as a wale template.
     */
    void add_variable_block(const std::string& name);

    /**
     * @brief Adds an expression block to the stream.
     *
     * Variable expansion blocks take the form of:
     *
     *    <#= EXPRESSION #>
     */
    void add_expression_block(const std::string& expression);

    /**
     * @brief Starts a standard control block, e.g. @e <#+.
     */
    void add_start_standard_control_block();

    /**
     * @brief Ends a standard control block, e.g. @e #>.
     */
    void add_end_standard_control_block();

private:
    std::ostream& stream_;
};

}

#endif
