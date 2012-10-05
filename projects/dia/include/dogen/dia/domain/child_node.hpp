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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_CHILD_NODE_HPP
#define DOGEN_DIA_DOMAIN_CHILD_NODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class child_node_serializer; } }

/**
 * @brief Represents a child_node in a diagram.
 */
class child_node {
public:
    child_node() = default;
    child_node(const child_node&) = default;
    ~child_node() = default;
    child_node(child_node&&) = default;
    child_node& operator=(const child_node&) = default;

private:
    friend class dogen::dia::serialization::detail::child_node_serializer;

public:
    explicit child_node(std::string parent) : parent_(parent) { }

public:
    /**
     * @brief
     */
    /**@{*/
    std::string parent() const { return(parent_); }
    void parent(std::string parent) { parent_ = parent; }
    /**@}*/

public:
    bool operator==(const dogen::dia::child_node& value) const {
        return(parent_ == value.parent());
    }

    bool operator!=(const dogen::dia::child_node& value) const {
        return(!this->operator==(value));
    }

private:
    std::string parent_;
};

} }

#endif
