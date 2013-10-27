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
#ifndef DOGEN_SML_TYPES_PROPERTY_HPP
#define DOGEN_SML_TYPES_PROPERTY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <string>
#include "dogen/sml/serialization/property_fwd_ser.hpp"
#include "dogen/sml/types/nested_qname.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents an attribute in an object.
 */
class property final {
public:
    property(const property&) = default;
    ~property() = default;

public:
    property();

public:
    property(property&& rhs);

public:
    property(
        const std::string& documentation,
        const boost::property_tree::ptree& tags,
        const std::string& name,
        const dogen::sml::nested_qname& type,
        const std::string& default_value,
        const bool is_immutable,
        const bool is_fluent);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const property& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, property& v, unsigned int version);

public:
    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the programming language in question, e.g. Doxygen for C++, JavaDoc
     * for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Tags associated with the object, opaque to SML.
     *
     * Tags are in the format key-value pair.
     */
    /**@{*/
    const boost::property_tree::ptree& tags() const;
    boost::property_tree::ptree& tags();
    void tags(const boost::property_tree::ptree& v);
    void tags(const boost::property_tree::ptree&& v);
    /**@}*/

    /**
     * @brief Name of the property.
     *
     * Must only contain characters that can be used for identifiers in the target backend.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Qualified name for the type of the property.
     */
    /**@{*/
    const dogen::sml::nested_qname& type() const;
    dogen::sml::nested_qname& type();
    void type(const dogen::sml::nested_qname& v);
    void type(const dogen::sml::nested_qname&& v);
    /**@}*/

    /**
     * @brief Default value of the property.
     *
     * Only valid if the property has a primitive type. Must be a valid string
     * representation of the primitive type.
     */
    /**@{*/
    const std::string& default_value() const;
    std::string& default_value();
    void default_value(const std::string& v);
    void default_value(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, the property can only be read but not set.
     */
    /**@{*/
    bool is_immutable() const;
    void is_immutable(const bool v);
    /**@}*/

    /**
     * @brief If true, the property's setter will return the object iteself.
     */
    /**@{*/
    bool is_fluent() const;
    void is_fluent(const bool v);
    /**@}*/

public:
    bool operator==(const property& rhs) const;
    bool operator!=(const property& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(property& other) noexcept;
    property& operator=(property other);

private:
    std::string documentation_;
    boost::property_tree::ptree tags_;
    std::string name_;
    dogen::sml::nested_qname type_;
    std::string default_value_;
    bool is_immutable_;
    bool is_fluent_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::property& lhs,
    dogen::sml::property& rhs) {
    lhs.swap(rhs);
}

}

#endif
