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
#ifndef DOGEN_STEREOTYPES_TYPES_REFINEMENT_CONCEPT_MODEL_HPP
#define DOGEN_STEREOTYPES_TYPES_REFINEMENT_CONCEPT_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/stereotypes/serialization/refinement_concept_model_fwd_ser.hpp"

namespace dogen {
namespace stereotypes {

/**
 * @brief This class models the Refinement concept.
 */
class refinement_concept_model final {
public:
    refinement_concept_model(const refinement_concept_model&) = default;
    refinement_concept_model(refinement_concept_model&&) = default;
    ~refinement_concept_model() = default;

public:
    refinement_concept_model();

public:
    refinement_concept_model(
        const int prop_0,
        const int prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const refinement_concept_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, refinement_concept_model& v, unsigned int version);

public:
    /**
     * @brief Property in the base concept.
     */
    /**@{*/
    int prop_0() const;
    void prop_0(const int v);
    /**@}*/

    /**
     * @brief Refinement concept property.
     */
    /**@{*/
    int prop_1() const;
    void prop_1(const int v);
    /**@}*/

public:
    bool operator==(const refinement_concept_model& rhs) const;
    bool operator!=(const refinement_concept_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(refinement_concept_model& other) noexcept;
    refinement_concept_model& operator=(refinement_concept_model other);

private:
    int prop_0_;
    int prop_1_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stereotypes::refinement_concept_model& lhs,
    dogen::stereotypes::refinement_concept_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
