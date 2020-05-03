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
#ifndef DOGEN_TEXT_CPP_TYPES_FORMATTABLES_LOCATOR_ARCHETYPE_CONFIGURATION_HPP
#define DOGEN_TEXT_CPP_TYPES_FORMATTABLES_LOCATOR_ARCHETYPE_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::text::cpp::formattables {

class locator_archetype_configuration final {
public:
    locator_archetype_configuration() = default;
    locator_archetype_configuration(const locator_archetype_configuration&) = default;
    locator_archetype_configuration(locator_archetype_configuration&&) = default;
    ~locator_archetype_configuration() = default;

public:
    locator_archetype_configuration(
        const std::string& facet_directory,
        const std::string& facet_postfix,
        const std::string& archetype_postfix);

public:
    const std::string& facet_directory() const;
    std::string& facet_directory();
    void facet_directory(const std::string& v);
    void facet_directory(const std::string&& v);

    const std::string& facet_postfix() const;
    std::string& facet_postfix();
    void facet_postfix(const std::string& v);
    void facet_postfix(const std::string&& v);

    const std::string& archetype_postfix() const;
    std::string& archetype_postfix();
    void archetype_postfix(const std::string& v);
    void archetype_postfix(const std::string&& v);

public:
    bool operator==(const locator_archetype_configuration& rhs) const;
    bool operator!=(const locator_archetype_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(locator_archetype_configuration& other) noexcept;
    locator_archetype_configuration& operator=(locator_archetype_configuration other);

private:
    std::string facet_directory_;
    std::string facet_postfix_;
    std::string archetype_postfix_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::cpp::formattables::locator_archetype_configuration& lhs,
    dogen::text::cpp::formattables::locator_archetype_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
