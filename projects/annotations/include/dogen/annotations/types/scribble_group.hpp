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
#ifndef DOGEN_ANNOTATIONS_TYPES_SCRIBBLE_GROUP_HPP
#define DOGEN_ANNOTATIONS_TYPES_SCRIBBLE_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/annotations/types/scribble.hpp"
#include "dogen/annotations/serialization/scribble_group_fwd_ser.hpp"

namespace dogen {
namespace annotations {

/**
 * @brief A scribble is an annotation in raw form, prior to processing. A scribble group is a hierachical set of scribles.
 */
class scribble_group final {
public:
    scribble_group() = default;
    scribble_group(const scribble_group&) = default;
    scribble_group(scribble_group&&) = default;
    ~scribble_group() = default;

public:
    scribble_group(
        const dogen::annotations::scribble& parent,
        const std::unordered_map<std::string, dogen::annotations::scribble>& children);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::scribble_group& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::scribble_group& v, unsigned int version);

public:
    /**
     * @brief Top-level scribble.
     */
    /**@{*/
    const dogen::annotations::scribble& parent() const;
    dogen::annotations::scribble& parent();
    void parent(const dogen::annotations::scribble& v);
    void parent(const dogen::annotations::scribble&& v);
    /**@}*/

    /**
     * @brief Child scribbles.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::annotations::scribble>& children() const;
    std::unordered_map<std::string, dogen::annotations::scribble>& children();
    void children(const std::unordered_map<std::string, dogen::annotations::scribble>& v);
    void children(const std::unordered_map<std::string, dogen::annotations::scribble>&& v);
    /**@}*/

public:
    bool operator==(const scribble_group& rhs) const;
    bool operator!=(const scribble_group& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(scribble_group& other) noexcept;
    scribble_group& operator=(scribble_group other);

private:
    dogen::annotations::scribble parent_;
    std::unordered_map<std::string, dogen::annotations::scribble> children_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::scribble_group& lhs,
    dogen::annotations::scribble_group& rhs) {
    lhs.swap(rhs);
}

}

#endif
