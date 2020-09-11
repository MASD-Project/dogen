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
#include "dogen.logical/types/entities/stereotypes.hpp"
#include "dogen.identification/types/entities/label.hpp"
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.logical/types/entities/element_visitor_fwd.hpp"
#include "dogen.logical/types/entities/generability_status.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.identification/types/entities/codec_provenance.hpp"
#include "dogen.identification/types/entities/logical_meta_name.hpp"
#include "dogen.identification/hash/entities/technical_space_hash.hpp"
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
        const dogen::identification::entities::logical_name& name,
        const std::string& documentation,
        const dogen::identification::entities::codec_provenance& provenance,
        const dogen::identification::entities::logical_id& contained_by,
        const bool in_global_module,
        const dogen::logical::entities::stereotypes& stereotypes,
        const dogen::identification::entities::logical_meta_name& meta_name,
        const dogen::identification::entities::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::list<dogen::identification::entities::label>& labels,
        const dogen::logical::entities::generability_status generability_status,
        const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration);

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
    const dogen::identification::entities::logical_name& name() const;
    dogen::identification::entities::logical_name& name();
    void name(const dogen::identification::entities::logical_name& v);
    void name(const dogen::identification::entities::logical_name&& v);
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
     * @brief Details of the provenance of this model element.
     */
    /**@{*/
    const dogen::identification::entities::codec_provenance& provenance() const;
    dogen::identification::entities::codec_provenance& provenance();
    void provenance(const dogen::identification::entities::codec_provenance& v);
    void provenance(const dogen::identification::entities::codec_provenance&& v);
    /**@}*/

    /**
     * @brief ID of the element in which we are contained, if any.
     */
    /**@{*/
    const dogen::identification::entities::logical_id& contained_by() const;
    dogen::identification::entities::logical_id& contained_by();
    void contained_by(const dogen::identification::entities::logical_id& v);
    void contained_by(const dogen::identification::entities::logical_id&& v);
    /**@}*/

    /**
     * @brief If true, the element is located in the global module.
     */
    /**@{*/
    bool in_global_module() const;
    void in_global_module(const bool v);
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
     * @brief Name of the element in the meta-model that this instance conforms to.
     */
    /**@{*/
    const dogen::identification::entities::logical_meta_name& meta_name() const;
    dogen::identification::entities::logical_meta_name& meta_name();
    void meta_name(const dogen::identification::entities::logical_meta_name& v);
    void meta_name(const dogen::identification::entities::logical_meta_name&& v);
    /**@}*/

    /**
     * @brief Describes the intrinsic nature of the modeling element with regards to technical
     * spaces.
     *
     * If the element can be mapped to a technical space then its intrinsic nature is
     * agnostic. Otherwise, the element belongs to a concrete technical space.
     */
    /**@{*/
    dogen::identification::entities::technical_space intrinsic_technical_space() const;
    void intrinsic_technical_space(const dogen::identification::entities::technical_space v);
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
     * @brief All labels associated with this element.
     */
    /**@{*/
    const std::list<dogen::identification::entities::label>& labels() const;
    std::list<dogen::identification::entities::label>& labels();
    void labels(const std::list<dogen::identification::entities::label>& v);
    void labels(const std::list<dogen::identification::entities::label>&& v);
    /**@}*/

    /**
     * @brief The status of this element with regards to generability.
     */
    /**@{*/
    dogen::logical::entities::generability_status generability_status() const;
    void generability_status(const dogen::logical::entities::generability_status v);
    /**@}*/

    /**
     * @brief If set, decoration to be added to each generated file.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration() const;
    std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration();
    void decoration(const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& v);
    void decoration(const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >&& v);
    /**@}*/

protected:
    bool compare(const element& rhs) const;
public:
    virtual bool equals(const element& other) const = 0;

protected:
    void swap(element& other) noexcept;

private:
    dogen::identification::entities::logical_name name_;
    std::string documentation_;
    dogen::identification::entities::codec_provenance provenance_;
    dogen::identification::entities::logical_id contained_by_;
    bool in_global_module_;
    dogen::logical::entities::stereotypes stereotypes_;
    dogen::identification::entities::logical_meta_name meta_name_;
    dogen::identification::entities::technical_space intrinsic_technical_space_;
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    std::list<dogen::identification::entities::label> labels_;
    dogen::logical::entities::generability_status generability_status_;
    std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> > decoration_;
};

inline element::~element() noexcept { }

inline bool operator==(const element& lhs, const element& rhs) {
    return lhs.equals(rhs);
}

}

#endif
