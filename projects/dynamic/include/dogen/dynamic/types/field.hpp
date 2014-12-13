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
#ifndef DOGEN_DYNAMIC_TYPES_FIELD_HPP
#define DOGEN_DYNAMIC_TYPES_FIELD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/dynamic/serialization/field_fwd_ser.hpp"
#include "dogen/dynamic/types/name.hpp"
#include "dogen/dynamic/types/value_fwd.hpp"

namespace dogen {
namespace dynamic {

class field final {
public:
    field() = default;
    field(const field&) = default;
    field(field&&) = default;
    ~field() = default;

public:
    field(
        const boost::shared_ptr<dogen::dynamic::value>& value,
        const dogen::dynamic::name& name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const field& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, field& v, unsigned int version);

public:
    const boost::shared_ptr<dogen::dynamic::value>& value() const;
    boost::shared_ptr<dogen::dynamic::value>& value();
    void value(const boost::shared_ptr<dogen::dynamic::value>& v);
    void value(const boost::shared_ptr<dogen::dynamic::value>&& v);

    const dogen::dynamic::name& name() const;
    dogen::dynamic::name& name();
    void name(const dogen::dynamic::name& v);
    void name(const dogen::dynamic::name&& v);

public:
    bool operator==(const field& rhs) const;
    bool operator!=(const field& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(field& other) noexcept;
    field& operator=(field other);

private:
    boost::shared_ptr<dogen::dynamic::value> value_;
    dogen::dynamic::name name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dynamic::field& lhs,
    dogen::dynamic::field& rhs) {
    lhs.swap(rhs);
}

}

#endif
