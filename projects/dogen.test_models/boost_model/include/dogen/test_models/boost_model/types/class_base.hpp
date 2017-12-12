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
#ifndef DOGEN_TEST_MODELS_BOOST_MODEL_TYPES_CLASS_BASE_HPP
#define DOGEN_TEST_MODELS_BOOST_MODEL_TYPES_CLASS_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/boost_model/serialization/class_base_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace boost_model {

class class_base {
public:
    class_base(const class_base&) = default;
    class_base(class_base&&) = default;

public:
    class_base();

    virtual ~class_base() noexcept = 0;

public:
    explicit class_base(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::boost_model::class_base& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::boost_model::class_base& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    int prop_0() const;
    void prop_0(const int v);

protected:
    bool compare(const class_base& rhs) const;
public:
    virtual bool equals(const class_base& other) const = 0;

protected:
    void swap(class_base& other) noexcept;

private:
    int prop_0_;
};

inline class_base::~class_base() noexcept { }

inline bool operator==(const class_base& lhs, const class_base& rhs) {
    return lhs.equals(rhs);
}

} } }

#endif
