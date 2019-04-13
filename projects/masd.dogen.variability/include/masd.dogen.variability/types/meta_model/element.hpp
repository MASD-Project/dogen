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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_META_MODEL_ELEMENT_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_META_MODEL_ELEMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "masd.dogen.variability/types/meta_model/name.hpp"

namespace masd::dogen::variability::meta_model {

/**
 * @brief Represents an element modeling some aspect of variability.
 */
class element {
public:
    element() = default;
    element(const element&) = default;
    element(element&&) = default;

    virtual ~element() noexcept = 0;

public:
    element(
        const masd::dogen::variability::meta_model::name& name,
        const std::string& description);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    const masd::dogen::variability::meta_model::name& name() const;
    masd::dogen::variability::meta_model::name& name();
    void name(const masd::dogen::variability::meta_model::name& v);
    void name(const masd::dogen::variability::meta_model::name&& v);

    /**
     * @brief Human readable description of the feature, used for documentation.
     */
    /**@{*/
    const std::string& description() const;
    std::string& description();
    void description(const std::string& v);
    void description(const std::string&& v);
    /**@}*/

protected:
    bool compare(const element& rhs) const;
public:
    virtual bool equals(const element& other) const = 0;

protected:
    void swap(element& other) noexcept;

private:
    masd::dogen::variability::meta_model::name name_;
    std::string description_;
};

inline element::~element() noexcept { }

inline bool operator==(const element& lhs, const element& rhs) {
    return lhs.equals(rhs);
}

}

#endif
