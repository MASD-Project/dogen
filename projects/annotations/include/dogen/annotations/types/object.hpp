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
#ifndef DOGEN_ANNOTATIONS_TYPES_OBJECT_HPP
#define DOGEN_ANNOTATIONS_TYPES_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/annotations/types/field_instance.hpp"
#include "dogen/annotations/serialization/object_fwd_ser.hpp"

namespace dogen {
namespace annotations {

/**
 * @brief Represents a set of annotations.
 */
class annotation final {
public:
    annotation() = default;
    annotation(const annotation&) = default;
    annotation(annotation&&) = default;
    ~annotation() = default;

public:
    explicit annotation(const std::unordered_map<std::string, dogen::annotations::field_instance>& fields);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::annotation& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::annotation& v, unsigned int version);

public:
    /**
     * @brief All field instances associated with this object, by qualified name.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::annotations::field_instance>& fields() const;
    std::unordered_map<std::string, dogen::annotations::field_instance>& fields();
    void fields(const std::unordered_map<std::string, dogen::annotations::field_instance>& v);
    void fields(const std::unordered_map<std::string, dogen::annotations::field_instance>&& v);
    /**@}*/

public:
    bool operator==(const annotation& rhs) const;
    bool operator!=(const annotation& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(annotation& other) noexcept;
    annotation& operator=(annotation other);

private:
    std::unordered_map<std::string, dogen::annotations::field_instance> fields_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::annotation& lhs,
    dogen::annotations::annotation& rhs) {
    lhs.swap(rhs);
}

}

#endif
