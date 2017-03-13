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
#ifndef DOGEN_YARN_TYPES_ORM_MODEL_PROPERTIES_HPP
#define DOGEN_YARN_TYPES_ORM_MODEL_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/yarn/types/letter_cases.hpp"
#include "dogen/yarn/types/orm_database_systems.hpp"
#include "dogen/yarn/serialization/orm_model_properties_fwd_ser.hpp"

namespace dogen {
namespace yarn {

class orm_model_properties final {
public:
    orm_model_properties() = default;
    orm_model_properties(const orm_model_properties&) = default;
    ~orm_model_properties() = default;

public:
    orm_model_properties(orm_model_properties&& rhs);

public:
    orm_model_properties(
        const std::vector<dogen::yarn::orm_database_systems>& database_systems,
        const std::string& schema_name,
        const boost::optional<dogen::yarn::letter_cases>& letter_case);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::orm_model_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::orm_model_properties& v, unsigned int version);

public:
    const std::vector<dogen::yarn::orm_database_systems>& database_systems() const;
    std::vector<dogen::yarn::orm_database_systems>& database_systems();
    void database_systems(const std::vector<dogen::yarn::orm_database_systems>& v);
    void database_systems(const std::vector<dogen::yarn::orm_database_systems>&& v);

    const std::string& schema_name() const;
    std::string& schema_name();
    void schema_name(const std::string& v);
    void schema_name(const std::string&& v);

    const boost::optional<dogen::yarn::letter_cases>& letter_case() const;
    boost::optional<dogen::yarn::letter_cases>& letter_case();
    void letter_case(const boost::optional<dogen::yarn::letter_cases>& v);
    void letter_case(const boost::optional<dogen::yarn::letter_cases>&& v);

public:
    bool operator==(const orm_model_properties& rhs) const;
    bool operator!=(const orm_model_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(orm_model_properties& other) noexcept;
    orm_model_properties& operator=(orm_model_properties other);

private:
    std::vector<dogen::yarn::orm_database_systems> database_systems_;
    std::string schema_name_;
    boost::optional<dogen::yarn::letter_cases> letter_case_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::orm_model_properties& lhs,
    dogen::yarn::orm_model_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
