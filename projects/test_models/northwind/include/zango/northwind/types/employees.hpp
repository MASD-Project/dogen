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
#ifndef ZANGO_NORTHWIND_TYPES_EMPLOYEES_HPP
#define ZANGO_NORTHWIND_TYPES_EMPLOYEES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include "zango/northwind/types/employee_id.hpp"
#include "zango/northwind/serialization/employees_fwd_ser.hpp"

namespace zango {
namespace northwind {

class employees final {
public:
    employees() = default;
    employees(const employees&) = default;
    employees(employees&&) = default;
    ~employees() = default;

public:
    employees(
        const zango::northwind::employee_id& employee_id,
        const std::string& last_name,
        const std::string& first_name,
        const std::string& title,
        const std::string& title_of_courtesy,
        const boost::gregorian::date& birth_date,
        const boost::gregorian::date& hire_date,
        const std::string& address,
        const std::string& city,
        const std::string& region,
        const std::string& postal_code,
        const std::string& country,
        const std::string& home_phone,
        const std::string& extension,
        const std::vector<char>& photo,
        const std::string& notes,
        const zango::northwind::employee_id& reports_to,
        const std::string& photo_path);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const zango::northwind::employees& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, zango::northwind::employees& v, unsigned int version);

public:
    const zango::northwind::employee_id& employee_id() const;
    zango::northwind::employee_id& employee_id();
    void employee_id(const zango::northwind::employee_id& v);
    void employee_id(const zango::northwind::employee_id&& v);

    const std::string& last_name() const;
    std::string& last_name();
    void last_name(const std::string& v);
    void last_name(const std::string&& v);

    const std::string& first_name() const;
    std::string& first_name();
    void first_name(const std::string& v);
    void first_name(const std::string&& v);

    const std::string& title() const;
    std::string& title();
    void title(const std::string& v);
    void title(const std::string&& v);

    const std::string& title_of_courtesy() const;
    std::string& title_of_courtesy();
    void title_of_courtesy(const std::string& v);
    void title_of_courtesy(const std::string&& v);

    const boost::gregorian::date& birth_date() const;
    boost::gregorian::date& birth_date();
    void birth_date(const boost::gregorian::date& v);
    void birth_date(const boost::gregorian::date&& v);

    const boost::gregorian::date& hire_date() const;
    boost::gregorian::date& hire_date();
    void hire_date(const boost::gregorian::date& v);
    void hire_date(const boost::gregorian::date&& v);

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

    const std::string& home_phone() const;
    std::string& home_phone();
    void home_phone(const std::string& v);
    void home_phone(const std::string&& v);

    const std::string& extension() const;
    std::string& extension();
    void extension(const std::string& v);
    void extension(const std::string&& v);

    const std::vector<char>& photo() const;
    std::vector<char>& photo();
    void photo(const std::vector<char>& v);
    void photo(const std::vector<char>&& v);

    const std::string& notes() const;
    std::string& notes();
    void notes(const std::string& v);
    void notes(const std::string&& v);

    const zango::northwind::employee_id& reports_to() const;
    zango::northwind::employee_id& reports_to();
    void reports_to(const zango::northwind::employee_id& v);
    void reports_to(const zango::northwind::employee_id&& v);

    const std::string& photo_path() const;
    std::string& photo_path();
    void photo_path(const std::string& v);
    void photo_path(const std::string&& v);

public:
    bool operator==(const employees& rhs) const;
    bool operator!=(const employees& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(employees& other) noexcept;
    employees& operator=(employees other);

private:
    zango::northwind::employee_id employee_id_;
    std::string last_name_;
    std::string first_name_;
    std::string title_;
    std::string title_of_courtesy_;
    boost::gregorian::date birth_date_;
    boost::gregorian::date hire_date_;
    std::string address_;
    std::string city_;
    std::string region_;
    std::string postal_code_;
    std::string country_;
    std::string home_phone_;
    std::string extension_;
    std::vector<char> photo_;
    std::string notes_;
    zango::northwind::employee_id reports_to_;
    std::string photo_path_;
};

} }

namespace std {

template<>
inline void swap(
    zango::northwind::employees& lhs,
    zango::northwind::employees& rhs) {
    lhs.swap(rhs);
}

}

#endif
