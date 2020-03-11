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
#ifndef DOGEN_VARIABILITY_TYPES_TRANSFORMS_PROFILE_REPOSITORY_INPUTS_HPP
#define DOGEN_VARIABILITY_TYPES_TRANSFORMS_PROFILE_REPOSITORY_INPUTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.variability/types/meta_model/profile.hpp"
#include "dogen.variability/types/meta_model/profile_template.hpp"

namespace dogen::variability::transforms {

class profile_repository_inputs final {
public:
    profile_repository_inputs() = default;
    profile_repository_inputs(const profile_repository_inputs&) = default;
    profile_repository_inputs(profile_repository_inputs&&) = default;
    ~profile_repository_inputs() = default;

public:
    profile_repository_inputs(
        const std::list<dogen::variability::meta_model::profile>& profiles,
        const std::list<dogen::variability::meta_model::profile_template>& templates);

public:
    const std::list<dogen::variability::meta_model::profile>& profiles() const;
    std::list<dogen::variability::meta_model::profile>& profiles();
    void profiles(const std::list<dogen::variability::meta_model::profile>& v);
    void profiles(const std::list<dogen::variability::meta_model::profile>&& v);

    const std::list<dogen::variability::meta_model::profile_template>& templates() const;
    std::list<dogen::variability::meta_model::profile_template>& templates();
    void templates(const std::list<dogen::variability::meta_model::profile_template>& v);
    void templates(const std::list<dogen::variability::meta_model::profile_template>&& v);

public:
    bool operator==(const profile_repository_inputs& rhs) const;
    bool operator!=(const profile_repository_inputs& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(profile_repository_inputs& other) noexcept;
    profile_repository_inputs& operator=(profile_repository_inputs other);

private:
    std::list<dogen::variability::meta_model::profile> profiles_;
    std::list<dogen::variability::meta_model::profile_template> templates_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::transforms::profile_repository_inputs& lhs,
    dogen::variability::transforms::profile_repository_inputs& rhs) {
    lhs.swap(rhs);
}

}

#endif
