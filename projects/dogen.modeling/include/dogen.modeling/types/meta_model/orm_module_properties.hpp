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
#ifndef DOGEN_MODELING_TYPES_META_MODEL_ORM_MODULE_PROPERTIES_HPP
#define DOGEN_MODELING_TYPES_META_MODEL_ORM_MODULE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.modeling/serialization/meta_model/orm_module_properties_fwd_ser.hpp"

namespace dogen {
namespace modeling {
namespace meta_model {

class orm_module_properties final {
public:
    orm_module_properties() = default;
    orm_module_properties(const orm_module_properties&) = default;
    orm_module_properties(orm_module_properties&&) = default;
    ~orm_module_properties() = default;

public:
    explicit orm_module_properties(const std::string& schema_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::modeling::meta_model::orm_module_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::modeling::meta_model::orm_module_properties& v, unsigned int version);

public:
    /**
     * @brief Name of the database schema in which elements contained by this module will placed in.
     */
    /**@{*/
    const std::string& schema_name() const;
    std::string& schema_name();
    void schema_name(const std::string& v);
    void schema_name(const std::string&& v);
    /**@}*/

public:
    bool operator==(const orm_module_properties& rhs) const;
    bool operator!=(const orm_module_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(orm_module_properties& other) noexcept;
    orm_module_properties& operator=(orm_module_properties other);

private:
    std::string schema_name_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::modeling::meta_model::orm_module_properties& lhs,
    dogen::modeling::meta_model::orm_module_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
