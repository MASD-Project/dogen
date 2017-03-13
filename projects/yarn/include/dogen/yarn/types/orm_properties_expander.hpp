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
#ifndef DOGEN_YARN_TYPES_ORM_PROPERTIES_EXPANDER_HPP
#define DOGEN_YARN_TYPES_ORM_PROPERTIES_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <vector>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/type.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/orm_model_properties.hpp"
#include "dogen/yarn/types/orm_object_properties.hpp"
#include "dogen/yarn/types/orm_module_properties.hpp"
#include "dogen/yarn/types/orm_attribute_properties.hpp"
#include "dogen/yarn/types/orm_primitive_properties.hpp"
#include "dogen/yarn/types/orm_database_systems.hpp"
#include "dogen/yarn/types/letter_cases.hpp"

namespace dogen {
namespace yarn {

class orm_properties_expander final {
private:
    orm_database_systems to_orm_database_system(const std::string& s) const;

    std::vector<orm_database_systems>
    to_orm_database_system(const std::list<std::string>& vs) const;

    letter_cases to_letter_case(const std::string& s) const;

    std::unordered_map<orm_database_systems, std::string>
    make_type_overrides(const std::list<std::string> ls) const;

private:
    struct type_group {
        annotations::type database_system;
        annotations::type table_name;
        annotations::type schema_name;
        annotations::type is_primary_key;
        annotations::type column_name;
        annotations::type is_nullable;
        annotations::type letter_case;
        annotations::type type_override;
        annotations::type is_composite;
    };

    friend std::ostream& operator<<(std::ostream& s, const type_group& v);

    type_group make_type_group(const annotations::type_repository& atrp) const;

    boost::optional<orm_model_properties> make_model_properties(
        const type_group& tg, const annotations::annotation& a) const;

    void update_object_properties(const type_group& tg,
        const annotations::annotation& a, orm_object_properties& cfg) const;

    boost::optional<orm_attribute_properties> make_attribute_properties(
        const type_group& tg, const annotations::annotation& a) const;

    void update_primitive_properties(const type_group& tg,
        const annotations::annotation& a,
        orm_primitive_properties& cfg) const;

    boost::optional<orm_module_properties> make_module_properties(
        const type_group& tg, const annotations::annotation& a) const;

private:
    void expand_objects(const type_group& tg, intermediate_model& im) const;
    void expand_concepts(const type_group& tg, intermediate_model& im) const;
    void expand_primitives(const type_group& tg, intermediate_model& im) const;
    void expand_modules(const type_group& tg, intermediate_model& im) const;

public:
    void expand(const annotations::type_repository& atrp,
        intermediate_model& im) const;
};

} }

#endif
