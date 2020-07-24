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
#ifndef DOGEN_ORCHESTRATION_TYPES_HELPERS_STEREOTYPES_CONVERSION_RESULT_HPP
#define DOGEN_ORCHESTRATION_TYPES_HELPERS_STEREOTYPES_CONVERSION_RESULT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.identification/types/entities/stereotype.hpp"
#include "dogen.logical/types/entities/static_stereotypes.hpp"

namespace dogen::orchestration::helpers {

/**
 * @brief Aggregates the result of parsing a CSV string with well-known stereotypes and
 * user defined stereotypes.
 */
class stereotypes_conversion_result final {
public:
    stereotypes_conversion_result() = default;
    stereotypes_conversion_result(const stereotypes_conversion_result&) = default;
    stereotypes_conversion_result(stereotypes_conversion_result&&) = default;
    ~stereotypes_conversion_result() = default;

public:
    stereotypes_conversion_result(
        const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
        const std::list<dogen::identification::entities::stereotype>& dynamic_stereotypes);

public:
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes() const;
    std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes();
    void static_stereotypes(const std::list<dogen::logical::entities::static_stereotypes>& v);
    void static_stereotypes(const std::list<dogen::logical::entities::static_stereotypes>&& v);

    const std::list<dogen::identification::entities::stereotype>& dynamic_stereotypes() const;
    std::list<dogen::identification::entities::stereotype>& dynamic_stereotypes();
    void dynamic_stereotypes(const std::list<dogen::identification::entities::stereotype>& v);
    void dynamic_stereotypes(const std::list<dogen::identification::entities::stereotype>&& v);

public:
    bool operator==(const stereotypes_conversion_result& rhs) const;
    bool operator!=(const stereotypes_conversion_result& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(stereotypes_conversion_result& other) noexcept;
    stereotypes_conversion_result& operator=(stereotypes_conversion_result other);

private:
    std::list<dogen::logical::entities::static_stereotypes> static_stereotypes_;
    std::list<dogen::identification::entities::stereotype> dynamic_stereotypes_;
};

}

namespace std {

template<>
inline void swap(
    dogen::orchestration::helpers::stereotypes_conversion_result& lhs,
    dogen::orchestration::helpers::stereotypes_conversion_result& rhs) {
    lhs.swap(rhs);
}

}

#endif
