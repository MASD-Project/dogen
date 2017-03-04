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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_BASE_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/cpp_model/types/base_visitor_fwd.hpp"
#include "dogen/test_models/cpp_model/serialization/base_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

class base {
public:
    base() = default;
    base(const base&) = default;
    base(base&&) = default;
    base& operator=(const base&) = default;

    virtual ~base() noexcept = 0;

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::base& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::base& v, unsigned int version);

public:
    virtual void accept(const base_visitor& v) const = 0;
    virtual void accept(base_visitor& v) const = 0;
    virtual void accept(const base_visitor& v) = 0;
    virtual void accept(base_visitor& v) = 0;

public:
    virtual void to_stream(std::ostream& s) const;

protected:
    bool compare(const base& rhs) const;
public:
    virtual bool equals(const base& other) const = 0;

protected:
    void swap(base& other) noexcept;

};

inline base::~base() noexcept { }

inline bool operator==(const base& lhs, const base& rhs) {
    return lhs.equals(rhs);
}

} } }

#endif
