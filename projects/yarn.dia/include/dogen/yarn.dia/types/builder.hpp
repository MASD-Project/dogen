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
#ifndef DOGEN_YARN_DIA_TYPES_BUILDER_HPP
#define DOGEN_YARN_DIA_TYPES_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn.dia/types/transformer.hpp"
#include "dogen/yarn.dia/types/profiled_object.hpp"

namespace dogen {
namespace yarn {
namespace dia {

class builder {
/*public:
    builder(transformer& transformer, const std::unordered_map<
        std::string, std::list<std::string>>& child_id_to_parent_ids);

private:
    void update_documentation(const processed_object& o) const;

private:


public:
    void add(const profiled_object& o);
    yarn::model build();

private:
    const std::unordered_map<std::string,
                             std::list<std::string>>& child_id_to_parent_ids_;
    transformer& transformer_;
    std::unordered_map<std::string, yarn::name> id_to_name_;
    yarn::model model_;*/
};

} } }

#endif
