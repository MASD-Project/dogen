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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_ENABLEMENT_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_ENABLEMENT_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>

namespace dogen::physical::entities {

/**
 * @brief Stores the properties related to the enablement, as read out from configuration.
 */
class enablement_properties final {
public:
    enablement_properties(const enablement_properties&) = default;
    ~enablement_properties() = default;

public:
    enablement_properties();

public:
    enablement_properties(enablement_properties&& rhs);

public:
    enablement_properties(
        const bool enabled,
        const bool overwrite,
        const boost::optional<bool>& facet_enabled,
        const boost::optional<bool>& archetype_enabled,
        const boost::optional<bool>& facet_overwrite,
        const boost::optional<bool>& archetype_overwrite);

public:
    /**
     * @brief If true, the artefact is enabled and its content will be computed.
     */
    /**@{*/
    bool enabled() const;
    void enabled(const bool v);
    /**@}*/

    /**
     * @brief If true, the artefact will be expressed to the filesystem if there are changes.
     */
    /**@{*/
    bool overwrite() const;
    void overwrite(const bool v);
    /**@}*/

    /**
     * @brief If supplied and true, the facet is enabled.
     */
    /**@{*/
    const boost::optional<bool>& facet_enabled() const;
    boost::optional<bool>& facet_enabled();
    void facet_enabled(const boost::optional<bool>& v);
    void facet_enabled(const boost::optional<bool>&& v);
    /**@}*/

    /**
     * @brief If supplied and true, the archetype is enabled.
     */
    /**@{*/
    const boost::optional<bool>& archetype_enabled() const;
    boost::optional<bool>& archetype_enabled();
    void archetype_enabled(const boost::optional<bool>& v);
    void archetype_enabled(const boost::optional<bool>&& v);
    /**@}*/

    /**
     * @brief If supplied and true, the facet will have overwrite on.
     */
    /**@{*/
    const boost::optional<bool>& facet_overwrite() const;
    boost::optional<bool>& facet_overwrite();
    void facet_overwrite(const boost::optional<bool>& v);
    void facet_overwrite(const boost::optional<bool>&& v);
    /**@}*/

    /**
     * @brief If supplied and true, the archetype will have overwrite on.
     */
    /**@{*/
    const boost::optional<bool>& archetype_overwrite() const;
    boost::optional<bool>& archetype_overwrite();
    void archetype_overwrite(const boost::optional<bool>& v);
    void archetype_overwrite(const boost::optional<bool>&& v);
    /**@}*/

public:
    bool operator==(const enablement_properties& rhs) const;
    bool operator!=(const enablement_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(enablement_properties& other) noexcept;
    enablement_properties& operator=(enablement_properties other);

private:
    bool enabled_;
    bool overwrite_;
    boost::optional<bool> facet_enabled_;
    boost::optional<bool> archetype_enabled_;
    boost::optional<bool> facet_overwrite_;
    boost::optional<bool> archetype_overwrite_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::enablement_properties& lhs,
    dogen::physical::entities::enablement_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
