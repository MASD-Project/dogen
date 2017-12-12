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
#ifndef DOGEN_TEST_MODELS_STD_MODEL_TYPES_CLASS_A_HPP
#define DOGEN_TEST_MODELS_STD_MODEL_TYPES_CLASS_A_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/std_model/serialization/class_a_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace std_model {

class class_a final {
public:
    class_a() = default;
    class_a(const class_a&) = default;
    class_a(class_a&&) = default;
    ~class_a() = default;

public:
    class_a(
        const std::string& prop0,
        const std::string& prop1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::std_model::class_a& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::std_model::class_a& v, unsigned int version);

public:
    const std::string& prop0() const;
    std::string& prop0();
    void prop0(const std::string& v);
    void prop0(const std::string&& v);

    /**
     * @brief test inclusion duplicates
     */
    /**@{*/
    const std::string& prop1() const;
    std::string& prop1();
    void prop1(const std::string& v);
    void prop1(const std::string&& v);
    /**@}*/

public:
    bool operator==(const class_a& rhs) const;
    bool operator!=(const class_a& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_a& other) noexcept;
    class_a& operator=(class_a other);

private:
    std::string prop0_;
    std::string prop1_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::std_model::class_a& lhs,
    dogen::test_models::std_model::class_a& rhs) {
    lhs.swap(rhs);
}

}

#endif
