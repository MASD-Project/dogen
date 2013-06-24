/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_STEREOTYPES_TYPES_SECOND_REFINEMENT_CONCEPT_MODEL_HPP
#define DOGEN_STEREOTYPES_TYPES_SECOND_REFINEMENT_CONCEPT_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/stereotypes/serialization/second_refinement_concept_model_fwd_ser.hpp"

namespace dogen {
namespace stereotypes {

/**
 * @brief Second refinement model
 */
class second_refinement_concept_model final {
public:
    second_refinement_concept_model(const second_refinement_concept_model&) = default;
    second_refinement_concept_model(second_refinement_concept_model&&) = default;
    ~second_refinement_concept_model() = default;

public:
    second_refinement_concept_model();

public:
    second_refinement_concept_model(
        const int prop_10,
        const int prop_2,
        const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const second_refinement_concept_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, second_refinement_concept_model& v, unsigned int version);

public:
    /**
     * @brief Property of the class itself.
     */
    /**@{*/
    int prop_10() const;
    void prop_10(const int v);
    /**@}*/

    /**
     * @brief Second refinement property
     */
    /**@{*/
    int prop_2() const;
    void prop_2(const int v);
    /**@}*/

    /**
     * @brief Base concept property
     */
    /**@{*/
    int prop_0() const;
    void prop_0(const int v);
    /**@}*/

public:
    bool operator==(const second_refinement_concept_model& rhs) const;
    bool operator!=(const second_refinement_concept_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(second_refinement_concept_model& other) noexcept;
    second_refinement_concept_model& operator=(second_refinement_concept_model other);

private:
    int prop_10_;
    int prop_2_;
    int prop_0_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stereotypes::second_refinement_concept_model& lhs,
    dogen::stereotypes::second_refinement_concept_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
