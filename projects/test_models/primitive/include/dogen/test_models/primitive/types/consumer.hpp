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
#ifndef DOGEN_TEST_MODELS_PRIMITIVE_TYPES_CONSUMER_HPP
#define DOGEN_TEST_MODELS_PRIMITIVE_TYPES_CONSUMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/primitive/types/product_id.hpp"
#include "dogen/test_models/primitive/serialization/consumer_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace primitive {

/**
 * @brief This type makes use of all primitves in this test model.
 */
class consumer final {
public:
    consumer() = default;
    consumer(const consumer&) = default;
    consumer(consumer&&) = default;
    ~consumer() = default;

public:
    explicit consumer(const dogen::test_models::primitive::product_id& prop0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::primitive::consumer& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::primitive::consumer& v, unsigned int version);

public:
    const dogen::test_models::primitive::product_id& prop0() const;
    dogen::test_models::primitive::product_id& prop0();
    void prop0(const dogen::test_models::primitive::product_id& v);
    void prop0(const dogen::test_models::primitive::product_id&& v);

public:
    bool operator==(const consumer& rhs) const;
    bool operator!=(const consumer& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(consumer& other) noexcept;
    consumer& operator=(consumer other);

private:
    dogen::test_models::primitive::product_id prop0_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::primitive::consumer& lhs,
    dogen::test_models::primitive::consumer& rhs) {
    lhs.swap(rhs);
}

}

#endif
