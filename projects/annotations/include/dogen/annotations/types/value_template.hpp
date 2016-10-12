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
#ifndef DOGEN_ANNOTATIONS_TYPES_VALUE_TEMPLATE_HPP
#define DOGEN_ANNOTATIONS_TYPES_VALUE_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/annotations/types/value_fwd.hpp"
#include "dogen/annotations/types/template_kinds.hpp"
#include "dogen/annotations/types/ownership_hierarchy.hpp"
#include "dogen/annotations/serialization/value_template_fwd_ser.hpp"

namespace dogen {
namespace annotations {

class value_template final {
public:
    value_template(const value_template&) = default;
    value_template(value_template&&) = default;
    ~value_template() = default;

public:
    value_template();

public:
    value_template(
        const std::string& name,
        const dogen::annotations::ownership_hierarchy& ownership_hierarchy,
        const boost::shared_ptr<dogen::annotations::value>& value,
        const dogen::annotations::template_kinds kind);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::value_template& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::value_template& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const dogen::annotations::ownership_hierarchy& ownership_hierarchy() const;
    dogen::annotations::ownership_hierarchy& ownership_hierarchy();
    void ownership_hierarchy(const dogen::annotations::ownership_hierarchy& v);
    void ownership_hierarchy(const dogen::annotations::ownership_hierarchy&& v);

    const boost::shared_ptr<dogen::annotations::value>& value() const;
    boost::shared_ptr<dogen::annotations::value>& value();
    void value(const boost::shared_ptr<dogen::annotations::value>& v);
    void value(const boost::shared_ptr<dogen::annotations::value>&& v);

    dogen::annotations::template_kinds kind() const;
    void kind(const dogen::annotations::template_kinds v);

public:
    bool operator==(const value_template& rhs) const;
    bool operator!=(const value_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(value_template& other) noexcept;
    value_template& operator=(value_template other);

private:
    std::string name_;
    dogen::annotations::ownership_hierarchy ownership_hierarchy_;
    boost::shared_ptr<dogen::annotations::value> value_;
    dogen::annotations::template_kinds kind_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::value_template& lhs,
    dogen::annotations::value_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
