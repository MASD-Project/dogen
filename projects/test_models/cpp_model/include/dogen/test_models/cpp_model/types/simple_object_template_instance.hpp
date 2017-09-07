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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_SIMPLE_OBJECT_TEMPLATE_INSTANCE_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_SIMPLE_OBJECT_TEMPLATE_INSTANCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/cpp_model/types/value.hpp"
#include "dogen/test_models/cpp_model/serialization/simple_object_template_instance_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

/**
 * @brief This class instantiates the simple object template.
 */
class simple_object_template_instance final {
public:
    simple_object_template_instance(const simple_object_template_instance&) = default;
    simple_object_template_instance(simple_object_template_instance&&) = default;
    ~simple_object_template_instance() = default;

public:
    simple_object_template_instance();

public:
    simple_object_template_instance(
        const int prop_0,
        const dogen::test_models::cpp_model::value& prop_1,
        const int prop_10);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::simple_object_template_instance& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::simple_object_template_instance& v, unsigned int version);

public:
    /**
     * @brief This is a sample property in an object template.
     */
    /**@{*/
    int prop_0() const;
    void prop_0(const int v);
    /**@}*/

    /**
     * @brief Prove that includes of types get picked up.
     */
    /**@{*/
    const dogen::test_models::cpp_model::value& prop_1() const;
    dogen::test_models::cpp_model::value& prop_1();
    void prop_1(const dogen::test_models::cpp_model::value& v);
    void prop_1(const dogen::test_models::cpp_model::value&& v);
    /**@}*/

    /**
     * @brief Property that belongs to class.
     */
    /**@{*/
    int prop_10() const;
    void prop_10(const int v);
    /**@}*/

public:
    bool operator==(const simple_object_template_instance& rhs) const;
    bool operator!=(const simple_object_template_instance& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(simple_object_template_instance& other) noexcept;
    simple_object_template_instance& operator=(simple_object_template_instance other);

private:
    int prop_0_;
    dogen::test_models::cpp_model::value prop_1_;
    int prop_10_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::simple_object_template_instance& lhs,
    dogen::test_models::cpp_model::simple_object_template_instance& rhs) {
    lhs.swap(rhs);
}

}

#endif
