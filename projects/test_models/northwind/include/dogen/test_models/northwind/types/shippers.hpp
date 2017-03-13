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
#ifndef DOGEN_TEST_MODELS_NORTHWIND_TYPES_SHIPPERS_HPP
#define DOGEN_TEST_MODELS_NORTHWIND_TYPES_SHIPPERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/northwind/types/shipper_id.hpp"
#include "dogen/test_models/northwind/serialization/shippers_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

class shippers final {
public:
    shippers() = default;
    shippers(const shippers&) = default;
    shippers(shippers&&) = default;
    ~shippers() = default;

public:
    shippers(
        const dogen::test_models::northwind::shipper_id& shipper_id,
        const std::string& company_name,
        const std::string& phone);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::northwind::shippers& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::northwind::shippers& v, unsigned int version);

public:
    const dogen::test_models::northwind::shipper_id& shipper_id() const;
    dogen::test_models::northwind::shipper_id& shipper_id();
    void shipper_id(const dogen::test_models::northwind::shipper_id& v);
    void shipper_id(const dogen::test_models::northwind::shipper_id&& v);

    const std::string& company_name() const;
    std::string& company_name();
    void company_name(const std::string& v);
    void company_name(const std::string&& v);

    const std::string& phone() const;
    std::string& phone();
    void phone(const std::string& v);
    void phone(const std::string&& v);

public:
    bool operator==(const shippers& rhs) const;
    bool operator!=(const shippers& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(shippers& other) noexcept;
    shippers& operator=(shippers other);

private:
    dogen::test_models::northwind::shipper_id shipper_id_;
    std::string company_name_;
    std::string phone_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::northwind::shippers& lhs,
    dogen::test_models::northwind::shippers& rhs) {
    lhs.swap(rhs);
}

}

#endif
