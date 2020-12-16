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
#ifndef DOGEN_ORG_TYPES_ENTITIES_DOCUMENT_HPP
#define DOGEN_ORG_TYPES_ENTITIES_DOCUMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.org/types/entities/drawer.hpp"
#include "dogen.org/types/entities/section.hpp"
#include "dogen.org/types/entities/headline.hpp"
#include "dogen.org/types/entities/affiliated_keyword.hpp"

namespace dogen::org::entities {

class document final {
public:
    document() = default;
    document(const document&) = default;
    document(document&&) = default;
    ~document() = default;

public:
    document(
        const std::list<dogen::org::entities::affiliated_keyword>& affiliated_keywords,
        const std::list<dogen::org::entities::drawer>& drawers,
        const dogen::org::entities::section& section,
        const std::list<dogen::org::entities::headline>& headlines);

public:
    const std::list<dogen::org::entities::affiliated_keyword>& affiliated_keywords() const;
    std::list<dogen::org::entities::affiliated_keyword>& affiliated_keywords();
    void affiliated_keywords(const std::list<dogen::org::entities::affiliated_keyword>& v);
    void affiliated_keywords(const std::list<dogen::org::entities::affiliated_keyword>&& v);

    const std::list<dogen::org::entities::drawer>& drawers() const;
    std::list<dogen::org::entities::drawer>& drawers();
    void drawers(const std::list<dogen::org::entities::drawer>& v);
    void drawers(const std::list<dogen::org::entities::drawer>&& v);

    /**
     * @brief Top-level section in document.
     */
    /**@{*/
    const dogen::org::entities::section& section() const;
    dogen::org::entities::section& section();
    void section(const dogen::org::entities::section& v);
    void section(const dogen::org::entities::section&& v);
    /**@}*/

    /**
     * @brief Top-level headlines in document.
     */
    /**@{*/
    const std::list<dogen::org::entities::headline>& headlines() const;
    std::list<dogen::org::entities::headline>& headlines();
    void headlines(const std::list<dogen::org::entities::headline>& v);
    void headlines(const std::list<dogen::org::entities::headline>&& v);
    /**@}*/

public:
    bool operator==(const document& rhs) const;
    bool operator!=(const document& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(document& other) noexcept;
    document& operator=(document other);

private:
    std::list<dogen::org::entities::affiliated_keyword> affiliated_keywords_;
    std::list<dogen::org::entities::drawer> drawers_;
    dogen::org::entities::section section_;
    std::list<dogen::org::entities::headline> headlines_;
};

}

namespace std {

template<>
inline void swap(
    dogen::org::entities::document& lhs,
    dogen::org::entities::document& rhs) {
    lhs.swap(rhs);
}

}

#endif
