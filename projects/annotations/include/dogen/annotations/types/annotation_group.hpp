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
#ifndef DOGEN_ANNOTATIONS_TYPES_ANNOTATION_GROUP_HPP
#define DOGEN_ANNOTATIONS_TYPES_ANNOTATION_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/annotations/types/object.hpp"
#include "dogen/annotations/serialization/annotation_group_fwd_ser.hpp"

namespace dogen {
namespace annotations {

/**
 * @brief Related set of annotations, grouped into a single-level hierarchy.
 */
class annotation_group final {
public:
    annotation_group() = default;
    annotation_group(const annotation_group&) = default;
    annotation_group(annotation_group&&) = default;
    ~annotation_group() = default;

public:
    annotation_group(
        const dogen::annotations::object& parent,
        const std::unordered_map<std::string, dogen::annotations::object>& children);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::annotation_group& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::annotation_group& v, unsigned int version);

public:
    /**
     * @brief Top-level annotation.
     */
    /**@{*/
    const dogen::annotations::object& parent() const;
    dogen::annotations::object& parent();
    void parent(const dogen::annotations::object& v);
    void parent(const dogen::annotations::object&& v);
    /**@}*/

    /**
     * @brief Child annotations.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::annotations::object>& children() const;
    std::unordered_map<std::string, dogen::annotations::object>& children();
    void children(const std::unordered_map<std::string, dogen::annotations::object>& v);
    void children(const std::unordered_map<std::string, dogen::annotations::object>&& v);
    /**@}*/

public:
    bool operator==(const annotation_group& rhs) const;
    bool operator!=(const annotation_group& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(annotation_group& other) noexcept;
    annotation_group& operator=(annotation_group other);

private:
    dogen::annotations::object parent_;
    std::unordered_map<std::string, dogen::annotations::object> children_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::annotation_group& lhs,
    dogen::annotations::annotation_group& rhs) {
    lhs.swap(rhs);
}

}

#endif
