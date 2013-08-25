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
#ifndef DOGEN_OM_TYPES_CPP_ENUMERATOR_HPP
#define DOGEN_OM_TYPES_CPP_ENUMERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/om/serialization/cpp_enumerator_fwd_ser.hpp"
#include "dogen/om/types/doxygen_command.hpp"

namespace dogen {
namespace om {

class cpp_enumerator final {
public:
    cpp_enumerator() = default;
    cpp_enumerator(const cpp_enumerator&) = default;
    cpp_enumerator(cpp_enumerator&&) = default;
    ~cpp_enumerator() = default;

public:
    cpp_enumerator(
        const std::list<dogen::om::doxygen_command>& commands,
        const std::string& name,
        const std::string& value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_enumerator& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_enumerator& v, unsigned int version);

public:
    const std::list<dogen::om::doxygen_command>& commands() const;
    std::list<dogen::om::doxygen_command>& commands();
    void commands(const std::list<dogen::om::doxygen_command>& v);
    void commands(const std::list<dogen::om::doxygen_command>&& v);

    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);

public:
    bool operator==(const cpp_enumerator& rhs) const;
    bool operator!=(const cpp_enumerator& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(cpp_enumerator& other) noexcept;
    cpp_enumerator& operator=(cpp_enumerator other);

private:
    std::list<dogen::om::doxygen_command> commands_;
    std::string name_;
    std::string value_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_enumerator& lhs,
    dogen::om::cpp_enumerator& rhs) {
    lhs.swap(rhs);
}

}

#endif
