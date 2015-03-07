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
#ifndef DOGEN_SML_TYPES_OPERATION_HPP
#define DOGEN_SML_TYPES_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include <list>
#include <string>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/sml/serialization/operation_fwd_ser.hpp"
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/sml/types/parameter.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents a method in an object.
 */
class operation final {
public:
    operation() = default;
    operation(const operation&) = default;
    ~operation() = default;

public:
    operation(operation&& rhs);

public:
    operation(
        const std::string& documentation,
        const dogen::dynamic::schema::object& extensions,
        const std::string& name,
        const std::list<dogen::sml::parameter>& parameters,
        const boost::optional<dogen::sml::nested_qname>& type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const operation& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, operation& v, unsigned int version);

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
     * @brief Dynamic extensions for this element.
     */
    /**@{*/
    const dogen::dynamic::schema::object& extensions() const;
    dogen::dynamic::schema::object& extensions();
    void extensions(const dogen::dynamic::schema::object& v);
    void extensions(const dogen::dynamic::schema::object&& v);
    /**@}*/

    /**
     * @brief Name of the operation.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief List of parameters that can be passed in to the operation.
     */
    /**@{*/
    const std::list<dogen::sml::parameter>& parameters() const;
    std::list<dogen::sml::parameter>& parameters();
    void parameters(const std::list<dogen::sml::parameter>& v);
    void parameters(const std::list<dogen::sml::parameter>&& v);
    /**@}*/

    /**
     * @brief Result of the operation, if any.
     */
    /**@{*/
    const boost::optional<dogen::sml::nested_qname>& type() const;
    boost::optional<dogen::sml::nested_qname>& type();
    void type(const boost::optional<dogen::sml::nested_qname>& v);
    void type(const boost::optional<dogen::sml::nested_qname>&& v);
    /**@}*/

public:
    bool operator==(const operation& rhs) const;
    bool operator!=(const operation& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(operation& other) noexcept;
    operation& operator=(operation other);

private:
    std::string documentation_;
    dogen::dynamic::schema::object extensions_;
    std::string name_;
    std::list<dogen::sml::parameter> parameters_;
    boost::optional<dogen::sml::nested_qname> type_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::operation& lhs,
    dogen::sml::operation& rhs) {
    lhs.swap(rhs);
}

}

#endif
