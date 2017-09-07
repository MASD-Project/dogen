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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_BASE_WITH_OBJECT_TEMPLATE_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_BASE_WITH_OBJECT_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen/test_models/cpp_model/serialization/base_with_object_template_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

/**
 * @brief Base class that instantiates a derived object template.
 */
class base_with_object_template {
public:
    base_with_object_template(const base_with_object_template&) = default;
    base_with_object_template(base_with_object_template&&) = default;

public:
    base_with_object_template();

    virtual ~base_with_object_template() noexcept = 0;

public:
    base_with_object_template(
        const int prop_2,
        const std::string& prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::base_with_object_template& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::base_with_object_template& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief Second descendant property
     */
    /**@{*/
    int prop_2() const;
    void prop_2(const int v);
    /**@}*/

    /**
     * @brief Ensure we're testing header files inclusion.
     */
    /**@{*/
    const std::string& prop_0() const;
    std::string& prop_0();
    void prop_0(const std::string& v);
    void prop_0(const std::string&& v);
    /**@}*/

protected:
    bool compare(const base_with_object_template& rhs) const;
public:
    virtual bool equals(const base_with_object_template& other) const = 0;

protected:
    void swap(base_with_object_template& other) noexcept;

private:
    int prop_2_;
    std::string prop_0_;
};

inline base_with_object_template::~base_with_object_template() noexcept { }

inline bool operator==(const base_with_object_template& lhs, const base_with_object_template& rhs) {
    return lhs.equals(rhs);
}

} } }

#endif
