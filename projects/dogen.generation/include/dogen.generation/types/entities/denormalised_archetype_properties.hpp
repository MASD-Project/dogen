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
#ifndef DOGEN_GENERATION_TYPES_ENTITIES_DENORMALISED_ARCHETYPE_PROPERTIES_HPP
#define DOGEN_GENERATION_TYPES_ENTITIES_DENORMALISED_ARCHETYPE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>

namespace dogen::generation::entities {

class denormalised_archetype_properties final {
public:
    denormalised_archetype_properties(const denormalised_archetype_properties&) = default;
    ~denormalised_archetype_properties() = default;

public:
    denormalised_archetype_properties();

public:
    denormalised_archetype_properties(denormalised_archetype_properties&& rhs);

public:
    denormalised_archetype_properties(
        const bool backend_enabled,
        const std::string& backend_directory,
        const bool facet_enabled,
        const bool facet_overwrite,
        const std::string& facet_directory,
        const std::string& facet_postfix,
        const bool archetype_enabled,
        const boost::optional<bool>& archetype_overwrite,
        const std::string& archetype_postfix);

public:
    bool backend_enabled() const;
    void backend_enabled(const bool v);

    const std::string& backend_directory() const;
    std::string& backend_directory();
    void backend_directory(const std::string& v);
    void backend_directory(const std::string&& v);

    bool facet_enabled() const;
    void facet_enabled(const bool v);

    bool facet_overwrite() const;
    void facet_overwrite(const bool v);

    const std::string& facet_directory() const;
    std::string& facet_directory();
    void facet_directory(const std::string& v);
    void facet_directory(const std::string&& v);

    const std::string& facet_postfix() const;
    std::string& facet_postfix();
    void facet_postfix(const std::string& v);
    void facet_postfix(const std::string&& v);

    bool archetype_enabled() const;
    void archetype_enabled(const bool v);

    const boost::optional<bool>& archetype_overwrite() const;
    boost::optional<bool>& archetype_overwrite();
    void archetype_overwrite(const boost::optional<bool>& v);
    void archetype_overwrite(const boost::optional<bool>&& v);

    const std::string& archetype_postfix() const;
    std::string& archetype_postfix();
    void archetype_postfix(const std::string& v);
    void archetype_postfix(const std::string&& v);

public:
    bool operator==(const denormalised_archetype_properties& rhs) const;
    bool operator!=(const denormalised_archetype_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(denormalised_archetype_properties& other) noexcept;
    denormalised_archetype_properties& operator=(denormalised_archetype_properties other);

private:
    bool backend_enabled_;
    std::string backend_directory_;
    bool facet_enabled_;
    bool facet_overwrite_;
    std::string facet_directory_;
    std::string facet_postfix_;
    bool archetype_enabled_;
    boost::optional<bool> archetype_overwrite_;
    std::string archetype_postfix_;
};

}

namespace std {

template<>
inline void swap(
    dogen::generation::entities::denormalised_archetype_properties& lhs,
    dogen::generation::entities::denormalised_archetype_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
