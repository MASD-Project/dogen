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
#ifndef DOGEN_CPP_TYPES_EXPANSION_INCLUSION_DEPENDENCIES_FOR_FORMATTER_HPP
#define DOGEN_CPP_TYPES_EXPANSION_INCLUSION_DEPENDENCIES_FOR_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/cpp/serialization/expansion/inclusion_dependencies_for_formatter_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace expansion {

class inclusion_dependencies_for_formatter final {
public:
    inclusion_dependencies_for_formatter() = default;
    inclusion_dependencies_for_formatter(const inclusion_dependencies_for_formatter&) = default;
    inclusion_dependencies_for_formatter(inclusion_dependencies_for_formatter&&) = default;
    ~inclusion_dependencies_for_formatter() = default;

public:
    inclusion_dependencies_for_formatter(
        const std::string& formatter_name,
        const std::list<std::string>& inclusion_dependencies);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const inclusion_dependencies_for_formatter& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, inclusion_dependencies_for_formatter& v, unsigned int version);

public:
    const std::string& formatter_name() const;
    std::string& formatter_name();
    void formatter_name(const std::string& v);
    void formatter_name(const std::string&& v);

    const std::list<std::string>& inclusion_dependencies() const;
    std::list<std::string>& inclusion_dependencies();
    void inclusion_dependencies(const std::list<std::string>& v);
    void inclusion_dependencies(const std::list<std::string>&& v);

public:
    bool operator==(const inclusion_dependencies_for_formatter& rhs) const;
    bool operator!=(const inclusion_dependencies_for_formatter& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(inclusion_dependencies_for_formatter& other) noexcept;
    inclusion_dependencies_for_formatter& operator=(inclusion_dependencies_for_formatter other);

private:
    std::string formatter_name_;
    std::list<std::string> inclusion_dependencies_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::expansion::inclusion_dependencies_for_formatter& lhs,
    dogen::cpp::expansion::inclusion_dependencies_for_formatter& rhs) {
    lhs.swap(rhs);
}

}

#endif
