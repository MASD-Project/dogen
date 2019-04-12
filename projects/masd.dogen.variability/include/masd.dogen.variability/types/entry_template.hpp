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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_ENTRY_TEMPLATE_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_ENTRY_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "masd.dogen.variability/types/name.hpp"
#include "masd.dogen.variability/types/template_kinds.hpp"
#include "masd.dogen.variability/types/archetype_location.hpp"

namespace masd::dogen::variability {

class entry_template final {
public:
    entry_template(const entry_template&) = default;
    entry_template(entry_template&&) = default;
    ~entry_template() = default;

public:
    entry_template();

public:
    entry_template(
        const masd::dogen::variability::name& name,
        const masd::dogen::variability::archetype_location& archetype_location,
        const std::list<std::string>& untyped_value,
        const masd::dogen::variability::template_kinds kind);

public:
    const masd::dogen::variability::name& name() const;
    masd::dogen::variability::name& name();
    void name(const masd::dogen::variability::name& v);
    void name(const masd::dogen::variability::name&& v);

    const masd::dogen::variability::archetype_location& archetype_location() const;
    masd::dogen::variability::archetype_location& archetype_location();
    void archetype_location(const masd::dogen::variability::archetype_location& v);
    void archetype_location(const masd::dogen::variability::archetype_location&& v);

    const std::list<std::string>& untyped_value() const;
    std::list<std::string>& untyped_value();
    void untyped_value(const std::list<std::string>& v);
    void untyped_value(const std::list<std::string>&& v);

    masd::dogen::variability::template_kinds kind() const;
    void kind(const masd::dogen::variability::template_kinds v);

public:
    bool operator==(const entry_template& rhs) const;
    bool operator!=(const entry_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(entry_template& other) noexcept;
    entry_template& operator=(entry_template other);

private:
    masd::dogen::variability::name name_;
    masd::dogen::variability::archetype_location archetype_location_;
    std::list<std::string> untyped_value_;
    masd::dogen::variability::template_kinds kind_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::variability::entry_template& lhs,
    masd::dogen::variability::entry_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
