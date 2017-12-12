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
#ifndef DOGEN_TEST_MODELS_NORTHWIND_TYPES_EMPLOYEE_ID_HPP
#define DOGEN_TEST_MODELS_NORTHWIND_TYPES_EMPLOYEE_ID_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/northwind/serialization/employee_id_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace northwind {
class employee_id final {
public:
    employee_id() = default;
    employee_id(const employee_id&) = default;
    employee_id(employee_id&&) = default;
    ~employee_id() = default;
public:
    explicit employee_id(const int value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::northwind::employee_id& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::northwind::employee_id& v, unsigned int version);

public:
    /**
     * @brief Obtain the underlying value.
     */
    /**@{*/
    int value() const;
    void value(const int v);
    /**@}*/

public:
    explicit operator int() const {
        return value_;
    }

public:
    bool operator==(const employee_id& rhs) const;
    bool operator!=(const employee_id& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(employee_id& other) noexcept;
    employee_id& operator=(employee_id other);

private:
    int value_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::northwind::employee_id& lhs,
    dogen::test_models::northwind::employee_id& rhs) {
    lhs.swap(rhs);
}

}

#endif
