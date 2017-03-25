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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_TRANSFORMER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/types/orm_database_systems.hpp"
#include "dogen/yarn/types/letter_cases.hpp"
#include "dogen/yarn/types/orm_model_properties.hpp"
#include "dogen/quilt.cpp/types/formatters/repository.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief Provides a number of useful transformations in the
 * formattables space.
 */
class transformer {
public:
    static std::string to_odb_database(const yarn::orm_database_systems ds);

private:
    std::string to_odb_sql_name_case(const yarn::letter_cases lc) const;

    std::list<std::string>
    make_databases(const yarn::orm_model_properties& omp) const;

public:
    /**
     * @brief Given a yarn model, produces the corresponding formattables.
     */
    model
    transform(const formatters::repository& frp, const yarn::model& m) const;
};

} } } }

#endif
