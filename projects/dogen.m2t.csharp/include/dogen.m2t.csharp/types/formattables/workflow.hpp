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
#ifndef DOGEN_M2T_CSHARP_TYPES_FORMATTABLES_WORKFLOW_HPP
#define DOGEN_M2T_CSHARP_TYPES_FORMATTABLES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.m2t/types/entities/model.hpp"
#include "dogen.m2t.csharp/types/formattables/model.hpp"
#include "dogen.m2t.csharp/types/formattables/locator.hpp"
#include "dogen.m2t.csharp/types/formatters/repository.hpp"
#include "dogen.m2t.csharp/types/formattables/formattable.hpp"

namespace dogen::m2t::csharp::formattables {

class workflow {
private:
    /**
     * @brief Retrieves the ids of all the modules in the model.
     */
    model make_model(const formatters::repository& frp,
        const m2t::entities::model& m) const;

    void expand_model(
        const variability::entities::feature_model& feature_model,
        const formatters::repository& frp, const locator& l, model& fm) const;

public:
    model execute(
        const variability::entities::feature_model& feature_model,
        const formatters::repository& frp, const locator& l,
        const m2t::entities::model& m) const;
};

}

#endif
