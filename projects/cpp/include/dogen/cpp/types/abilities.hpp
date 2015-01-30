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
#ifndef DOGEN_CPP_TYPES_ABILITIES_HPP
#define DOGEN_CPP_TYPES_ABILITIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/cpp/serialization/abilities_fwd_ser.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Represents a C++ class.
 */
class abilities final {
public:
    abilities(const abilities&) = default;
    abilities(abilities&&) = default;
    ~abilities() = default;

public:
    abilities();

public:
    abilities(
        const bool is_comparable,
        const bool is_visitable,
        const bool is_immutable,
        const bool is_original_parent_visitable,
        const bool is_assignable,
        const bool is_swappable);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const abilities& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, abilities& v, unsigned int version);

public:
    /**
     * @brief If true, the C++ class has operator<  defined.
     */
    /**@{*/
    bool is_comparable() const;
    void is_comparable(const bool v);
    /**@}*/

    /**
     * @brief If true, the class has a visitor defined.
     */
    /**@{*/
    bool is_visitable() const;
    void is_visitable(const bool v);
    /**@}*/

    /**
     * @brief If true, the class has only getters.
     */
    /**@{*/
    bool is_immutable() const;
    void is_immutable(const bool v);
    /**@}*/

    /**
     * @brief If true, the class' original parent has a visitor defined.
     */
    /**@{*/
    bool is_original_parent_visitable() const;
    void is_original_parent_visitable(const bool v);
    /**@}*/

    /**
     * @brief If true, the class has the assignment operator.
     */
    /**@{*/
    bool is_assignable() const;
    void is_assignable(const bool v);
    /**@}*/

    /**
     * @brief If true, the class has the swap function.
     */
    /**@{*/
    bool is_swappable() const;
    void is_swappable(const bool v);
    /**@}*/

public:
    bool operator==(const abilities& rhs) const;
    bool operator!=(const abilities& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(abilities& other) noexcept;
    abilities& operator=(abilities other);

private:
    bool is_comparable_;
    bool is_visitable_;
    bool is_immutable_;
    bool is_original_parent_visitable_;
    bool is_assignable_;
    bool is_swappable_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::abilities& lhs,
    dogen::cpp::abilities& rhs) {
    lhs.swap(rhs);
}

}

#endif
