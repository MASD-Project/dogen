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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_META_MODEL_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_META_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "dogen.physical/types/entities/backend.hpp"
#include "dogen.physical/types/entities/meta_name.hpp"
#include "dogen.physical/types/entities/enablement_flags.hpp"
#include "dogen.physical/types/entities/meta_name_indices.hpp"

namespace dogen::physical::entities {

/**
 * @brief Describes the geomtry of physical space.
 *
 * Provides details of the kernels available in the current instance of Dogen.
 */
class meta_model final {
public:
    meta_model() = default;
    meta_model(const meta_model&) = default;
    meta_model(meta_model&&) = default;
    ~meta_model() = default;

public:
    meta_model(
        const std::string& description,
        const dogen::physical::entities::meta_name& meta_name,
        const std::unordered_map<std::string, dogen::physical::entities::enablement_flags>& enablement_flags,
        const std::unordered_map<std::string, std::vector<std::string> >& template_instantiation_domains,
        const std::list<dogen::physical::entities::backend>& backends,
        const dogen::physical::entities::meta_name_indices& indexed_names);

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
     * @brief Global enablement flags
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::physical::entities::enablement_flags>& enablement_flags() const;
    std::unordered_map<std::string, dogen::physical::entities::enablement_flags>& enablement_flags();
    void enablement_flags(const std::unordered_map<std::string, dogen::physical::entities::enablement_flags>& v);
    void enablement_flags(const std::unordered_map<std::string, dogen::physical::entities::enablement_flags>&& v);
    /**@}*/

    /**
     * @brief Provides all of the domains to be used for template instantiation.
     *
     * Example of a domain is "masd.facet" which contains the list of all available facets.
     * Templates (facet and profile) are then instantiated over this range, depending on
     * user choices.
     */
    /**@{*/
    const std::unordered_map<std::string, std::vector<std::string> >& template_instantiation_domains() const;
    std::unordered_map<std::string, std::vector<std::string> >& template_instantiation_domains();
    void template_instantiation_domains(const std::unordered_map<std::string, std::vector<std::string> >& v);
    void template_instantiation_domains(const std::unordered_map<std::string, std::vector<std::string> >&& v);
    /**@}*/

    /**
     * @brief All backends available in this meta-model.
     */
    /**@{*/
    const std::list<dogen::physical::entities::backend>& backends() const;
    std::list<dogen::physical::entities::backend>& backends();
    void backends(const std::list<dogen::physical::entities::backend>& v);
    void backends(const std::list<dogen::physical::entities::backend>&& v);
    /**@}*/

    /**
     * @brief Repository with all the meta-names in this kernel, indexed appropriately.
     */
    /**@{*/
    const dogen::physical::entities::meta_name_indices& indexed_names() const;
    dogen::physical::entities::meta_name_indices& indexed_names();
    void indexed_names(const dogen::physical::entities::meta_name_indices& v);
    void indexed_names(const dogen::physical::entities::meta_name_indices&& v);
    /**@}*/

public:
    bool operator==(const meta_model& rhs) const;
    bool operator!=(const meta_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(meta_model& other) noexcept;
    meta_model& operator=(meta_model other);

private:
    std::string description_;
    dogen::physical::entities::meta_name meta_name_;
    std::unordered_map<std::string, dogen::physical::entities::enablement_flags> enablement_flags_;
    std::unordered_map<std::string, std::vector<std::string> > template_instantiation_domains_;
    std::list<dogen::physical::entities::backend> backends_;
    dogen::physical::entities::meta_name_indices indexed_names_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::meta_model& lhs,
    dogen::physical::entities::meta_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
