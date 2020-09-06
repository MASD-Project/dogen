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
#ifndef DOGEN_TEXT_CPP_TYPES_FORMATTABLES_DIRECTIVE_GROUP_REPOSITORY_HPP
#define DOGEN_TEXT_CPP_TYPES_FORMATTABLES_DIRECTIVE_GROUP_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.text.cpp/types/formattables/directive_group.hpp"
#include "dogen.identification/hash/entities/logical_id_hash.hpp"

namespace dogen::text::cpp::formattables {

class directive_group_repository final {
public:
    directive_group_repository() = default;
    directive_group_repository(const directive_group_repository&) = default;
    directive_group_repository(directive_group_repository&&) = default;
    ~directive_group_repository() = default;

public:
    explicit directive_group_repository(const std::unordered_map<dogen::identification::entities::logical_id, std::unordered_map<std::string, dogen::text::cpp::formattables::directive_group> >& by_id);

public:
    const std::unordered_map<dogen::identification::entities::logical_id, std::unordered_map<std::string, dogen::text::cpp::formattables::directive_group> >& by_id() const;
    std::unordered_map<dogen::identification::entities::logical_id, std::unordered_map<std::string, dogen::text::cpp::formattables::directive_group> >& by_id();
    void by_id(const std::unordered_map<dogen::identification::entities::logical_id, std::unordered_map<std::string, dogen::text::cpp::formattables::directive_group> >& v);
    void by_id(const std::unordered_map<dogen::identification::entities::logical_id, std::unordered_map<std::string, dogen::text::cpp::formattables::directive_group> >&& v);

public:
    bool operator==(const directive_group_repository& rhs) const;
    bool operator!=(const directive_group_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(directive_group_repository& other) noexcept;
    directive_group_repository& operator=(directive_group_repository other);

private:
    std::unordered_map<dogen::identification::entities::logical_id, std::unordered_map<std::string, dogen::text::cpp::formattables::directive_group> > by_id_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::cpp::formattables::directive_group_repository& lhs,
    dogen::text::cpp::formattables::directive_group_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
