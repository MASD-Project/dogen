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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_FURTHER_INHERITED_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_FURTHER_INHERITED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/cpp_model/types/base_with_object_template.hpp"
#include "dogen/test_models/cpp_model/serialization/further_inherited_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

/**
 * @brief Descendant class that instantiates an object template which is a descendant
 * of the object template instantiated by the base class.
 */
class further_inherited final : public dogen::test_models::cpp_model::base_with_object_template {
public:
    further_inherited(const further_inherited&) = default;
    further_inherited(further_inherited&&) = default;

public:
    further_inherited();

    virtual ~further_inherited() noexcept { }

public:
    further_inherited(
        const int prop_2,
        const std::string& prop_0,
        const int prop_3,
        const int prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::further_inherited& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::further_inherited& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Multiple parents property.
     */
    /**@{*/
    int prop_3() const;
    void prop_3(const int v);
    /**@}*/

    /**
     * @brief A property
     */
    /**@{*/
    int prop_1() const;
    void prop_1(const int v);
    /**@}*/

public:
    bool operator==(const further_inherited& rhs) const;
    bool operator!=(const further_inherited& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::test_models::cpp_model::base_with_object_template& other) const override;

public:
    void swap(further_inherited& other) noexcept;
    further_inherited& operator=(further_inherited other);

private:
    int prop_3_;
    int prop_1_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::further_inherited& lhs,
    dogen::test_models::cpp_model::further_inherited& rhs) {
    lhs.swap(rhs);
}

}

#endif
