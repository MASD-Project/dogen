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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_FORWARD_DECLARATIONS_FORMATTER_INTERFACE_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_FORWARD_DECLARATIONS_FORMATTER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/formatters/types/file.hpp"
#include "dogen/quilt.cpp/types/formatters/context.hpp"
#include "dogen/quilt.cpp/types/fabric/forward_declarations.hpp"
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

class forward_declarations_formatter_interface
    : public file_formatter_interface {
public:
    forward_declarations_formatter_interface() = default;
    forward_declarations_formatter_interface(
        const forward_declarations_formatter_interface&) = delete;
    forward_declarations_formatter_interface(
        forward_declarations_formatter_interface&&) = default;
    virtual ~forward_declarations_formatter_interface() noexcept = 0;

public:
    /**
     * @brief Generates a forward declaration for the type.
     */
    virtual dogen::formatters::file format(const context& ctx,
        const fabric::forward_declarations& fd) const = 0;
};

} } } }

#endif
