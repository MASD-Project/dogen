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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_MOVE_CTOR_BASE_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_MOVE_CTOR_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/test_models/cpp_model/serialization/move_ctor_base_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

/**
 * @brief Base class for scenario that tests code generated move contructors.
 */
class move_ctor_base {
public:
    move_ctor_base() = default;
    move_ctor_base(const move_ctor_base&) = default;

    virtual ~move_ctor_base() noexcept = 0;

public:
    move_ctor_base(move_ctor_base&& rhs);

public:
    explicit move_ctor_base(const boost::filesystem::path& prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::move_ctor_base& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::move_ctor_base& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief Force manual move constructor.
     */
    /**@{*/
    const boost::filesystem::path& prop_0() const;
    boost::filesystem::path& prop_0();
    void prop_0(const boost::filesystem::path& v);
    void prop_0(const boost::filesystem::path&& v);
    /**@}*/

protected:
    bool compare(const move_ctor_base& rhs) const;
public:
    virtual bool equals(const move_ctor_base& other) const = 0;

protected:
    void swap(move_ctor_base& other) noexcept;

private:
    boost::filesystem::path prop_0_;
};

inline move_ctor_base::~move_ctor_base() noexcept { }

inline bool operator==(const move_ctor_base& lhs, const move_ctor_base& rhs) {
    return lhs.equals(rhs);
}

} } }

#endif
