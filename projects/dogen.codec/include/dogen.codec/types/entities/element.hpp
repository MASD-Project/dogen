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
#ifndef DOGEN_CODEC_TYPES_ENTITIES_ELEMENT_HPP
#define DOGEN_CODEC_TYPES_ENTITIES_ELEMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.codec/types/entities/comment.hpp"
#include "dogen.codec/types/entities/attribute.hpp"
#include "dogen.identification/types/entities/name.hpp"
#include "dogen.identification/types/entities/codec_id.hpp"
#include "dogen.identification/types/entities/stereotype.hpp"
#include "dogen.identification/types/entities/tagged_value.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"
#include "dogen.identification/types/entities/codec_provenance.hpp"

namespace dogen::codec::entities {

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
        const std::list<dogen::identification::entities::tagged_value>& tagged_values,
        const std::list<dogen::identification::entities::stereotype>& stereotypes,
        const std::string& documentation,
        const dogen::identification::entities::name& name,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const dogen::identification::entities::codec_provenance& provenance,
        const std::list<dogen::identification::entities::tagged_value>& tagged_values_overrides,
        const dogen::codec::entities::comment& comment,
        const std::list<std::string>& parents,
        const std::list<dogen::codec::entities::attribute>& attributes,
        const std::string& fallback_element_type,
        const bool can_be_primitive_underlier,
        const bool in_global_module,
        const bool can_be_enumeration_underlier,
        const bool is_default_enumeration_type,
        const bool is_associative_container,
        const bool is_floating_point,
        const dogen::identification::entities::codec_id& containing_element_id);

public:
    const std::list<dogen::identification::entities::tagged_value>& tagged_values() const;
    std::list<dogen::identification::entities::tagged_value>& tagged_values();
    void tagged_values(const std::list<dogen::identification::entities::tagged_value>& v);
    void tagged_values(const std::list<dogen::identification::entities::tagged_value>&& v);

    const std::list<dogen::identification::entities::stereotype>& stereotypes() const;
    std::list<dogen::identification::entities::stereotype>& stereotypes();
    void stereotypes(const std::list<dogen::identification::entities::stereotype>& v);
    void stereotypes(const std::list<dogen::identification::entities::stereotype>&& v);

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

    /**
     * @brief Name of the codec element.
     */
    /**@{*/
    const dogen::identification::entities::name& name() const;
    dogen::identification::entities::name& name();
    void name(const dogen::identification::entities::name& v);
    void name(const dogen::identification::entities::name&& v);
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
     * @brief Provenance details of this codec element.
     */
    /**@{*/
    const dogen::identification::entities::codec_provenance& provenance() const;
    dogen::identification::entities::codec_provenance& provenance();
    void provenance(const dogen::identification::entities::codec_provenance& v);
    void provenance(const dogen::identification::entities::codec_provenance&& v);
    /**@}*/

    /**
     * @brief Meta-data sourced externally that can be used to override meta-data in model.
     */
    /**@{*/
    const std::list<dogen::identification::entities::tagged_value>& tagged_values_overrides() const;
    std::list<dogen::identification::entities::tagged_value>& tagged_values_overrides();
    void tagged_values_overrides(const std::list<dogen::identification::entities::tagged_value>& v);
    void tagged_values_overrides(const std::list<dogen::identification::entities::tagged_value>&& v);
    /**@}*/

    /**
     * @brief Properties associated with the codec comment.
     */
    /**@{*/
    const dogen::codec::entities::comment& comment() const;
    dogen::codec::entities::comment& comment();
    void comment(const dogen::codec::entities::comment& v);
    void comment(const dogen::codec::entities::comment&& v);
    /**@}*/

    const std::list<std::string>& parents() const;
    std::list<std::string>& parents();
    void parents(const std::list<std::string>& v);
    void parents(const std::list<std::string>&& v);

    const std::list<dogen::codec::entities::attribute>& attributes() const;
    std::list<dogen::codec::entities::attribute>& attributes();
    void attributes(const std::list<dogen::codec::entities::attribute>& v);
    void attributes(const std::list<dogen::codec::entities::attribute>&& v);

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

    /**
     * @brief ID of the containing element, if any.
     */
    /**@{*/
    const dogen::identification::entities::codec_id& containing_element_id() const;
    dogen::identification::entities::codec_id& containing_element_id();
    void containing_element_id(const dogen::identification::entities::codec_id& v);
    void containing_element_id(const dogen::identification::entities::codec_id&& v);
    /**@}*/

public:
    bool operator==(const element& rhs) const;
    bool operator!=(const element& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element& other) noexcept;
    element& operator=(element other);

private:
    std::list<dogen::identification::entities::tagged_value> tagged_values_;
    std::list<dogen::identification::entities::stereotype> stereotypes_;
    std::string documentation_;
    dogen::identification::entities::name name_;
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    dogen::identification::entities::codec_provenance provenance_;
    std::list<dogen::identification::entities::tagged_value> tagged_values_overrides_;
    dogen::codec::entities::comment comment_;
    std::list<std::string> parents_;
    std::list<dogen::codec::entities::attribute> attributes_;
    std::string fallback_element_type_;
    bool can_be_primitive_underlier_;
    bool in_global_module_;
    bool can_be_enumeration_underlier_;
    bool is_default_enumeration_type_;
    bool is_associative_container_;
    bool is_floating_point_;
    dogen::identification::entities::codec_id containing_element_id_;
};

}

namespace std {

template<>
inline void swap(
    dogen::codec::entities::element& lhs,
    dogen::codec::entities::element& rhs) {
    lhs.swap(rhs);
}

}

#endif
