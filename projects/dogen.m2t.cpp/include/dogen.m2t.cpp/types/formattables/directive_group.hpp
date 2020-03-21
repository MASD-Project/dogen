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
#ifndef DOGEN_M2T_CPP_TYPES_FORMATTABLES_DIRECTIVE_GROUP_HPP
#define DOGEN_M2T_CPP_TYPES_FORMATTABLES_DIRECTIVE_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>

namespace dogen::m2t::cpp::formattables {

/**
 * @brief Represents the group of inclusion directives associated with a name and an archetype.
 */
class directive_group final {
public:
    directive_group() = default;
    directive_group(const directive_group&) = default;
    directive_group(directive_group&&) = default;
    ~directive_group() = default;

public:
    directive_group(
        const std::string& primary,
        const std::list<std::string>& secondary);

public:
    /**
     * @brief The main inclusion directive needed for this element.
     */
    /**@{*/
    const std::string& primary() const;
    std::string& primary();
    void primary(const std::string& v);
    void primary(const std::string&& v);
    /**@}*/

    /**
     * @brief Any other directives that are also needed for this element.
     */
    /**@{*/
    const std::list<std::string>& secondary() const;
    std::list<std::string>& secondary();
    void secondary(const std::list<std::string>& v);
    void secondary(const std::list<std::string>&& v);
    /**@}*/

public:
    bool operator==(const directive_group& rhs) const;
    bool operator!=(const directive_group& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(directive_group& other) noexcept;
    directive_group& operator=(directive_group other);

private:
    std::string primary_;
    std::list<std::string> secondary_;
};

}

namespace std {

template<>
inline void swap(
    dogen::m2t::cpp::formattables::directive_group& lhs,
    dogen::m2t::cpp::formattables::directive_group& rhs) {
    lhs.swap(rhs);
}

}

#endif
