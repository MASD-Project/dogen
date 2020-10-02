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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_FACET_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_FACET_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.identification/types/entities/physical_meta_name.hpp"

namespace dogen::physical::entities {

/**
 * @brief Properties related to the facet.
 */
class facet_properties final {
public:
    facet_properties(const facet_properties&) = default;
    facet_properties(facet_properties&&) = default;
    ~facet_properties() = default;

public:
    facet_properties();

public:
    facet_properties(
        const dogen::identification::entities::physical_meta_name& meta_name,
        const bool enabled,
        const bool overwrite,
        const std::string& directory_name,
        const std::string& computed_directory_name,
        const std::string& postfix,
        const std::string& computed_postfix);

public:
    /**
     * @brief Meta-name for this meta-element.
     */
    /**@{*/
    const dogen::identification::entities::physical_meta_name& meta_name() const;
    dogen::identification::entities::physical_meta_name& meta_name();
    void meta_name(const dogen::identification::entities::physical_meta_name& v);
    void meta_name(const dogen::identification::entities::physical_meta_name&& v);
    /**@}*/

    /**
     * @brief If true, the facet is enabled.
     */
    /**@{*/
    bool enabled() const;
    void enabled(const bool v);
    /**@}*/

    /**
     * @brief If true, all archetypes in this facet will be set to overwrite.
     */
    /**@{*/
    bool overwrite() const;
    void overwrite(const bool v);
    /**@}*/

    /**
     * @brief Directory name as read out from the configuration.
     */
    /**@{*/
    const std::string& directory_name() const;
    std::string& directory_name();
    void directory_name(const std::string& v);
    void directory_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Computed name of the directory to use for the facet.
     */
    /**@{*/
    const std::string& computed_directory_name() const;
    std::string& computed_directory_name();
    void computed_directory_name(const std::string& v);
    void computed_directory_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Postfix as read out from the configuration, if any.
     */
    /**@{*/
    const std::string& postfix() const;
    std::string& postfix();
    void postfix(const std::string& v);
    void postfix(const std::string&& v);
    /**@}*/

    /**
     * @brief Computed postfix to apply to all artefacts in this facet.
     */
    /**@{*/
    const std::string& computed_postfix() const;
    std::string& computed_postfix();
    void computed_postfix(const std::string& v);
    void computed_postfix(const std::string&& v);
    /**@}*/

public:
    bool operator==(const facet_properties& rhs) const;
    bool operator!=(const facet_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(facet_properties& other) noexcept;
    facet_properties& operator=(facet_properties other);

private:
    dogen::identification::entities::physical_meta_name meta_name_;
    bool enabled_;
    bool overwrite_;
    std::string directory_name_;
    std::string computed_directory_name_;
    std::string postfix_;
    std::string computed_postfix_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::facet_properties& lhs,
    dogen::physical::entities::facet_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
