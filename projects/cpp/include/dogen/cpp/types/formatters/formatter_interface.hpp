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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_FORMATTER_INTERFACE_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_FORMATTER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dynamic/schema/types/ownership_hierarchy.hpp"
#include "dogen/cpp/types/formattables/registrar.hpp"
#include "dogen/cpp/types/formatters/file_types.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class formatter_interface {
public:
    formatter_interface() = default;
    formatter_interface(const formatter_interface&) = delete;
    formatter_interface(formatter_interface&&) = default;
    virtual ~formatter_interface() noexcept = 0;

public:
    /**
     * @brief Ownership hierarchy for this formatter
     */
    virtual dynamic::schema::ownership_hierarchy
    ownership_hierarchy() const = 0;

    /**
     * @brief Type of the file this formatter generates.
     */
    virtual file_types file_type() const = 0;


    /**
     * @brief Registers an inclusion dependency providers this
     * formatter may know of.
     */
    virtual void register_inclusion_dependencies_provider(
        formattables::registrar& rg) const = 0;
};

} } }

#endif
