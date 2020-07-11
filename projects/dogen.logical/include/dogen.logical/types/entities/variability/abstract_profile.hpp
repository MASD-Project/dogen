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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_ABSTRACT_PROFILE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_ABSTRACT_PROFILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.logical/types/entities/element.hpp"

namespace dogen::logical::entities::variability {

class abstract_profile : public dogen::logical::entities::element {
public:
    abstract_profile() = default;
    abstract_profile(const abstract_profile&) = default;
    abstract_profile(abstract_profile&&) = default;

    virtual ~abstract_profile() noexcept = 0;

public:
    abstract_profile(
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
        const dogen::logical::entities::generability_status generability_status,
        const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& enablement_properties,
        const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const std::string& stereotype,
        const std::list<dogen::logical::entities::name>& parents,
        const std::string& key_prefix);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    const std::string& stereotype() const;
    std::string& stereotype();
    void stereotype(const std::string& v);
    void stereotype(const std::string&& v);

    /**
     * @brief Parents of this profile template.
     */
    /**@{*/
    const std::list<dogen::logical::entities::name>& parents() const;
    std::list<dogen::logical::entities::name>& parents();
    void parents(const std::list<dogen::logical::entities::name>& v);
    void parents(const std::list<dogen::logical::entities::name>&& v);
    /**@}*/

    /**
     * @brief Prefix to use when composing the key, if any.
     */
    /**@{*/
    const std::string& key_prefix() const;
    std::string& key_prefix();
    void key_prefix(const std::string& v);
    void key_prefix(const std::string&& v);
    /**@}*/

protected:
    bool compare(const abstract_profile& rhs) const;
public:
    virtual bool equals(const dogen::logical::entities::element& other) const = 0;

protected:
    void swap(abstract_profile& other) noexcept;

private:
    std::string stereotype_;
    std::list<dogen::logical::entities::name> parents_;
    std::string key_prefix_;
};

inline abstract_profile::~abstract_profile() noexcept { }

inline bool operator==(const abstract_profile& lhs, const abstract_profile& rhs) {
    return lhs.equals(rhs);
}

}

#endif
