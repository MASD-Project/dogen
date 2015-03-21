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
#ifndef DOGEN_DYNAMIC_EXPANSION_TYPES_EXPANDER_INTERFACE_HPP
#define DOGEN_DYNAMIC_EXPANSION_TYPES_EXPANDER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include "dogen/sml/types/qname.hpp"
#include "dogen/dynamic/expansion/types/expansion_context.hpp"
#include "dogen/dynamic/schema/types/scope_types.hpp"
#include "dogen/dynamic/schema/types/object.hpp"

namespace dogen {
namespace dynamic {
namespace expansion {

class expander_interface {
public:
    expander_interface() = default;
    expander_interface(const expander_interface&) = delete;
    expander_interface(expander_interface&&) = default;
    virtual ~expander_interface() noexcept = 0;

public:
    /**
     * @brief Name of the expander. Must be unique.
     */
    virtual std::string name() const = 0;

    /**
     * @brief Names of all expanders that this expander depends on.
     *
     * @pre Names have been registered by expanders
     * @pre There must be no circular dependencies between expanders.
     */
    virtual const std::forward_list<std::string>& dependencies() const = 0;

    /**
     * @brief Sets up the expander. This method is called only once.
     */
    virtual void setup(expansion_context& ec) = 0;

    /**
     * @brief Perform the expansion.
     */
    virtual void expand(const sml::qname& qn, const schema::scope_types& st,
        schema::object& o) const = 0;
};

} } }

#endif
