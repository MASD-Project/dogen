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
#ifndef DOGEN_TEST_MODELS_BOOST_MODEL_TYPES_SOME_SERVICE_HPP
#define DOGEN_TEST_MODELS_BOOST_MODEL_TYPES_SOME_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/test_models/boost_model/types/class_a_fwd.hpp"

namespace dogen {
namespace test_models {
namespace boost_model {

class some_service final {
public:
    some_service() = default;
    some_service(const some_service&) = default;
    some_service(some_service&&) = default;
    ~some_service() = default;

public:
    explicit some_service(const boost::shared_ptr<dogen::test_models::boost_model::class_a>& prop_0);

public:
    const boost::shared_ptr<dogen::test_models::boost_model::class_a>& prop_0() const;
    boost::shared_ptr<dogen::test_models::boost_model::class_a>& prop_0();
    void prop_0(const boost::shared_ptr<dogen::test_models::boost_model::class_a>& v);
    void prop_0(const boost::shared_ptr<dogen::test_models::boost_model::class_a>&& v);

public:
    bool operator==(const some_service& rhs) const;
    bool operator!=(const some_service& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(some_service& other) noexcept;
    some_service& operator=(some_service other);

private:
    boost::shared_ptr<dogen::test_models::boost_model::class_a> prop_0_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::boost_model::some_service& lhs,
    dogen::test_models::boost_model::some_service& rhs) {
    lhs.swap(rhs);
}

}

#endif
