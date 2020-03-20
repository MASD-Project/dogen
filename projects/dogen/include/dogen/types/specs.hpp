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
#ifndef DOGEN_TYPES_SPECS_HPP
#define DOGEN_TYPES_SPECS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen/types/spec_category.hpp"

namespace dogen {

/**
 * @brief Describes details of the available functionality within this version of Dogen.
 */
class specs final {
public:
    specs() = default;
    specs(const specs&) = default;
    specs(specs&&) = default;
    ~specs() = default;

public:
    explicit specs(const std::list<dogen::spec_category>& categories);

public:
    /**
     * @brief All categories of specifications.
     */
    /**@{*/
    const std::list<dogen::spec_category>& categories() const;
    std::list<dogen::spec_category>& categories();
    void categories(const std::list<dogen::spec_category>& v);
    void categories(const std::list<dogen::spec_category>&& v);
    /**@}*/

public:
    bool operator==(const specs& rhs) const;
    bool operator!=(const specs& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(specs& other) noexcept;
    specs& operator=(specs other);

private:
    std::list<dogen::spec_category> categories_;
};

}

namespace std {

template<>
inline void swap(
    dogen::specs& lhs,
    dogen::specs& rhs) {
    lhs.swap(rhs);
}

}

#endif
