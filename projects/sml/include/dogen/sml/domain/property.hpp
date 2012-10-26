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
#ifndef DOGEN_SML_DOMAIN_PROPERTY_HPP
#define DOGEN_SML_DOMAIN_PROPERTY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include "dogen/sml/domain/qualified_name.hpp"

namespace dogen {
namespace sml {

class property_serializer;

/**
 * @brief Represents a property.
 */
class property {
public:
    property() = default;
    property(const property&) = default;
    ~property() = default;
    property(property&&) = default;
    property& operator=(const property&) = default;

private:
    friend class property_serializer;

public:
    /**
     * @brief Initialises the property.
     *
     * @param name of the property
     * @param type_name the type name associated with the property
     * @param default_value the default value the property should take
     * @param documentation the documentation for the property
     * if not specified
     */
    inline property(const std::string& name,
        const dogen::sml::qualified_name& type_name,
        const std::string& default_value,
        const std::string& documentation)
        : name_(name), type_name_(type_name ), default_value_(default_value),
          documentation_(documentation) { }

public:
    /**
     * @brief Name of the property.
     */
    std::string name() const { return name_; }
    void name(std::string name) { name_ = name; }

    /**
     * @brief Type name for the property.
     */
    dogen::sml::qualified_name type_name() const { return type_name_; }
    void type_name(dogen::sml::qualified_name type_name) {
        type_name_ = type_name;
    }

    /**
     * @brief Default value of the property.
     */
    std::string default_value() const { return default_value_; }
    void default_value(std::string default_value) {
        default_value_ = default_value;
    }

    /**
     * @brief Doxygen documentation for the type.
     */
    /**@{*/
    std::string documentation() const { return documentation_; }
    void documentation(const std::string& value) { documentation_ = value; }
    /**@}*/

public:
    bool operator==(const property& rhs) const;

    bool operator!=(const property& rhs) const {
        return(!this->operator==(rhs));
    }

public:
    void to_stream(std::ostream& stream) const;

private:
    std::string name_;
    dogen::sml::qualified_name type_name_;
    std::string default_value_;
    std::string documentation_;
};

} }

#endif
