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
#include <string>
#include <utility>
#include <vector>
#include "dogen/sml/serialization/property_fwd_ser.hpp"
#include "dogen/sml/types/nested_qname.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Memberof a pod that provides a mechanism to read and write values of a type.
 */
class property final {
public:
    property(const property&) = default;
    property(property&&) = default;
    ~property() = default;

public:
    property();

public:
    property(
        const std::string& name,
        const dogen::sml::nested_qname& type_name,
        const std::string& default_value,
        const std::string& documentation,
        const bool is_identity_attribute,
        const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const property& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, property& v, unsigned int version);

public:
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
     * @brief Type name for the property.
     */
    /**@{*/
    const dogen::sml::nested_qname& type_name() const;
    dogen::sml::nested_qname& type_name();
    void type_name(const dogen::sml::nested_qname& v);
    void type_name(const dogen::sml::nested_qname&& v);
    /**@}*/

    /**
     * @brief Default value of the property.
     */
    /**@{*/
    const std::string& default_value() const;
    std::string& default_value();
    void default_value(const std::string& v);
    void default_value(const std::string&& v);
    /**@}*/

    /**
     * @brief Doxygen documentation for the type.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, the attribute is part of the object's identity attribute set.
     */
    /**@{*/
    bool is_identity_attribute() const;
    void is_identity_attribute(const bool v);
    /**@}*/

    /**
     * @brief Parameters associated with the property which are opaque to SML.
     */
    /**@{*/
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters() const;
    std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters();
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v);
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v);
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
    std::string name_;
    dogen::sml::nested_qname type_name_;
    std::string default_value_;
    std::string documentation_;
    bool is_identity_attribute_;
    std::vector<std::pair<std::string, std::string> > implementation_specific_parameters_;
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
