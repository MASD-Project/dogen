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
#ifndef DOGEN_TEST_MODELS_NORTHWIND_TYPES_CATEGORIES_HPP
#define DOGEN_TEST_MODELS_NORTHWIND_TYPES_CATEGORIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/northwind/types/category_id.hpp"
#include "dogen/test_models/northwind/serialization/categories_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

class categories final {
public:
    categories() = default;
    categories(const categories&) = default;
    categories(categories&&) = default;
    ~categories() = default;

public:
    categories(
        const dogen::test_models::northwind::category_id& category_id,
        const std::string& category_name,
        const std::string& description,
        const std::string& picutre);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::northwind::categories& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::northwind::categories& v, unsigned int version);

public:
    const dogen::test_models::northwind::category_id& category_id() const;
    dogen::test_models::northwind::category_id& category_id();
    void category_id(const dogen::test_models::northwind::category_id& v);
    void category_id(const dogen::test_models::northwind::category_id&& v);

    const std::string& category_name() const;
    std::string& category_name();
    void category_name(const std::string& v);
    void category_name(const std::string&& v);

    const std::string& description() const;
    std::string& description();
    void description(const std::string& v);
    void description(const std::string&& v);

    const std::string& picutre() const;
    std::string& picutre();
    void picutre(const std::string& v);
    void picutre(const std::string&& v);

public:
    bool operator==(const categories& rhs) const;
    bool operator!=(const categories& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(categories& other) noexcept;
    categories& operator=(categories other);

private:
    dogen::test_models::northwind::category_id category_id_;
    std::string category_name_;
    std::string description_;
    std::string picutre_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::northwind::categories& lhs,
    dogen::test_models::northwind::categories& rhs) {
    lhs.swap(rhs);
}

}

#endif
