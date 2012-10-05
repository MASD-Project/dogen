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
#ifndef DOGEN_DIA_DOMAIN_OBJECT_HPP
#define DOGEN_DIA_DOMAIN_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <string>
#include <utility>
#include "boost/optional.hpp"
#include "dogen/dia/domain/object_types.hpp"
#include "dogen/dia/domain/attribute.hpp"
#include "dogen/dia/domain/child_node.hpp"

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class object_serializer; } }

/**
 * @brief Represents a Dia object
 */
class object {
public:
    object(const object&) = default;
    ~object() = default;
    object& operator=(const object&) = default;

private:
    friend class dogen::dia::serialization::detail::object_serializer;

public:
    object() : version_() { }
    object(std::string type, int version, std::string id,
        std::vector<attribute> attributes,
        boost::optional<dogen::dia::child_node> child_node)
        : type_(type), version_(version), id_(id), attributes_(attributes),
          child_node_(child_node) { }

    object(object&& other) : type_(std::move(other.type_)),
                             version_(std::move(other.version_)),
                             id_(std::move(other.id_)),
                             attributes_(std::move(other.attributes_)),
                             child_node_(std::move(other.child_node_)) { }

public:
    /**
     * @brief Type of the object.
     */
    /**@{*/
    std::string type() const { return(type_); }
    void type(std::string value) { type_ = value; }
    /**@}*/

    /**
     * @brief Version of the object.
     */
    /**@{*/
    int version() const { return(version_); }
    void version(int value) { version_ = value; }
    /**@}*/

    /**
     * @brief Unique identifier for the object in this diagram.
     */
    /**@{*/
    std::string id() const { return(id_); }
    void id(std::string value) { id_ = value; }
    /**@}*/

    /**
     * @brief All attributes associated with the diagram data.
     */
    /**@{*/
    std::vector<attribute> attributes() const { return(attributes_); }
    void attributes(std::vector<attribute> value) {
        attributes_ = value;
    }
    /**@}*/

    /**
     * @brief Parenting information for this object.
     */
    /**@{*/
    boost::optional<dogen::dia::child_node> child_node() const {
        return(child_node_);
    }

    void child_node(boost::optional<dogen::dia::child_node> value) {
        child_node_ = value;
    }
    /**@}*/

public:
    bool operator==(dogen::dia::object value) const {
        return
            type_ == value.type() &&
            version_ == value.version() &&
            id_  == value.id() &&
            attributes_ == value.attributes() &&
            child_node_  == value.child_node();
    }

    bool operator!=(const dogen::dia::object& value) const {
        return(!this->operator==(value));
    }

private:
    std::string type_;
    int version_;
    std::string id_;
    std::vector<attribute> attributes_;
    boost::optional<dogen::dia::child_node> child_node_;
};

} }

#endif
