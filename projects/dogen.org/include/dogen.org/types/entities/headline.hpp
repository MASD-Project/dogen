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
#include "dogen.org/types/entities/affiliated_keyword.hpp"

namespace dogen::org::entities {

/**
 * @brief Represents a headline in org mode.
 *
 * Headlines and Sections
 *
 * https://orgmode.org/worg/dev/org-syntax.html#Headlines_and_Sections
 *
 * A headline is defined as:
 *
 * STARS KEYWORD PRIORITY TITLE TAGS
 *
 * STARS is a string starting at column 0, containing at least one
 * asterisk (and up to org-inlinetask-min-level if org-inlinetask library
 * is loaded) and ended by a space character. The number of asterisks is
 * used to define the level of the headline. It’s the sole compulsory
 * part of a headline.
 *
 * KEYWORD is a TODO keyword, which has to belong to the list defined in
 * org-todo-keywords-1. Case is significant.
 *
 * PRIORITY is a priority cookie, i.e. a single letter preceded by a hash
 * sign # and enclosed within square brackets.
 *
 * TITLE can be made of any character but a new line. Though, it will
 * match after every other part have been matched.
 *
 * TAGS is made of words containing any alpha-numeric character,
 * underscore, at sign, hash sign or percent sign, and separated with
 * colons.
 */
class headline final {
public:
    headline(const headline&) = default;
    headline(headline&&) = default;
    ~headline() = default;

public:
    headline();

public:
    headline(
        const unsigned int line_number,
        const std::list<dogen::org::entities::affiliated_keyword>& affiliated_keywords,
        const std::list<dogen::org::entities::drawer>& drawers,
        const dogen::org::entities::section& section,
        const std::list<dogen::org::entities::headline>& headlines,
        const unsigned int level,
        const dogen::org::entities::priority_cookie& priority,
        const std::string& title,
        const std::list<dogen::org::entities::tag>& tags,
        const dogen::org::entities::todo_keyword& todo_keyword);

public:
    /**
     * @brief Number of the line in the file which contained this headline.
     */
    /**@{*/
    unsigned int line_number() const;
    void line_number(const unsigned int v);
    /**@}*/

    const std::list<dogen::org::entities::affiliated_keyword>& affiliated_keywords() const;
    std::list<dogen::org::entities::affiliated_keyword>& affiliated_keywords();
    void affiliated_keywords(const std::list<dogen::org::entities::affiliated_keyword>& v);
    void affiliated_keywords(const std::list<dogen::org::entities::affiliated_keyword>&& v);

    const std::list<dogen::org::entities::drawer>& drawers() const;
    std::list<dogen::org::entities::drawer>& drawers();
    void drawers(const std::list<dogen::org::entities::drawer>& v);
    void drawers(const std::list<dogen::org::entities::drawer>&& v);

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

public:
    bool operator==(const headline& rhs) const;
    bool operator!=(const headline& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(headline& other) noexcept;
    headline& operator=(headline other);

private:
    unsigned int line_number_;
    std::list<dogen::org::entities::affiliated_keyword> affiliated_keywords_;
    std::list<dogen::org::entities::drawer> drawers_;
    dogen::org::entities::section section_;
    std::list<dogen::org::entities::headline> headlines_;
    unsigned int level_;
    dogen::org::entities::priority_cookie priority_;
    std::string title_;
    std::list<dogen::org::entities::tag> tags_;
    dogen::org::entities::todo_keyword todo_keyword_;
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
