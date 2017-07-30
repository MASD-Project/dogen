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
#ifndef DOGEN_YARN_TYPES_HELPERS_LOCATION_BUILDER_HPP
#define DOGEN_YARN_TYPES_HELPERS_LOCATION_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/yarn/types/meta_model/location.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class location_builder final {
public:
    location_builder() = default;
    location_builder(const location_builder&) = default;
    location_builder(location_builder&&) = default;
    ~location_builder() = default;

public:
    explicit location_builder(const dogen::yarn::meta_model::location& location_);

public:
    const dogen::yarn::meta_model::location& location_() const;
    dogen::yarn::meta_model::location& location_();
    void location_(const dogen::yarn::meta_model::location& v);
    void location_(const dogen::yarn::meta_model::location&& v);

public:
    bool operator==(const location_builder& rhs) const;
    bool operator!=(const location_builder& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(location_builder& other) noexcept;
    location_builder& operator=(location_builder other);

private:
    dogen::yarn::meta_model::location location__;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::helpers::location_builder& lhs,
    dogen::yarn::helpers::location_builder& rhs) {
    lhs.swap(rhs);
}

}

#endif
