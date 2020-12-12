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
#ifndef DOGEN_DIA_TYPES_ENTITIES_OBJECT_HPP
#define DOGEN_DIA_TYPES_ENTITIES_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.dia/types/entities/attribute.hpp"
#include "dogen.dia/types/entities/child_node.hpp"
#include "dogen.dia/types/entities/connection.hpp"

namespace dogen::dia::entities {

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
        const std::string& id,
        const std::string& type,
        const int version,
        const std::vector<dogen::dia::entities::connection>& connections,
        const boost::optional<dogen::dia::entities::child_node>& child_node,
        const std::vector<dogen::dia::entities::attribute>& attributes);

public:
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
     * @brief Connection details for this object.
     */
    /**@{*/
    const std::vector<dogen::dia::entities::connection>& connections() const;
    std::vector<dogen::dia::entities::connection>& connections();
    void connections(const std::vector<dogen::dia::entities::connection>& v);
    void connections(const std::vector<dogen::dia::entities::connection>&& v);
    /**@}*/

    const boost::optional<dogen::dia::entities::child_node>& child_node() const;
    boost::optional<dogen::dia::entities::child_node>& child_node();
    void child_node(const boost::optional<dogen::dia::entities::child_node>& v);
    void child_node(const boost::optional<dogen::dia::entities::child_node>&& v);

    /**
     * @brief All attributes associated with the object.
     */
    /**@{*/
    const std::vector<dogen::dia::entities::attribute>& attributes() const;
    std::vector<dogen::dia::entities::attribute>& attributes();
    void attributes(const std::vector<dogen::dia::entities::attribute>& v);
    void attributes(const std::vector<dogen::dia::entities::attribute>&& v);
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
    std::string id_;
    std::string type_;
    int version_;
    std::vector<dogen::dia::entities::connection> connections_;
    boost::optional<dogen::dia::entities::child_node> child_node_;
    std::vector<dogen::dia::entities::attribute> attributes_;
};

}

namespace std {

template<>
inline void swap(
    dogen::dia::entities::object& lhs,
    dogen::dia::entities::object& rhs) {
    lhs.swap(rhs);
}

}

#endif
