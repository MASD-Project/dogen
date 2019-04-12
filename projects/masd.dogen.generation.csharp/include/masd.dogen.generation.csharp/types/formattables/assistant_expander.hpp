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
#ifndef MASD_DOGEN_GENERATION_CSHARP_TYPES_FORMATTABLES_ASSISTANT_EXPANDER_HPP
#define MASD_DOGEN_GENERATION_CSHARP_TYPES_FORMATTABLES_ASSISTANT_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include "masd.dogen.variability/types/type.hpp"
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.generation.csharp/types/formattables/model.hpp"
#include "masd.dogen.generation.csharp/types/formattables/assistant_properties.hpp"

namespace masd::dogen::generation::csharp::formattables {

class assistant_expander final {
private:
    struct type_group {
        variability::type requires_assistance;
        variability::type method_postfix;
    };

    type_group make_type_group(const variability::type_repository& atrp) const;

    boost::optional<assistant_properties> make_assistant_properties(
        const type_group& tg, const variability::annotation& a) const;

public:
    void expand(const variability::type_repository& atrp, model& fm) const;
};

}

#endif
