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
#ifndef DOGEN_DIA_TYPES_OBJECT_HPP
#define DOGEN_DIA_TYPES_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.dia/types/attribute.hpp"
#include "dogen.dia/types/child_node.hpp"
#include "dogen.dia/types/connection.hpp"

namespace dogen::dia {

/**
 * @brief Represents a Dia object.
 */
class object final {
public:
    object(const object&) = default;
    ~object() = default;

public:
    object();

public:
    object(object&& rhs);

public:
    object(
        const std::string& type,
        const int version,
        const std::string& id,
        const std::vector<dogen::dia::connection>& connections,
        const boost::optional<dogen::dia::child_node>& child_node,
        const std::vector<dogen::dia::attribute>& attributes);

public:
    /**
     * @brief Type of the object.
     */
    /**@{*/
    const std::string& type() const;
    std::string& type();
    void type(const std::string& v);
    void type(const std::string&& v);
    /**@}*/

    /**
     * @brief Version of the object.
     */
    /**@{*/
    int version() const;
    void version(const int v);
    /**@}*/

    /**
     * @brief Unique identifier for the object in this diagram.
     */
    /**@{*/
    const std::string& id() const;
    std::string& id();
    void id(const std::string& v);
    void id(const std::string&& v);
    /**@}*/

    /**
     * @brief Connection details for this object.
     */
    /**@{*/
    const std::vector<dogen::dia::connection>& connections() const;
    std::vector<dogen::dia::connection>& connections();
    void connections(const std::vector<dogen::dia::connection>& v);
    void connections(const std::vector<dogen::dia::connection>&& v);
    /**@}*/

    /**
     * @brief Parenting information for this object.
     */
    /**@{*/
    const boost::optional<dogen::dia::child_node>& child_node() const;
    boost::optional<dogen::dia::child_node>& child_node();
    void child_node(const boost::optional<dogen::dia::child_node>& v);
    void child_node(const boost::optional<dogen::dia::child_node>&& v);
    /**@}*/

    /**
     * @brief All attributes associated with the object.
     */
    /**@{*/
    const std::vector<dogen::dia::attribute>& attributes() const;
    std::vector<dogen::dia::attribute>& attributes();
    void attributes(const std::vector<dogen::dia::attribute>& v);
    void attributes(const std::vector<dogen::dia::attribute>&& v);
    /**@}*/

public:
    bool operator==(const object& rhs) const;
    bool operator!=(const object& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(object& other) noexcept;
    object& operator=(object other);

private:
    std::string type_;
    int version_;
    std::string id_;
    std::vector<dogen::dia::connection> connections_;
    boost::optional<dogen::dia::child_node> child_node_;
    std::vector<dogen::dia::attribute> attributes_;
};

}

namespace std {

template<>
inline void swap(
    dogen::dia::object& lhs,
    dogen::dia::object& rhs) {
    lhs.swap(rhs);
}

}

#endif
