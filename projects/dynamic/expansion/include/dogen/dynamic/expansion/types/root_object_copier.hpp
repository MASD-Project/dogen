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
#ifndef DOGEN_DYNAMIC_EXPANSION_TYPES_ROOT_OBJECT_COPIER_HPP
#define DOGEN_DYNAMIC_EXPANSION_TYPES_ROOT_OBJECT_COPIER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dynamic/expansion/types/expander_interface.hpp"

namespace dogen {
namespace dynamic {
namespace expansion {

class root_object_copier : public expander_interface {
public:
    ~root_object_copier() noexcept;

public:
    /**
     * @brief Name property for other expanders that need to declare
     * it as a dependency.
     */
    static std::string static_name();

public:
    std::string name() const final override;

    const std::forward_list<std::string>& dependencies() const final override;

    void setup(expansion_context& ec) override;

    void expand(const sml::qname& qn, const schema::scope_types& st,
        schema::object& o) const override;
};

} } }

#endif
