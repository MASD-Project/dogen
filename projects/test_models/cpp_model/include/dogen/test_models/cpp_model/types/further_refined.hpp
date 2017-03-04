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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_FURTHER_REFINED_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_FURTHER_REFINED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/cpp_model/types/base_with_concept.hpp"
#include "dogen/test_models/cpp_model/serialization/further_refined_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

/**
 * @brief Descendant class that models a concept which is a refinement of the concept
 * modeled by the base.
 */
class further_refined final : public dogen::test_models::cpp_model::base_with_concept {
public:
    further_refined(const further_refined&) = default;
    further_refined(further_refined&&) = default;

public:
    further_refined();

    virtual ~further_refined() noexcept { }

public:
    further_refined(
        const int prop_2,
        const std::string& prop_0,
        const int prop_3,
        const int prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::further_refined& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::further_refined& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Multiple refinements property.
     */
    /**@{*/
    int prop_3() const;
    void prop_3(const int v);
    /**@}*/

    /**
     * @brief First refinement property
     */
    /**@{*/
    int prop_1() const;
    void prop_1(const int v);
    /**@}*/

public:
    bool operator==(const further_refined& rhs) const;
    bool operator!=(const further_refined& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::test_models::cpp_model::base_with_concept& other) const override;

public:
    void swap(further_refined& other) noexcept;
    further_refined& operator=(further_refined other);

private:
    int prop_3_;
    int prop_1_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::further_refined& lhs,
    dogen::test_models::cpp_model::further_refined& rhs) {
    lhs.swap(rhs);
}

}

#endif
