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
#ifndef DOGEN_TEST_MODELS_NORTHWIND_TYPES_TERRITORY_HPP
#define DOGEN_TEST_MODELS_NORTHWIND_TYPES_TERRITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/northwind/types/region_id.hpp"
#include "dogen/test_models/northwind/types/territory_id.hpp"
#include "dogen/test_models/northwind/serialization/territory_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

class territory final {
public:
    territory() = default;
    territory(const territory&) = default;
    territory(territory&&) = default;
    ~territory() = default;

public:
    territory(
        const dogen::test_models::northwind::territory_id& territory_id,
        const std::string& territory_description,
        const dogen::test_models::northwind::region_id& region_id);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::northwind::territory& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::northwind::territory& v, unsigned int version);

public:
    const dogen::test_models::northwind::territory_id& territory_id() const;
    dogen::test_models::northwind::territory_id& territory_id();
    void territory_id(const dogen::test_models::northwind::territory_id& v);
    void territory_id(const dogen::test_models::northwind::territory_id&& v);

    const std::string& territory_description() const;
    std::string& territory_description();
    void territory_description(const std::string& v);
    void territory_description(const std::string&& v);

    const dogen::test_models::northwind::region_id& region_id() const;
    dogen::test_models::northwind::region_id& region_id();
    void region_id(const dogen::test_models::northwind::region_id& v);
    void region_id(const dogen::test_models::northwind::region_id&& v);

public:
    bool operator==(const territory& rhs) const;
    bool operator!=(const territory& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(territory& other) noexcept;
    territory& operator=(territory other);

private:
    dogen::test_models::northwind::territory_id territory_id_;
    std::string territory_description_;
    dogen::test_models::northwind::region_id region_id_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::northwind::territory& lhs,
    dogen::test_models::northwind::territory& rhs) {
    lhs.swap(rhs);
}

}

#endif
