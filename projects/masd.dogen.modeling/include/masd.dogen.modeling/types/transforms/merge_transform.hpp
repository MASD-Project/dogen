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
#ifndef DOGEN_MODELING_TYPES_TRANSFORMS_MERGE_TRANSFORM_HPP
#define DOGEN_MODELING_TYPES_TRANSFORMS_MERGE_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen.modeling/types/meta_model/languages.hpp"
#include "dogen.modeling/types/meta_model/endomodel.hpp"
#include "dogen.modeling/types/transforms/context.hpp"

namespace dogen::modeling::transforms {

/**
 * @brief Combines a number of intermediate models into a single
 * intermediate model.
 *
 * The role of the merger is to aggregate a number of intermediate
 * models into a single, coherent model called the intermediate
 * @e merged model.
 *
 * There are two kinds of intermediate models:
 *
 * @li the intermediate @e target model: the model which the user is
 * focusing on, most likely with the intention of code generating
 * it. There can only be one target model for a given merge.
 *
 * @li the intermediate @e reference models; a model is a reference
 * model if the target model refers to one or more of its types - or a
 * model referred to by the target model refers to its types and so
 * on.
 *
 * In summary, the target model cannot be evaluated without the
 * definition of all models it references, directly or
 * indirectly. Merging will fail if one or more of the referenced
 * models have not been supplied.
 */
class merge_transform final {
private:
    static void merge(const meta_model::endomodel& src,
        meta_model::endomodel& dst);

public:
    static meta_model::endomodel transform(const context& ctx,
        const meta_model::endomodel& target,
        const std::list<meta_model::endomodel>& refs);
};

}

#endif
