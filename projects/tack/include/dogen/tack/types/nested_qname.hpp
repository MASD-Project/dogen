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
#ifndef DOGEN_TACK_TYPES_NESTED_QNAME_HPP
#define DOGEN_TACK_TYPES_NESTED_QNAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen/tack/types/qname.hpp"
#include "dogen/tack/types/nested_qname.hpp"
#include "dogen/tack/serialization/nested_qname_fwd_ser.hpp"

namespace dogen {
namespace tack {

/**
 * @brief A composite qname.
 */
class nested_qname final {
public:
    nested_qname(const nested_qname&) = default;
    nested_qname(nested_qname&&) = default;
    ~nested_qname() = default;

public:
    nested_qname();

public:
    nested_qname(
        const dogen::tack::qname& type,
        const std::list<dogen::tack::nested_qname>& children,
        const bool is_pointer);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const nested_qname& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, nested_qname& v, unsigned int version);

public:
    /**
     * @brief Top-level, containing type.
     */
    /**@{*/
    const dogen::tack::qname& type() const;
    dogen::tack::qname& type();
    void type(const dogen::tack::qname& v);
    void type(const dogen::tack::qname&& v);
    /**@}*/

    /**
     * @brief Child types.
     */
    /**@{*/
    const std::list<dogen::tack::nested_qname>& children() const;
    std::list<dogen::tack::nested_qname>& children();
    void children(const std::list<dogen::tack::nested_qname>& v);
    void children(const std::list<dogen::tack::nested_qname>&& v);
    /**@}*/

    /**
     * @brief If true, the top-level type is a pointer. If false, its a stack variable.
     */
    /**@{*/
    bool is_pointer() const;
    void is_pointer(const bool v);
    /**@}*/

public:
    bool operator==(const nested_qname& rhs) const;
    bool operator!=(const nested_qname& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(nested_qname& other) noexcept;
    nested_qname& operator=(nested_qname other);

private:
    dogen::tack::qname type_;
    std::list<dogen::tack::nested_qname> children_;
    bool is_pointer_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::tack::nested_qname& lhs,
    dogen::tack::nested_qname& rhs) {
    lhs.swap(rhs);
}

}

#endif
