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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_ATTRIBUTE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_ATTRIBUTE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/stereotypes.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.logical/types/entities/streaming_properties.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"
#include "dogen.identification/types/entities/logical_name_tree.hpp"
#include "dogen.logical/types/entities/orm/attribute_properties.hpp"

namespace dogen::logical::entities {

/**
 * @brief Represents an attribute in an object.
 */
class attribute final {
public:
    attribute(const attribute&) = default;
    ~attribute() = default;

public:
    attribute();

public:
    attribute(attribute&& rhs);

public:
    attribute(
        const std::string& documentation,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const dogen::identification::entities::logical_name& name,
        const dogen::logical::entities::stereotypes& stereotypes,
        const std::string& unparsed_type,
        const dogen::identification::entities::logical_name_tree& parsed_type,
        const bool is_immutable,
        const bool is_fluent,
        const boost::optional<dogen::logical::entities::orm::attribute_properties>& orm_properties,
        const std::string& member_variable_name,
        const std::string& getter_setter_name,
        const boost::optional<dogen::logical::entities::streaming_properties>& streaming_properties);

public:
    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the technical space in question, e.g. Doxygen for C++, JavaDoc for Java,
     * etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Configuration for this element.
     */
    /**@{*/
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration() const;
    boost::shared_ptr<dogen::variability::entities::configuration>& configuration();
    void configuration(const boost::shared_ptr<dogen::variability::entities::configuration>& v);
    void configuration(const boost::shared_ptr<dogen::variability::entities::configuration>&& v);
    /**@}*/

    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::identification::entities::logical_name& name() const;
    dogen::identification::entities::logical_name& name();
    void name(const dogen::identification::entities::logical_name& v);
    void name(const dogen::identification::entities::logical_name&& v);
    /**@}*/

    /**
     * @brief All stereotypes associated with this element.
     */
    /**@{*/
    const dogen::logical::entities::stereotypes& stereotypes() const;
    dogen::logical::entities::stereotypes& stereotypes();
    void stereotypes(const dogen::logical::entities::stereotypes& v);
    void stereotypes(const dogen::logical::entities::stereotypes&& v);
    /**@}*/

    /**
     * @brief Original type name as it appeared in the source, without any parsing.
     *
     * Name must be in one of the supported notations.
     */
    /**@{*/
    const std::string& unparsed_type() const;
    std::string& unparsed_type();
    void unparsed_type(const std::string& v);
    void unparsed_type(const std::string&& v);
    /**@}*/

    /**
     * @brief Tree of names that represent the type of the attribute, after suitable parsing.
     */
    /**@{*/
    const dogen::identification::entities::logical_name_tree& parsed_type() const;
    dogen::identification::entities::logical_name_tree& parsed_type();
    void parsed_type(const dogen::identification::entities::logical_name_tree& v);
    void parsed_type(const dogen::identification::entities::logical_name_tree&& v);
    /**@}*/

    /**
     * @brief If true, the attribute can only be read but not set.
     */
    /**@{*/
    bool is_immutable() const;
    void is_immutable(const bool v);
    /**@}*/

    /**
     * @brief If true, the attribute's setter will return the object iteself.
     */
    /**@{*/
    bool is_fluent() const;
    void is_fluent(const bool v);
    /**@}*/

    const boost::optional<dogen::logical::entities::orm::attribute_properties>& orm_properties() const;
    boost::optional<dogen::logical::entities::orm::attribute_properties>& orm_properties();
    void orm_properties(const boost::optional<dogen::logical::entities::orm::attribute_properties>& v);
    void orm_properties(const boost::optional<dogen::logical::entities::orm::attribute_properties>&& v);

    /**
     * @brief Representation of the attribute name as a member variable.
     *
     * Note that at present we only support a single style for naming member variables,
     * across all languages. This will have to be revisited in the future.
     */
    /**@{*/
    const std::string& member_variable_name() const;
    std::string& member_variable_name();
    void member_variable_name(const std::string& v);
    void member_variable_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Name to use for getter and setter.
     */
    /**@{*/
    const std::string& getter_setter_name() const;
    std::string& getter_setter_name();
    void getter_setter_name(const std::string& v);
    void getter_setter_name(const std::string&& v);
    /**@}*/

    const boost::optional<dogen::logical::entities::streaming_properties>& streaming_properties() const;
    boost::optional<dogen::logical::entities::streaming_properties>& streaming_properties();
    void streaming_properties(const boost::optional<dogen::logical::entities::streaming_properties>& v);
    void streaming_properties(const boost::optional<dogen::logical::entities::streaming_properties>&& v);

public:
    bool operator==(const attribute& rhs) const;
    bool operator!=(const attribute& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(attribute& other) noexcept;
    attribute& operator=(attribute other);

private:
    std::string documentation_;
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    dogen::identification::entities::logical_name name_;
    dogen::logical::entities::stereotypes stereotypes_;
    std::string unparsed_type_;
    dogen::identification::entities::logical_name_tree parsed_type_;
    bool is_immutable_;
    bool is_fluent_;
    boost::optional<dogen::logical::entities::orm::attribute_properties> orm_properties_;
    std::string member_variable_name_;
    std::string getter_setter_name_;
    boost::optional<dogen::logical::entities::streaming_properties> streaming_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::attribute& lhs,
    dogen::logical::entities::attribute& rhs) {
    lhs.swap(rhs);
}

}

#endif
