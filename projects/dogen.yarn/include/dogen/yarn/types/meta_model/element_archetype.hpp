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
#ifndef DOGEN_YARN_TYPES_META_MODEL_ELEMENT_ARCHETYPE_HPP
#define DOGEN_YARN_TYPES_META_MODEL_ELEMENT_ARCHETYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/yarn/serialization/meta_model/element_archetype_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

class element_archetype final {
public:
    element_archetype() = default;
    element_archetype(const element_archetype&) = default;
    element_archetype(element_archetype&&) = default;
    ~element_archetype() = default;

public:
    element_archetype(
        const std::string& element,
        const std::string& archetype);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::element_archetype& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::element_archetype& v, unsigned int version);

public:
    const std::string& element() const;
    std::string& element();
    void element(const std::string& v);
    void element(const std::string&& v);

    const std::string& archetype() const;
    std::string& archetype();
    void archetype(const std::string& v);
    void archetype(const std::string&& v);

public:
    bool operator==(const element_archetype& rhs) const;
    bool operator!=(const element_archetype& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_archetype& other) noexcept;
    element_archetype& operator=(element_archetype other);

private:
    std::string element_;
    std::string archetype_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::element_archetype& lhs,
    dogen::yarn::meta_model::element_archetype& rhs) {
    lhs.swap(rhs);
}

}

#endif
