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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_PROPERTY_INFO_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_PROPERTY_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/cpp/types/settings/opaque_settings_fwd.hpp"
#include "dogen/cpp/types/formattables/nested_type_info.hpp"
#include "dogen/cpp/serialization/formattables/property_info_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Represents a pair of getter and setter methods.
 */
class property_info final {
public:
    property_info(const property_info&) = default;
    property_info(property_info&&) = default;
    ~property_info() = default;

public:
    property_info();

public:
    property_info(
        const std::string& name,
        const std::string& qualified_name,
        const std::string& documentation,
        const dogen::cpp::formattables::nested_type_info& type,
        const std::list<std::pair<std::string, std::string> >& opaque_parameters,
        const bool is_immutable,
        const bool is_fluent,
        const boost::shared_ptr<dogen::cpp::settings::opaque_settings>& opaque_settings);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const property_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, property_info& v, unsigned int version);

public:
    /**
     * @brief Name of the entity.
     *
     * Must be valid according to the rules for C++ names.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Fully qualified name of the entity.
     */
    /**@{*/
    const std::string& qualified_name() const;
    std::string& qualified_name();
    void qualified_name(const std::string& v);
    void qualified_name(const std::string&& v);
    /**@}*/

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
     * @brief Type of the property.
     */
    /**@{*/
    const dogen::cpp::formattables::nested_type_info& type() const;
    dogen::cpp::formattables::nested_type_info& type();
    void type(const dogen::cpp::formattables::nested_type_info& v);
    void type(const dogen::cpp::formattables::nested_type_info&& v);
    /**@}*/

    const std::list<std::pair<std::string, std::string> >& opaque_parameters() const;
    std::list<std::pair<std::string, std::string> >& opaque_parameters();
    void opaque_parameters(const std::list<std::pair<std::string, std::string> >& v);
    void opaque_parameters(const std::list<std::pair<std::string, std::string> >&& v);

    /**
     * @brief If true, the setter is not available for this property.
     */
    /**@{*/
    bool is_immutable() const;
    void is_immutable(const bool v);
    /**@}*/

    /**
     * @brief If true, the setter returns the instance of the object.
     */
    /**@{*/
    bool is_fluent() const;
    void is_fluent(const bool v);
    /**@}*/

    const boost::shared_ptr<dogen::cpp::settings::opaque_settings>& opaque_settings() const;
    boost::shared_ptr<dogen::cpp::settings::opaque_settings>& opaque_settings();
    void opaque_settings(const boost::shared_ptr<dogen::cpp::settings::opaque_settings>& v);
    void opaque_settings(const boost::shared_ptr<dogen::cpp::settings::opaque_settings>&& v);

public:
    bool operator==(const property_info& rhs) const;
    bool operator!=(const property_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(property_info& other) noexcept;
    property_info& operator=(property_info other);

private:
    std::string name_;
    std::string qualified_name_;
    std::string documentation_;
    dogen::cpp::formattables::nested_type_info type_;
    std::list<std::pair<std::string, std::string> > opaque_parameters_;
    bool is_immutable_;
    bool is_fluent_;
    boost::shared_ptr<dogen::cpp::settings::opaque_settings> opaque_settings_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::property_info& lhs,
    dogen::cpp::formattables::property_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
