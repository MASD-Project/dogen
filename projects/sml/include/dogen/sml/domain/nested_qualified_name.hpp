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
#ifndef DOGEN_SML_DOMAIN_NESTED_QUALIFIED_NAME_HPP
#define DOGEN_SML_DOMAIN_NESTED_QUALIFIED_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen/sml/domain/qualified_name.hpp"

namespace dogen {
namespace sml {

class nested_qualified_name_serializer;

class nested_qualified_name {
public:
    nested_qualified_name() = default;
    nested_qualified_name(const nested_qualified_name&) = default;
    ~nested_qualified_name() = default;
    nested_qualified_name(nested_qualified_name&&) = default;
    nested_qualified_name& operator=(const nested_qualified_name&) = default;

private:
    friend class nested_qualified_name_serializer;

public:
    nested_qualified_name(const qualified_name& type,
        std::list<nested_qualified_name> children)
        : type_(type), children_(children) { }

public:
    /**
     * @brief Top-level, containing type.
     */
    qualified_name type() const { return(type_); }
    void type(const qualified_name& v) { type_ = v; }

    /**
     * @brief Child types.
     */
    std::list<nested_qualified_name> children() const { return(children_); }
    void childred(const std::list<nested_qualified_name>& v) { children_ = v; }

public:
    void to_stream(std::ostream& stream) const;

public:
    bool operator==(const nested_qualified_name& rhs) const;

    bool operator!=(const nested_qualified_name& rhs) const {
        return(!this->operator==(rhs));
    }

private:
    qualified_name type_;
    std::list<nested_qualified_name> children_;
};

} }

#endif
