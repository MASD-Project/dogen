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
#ifndef DOGEN_ANNOTATIONS_TYPES_ANNOTATION_HPP
#define DOGEN_ANNOTATIONS_TYPES_ANNOTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen/annotations/types/value_fwd.hpp"
#include "dogen/annotations/types/scope_types.hpp"
#include "dogen/annotations/serialization/annotation_fwd_ser.hpp"

namespace dogen {
namespace annotations {

/**
 * @brief Represents an annotation that can be associated with an external object.
 */
class annotation final {
public:
    annotation(const annotation&) = default;
    annotation(annotation&&) = default;
    ~annotation() = default;

public:
    annotation();

public:
    annotation(
        const std::unordered_map<std::string, boost::shared_ptr<dogen::annotations::value> >& entries,
        const dogen::annotations::scope_types scope);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::annotation& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::annotation& v, unsigned int version);

public:
    /**
     * @brief All entries in this annotation. Each entry is a key-value-pair of id and value.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<dogen::annotations::value> >& entries() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::annotations::value> >& entries();
    void entries(const std::unordered_map<std::string, boost::shared_ptr<dogen::annotations::value> >& v);
    void entries(const std::unordered_map<std::string, boost::shared_ptr<dogen::annotations::value> >&& v);
    /**@}*/

    dogen::annotations::scope_types scope() const;
    void scope(const dogen::annotations::scope_types v);

public:
    bool operator==(const annotation& rhs) const;
    bool operator!=(const annotation& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(annotation& other) noexcept;
    annotation& operator=(annotation other);

private:
    std::unordered_map<std::string, boost::shared_ptr<dogen::annotations::value> > entries_;
    dogen::annotations::scope_types scope_;
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
