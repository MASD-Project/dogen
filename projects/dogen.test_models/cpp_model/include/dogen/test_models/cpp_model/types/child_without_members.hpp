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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_CHILD_WITHOUT_MEMBERS_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_CHILD_WITHOUT_MEMBERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/cpp_model/types/parent_without_members.hpp"
#include "dogen/test_models/cpp_model/serialization/child_without_members_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

class child_without_members final : public dogen::test_models::cpp_model::parent_without_members {
public:
    child_without_members() = default;
    child_without_members(const child_without_members&) = default;
    child_without_members(child_without_members&&) = default;
    child_without_members& operator=(const child_without_members&) = default;

    virtual ~child_without_members() noexcept { }

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::child_without_members& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::child_without_members& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const child_without_members& rhs) const;
    bool operator!=(const child_without_members& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::test_models::cpp_model::parent_without_members& other) const override;

};

} } }

#endif
