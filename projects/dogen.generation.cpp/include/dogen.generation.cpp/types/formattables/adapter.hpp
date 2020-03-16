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
#ifndef DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_ADAPTER_HPP
#define DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen.logical/types/entities/orm/letter_case.hpp"
#include "dogen.logical/types/entities/orm/database_system.hpp"
#include "dogen.logical/types/entities/orm/model_properties.hpp"
#include "dogen.generation/types/entities/model.hpp"
#include "dogen.generation.cpp/types/formatters/repository.hpp"
#include "dogen.generation.cpp/types/formattables/formattable.hpp"
#include "dogen.generation.cpp/types/formattables/model.hpp"

namespace dogen::generation::cpp::formattables {

/**
 * @brief Provides a number of useful transformations in the
 * formattables space.
 */
class adapter {
public:
    static std::string
    to_odb_database(const logical::entities::orm::database_system ds);

private:
    std::string
    to_odb_sql_name_case(const logical::entities::orm::letter_case lc) const;

    std::list<std::string>
    make_databases(const logical::entities::orm::model_properties& omp) const;

public:
    /**
     * @brief Given a yarn model, produces the corresponding formattables.
     */
    model adapt(const formatters::repository& frp,
        const generation::entities::model& m) const;
};

}

#endif
