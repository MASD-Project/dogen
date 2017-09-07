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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_SECOND_DESCENDANT_OBJECT_TEMPLATE_INSTANCE_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_SECOND_DESCENDANT_OBJECT_TEMPLATE_INSTANCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/cpp_model/serialization/second_descendant_object_template_instance_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

/**
 * @brief Second descendant instance
 */
class second_descendant_object_template_instance final {
public:
    second_descendant_object_template_instance(const second_descendant_object_template_instance&) = default;
    second_descendant_object_template_instance(second_descendant_object_template_instance&&) = default;
    ~second_descendant_object_template_instance() = default;

public:
    second_descendant_object_template_instance();

public:
    second_descendant_object_template_instance(
        const int prop_2,
        const std::string& prop_0,
        const int prop_10);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::second_descendant_object_template_instance& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::second_descendant_object_template_instance& v, unsigned int version);

public:
    /**
     * @brief Second descendant property
     */
    /**@{*/
    int prop_2() const;
    void prop_2(const int v);
    /**@}*/

    /**
     * @brief Ensure we're testing header files inclusion.
     */
    /**@{*/
    const std::string& prop_0() const;
    std::string& prop_0();
    void prop_0(const std::string& v);
    void prop_0(const std::string&& v);
    /**@}*/

    /**
     * @brief Property of the class itself.
     */
    /**@{*/
    int prop_10() const;
    void prop_10(const int v);
    /**@}*/

public:
    bool operator==(const second_descendant_object_template_instance& rhs) const;
    bool operator!=(const second_descendant_object_template_instance& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(second_descendant_object_template_instance& other) noexcept;
    second_descendant_object_template_instance& operator=(second_descendant_object_template_instance other);

private:
    int prop_2_;
    std::string prop_0_;
    int prop_10_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::second_descendant_object_template_instance& lhs,
    dogen::test_models::cpp_model::second_descendant_object_template_instance& rhs) {
    lhs.swap(rhs);
}

}

#endif
