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
#ifndef DOGEN_YARN_TYPES_EXTERNAL_EXPANDER_INTERFACE_HPP
#define DOGEN_YARN_TYPES_EXTERNAL_EXPANDER_INTERFACE_HPP

#include <string>
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace yarn {

class external_expander_interface {
public:
    external_expander_interface() = default;
    external_expander_interface(const external_expander_interface&) = delete;
    external_expander_interface(external_expander_interface&&) = default;
    virtual ~external_expander_interface() noexcept = 0;

public:
    virtual std::string id() const = 0;
    virtual void expand(const annotations::type_repository& atrp,
        intermediate_model& im) const = 0;
};

} }

#endif
