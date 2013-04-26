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
#ifndef DOGEN_SML_TYPES_ENTRY_HPP
#define DOGEN_SML_TYPES_ENTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/sml/serialization/entry_fwd_ser.hpp"

namespace dogen {
namespace sml {

class entry final {
public:
    entry() = default;
    entry(const entry&) = default;
    entry(entry&&) = default;
    ~entry() = default;

public:
    entry(
        const std::string& name,
        const std::string& value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const entry& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, entry& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);

public:
    bool operator==(const entry& rhs) const;
    bool operator!=(const entry& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(entry& other) noexcept;
    entry& operator=(entry other);

private:
    std::string name_;
    std::string value_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::entry& lhs,
    dogen::sml::entry& rhs) {
    lhs.swap(rhs);
}

}

#endif
