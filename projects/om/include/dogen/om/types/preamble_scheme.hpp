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
#ifndef DOGEN_OM_TYPES_PREAMBLE_SCHEME_HPP
#define DOGEN_OM_TYPES_PREAMBLE_SCHEME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include <unordered_map>
#include "dogen/om/serialization/preamble_scheme_fwd_ser.hpp"
#include "dogen/om/types/preamble.hpp"

namespace dogen {
namespace om {

/**
 * @brief Group of preambles logically associated.
 *
 * For example, one may choose to have a set of preambles for @e emacs , or for
 * @e vi, etc.
 */
class preamble_scheme final {
public:
    preamble_scheme() = default;
    preamble_scheme(const preamble_scheme&) = default;
    preamble_scheme(preamble_scheme&&) = default;
    ~preamble_scheme() = default;

public:
    explicit preamble_scheme(const std::unordered_map<std::string, dogen::om::preamble>& preambles);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const preamble_scheme& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, preamble_scheme& v, unsigned int version);

public:
    /**
     * @brief All the preambles for this scheme.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::om::preamble>& preambles() const;
    std::unordered_map<std::string, dogen::om::preamble>& preambles();
    void preambles(const std::unordered_map<std::string, dogen::om::preamble>& v);
    void preambles(const std::unordered_map<std::string, dogen::om::preamble>&& v);
    /**@}*/

public:
    bool operator==(const preamble_scheme& rhs) const;
    bool operator!=(const preamble_scheme& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(preamble_scheme& other) noexcept;
    preamble_scheme& operator=(preamble_scheme other);

private:
    std::unordered_map<std::string, dogen::om::preamble> preambles_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::preamble_scheme& lhs,
    dogen::om::preamble_scheme& rhs) {
    lhs.swap(rhs);
}

}

#endif
