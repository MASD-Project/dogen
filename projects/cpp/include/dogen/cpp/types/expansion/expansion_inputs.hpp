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
#ifndef DOGEN_CPP_TYPES_EXPANSION_EXPANSION_INPUTS_HPP
#define DOGEN_CPP_TYPES_EXPANSION_EXPANSION_INPUTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/cpp/serialization/expansion/expansion_inputs_fwd_ser.hpp"
#include "dogen/cpp/types/expansion/path_derivatives.hpp"

namespace dogen {
namespace cpp {
namespace expansion {

class expansion_inputs final {
public:
    expansion_inputs() = default;
    expansion_inputs(const expansion_inputs&) = default;
    expansion_inputs(expansion_inputs&&) = default;
    ~expansion_inputs() = default;

public:
    expansion_inputs(
        const dogen::cpp::expansion::path_derivatives& path_derivatives,
        const std::list<std::string>& inclusion_dependencies);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const expansion_inputs& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, expansion_inputs& v, unsigned int version);

public:
    const dogen::cpp::expansion::path_derivatives& path_derivatives() const;
    dogen::cpp::expansion::path_derivatives& path_derivatives();
    void path_derivatives(const dogen::cpp::expansion::path_derivatives& v);
    void path_derivatives(const dogen::cpp::expansion::path_derivatives&& v);

    const std::list<std::string>& inclusion_dependencies() const;
    std::list<std::string>& inclusion_dependencies();
    void inclusion_dependencies(const std::list<std::string>& v);
    void inclusion_dependencies(const std::list<std::string>&& v);

public:
    bool operator==(const expansion_inputs& rhs) const;
    bool operator!=(const expansion_inputs& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(expansion_inputs& other) noexcept;
    expansion_inputs& operator=(expansion_inputs other);

private:
    dogen::cpp::expansion::path_derivatives path_derivatives_;
    std::list<std::string> inclusion_dependencies_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::expansion::expansion_inputs& lhs,
    dogen::cpp::expansion::expansion_inputs& rhs) {
    lhs.swap(rhs);
}

}

#endif
