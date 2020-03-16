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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_ODB_OPTIONS_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_ODB_OPTIONS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include<list>
#include <string>
#include "dogen.logical/types/meta_model/orm/letter_case.hpp"
#include "dogen.logical/types/meta_model/orm/database_system.hpp"
#include "dogen.logical/types/meta_model/orm/model_properties.hpp"
#include "dogen.logical/types/meta_model/model.hpp"
#include "dogen.logical/types/transforms/context.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Transforms the meta-model elements related to ODB options.
 */
class odb_options_transform final {
public:
    static std::string
    to_odb_database(const logical::meta_model::orm::database_system ds);

    static std::string
    to_odb_sql_name_case(const logical::meta_model::orm::letter_case lc);

    static std::list<std::string>
    make_databases(const logical::meta_model::orm::model_properties& omp);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
