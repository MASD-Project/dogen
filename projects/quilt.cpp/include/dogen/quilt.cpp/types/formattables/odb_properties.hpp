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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_ODB_PROPERTIES_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_ODB_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/quilt.cpp/serialization/formattables/odb_properties_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class odb_properties final {
public:
    odb_properties(const odb_properties&) = default;
    odb_properties(odb_properties&&) = default;
    ~odb_properties() = default;

public:
    odb_properties();

public:
    odb_properties(
        const bool is_value,
        const std::list<std::string>& top_level_odb_pragmas,
        const std::unordered_map<std::string, std::list<std::string> >& attribute_level_odb_pragmas);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::odb_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::odb_properties& v, unsigned int version);

public:
    bool is_value() const;
    void is_value(const bool v);

    const std::list<std::string>& top_level_odb_pragmas() const;
    std::list<std::string>& top_level_odb_pragmas();
    void top_level_odb_pragmas(const std::list<std::string>& v);
    void top_level_odb_pragmas(const std::list<std::string>&& v);

    const std::unordered_map<std::string, std::list<std::string> >& attribute_level_odb_pragmas() const;
    std::unordered_map<std::string, std::list<std::string> >& attribute_level_odb_pragmas();
    void attribute_level_odb_pragmas(const std::unordered_map<std::string, std::list<std::string> >& v);
    void attribute_level_odb_pragmas(const std::unordered_map<std::string, std::list<std::string> >&& v);

public:
    bool operator==(const odb_properties& rhs) const;
    bool operator!=(const odb_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(odb_properties& other) noexcept;
    odb_properties& operator=(odb_properties other);

private:
    bool is_value_;
    std::list<std::string> top_level_odb_pragmas_;
    std::unordered_map<std::string, std::list<std::string> > attribute_level_odb_pragmas_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::odb_properties& lhs,
    dogen::quilt::cpp::formattables::odb_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
