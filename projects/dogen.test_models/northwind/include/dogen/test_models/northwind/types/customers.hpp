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
#ifndef DOGEN_TEST_MODELS_NORTHWIND_TYPES_CUSTOMERS_HPP
#define DOGEN_TEST_MODELS_NORTHWIND_TYPES_CUSTOMERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/northwind/types/customer_id.hpp"
#include "dogen/test_models/northwind/serialization/customers_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

class customers final {
public:
    customers() = default;
    customers(const customers&) = default;
    customers(customers&&) = default;
    ~customers() = default;

public:
    customers(
        const dogen::test_models::northwind::customer_id& customer_id,
        const std::string& customer_code,
        const std::string& company_name,
        const std::string& contact_name,
        const std::string& contact_title,
        const std::string& address,
        const std::string& city,
        const std::string& region,
        const std::string& postal_code,
        const std::string& country,
        const std::string& phone,
        const std::string& fax);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::northwind::customers& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::northwind::customers& v, unsigned int version);

public:
    const dogen::test_models::northwind::customer_id& customer_id() const;
    dogen::test_models::northwind::customer_id& customer_id();
    void customer_id(const dogen::test_models::northwind::customer_id& v);
    void customer_id(const dogen::test_models::northwind::customer_id&& v);

    const std::string& customer_code() const;
    std::string& customer_code();
    void customer_code(const std::string& v);
    void customer_code(const std::string&& v);

    const std::string& company_name() const;
    std::string& company_name();
    void company_name(const std::string& v);
    void company_name(const std::string&& v);

    const std::string& contact_name() const;
    std::string& contact_name();
    void contact_name(const std::string& v);
    void contact_name(const std::string&& v);

    const std::string& contact_title() const;
    std::string& contact_title();
    void contact_title(const std::string& v);
    void contact_title(const std::string&& v);

    const std::string& address() const;
    std::string& address();
    void address(const std::string& v);
    void address(const std::string&& v);

    const std::string& city() const;
    std::string& city();
    void city(const std::string& v);
    void city(const std::string&& v);

    const std::string& region() const;
    std::string& region();
    void region(const std::string& v);
    void region(const std::string&& v);

    const std::string& postal_code() const;
    std::string& postal_code();
    void postal_code(const std::string& v);
    void postal_code(const std::string&& v);

    const std::string& country() const;
    std::string& country();
    void country(const std::string& v);
    void country(const std::string&& v);

    const std::string& phone() const;
    std::string& phone();
    void phone(const std::string& v);
    void phone(const std::string&& v);

    const std::string& fax() const;
    std::string& fax();
    void fax(const std::string& v);
    void fax(const std::string&& v);

public:
    bool operator==(const customers& rhs) const;
    bool operator!=(const customers& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(customers& other) noexcept;
    customers& operator=(customers other);

private:
    dogen::test_models::northwind::customer_id customer_id_;
    std::string customer_code_;
    std::string company_name_;
    std::string contact_name_;
    std::string contact_title_;
    std::string address_;
    std::string city_;
    std::string region_;
    std::string postal_code_;
    std::string country_;
    std::string phone_;
    std::string fax_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::northwind::customers& lhs,
    dogen::test_models::northwind::customers& rhs) {
    lhs.swap(rhs);
}

}

#endif
