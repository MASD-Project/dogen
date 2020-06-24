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
#ifndef DOGEN_INJECTION_TYPES_ENTITIES_ELEMENT_HPP
#define DOGEN_INJECTION_TYPES_ENTITIES_ELEMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.injection/types/entities/attribute.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"

namespace dogen::injection::entities {

/**
 * @brief Represents an element from an external model.
 */
class element final {
public:
    element(const element&) = default;
    element(element&&) = default;
    ~element() = default;

public:
    element();

public:
    element(
        const std::list<std::pair<std::string, std::string> >& tagged_values,
        const std::list<std::pair<std::string, std::string> >& tagged_values_overrides,
        const std::list<std::string>& stereotypes,
        const std::string& documentation,
        const std::string& name,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::string& origin_sha1_hash,
        const std::string& origin_element_id,
        const std::string& origin_containing_element_id,
        const std::list<std::string>& parents,
        const std::list<dogen::injection::entities::attribute>& attributes,
        const std::string& fallback_element_type,
        const bool can_be_primitive_underlier,
        const bool in_global_module,
        const bool can_be_enumeration_underlier,
        const bool is_default_enumeration_type,
        const bool is_associative_container,
        const bool is_floating_point);

public:
    const std::list<std::pair<std::string, std::string> >& tagged_values() const;
    std::list<std::pair<std::string, std::string> >& tagged_values();
    void tagged_values(const std::list<std::pair<std::string, std::string> >& v);
    void tagged_values(const std::list<std::pair<std::string, std::string> >&& v);

    /**
     * @brief Meta-data sourced externally that can be used to override meta-data in model.
     */
    /**@{*/
    const std::list<std::pair<std::string, std::string> >& tagged_values_overrides() const;
    std::list<std::pair<std::string, std::string> >& tagged_values_overrides();
    void tagged_values_overrides(const std::list<std::pair<std::string, std::string> >& v);
    void tagged_values_overrides(const std::list<std::pair<std::string, std::string> >&& v);
    /**@}*/

    const std::list<std::string>& stereotypes() const;
    std::list<std::string>& stereotypes();
    void stereotypes(const std::list<std::string>& v);
    void stereotypes(const std::list<std::string>&& v);

    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the technical space in question, e.g. Doxygen for C++, JavaDoc for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

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
     * @brief SHA1 hash of the original model that contained the element.
     */
    /**@{*/
    const std::string& origin_sha1_hash() const;
    std::string& origin_sha1_hash();
    void origin_sha1_hash(const std::string& v);
    void origin_sha1_hash(const std::string&& v);
    /**@}*/

    /**
     * @brief Identifier within the origin model for the modeling element.
     */
    /**@{*/
    const std::string& origin_element_id() const;
    std::string& origin_element_id();
    void origin_element_id(const std::string& v);
    void origin_element_id(const std::string&& v);
    /**@}*/

    /**
     * @brief Unique identifier for an element containing this element, if any.
     */
    /**@{*/
    const std::string& origin_containing_element_id() const;
    std::string& origin_containing_element_id();
    void origin_containing_element_id(const std::string& v);
    void origin_containing_element_id(const std::string&& v);
    /**@}*/

    const std::list<std::string>& parents() const;
    std::list<std::string>& parents();
    void parents(const std::list<std::string>& v);
    void parents(const std::list<std::string>&& v);

    const std::list<dogen::injection::entities::attribute>& attributes() const;
    std::list<dogen::injection::entities::attribute>& attributes();
    void attributes(const std::list<dogen::injection::entities::attribute>& v);
    void attributes(const std::list<dogen::injection::entities::attribute>&& v);

    /**
     * @brief Stereotype conveying element type, to be used when none is provided with the
     * main stereotypes.
     */
    /**@{*/
    const std::string& fallback_element_type() const;
    std::string& fallback_element_type();
    void fallback_element_type(const std::string& v);
    void fallback_element_type(const std::string&& v);
    /**@}*/

    bool can_be_primitive_underlier() const;
    void can_be_primitive_underlier(const bool v);

    bool in_global_module() const;
    void in_global_module(const bool v);

    bool can_be_enumeration_underlier() const;
    void can_be_enumeration_underlier(const bool v);

    bool is_default_enumeration_type() const;
    void is_default_enumeration_type(const bool v);

    bool is_associative_container() const;
    void is_associative_container(const bool v);

    bool is_floating_point() const;
    void is_floating_point(const bool v);

public:
    bool operator==(const element& rhs) const;
    bool operator!=(const element& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element& other) noexcept;
    element& operator=(element other);

private:
    std::list<std::pair<std::string, std::string> > tagged_values_;
    std::list<std::pair<std::string, std::string> > tagged_values_overrides_;
    std::list<std::string> stereotypes_;
    std::string documentation_;
    std::string name_;
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    std::string origin_sha1_hash_;
    std::string origin_element_id_;
    std::string origin_containing_element_id_;
    std::list<std::string> parents_;
    std::list<dogen::injection::entities::attribute> attributes_;
    std::string fallback_element_type_;
    bool can_be_primitive_underlier_;
    bool in_global_module_;
    bool can_be_enumeration_underlier_;
    bool is_default_enumeration_type_;
    bool is_associative_container_;
    bool is_floating_point_;
};

}

namespace std {

template<>
inline void swap(
    dogen::injection::entities::element& lhs,
    dogen::injection::entities::element& rhs) {
    lhs.swap(rhs);
}

}

#endif
