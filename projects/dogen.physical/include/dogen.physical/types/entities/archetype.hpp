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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_ARCHETYPE_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_ARCHETYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen.physical/types/entities/label.hpp"
#include "dogen.physical/types/entities/meta_name.hpp"
#include "dogen.physical/types/entities/fixed_relation.hpp"
#include "dogen.physical/types/entities/relation_status.hpp"
#include "dogen.physical/types/entities/variable_relation.hpp"

namespace dogen::physical::entities {

/**
 * @brief Represents a meta-artefact.
 */
class archetype final {
public:
    archetype(const archetype&) = default;
    archetype(archetype&&) = default;
    ~archetype() = default;

public:
    archetype();

public:
    archetype(
        const std::string& description,
        const dogen::physical::entities::meta_name& meta_name,
        const std::list<dogen::physical::entities::label>& labels,
        const std::string& default_postfix,
        const std::string& override_postfix,
        const std::list<std::string>& depends,
        const std::list<std::string>& generates,
        const std::string& generated_by,
        const std::string& archetype_kind_id,
        const std::string& logical_meta_element_id,
        const std::string& part,
        const dogen::physical::entities::relation_status relation_status,
        const std::list<dogen::physical::entities::variable_relation>& variable_relations,
        const std::list<dogen::physical::entities::fixed_relation>& fixed_relations);

public:
    /**
     * @brief Human readable description of the entity.
     */
    /**@{*/
    const std::string& description() const;
    std::string& description();
    void description(const std::string& v);
    void description(const std::string&& v);
    /**@}*/

    /**
     * @brief Meta-name for this meta-element.
     */
    /**@{*/
    const dogen::physical::entities::meta_name& meta_name() const;
    dogen::physical::entities::meta_name& meta_name();
    void meta_name(const dogen::physical::entities::meta_name& v);
    void meta_name(const dogen::physical::entities::meta_name&& v);
    /**@}*/

    /**
     * @brief All labels associated with this element.
     */
    /**@{*/
    const std::list<dogen::physical::entities::label>& labels() const;
    std::list<dogen::physical::entities::label>& labels();
    void labels(const std::list<dogen::physical::entities::label>& v);
    void labels(const std::list<dogen::physical::entities::label>&& v);
    /**@}*/

    /**
     * @brief Default postfix for the element.
     */
    /**@{*/
    const std::string& default_postfix() const;
    std::string& default_postfix();
    void default_postfix(const std::string& v);
    void default_postfix(const std::string&& v);
    /**@}*/

    /**
     * @brief Overridden postfix, if any.
     */
    /**@{*/
    const std::string& override_postfix() const;
    std::string& override_postfix();
    void override_postfix(const std::string& v);
    void override_postfix(const std::string&& v);
    /**@}*/

    /**
     * @brief List of meta-elements this meta-element depends upon, if any.
     */
    /**@{*/
    const std::list<std::string>& depends() const;
    std::list<std::string>& depends();
    void depends(const std::list<std::string>& v);
    void depends(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief List of meta-elements this meta-element is used to generate, if any.
     */
    /**@{*/
    const std::list<std::string>& generates() const;
    std::list<std::string>& generates();
    void generates(const std::list<std::string>& v);
    void generates(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Meta-element used to generate this meta-element, if any.
     */
    /**@{*/
    const std::string& generated_by() const;
    std::string& generated_by();
    void generated_by(const std::string& v);
    void generated_by(const std::string&& v);
    /**@}*/

    /**
     * @brief ID for the archetype kind that this archetype is an instance of.
     */
    /**@{*/
    const std::string& archetype_kind_id() const;
    std::string& archetype_kind_id();
    void archetype_kind_id(const std::string& v);
    void archetype_kind_id(const std::string&& v);
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
     * @brief Part in which we are located.
     */
    /**@{*/
    const std::string& part() const;
    std::string& part();
    void part(const std::string& v);
    void part(const std::string&& v);
    /**@}*/

    /**
     * @brief Status of this archetype with regards to being related to archetypes.
     */
    /**@{*/
    dogen::physical::entities::relation_status relation_status() const;
    void relation_status(const dogen::physical::entities::relation_status v);
    /**@}*/

    /**
     * @brief All archetypes this archetype is related to,  over a variable logical meta-model
     * element.
     */
    /**@{*/
    const std::list<dogen::physical::entities::variable_relation>& variable_relations() const;
    std::list<dogen::physical::entities::variable_relation>& variable_relations();
    void variable_relations(const std::list<dogen::physical::entities::variable_relation>& v);
    void variable_relations(const std::list<dogen::physical::entities::variable_relation>&& v);
    /**@}*/

    /**
     * @brief All archetypes this archetype is related to,  over a fixed logical meta-model
     * element.
     */
    /**@{*/
    const std::list<dogen::physical::entities::fixed_relation>& fixed_relations() const;
    std::list<dogen::physical::entities::fixed_relation>& fixed_relations();
    void fixed_relations(const std::list<dogen::physical::entities::fixed_relation>& v);
    void fixed_relations(const std::list<dogen::physical::entities::fixed_relation>&& v);
    /**@}*/

public:
    bool operator==(const archetype& rhs) const;
    bool operator!=(const archetype& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype& other) noexcept;
    archetype& operator=(archetype other);

private:
    std::string description_;
    dogen::physical::entities::meta_name meta_name_;
    std::list<dogen::physical::entities::label> labels_;
    std::string default_postfix_;
    std::string override_postfix_;
    std::list<std::string> depends_;
    std::list<std::string> generates_;
    std::string generated_by_;
    std::string archetype_kind_id_;
    std::string logical_meta_element_id_;
    std::string part_;
    dogen::physical::entities::relation_status relation_status_;
    std::list<dogen::physical::entities::variable_relation> variable_relations_;
    std::list<dogen::physical::entities::fixed_relation> fixed_relations_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::archetype& lhs,
    dogen::physical::entities::archetype& rhs) {
    lhs.swap(rhs);
}

}

#endif
