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
#ifndef DOGEN_GENERATION_CPP_TYPES_FABRIC_DECORATION_EXPANDER_HPP
#define DOGEN_GENERATION_CPP_TYPES_FABRIC_DECORATION_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.formatting/types/decoration_properties.hpp"
#include "dogen.formatting/types/decoration_properties_factory.hpp"
#include "dogen.modeling/types/meta_model/model.hpp"

namespace dogen {
namespace generation {
namespace cpp {
namespace fabric {

class decoration_expander final {
public:
    void expand(const dogen::formatting::decoration_properties_factory& dpf,
        modeling::meta_model::model& m) const;
};

} } } }

#endif
