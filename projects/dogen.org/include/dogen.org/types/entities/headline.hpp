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
#ifndef DOGEN_ORG_TYPES_ENTITIES_HEADLINE_HPP
#define DOGEN_ORG_TYPES_ENTITIES_HEADLINE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen.org/types/entities/tag.hpp"
#include "dogen.org/types/entities/drawer.hpp"
#include "dogen.org/types/entities/section.hpp"
#include "dogen.org/types/entities/headline.hpp"
#include "dogen.org/types/entities/todo_keyword.hpp"
#include "dogen.org/types/entities/priority_cookie.hpp"

namespace dogen::org::entities {

class headline final {
public:
    headline(const headline&) = default;
    headline(headline&&) = default;
    ~headline() = default;

public:
    headline();

public:
    headline(
        const dogen::org::entities::section& section,
        const std::list<dogen::org::entities::headline>& headlines,
        const unsigned int level,
        const dogen::org::entities::priority_cookie& priority,
        const std::string& title,
        const std::list<dogen::org::entities::tag>& tags,
        const dogen::org::entities::todo_keyword& todo_keyword,
        const std::list<dogen::org::entities::drawer>& drawers);

public:
    const dogen::org::entities::section& section() const;
    dogen::org::entities::section& section();
    void section(const dogen::org::entities::section& v);
    void section(const dogen::org::entities::section&& v);

    /**
     * @brief Top-most headlines within this headline.
     */
    /**@{*/
    const std::list<dogen::org::entities::headline>& headlines() const;
    std::list<dogen::org::entities::headline>& headlines();
    void headlines(const std::list<dogen::org::entities::headline>& v);
    void headlines(const std::list<dogen::org::entities::headline>&& v);
    /**@}*/

    /**
     * @brief Reduced level of the headline. STARS in the original org-mode format.
     */
    /**@{*/
    unsigned int level() const;
    void level(const unsigned int v);
    /**@}*/

    /**
     * @brief Headline's priority.
     */
    /**@{*/
    const dogen::org::entities::priority_cookie& priority() const;
    dogen::org::entities::priority_cookie& priority();
    void priority(const dogen::org::entities::priority_cookie& v);
    void priority(const dogen::org::entities::priority_cookie&& v);
    /**@}*/

    /**
     * @brief Parsed headline's text, without the stars and the tags.
     */
    /**@{*/
    const std::string& title() const;
    std::string& title();
    void title(const std::string& v);
    void title(const std::string&& v);
    /**@}*/

    /**
     * @brief Headline's tags, if any.
     */
    /**@{*/
    const std::list<dogen::org::entities::tag>& tags() const;
    std::list<dogen::org::entities::tag>& tags();
    void tags(const std::list<dogen::org::entities::tag>& v);
    void tags(const std::list<dogen::org::entities::tag>&& v);
    /**@}*/

    /**
     * @brief Headline's TODO keyword.
     */
    /**@{*/
    const dogen::org::entities::todo_keyword& todo_keyword() const;
    dogen::org::entities::todo_keyword& todo_keyword();
    void todo_keyword(const dogen::org::entities::todo_keyword& v);
    void todo_keyword(const dogen::org::entities::todo_keyword&& v);
    /**@}*/

    const std::list<dogen::org::entities::drawer>& drawers() const;
    std::list<dogen::org::entities::drawer>& drawers();
    void drawers(const std::list<dogen::org::entities::drawer>& v);
    void drawers(const std::list<dogen::org::entities::drawer>&& v);

public:
    bool operator==(const headline& rhs) const;
    bool operator!=(const headline& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(headline& other) noexcept;
    headline& operator=(headline other);

private:
    dogen::org::entities::section section_;
    std::list<dogen::org::entities::headline> headlines_;
    unsigned int level_;
    dogen::org::entities::priority_cookie priority_;
    std::string title_;
    std::list<dogen::org::entities::tag> tags_;
    dogen::org::entities::todo_keyword todo_keyword_;
    std::list<dogen::org::entities::drawer> drawers_;
};

}

namespace std {

template<>
inline void swap(
    dogen::org::entities::headline& lhs,
    dogen::org::entities::headline& rhs) {
    lhs.swap(rhs);
}

}

#endif
