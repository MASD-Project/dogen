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
#ifndef DOGEN_TACK_TYPES_NESTED_NAME_HPP
#define DOGEN_TACK_TYPES_NESTED_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen/tack/types/name.hpp"
#include "dogen/tack/types/nested_name.hpp"
#include "dogen/tack/serialization/nested_name_fwd_ser.hpp"

namespace dogen {
namespace tack {

/**
 * @brief A composite name.
 */
class nested_name final {
public:
    nested_name(const nested_name&) = default;
    nested_name(nested_name&&) = default;
    ~nested_name() = default;

public:
    nested_name();

public:
    nested_name(
        const dogen::tack::name& type,
        const std::list<dogen::tack::nested_name>& children,
        const bool is_pointer);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const nested_name& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, nested_name& v, unsigned int version);

public:
    /**
     * @brief Top-level, containing type.
     */
    /**@{*/
    const dogen::tack::name& type() const;
    dogen::tack::name& type();
    void type(const dogen::tack::name& v);
    void type(const dogen::tack::name&& v);
    /**@}*/

    /**
     * @brief Child types.
     */
    /**@{*/
    const std::list<dogen::tack::nested_name>& children() const;
    std::list<dogen::tack::nested_name>& children();
    void children(const std::list<dogen::tack::nested_name>& v);
    void children(const std::list<dogen::tack::nested_name>&& v);
    /**@}*/

    /**
     * @brief If true, the top-level type is a pointer. If false, its a stack variable.
     */
    /**@{*/
    bool is_pointer() const;
    void is_pointer(const bool v);
    /**@}*/

public:
    bool operator==(const nested_name& rhs) const;
    bool operator!=(const nested_name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(nested_name& other) noexcept;
    nested_name& operator=(nested_name other);

private:
    dogen::tack::name type_;
    std::list<dogen::tack::nested_name> children_;
    bool is_pointer_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::tack::nested_name& lhs,
    dogen::tack::nested_name& rhs) {
    lhs.swap(rhs);
}

}

#endif
