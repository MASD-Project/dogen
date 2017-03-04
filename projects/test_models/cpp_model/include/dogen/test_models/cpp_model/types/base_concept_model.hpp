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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_BASE_CONCEPT_MODEL_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_BASE_CONCEPT_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/cpp_model/serialization/base_concept_model_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

/**
 * @brief This class models the BaseConcept.
 */
class base_concept_model final {
public:
    base_concept_model(const base_concept_model&) = default;
    base_concept_model(base_concept_model&&) = default;
    ~base_concept_model() = default;

public:
    base_concept_model();

public:
    explicit base_concept_model(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::base_concept_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::base_concept_model& v, unsigned int version);

public:
    /**
     * @brief Property in the base concept.
     */
    /**@{*/
    int prop_0() const;
    void prop_0(const int v);
    /**@}*/

public:
    bool operator==(const base_concept_model& rhs) const;
    bool operator!=(const base_concept_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(base_concept_model& other) noexcept;
    base_concept_model& operator=(base_concept_model other);

private:
    int prop_0_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::base_concept_model& lhs,
    dogen::test_models::cpp_model::base_concept_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
