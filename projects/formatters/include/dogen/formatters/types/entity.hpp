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
#ifndef DOGEN_FORMATTERS_TYPES_ENTITY_HPP
#define DOGEN_FORMATTERS_TYPES_ENTITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/formatters/serialization/entity_fwd_ser.hpp"
#include "dogen/formatters/types/annotation.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Entity which can be formatted.
 *
 *
 * Maps to the Member class in the Columbus schema, but in order to avoid
 * confusion with member variables, etc we renamed it to element.
 *
 * §3.1.1:
 *
 * An entity is a value, object, subobject, base class subobject, array element,
 * variable, function, instance of a function, enumerator, type, class member,
 * template, or namespace.
 */
class entity final {
public:
    entity() = default;
    entity(const entity&) = default;
    entity(entity&&) = default;
    ~entity() = default;

public:
    explicit entity(const dogen::formatters::annotation& annotation);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const entity& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, entity& v, unsigned int version);

public:
    /**
     * @brief Generic information about the entity such as licence, etc.
     */
    /**@{*/
    const dogen::formatters::annotation& annotation() const;
    dogen::formatters::annotation& annotation();
    void annotation(const dogen::formatters::annotation& v);
    void annotation(const dogen::formatters::annotation&& v);
    /**@}*/

public:
    bool operator==(const entity& rhs) const;
    bool operator!=(const entity& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(entity& other) noexcept;
    entity& operator=(entity other);

private:
    dogen::formatters::annotation annotation_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatters::entity& lhs,
    dogen::formatters::entity& rhs) {
    lhs.swap(rhs);
}

}

#endif
