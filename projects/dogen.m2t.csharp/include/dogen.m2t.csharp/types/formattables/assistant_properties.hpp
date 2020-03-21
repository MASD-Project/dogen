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
#ifndef DOGEN_M2T_CSHARP_TYPES_FORMATTABLES_ASSISTANT_PROPERTIES_HPP
#define DOGEN_M2T_CSHARP_TYPES_FORMATTABLES_ASSISTANT_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::m2t::csharp::formattables {

class assistant_properties final {
public:
    assistant_properties(const assistant_properties&) = default;
    assistant_properties(assistant_properties&&) = default;
    ~assistant_properties() = default;

public:
    assistant_properties();

public:
    assistant_properties(
        const bool requires_assistance,
        const std::string& method_postfix);

public:
    /**
     * @brief If true, the type needs help of an assistant.
     */
    /**@{*/
    bool requires_assistance() const;
    void requires_assistance(const bool v);
    /**@}*/

    /**
     * @brief Postfix to use to call the appropriate assistant method, if required.
     */
    /**@{*/
    const std::string& method_postfix() const;
    std::string& method_postfix();
    void method_postfix(const std::string& v);
    void method_postfix(const std::string&& v);
    /**@}*/

public:
    bool operator==(const assistant_properties& rhs) const;
    bool operator!=(const assistant_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(assistant_properties& other) noexcept;
    assistant_properties& operator=(assistant_properties other);

private:
    bool requires_assistance_;
    std::string method_postfix_;
};

}

namespace std {

template<>
inline void swap(
    dogen::m2t::csharp::formattables::assistant_properties& lhs,
    dogen::m2t::csharp::formattables::assistant_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
