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
#ifndef DOGEN_TEST_MODELS_NORTHWIND_TYPES_CUSTOMER_DEMOGRAPHICS_HPP
#define DOGEN_TEST_MODELS_NORTHWIND_TYPES_CUSTOMER_DEMOGRAPHICS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/northwind/types/customer_type_id.hpp"
#include "dogen/test_models/northwind/serialization/customer_demographics_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

class customer_demographics final {
public:
    customer_demographics() = default;
    customer_demographics(const customer_demographics&) = default;
    customer_demographics(customer_demographics&&) = default;
    ~customer_demographics() = default;

public:
    customer_demographics(
        const dogen::test_models::northwind::customer_type_id& customer_type_id,
        const std::string& customer_description);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::northwind::customer_demographics& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::northwind::customer_demographics& v, unsigned int version);

public:
    const dogen::test_models::northwind::customer_type_id& customer_type_id() const;
    dogen::test_models::northwind::customer_type_id& customer_type_id();
    void customer_type_id(const dogen::test_models::northwind::customer_type_id& v);
    void customer_type_id(const dogen::test_models::northwind::customer_type_id&& v);

    const std::string& customer_description() const;
    std::string& customer_description();
    void customer_description(const std::string& v);
    void customer_description(const std::string&& v);

public:
    bool operator==(const customer_demographics& rhs) const;
    bool operator!=(const customer_demographics& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(customer_demographics& other) noexcept;
    customer_demographics& operator=(customer_demographics other);

private:
    dogen::test_models::northwind::customer_type_id customer_type_id_;
    std::string customer_description_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::northwind::customer_demographics& lhs,
    dogen::test_models::northwind::customer_demographics& rhs) {
    lhs.swap(rhs);
}

}

#endif
