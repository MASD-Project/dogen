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
#ifndef DOGEN_COMMENTS_DOMAIN_ONE_LINE_HPP
#define DOGEN_COMMENTS_DOMAIN_ONE_LINE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/comments/domain/versioned_key.hpp"
#include "dogen/comments/serialization/one_line_fwd_ser.hpp"

namespace dogen {
namespace comments {

/*
 * @brief this is the brief comment
 */
class one_line final {
public:
    one_line(const one_line&) = default;
    one_line(one_line&&) = default;
    ~one_line() = default;

public:
    one_line();

public:
    one_line(
        const int prop_0,
        const int prop_1,
        const int prop_2,
        const dogen::comments::versioned_key& versioned_key);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const one_line& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, one_line& v, unsigned int version);

public:
    /*
     * @brief another brief comment
     */
    /**@{*/
    int prop_0() const {
        return prop_0_;
    }

    void prop_0(const int v) {
        prop_0_ = v;
    }
    /**@}*/

    /*
     * @brief the brief comment
     *
     * a second line
     */
    /**@{*/
    int prop_1() const {
        return prop_1_;
    }

    void prop_1(const int v) {
        prop_1_ = v;
    }
    /**@}*/

    int prop_2() const {
        return prop_2_;
    }

    void prop_2(const int v) {
        prop_2_ = v;
    }

    dogen::comments::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(const dogen::comments::versioned_key& v) {
        versioned_key_ = v;
    }

public:
    bool operator==(const one_line& rhs) const;
    bool operator!=(const one_line& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(one_line& other) noexcept;
    one_line& operator=(one_line other);

private:
    int prop_0_;
    int prop_1_;
    int prop_2_;
    dogen::comments::versioned_key versioned_key_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::comments::one_line& lhs,
    dogen::comments::one_line& rhs) {
    lhs.swap(rhs);
}

}

#endif
