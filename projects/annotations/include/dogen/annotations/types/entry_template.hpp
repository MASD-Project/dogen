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
#ifndef DOGEN_ANNOTATIONS_TYPES_ENTRY_TEMPLATE_HPP
#define DOGEN_ANNOTATIONS_TYPES_ENTRY_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/annotations/types/name.hpp"
#include "dogen/annotations/types/template_kinds.hpp"
#include "dogen/annotations/types/ownership_hierarchy.hpp"
#include "dogen/annotations/serialization/entry_template_fwd_ser.hpp"

namespace dogen {
namespace annotations {

class entry_template final {
public:
    entry_template(const entry_template&) = default;
    entry_template(entry_template&&) = default;
    ~entry_template() = default;

public:
    entry_template();

public:
    entry_template(
        const dogen::annotations::name& name,
        const dogen::annotations::ownership_hierarchy& ownership_hierarchy,
        const std::list<std::string>& untyped_value,
        const dogen::annotations::template_kinds kind);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::entry_template& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::entry_template& v, unsigned int version);

public:
    const dogen::annotations::name& name() const;
    dogen::annotations::name& name();
    void name(const dogen::annotations::name& v);
    void name(const dogen::annotations::name&& v);

    const dogen::annotations::ownership_hierarchy& ownership_hierarchy() const;
    dogen::annotations::ownership_hierarchy& ownership_hierarchy();
    void ownership_hierarchy(const dogen::annotations::ownership_hierarchy& v);
    void ownership_hierarchy(const dogen::annotations::ownership_hierarchy&& v);

    const std::list<std::string>& untyped_value() const;
    std::list<std::string>& untyped_value();
    void untyped_value(const std::list<std::string>& v);
    void untyped_value(const std::list<std::string>&& v);

    dogen::annotations::template_kinds kind() const;
    void kind(const dogen::annotations::template_kinds v);

public:
    bool operator==(const entry_template& rhs) const;
    bool operator!=(const entry_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(entry_template& other) noexcept;
    entry_template& operator=(entry_template other);

private:
    dogen::annotations::name name_;
    dogen::annotations::ownership_hierarchy ownership_hierarchy_;
    std::list<std::string> untyped_value_;
    dogen::annotations::template_kinds kind_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::entry_template& lhs,
    dogen::annotations::entry_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
