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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_NON_FINAL_LEAF_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_NON_FINAL_LEAF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/cpp_model/types/descendant1.hpp"
#include "dogen/test_models/cpp_model/serialization/non_final_leaf_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

class non_final_leaf : public dogen::test_models::cpp_model::descendant1 {
public:
    non_final_leaf(const non_final_leaf&) = default;
    non_final_leaf(non_final_leaf&&) = default;

public:
    non_final_leaf();

    virtual ~non_final_leaf() noexcept { }

public:
    explicit non_final_leaf(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::non_final_leaf& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::non_final_leaf& v, unsigned int version);

public:
    using base::accept;

    virtual void accept(const base_visitor& v) const override;
    virtual void accept(base_visitor& v) const override;
    virtual void accept(const base_visitor& v) override;
    virtual void accept(base_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    int prop_0() const;
    void prop_0(const int v);

public:
    bool operator==(const non_final_leaf& rhs) const;
    bool operator!=(const non_final_leaf& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::test_models::cpp_model::base& other) const override;

public:
    void swap(non_final_leaf& other) noexcept;
    non_final_leaf& operator=(non_final_leaf other);

private:
    int prop_0_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::non_final_leaf& lhs,
    dogen::test_models::cpp_model::non_final_leaf& rhs) {
    lhs.swap(rhs);
}

}

#endif
