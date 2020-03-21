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
#ifndef DOGEN_M2T_CSHARP_TYPES_FORMATTABLES_LOCATOR_FACET_CONFIGURATION_HPP
#define DOGEN_M2T_CSHARP_TYPES_FORMATTABLES_LOCATOR_FACET_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::m2t::csharp::formattables {

class locator_facet_configuration final {
public:
    locator_facet_configuration() = default;
    locator_facet_configuration(const locator_facet_configuration&) = default;
    locator_facet_configuration(locator_facet_configuration&&) = default;
    ~locator_facet_configuration() = default;

public:
    locator_facet_configuration(
        const std::string& directory,
        const std::string& postfix);

public:
    const std::string& directory() const;
    std::string& directory();
    void directory(const std::string& v);
    void directory(const std::string&& v);

    const std::string& postfix() const;
    std::string& postfix();
    void postfix(const std::string& v);
    void postfix(const std::string&& v);

public:
    bool operator==(const locator_facet_configuration& rhs) const;
    bool operator!=(const locator_facet_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(locator_facet_configuration& other) noexcept;
    locator_facet_configuration& operator=(locator_facet_configuration other);

private:
    std::string directory_;
    std::string postfix_;
};

}

namespace std {

template<>
inline void swap(
    dogen::m2t::csharp::formattables::locator_facet_configuration& lhs,
    dogen::m2t::csharp::formattables::locator_facet_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
