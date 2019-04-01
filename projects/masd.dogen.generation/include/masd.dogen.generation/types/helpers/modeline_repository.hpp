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
#ifndef MASD_DOGEN_GENERATION_TYPES_HELPERS_MODELINE_REPOSITORY_HPP
#define MASD_DOGEN_GENERATION_TYPES_HELPERS_MODELINE_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "masd.dogen.coding/types/meta_model/modeline.hpp"
#include "masd.dogen.coding/types/meta_model/technical_space.hpp"
#include "masd.dogen.coding/hash/meta_model/technical_space_hash.hpp"

namespace masd::dogen::generation::helpers {

class modeline_repository final {
public:
    modeline_repository() = default;
    modeline_repository(const modeline_repository&) = default;
    modeline_repository(modeline_repository&&) = default;
    ~modeline_repository() = default;

public:
    explicit modeline_repository(const std::unordered_map<std::string, std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> >& modelines_by_group_by_technical_space);

public:
    const std::unordered_map<std::string, std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> >& modelines_by_group_by_technical_space() const;
    std::unordered_map<std::string, std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> >& modelines_by_group_by_technical_space();
    void modelines_by_group_by_technical_space(const std::unordered_map<std::string, std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> >& v);
    void modelines_by_group_by_technical_space(const std::unordered_map<std::string, std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> >&& v);

public:
    bool operator==(const modeline_repository& rhs) const;
    bool operator!=(const modeline_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(modeline_repository& other) noexcept;
    modeline_repository& operator=(modeline_repository other);

private:
    std::unordered_map<std::string, std::unordered_map<masd::dogen::coding::meta_model::technical_space, masd::dogen::coding::meta_model::modeline> > modelines_by_group_by_technical_space_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::generation::helpers::modeline_repository& lhs,
    masd::dogen::generation::helpers::modeline_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
