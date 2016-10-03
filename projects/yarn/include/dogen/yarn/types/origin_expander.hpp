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
#ifndef DOGEN_YARN_TYPES_ORIGIN_EXPANDER_HPP
#define DOGEN_YARN_TYPES_ORIGIN_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

class origin_expander {
public:
    explicit origin_expander(const dynamic::repository& rp);

private:
    struct field_definitions {
        dynamic::field_definition is_proxy_model;
    };

    field_definitions make_field_definitions(
        const dynamic::repository& rp) const;

    bool is_proxy_model(const intermediate_model& im) const;
    origin_types compute_origin_types(const intermediate_model& im,
        const bool is_proxy_model) const;

public:
    void expand(intermediate_model& im) const;

private:
    const field_definitions field_definitions_;
};

} }

#endif
