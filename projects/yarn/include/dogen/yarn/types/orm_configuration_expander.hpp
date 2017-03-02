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
#ifndef DOGEN_YARN_TYPES_ORM_CONFIGURATION_EXPANDER_HPP
#define DOGEN_YARN_TYPES_ORM_CONFIGURATION_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <boost/optional.hpp>
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/type.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/orm_model_configuration.hpp"
#include "dogen/yarn/types/orm_object_configuration.hpp"
#include "dogen/yarn/types/orm_attribute_configuration.hpp"

namespace dogen {
namespace yarn {

class orm_configuration_expander final {
public:
    struct type_group {
        annotations::type generate_mapping;
        annotations::type database_system;
        annotations::type table_name;
        annotations::type schema_name;
        annotations::type is_primary_key;
        annotations::type column_name;
        annotations::type is_nullable;
        annotations::type letter_case;
        annotations::type is_value;
        annotations::type type_override;
    };

    friend std::ostream& operator<<(std::ostream& s, const type_group& v);

    type_group make_type_group(const annotations::type_repository& atrp) const;

    boost::optional<orm_model_configuration> make_model_configuration(
        const type_group& tg, const annotations::annotation& a) const;

    boost::optional<orm_object_configuration> make_object_configuration(
        const type_group& tg, const annotations::annotation& a) const;

    boost::optional<orm_attribute_configuration> make_attribute_configuration(
        const type_group& tg, const annotations::annotation& a) const;

public:
    void expand(const annotations::type_repository& atrp,
        intermediate_model& im) const;
};

} }

#endif
