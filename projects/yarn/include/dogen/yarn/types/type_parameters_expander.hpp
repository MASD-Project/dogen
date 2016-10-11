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
#ifndef DOGEN_YARN_TYPES_TYPE_PARAMETERS_EXPANDER_HPP
#define DOGEN_YARN_TYPES_TYPE_PARAMETERS_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/repository.hpp"
#include "dogen/annotations/types/type.hpp"
#include "dogen/yarn/types/type_parameters.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

class type_parameters_expander {
private:
    struct type_group {
        annotations::type variable_number_of_parameters;
        annotations::type type_parameters_count;
        annotations::type type_parameters_always_in_heap;
    };

    type_group make_type_group(const annotations::type_repository& atrp) const;

    type_parameters make_type_parameters(const type_group& tg,
        const annotations::annotation& a) const;

private:
    void expand_type_parameters(const type_group& tg, object& o) const;

public:
    void expand(const annotations::type_repository& atrp,
        intermediate_model& m) const;
};

} }

#endif
