/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
     * if not specified
     */
    inline property(std::string name, dogen::sml::qualified_name type_name,
        std::string default_value)
        : name_(name), type_name_(type_name ), default_value_(default_value){ }

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
};

} }

#endif
