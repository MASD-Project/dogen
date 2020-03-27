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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_ELEMENT_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_ELEMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.logical/types/entities/origin_types.hpp"
#include "dogen.logical/types/entities/technical_space.hpp"
#include "dogen.logical/types/entities/static_stereotypes.hpp"
#include "dogen.logical/hash/entities/technical_space_hash.hpp"
#include "dogen.logical/types/entities/artefact_properties.hpp"
#include "dogen.logical/types/entities/element_visitor_fwd.hpp"
#include "dogen.logical/types/entities/enablement_properties.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"
#include "dogen.logical/types/entities/decoration/element_properties.hpp"

namespace dogen::logical::entities {

/**
 * @brief Represents a generic logical construct.
 *
 * An element is anything of interest in a problem domain which needs to be
 * expressed in code generation. It covers both types (objects, enumerations, etc),
 * meta-types (object templates) and non-types (modules and backend specific entities).
 */
class element {
public:
    element(const element&) = default;
    element(element&&) = default;

public:
    element();

    virtual ~element() noexcept = 0;

public:
    element(
        const dogen::logical::entities::name& name,
        const std::string& documentation,
        const dogen::logical::entities::origin_types origin_type,
        const std::string& origin_sha1_hash,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::logical::entities::name& meta_name,
        const dogen::logical::entities::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& archetype_location_properties,
        const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration);

public:
    virtual void accept(const element_visitor& v) const = 0;
    virtual void accept(element_visitor& v) const = 0;
    virtual void accept(const element_visitor& v) = 0;
    virtual void accept(element_visitor& v) = 0;

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::logical::entities::name& name() const;
    dogen::logical::entities::name& name();
    void name(const dogen::logical::entities::name& v);
    void name(const dogen::logical::entities::name&& v);
    /**@}*/

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
     * @brief How was this model element originated.
     */
    /**@{*/
    dogen::logical::entities::origin_types origin_type() const;
    void origin_type(const dogen::logical::entities::origin_types v);
    /**@}*/

    /**
     * @brief SHA1 key of the original injection model.
     */
    /**@{*/
    const std::string& origin_sha1_hash() const;
    std::string& origin_sha1_hash();
    void origin_sha1_hash(const std::string& v);
    void origin_sha1_hash(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the module in which we are contained, if any.
     */
    /**@{*/
    const std::string& contained_by() const;
    std::string& contained_by();
    void contained_by(const std::string& v);
    void contained_by(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, the element is located in the global module.
     */
    /**@{*/
    bool in_global_module() const;
    void in_global_module(const bool v);
    /**@}*/

    /**
     * @brief Stereotypes that are part of the dogen UML profile, and so are well-known to the
     * model.
     */
    /**@{*/
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes() const;
    std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes();
    void static_stereotypes(const std::list<dogen::logical::entities::static_stereotypes>& v);
    void static_stereotypes(const std::list<dogen::logical::entities::static_stereotypes>&& v);
    /**@}*/

    /**
     * @brief Stereotypes that are not part of the masd UML profile. These are user defined.
     */
    /**@{*/
    const std::list<std::string>& dynamic_stereotypes() const;
    std::list<std::string>& dynamic_stereotypes();
    void dynamic_stereotypes(const std::list<std::string>& v);
    void dynamic_stereotypes(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Name of the element in the meta-model that this instance conforms to.
     */
    /**@{*/
    const dogen::logical::entities::name& meta_name() const;
    dogen::logical::entities::name& meta_name();
    void meta_name(const dogen::logical::entities::name& v);
    void meta_name(const dogen::logical::entities::name&& v);
    /**@}*/

    /**
     * @brief Describes the intrinsic nature of the modeling element with regards to technical
     * spaces.
     *
     * If the element can be mapped to a technical space then its intrinsic nature is
     * agnostic. Otherwise, the element belongs to a concrete technical space.
     */
    /**@{*/
    dogen::logical::entities::technical_space intrinsic_technical_space() const;
    void intrinsic_technical_space(const dogen::logical::entities::technical_space v);
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

    const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties() const;
    std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties();
    void artefact_properties(const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& v);
    void artefact_properties(const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>&& v);

    const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& archetype_location_properties() const;
    std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& archetype_location_properties();
    void archetype_location_properties(const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& v);
    void archetype_location_properties(const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>&& v);

    /**
     * @brief If set, decoration to be added to each generated file.
     */
    /**@{*/
    const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration() const;
    std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration();
    void decoration(const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& v);
    void decoration(const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >&& v);
    /**@}*/

protected:
    bool compare(const element& rhs) const;
public:
    virtual bool equals(const element& other) const = 0;

protected:
    void swap(element& other) noexcept;

private:
    dogen::logical::entities::name name_;
    std::string documentation_;
    dogen::logical::entities::origin_types origin_type_;
    std::string origin_sha1_hash_;
    std::string contained_by_;
    bool in_global_module_;
    std::list<dogen::logical::entities::static_stereotypes> static_stereotypes_;
    std::list<std::string> dynamic_stereotypes_;
    dogen::logical::entities::name meta_name_;
    dogen::logical::entities::technical_space intrinsic_technical_space_;
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    std::unordered_map<std::string, dogen::logical::entities::artefact_properties> artefact_properties_;
    std::unordered_map<std::string, dogen::logical::entities::enablement_properties> archetype_location_properties_;
    std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> > decoration_;
};

inline element::~element() noexcept { }

inline bool operator==(const element& lhs, const element& rhs) {
    return lhs.equals(rhs);
}

}

#endif
