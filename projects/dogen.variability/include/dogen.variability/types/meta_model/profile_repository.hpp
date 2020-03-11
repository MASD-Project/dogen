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
#ifndef DOGEN_VARIABILITY_TYPES_META_MODEL_PROFILE_REPOSITORY_HPP
#define DOGEN_VARIABILITY_TYPES_META_MODEL_PROFILE_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.variability/types/meta_model/profile.hpp"

namespace dogen::variability::meta_model {

class profile_repository final {
public:
    profile_repository() = default;
    profile_repository(const profile_repository&) = default;
    profile_repository(profile_repository&&) = default;
    ~profile_repository() = default;

public:
    profile_repository(
        const std::unordered_map<std::string, dogen::variability::meta_model::profile>& by_name,
        const std::unordered_map<std::string, dogen::variability::meta_model::profile>& by_stereotype);

public:
    const std::unordered_map<std::string, dogen::variability::meta_model::profile>& by_name() const;
    std::unordered_map<std::string, dogen::variability::meta_model::profile>& by_name();
    void by_name(const std::unordered_map<std::string, dogen::variability::meta_model::profile>& v);
    void by_name(const std::unordered_map<std::string, dogen::variability::meta_model::profile>&& v);

    const std::unordered_map<std::string, dogen::variability::meta_model::profile>& by_stereotype() const;
    std::unordered_map<std::string, dogen::variability::meta_model::profile>& by_stereotype();
    void by_stereotype(const std::unordered_map<std::string, dogen::variability::meta_model::profile>& v);
    void by_stereotype(const std::unordered_map<std::string, dogen::variability::meta_model::profile>&& v);

public:
    bool operator==(const profile_repository& rhs) const;
    bool operator!=(const profile_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(profile_repository& other) noexcept;
    profile_repository& operator=(profile_repository other);

private:
    std::unordered_map<std::string, dogen::variability::meta_model::profile> by_name_;
    std::unordered_map<std::string, dogen::variability::meta_model::profile> by_stereotype_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::meta_model::profile_repository& lhs,
    dogen::variability::meta_model::profile_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
