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
#ifndef DOGEN_CPP_TYPES_TEMPLATE_ARGUMENT_HPP
#define DOGEN_CPP_TYPES_TEMPLATE_ARGUMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/cpp/serialization/template_argument_fwd_ser.hpp"

namespace dogen {
namespace cpp {

class template_argument final {
public:
    template_argument() = default;
    template_argument(const template_argument&) = default;
    template_argument(template_argument&&) = default;
    ~template_argument() = default;

public:
    explicit template_argument(const std::string& name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const template_argument& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, template_argument& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

public:
    bool operator==(const template_argument& rhs) const;
    bool operator!=(const template_argument& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(template_argument& other) noexcept;
    template_argument& operator=(template_argument other);

private:
    std::string name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::template_argument& lhs,
    dogen::cpp::template_argument& rhs) {
    lhs.swap(rhs);
}

}

#endif
