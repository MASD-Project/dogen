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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_ARCHETYPE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_ARCHETYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/technical_space.hpp"
#include "dogen.logical/types/entities/physical/fixed_relation.hpp"
#include "dogen.logical/types/entities/physical/variable_relation.hpp"

namespace dogen::logical::entities::physical {

/**
 * @brief Represents an archetype within a facet.
 */
class archetype final : public dogen::logical::entities::element {
public:
    archetype(const archetype&) = default;

public:
    archetype();

    virtual ~archetype() noexcept { }

public:
    archetype(archetype&& rhs);

public:
    archetype(
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
        const std::list<dogen::logical::entities::label>& labels,
        const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& enablement_properties,
        const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const std::string& id,
        const dogen::logical::entities::technical_space major_technical_space,
        const std::string& meta_model_name,
        const std::string& backend_name,
        const std::string& facet_name,
        const std::string& part_id,
        const std::string& logical_meta_element_id,
        const std::string& stitch_template_content,
        const boost::optional<dogen::logical::entities::name>& wale_template,
        const std::string& wale_template_content,
        const std::string& rendered_stitch_template,
        const std::string& relation_status,
        const std::list<dogen::logical::entities::physical::variable_relation>& variable_relations,
        const std::list<dogen::logical::entities::physical::fixed_relation>& fixed_relations);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Unique identifier in physical space for this element.
     */
    /**@{*/
    const std::string& id() const;
    std::string& id();
    void id(const std::string& v);
    void id(const std::string&& v);
    /**@}*/

    /**
     * @brief Technical space to which this physical element belongs to.
     */
    /**@{*/
    dogen::logical::entities::technical_space major_technical_space() const;
    void major_technical_space(const dogen::logical::entities::technical_space v);
    /**@}*/

    /**
     * @brief Name of the physical meta-model containing this element.
     */
    /**@{*/
    const std::string& meta_model_name() const;
    std::string& meta_model_name();
    void meta_model_name(const std::string& v);
    void meta_model_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the backend containing this element.
     */
    /**@{*/
    const std::string& backend_name() const;
    std::string& backend_name();
    void backend_name(const std::string& v);
    void backend_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the facet containing this element.
     */
    /**@{*/
    const std::string& facet_name() const;
    std::string& facet_name();
    void facet_name(const std::string& v);
    void facet_name(const std::string&& v);
    /**@}*/

    /**
     * @brief ID for the part this archetype belongs to.
     */
    /**@{*/
    const std::string& part_id() const;
    std::string& part_id();
    void part_id(const std::string& v);
    void part_id(const std::string&& v);
    /**@}*/

    /**
     * @brief ID of the meta-element in the logical model this archetype binds to.
     */
    /**@{*/
    const std::string& logical_meta_element_id() const;
    std::string& logical_meta_element_id();
    void logical_meta_element_id(const std::string& v);
    void logical_meta_element_id(const std::string&& v);
    /**@}*/

    /**
     * @brief Content of the stitch template associated with this archetype, if any exists.
     */
    /**@{*/
    const std::string& stitch_template_content() const;
    std::string& stitch_template_content();
    void stitch_template_content(const std::string& v);
    void stitch_template_content(const std::string&& v);
    /**@}*/

    /**
     * @brief Parsed name of the wale template linked to this archetype, if any.
     */
    /**@{*/
    const boost::optional<dogen::logical::entities::name>& wale_template() const;
    boost::optional<dogen::logical::entities::name>& wale_template();
    void wale_template(const boost::optional<dogen::logical::entities::name>& v);
    void wale_template(const boost::optional<dogen::logical::entities::name>&& v);
    /**@}*/

    /**
     * @brief Content of the wale template associated with this archetype, if any exists.
     */
    /**@{*/
    const std::string& wale_template_content() const;
    std::string& wale_template_content();
    void wale_template_content(const std::string& v);
    void wale_template_content(const std::string&& v);
    /**@}*/

    /**
     * @brief Contains the result of the stitch template after rendering.
     */
    /**@{*/
    const std::string& rendered_stitch_template() const;
    std::string& rendered_stitch_template();
    void rendered_stitch_template(const std::string& v);
    void rendered_stitch_template(const std::string&& v);
    /**@}*/

    /**
     * @brief Status of this archetype with regards to relations.
     */
    /**@{*/
    const std::string& relation_status() const;
    std::string& relation_status();
    void relation_status(const std::string& v);
    void relation_status(const std::string&& v);
    /**@}*/

    /**
     * @brief All archetypes this archetype is related to,  over a variable logical meta-model
     * element.
     */
    /**@{*/
    const std::list<dogen::logical::entities::physical::variable_relation>& variable_relations() const;
    std::list<dogen::logical::entities::physical::variable_relation>& variable_relations();
    void variable_relations(const std::list<dogen::logical::entities::physical::variable_relation>& v);
    void variable_relations(const std::list<dogen::logical::entities::physical::variable_relation>&& v);
    /**@}*/

    /**
     * @brief All archetypes this archetype is related to,  over a fixed logical meta-model
     * element.
     */
    /**@{*/
    const std::list<dogen::logical::entities::physical::fixed_relation>& fixed_relations() const;
    std::list<dogen::logical::entities::physical::fixed_relation>& fixed_relations();
    void fixed_relations(const std::list<dogen::logical::entities::physical::fixed_relation>& v);
    void fixed_relations(const std::list<dogen::logical::entities::physical::fixed_relation>&& v);
    /**@}*/

public:
    bool operator==(const archetype& rhs) const;
    bool operator!=(const archetype& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(archetype& other) noexcept;
    archetype& operator=(archetype other);

private:
    std::string id_;
    dogen::logical::entities::technical_space major_technical_space_;
    std::string meta_model_name_;
    std::string backend_name_;
    std::string facet_name_;
    std::string part_id_;
    std::string logical_meta_element_id_;
    std::string stitch_template_content_;
    boost::optional<dogen::logical::entities::name> wale_template_;
    std::string wale_template_content_;
    std::string rendered_stitch_template_;
    std::string relation_status_;
    std::list<dogen::logical::entities::physical::variable_relation> variable_relations_;
    std::list<dogen::logical::entities::physical::fixed_relation> fixed_relations_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::physical::archetype& lhs,
    dogen::logical::entities::physical::archetype& rhs) {
    lhs.swap(rhs);
}

}

#endif
