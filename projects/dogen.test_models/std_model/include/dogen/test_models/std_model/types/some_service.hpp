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
#ifndef DOGEN_TEST_MODELS_STD_MODEL_TYPES_SOME_SERVICE_HPP
#define DOGEN_TEST_MODELS_STD_MODEL_TYPES_SOME_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <algorithm>
#include "dogen/test_models/std_model/types/base_fwd.hpp"

namespace dogen {
namespace test_models {
namespace std_model {

class some_service final {
public:
    some_service() = default;
    some_service(const some_service&) = default;
    some_service(some_service&&) = default;
    ~some_service() = default;

public:
    explicit some_service(const std::shared_ptr<dogen::test_models::std_model::base>& prop_0);

public:
    const std::shared_ptr<dogen::test_models::std_model::base>& prop_0() const;
    std::shared_ptr<dogen::test_models::std_model::base>& prop_0();
    void prop_0(const std::shared_ptr<dogen::test_models::std_model::base>& v);
    void prop_0(const std::shared_ptr<dogen::test_models::std_model::base>&& v);

public:
    bool operator==(const some_service& rhs) const;
    bool operator!=(const some_service& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(some_service& other) noexcept;
    some_service& operator=(some_service other);

private:
    std::shared_ptr<dogen::test_models::std_model::base> prop_0_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::std_model::some_service& lhs,
    dogen::test_models::std_model::some_service& rhs) {
    lhs.swap(rhs);
}

}

#endif
