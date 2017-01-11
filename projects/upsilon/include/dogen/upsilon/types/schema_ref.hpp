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
#ifndef DOGEN_UPSILON_TYPES_SCHEMA_REF_HPP
#define DOGEN_UPSILON_TYPES_SCHEMA_REF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/upsilon/serialization/schema_ref_fwd_ser.hpp"

namespace dogen {
namespace upsilon {

class schema_ref final {
public:
    schema_ref() = default;
    schema_ref(const schema_ref&) = default;
    schema_ref(schema_ref&&) = default;
    ~schema_ref() = default;

public:
    schema_ref(
        const std::string& name,
        const std::string& file);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::upsilon::schema_ref& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::upsilon::schema_ref& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& file() const;
    std::string& file();
    void file(const std::string& v);
    void file(const std::string&& v);

public:
    bool operator==(const schema_ref& rhs) const;
    bool operator!=(const schema_ref& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(schema_ref& other) noexcept;
    schema_ref& operator=(schema_ref other);

private:
    std::string name_;
    std::string file_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::upsilon::schema_ref& lhs,
    dogen::upsilon::schema_ref& rhs) {
    lhs.swap(rhs);
}

}

#endif
