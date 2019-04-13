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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_TRANSFORMS_CONTEXT_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.archetypes/types/location_repository.hpp"

namespace masd::dogen::variability::transforms {

/**
 * @brief Context for transformations.
 */
class context final {
public:
    context() = default;
    context(const context&) = default;
    context(context&&) = default;
    ~context() = default;

public:
    context(
        const masd::dogen::archetypes::location_repository& archetype_location_repository,
        const std::vector<boost::filesystem::path>& data_directories);

public:
    const masd::dogen::archetypes::location_repository& archetype_location_repository() const;
    masd::dogen::archetypes::location_repository& archetype_location_repository();
    void archetype_location_repository(const masd::dogen::archetypes::location_repository& v);
    void archetype_location_repository(const masd::dogen::archetypes::location_repository&& v);

    const std::vector<boost::filesystem::path>& data_directories() const;
    std::vector<boost::filesystem::path>& data_directories();
    void data_directories(const std::vector<boost::filesystem::path>& v);
    void data_directories(const std::vector<boost::filesystem::path>&& v);

public:
    bool operator==(const context& rhs) const;
    bool operator!=(const context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(context& other) noexcept;
    context& operator=(context other);

private:
    masd::dogen::archetypes::location_repository archetype_location_repository_;
    std::vector<boost::filesystem::path> data_directories_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::variability::transforms::context& lhs,
    masd::dogen::variability::transforms::context& rhs) {
    lhs.swap(rhs);
}

}

#endif
