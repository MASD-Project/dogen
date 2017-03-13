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
#ifndef ZANGO_NORTHWIND_TYPES_CUSTOMER_CUSTOMER_DEMO_KEY_HPP
#define ZANGO_NORTHWIND_TYPES_CUSTOMER_CUSTOMER_DEMO_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "zango/northwind/types/customer_id.hpp"
#include "zango/northwind/types/customer_type_id.hpp"
#include "zango/northwind/serialization/customer_customer_demo_key_fwd_ser.hpp"

namespace zango {
namespace northwind {

class customer_customer_demo_key final {
public:
    customer_customer_demo_key() = default;
    customer_customer_demo_key(const customer_customer_demo_key&) = default;
    customer_customer_demo_key(customer_customer_demo_key&&) = default;
    ~customer_customer_demo_key() = default;

public:
    customer_customer_demo_key(
        const zango::northwind::customer_id& customer_id,
        const zango::northwind::customer_type_id& customer_type_id);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const zango::northwind::customer_customer_demo_key& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, zango::northwind::customer_customer_demo_key& v, unsigned int version);

public:
    const zango::northwind::customer_id& customer_id() const;
    zango::northwind::customer_id& customer_id();
    void customer_id(const zango::northwind::customer_id& v);
    void customer_id(const zango::northwind::customer_id&& v);

    const zango::northwind::customer_type_id& customer_type_id() const;
    zango::northwind::customer_type_id& customer_type_id();
    void customer_type_id(const zango::northwind::customer_type_id& v);
    void customer_type_id(const zango::northwind::customer_type_id&& v);

public:
    bool operator==(const customer_customer_demo_key& rhs) const;
    bool operator!=(const customer_customer_demo_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(customer_customer_demo_key& other) noexcept;
    customer_customer_demo_key& operator=(customer_customer_demo_key other);

private:
    zango::northwind::customer_id customer_id_;
    zango::northwind::customer_type_id customer_type_id_;
};

} }

namespace std {

template<>
inline void swap(
    zango::northwind::customer_customer_demo_key& lhs,
    zango::northwind::customer_customer_demo_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
