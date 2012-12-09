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
#ifndef DOGEN_SML_TYPES_NESTED_QUALIFIED_NAME_HPP
#define DOGEN_SML_TYPES_NESTED_QUALIFIED_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include "dogen/sml/serialization/nested_qualified_name_fwd_ser.hpp"
#include "dogen/sml/types/nested_qualified_name.hpp"
#include "dogen/sml/types/qualified_name.hpp"

namespace dogen {
namespace sml {

/*
 * @brief A composite qualified name.
 */
class nested_qualified_name final {
public:
    nested_qualified_name(const nested_qualified_name&) = default;
    nested_qualified_name(nested_qualified_name&&) = default;
    ~nested_qualified_name() = default;

public:
    nested_qualified_name();

public:
    nested_qualified_name(
        const dogen::sml::qualified_name& type,
        const std::list<dogen::sml::nested_qualified_name>& children,
        const bool is_pointer);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const nested_qualified_name& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, nested_qualified_name& v, unsigned int version);

public:
    /*
     * @brief Top-level, containing type.
     */
    /**@{*/
    const dogen::sml::qualified_name& type() const {
        return type_;
    }

    dogen::sml::qualified_name& type() {
        return type_;
    }

    void type(const dogen::sml::qualified_name& v) {
        type_ = v;
    }

    void type(const dogen::sml::qualified_name&& v) {
        type_ = std::move(v);
    }
    /**@}*/

    /*
     * @brief Child types.
     */
    /**@{*/
    const std::list<dogen::sml::nested_qualified_name>& children() const {
        return children_;
    }

    std::list<dogen::sml::nested_qualified_name>& children() {
        return children_;
    }

    void children(const std::list<dogen::sml::nested_qualified_name>& v) {
        children_ = v;
    }

    void children(const std::list<dogen::sml::nested_qualified_name>&& v) {
        children_ = std::move(v);
    }
    /**@}*/

    /*
     * @brief If true, the top-level type is a pointer. If false, its a stack variable.
     */
    /**@{*/
    bool is_pointer() const {
        return is_pointer_;
    }

    void is_pointer(const bool v) {
        is_pointer_ = v;
    }
    /**@}*/

public:
    bool operator==(const nested_qualified_name& rhs) const;
    bool operator!=(const nested_qualified_name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(nested_qualified_name& other) noexcept;
    nested_qualified_name& operator=(nested_qualified_name other);

private:
    dogen::sml::qualified_name type_;
    std::list<dogen::sml::nested_qualified_name> children_;
    bool is_pointer_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::nested_qualified_name& lhs,
    dogen::sml::nested_qualified_name& rhs) {
    lhs.swap(rhs);
}

}

#endif
