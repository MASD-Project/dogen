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
#ifndef MASD_DOGEN_EXTRACTION_TYPES_META_MODEL_OPERATION_HPP
#define MASD_DOGEN_EXTRACTION_TYPES_META_MODEL_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "masd.dogen.extraction/types/meta_model/operation_type.hpp"
#include "masd.dogen.extraction/types/meta_model/operation_reason.hpp"

namespace masd::dogen::extraction::meta_model {

class operation final {
public:
    operation(const operation&) = default;
    operation(operation&&) = default;
    ~operation() = default;

public:
    operation();

public:
    operation(
        const masd::dogen::extraction::meta_model::operation_type type,
        const masd::dogen::extraction::meta_model::operation_reason reason);

public:
    masd::dogen::extraction::meta_model::operation_type type() const;
    void type(const masd::dogen::extraction::meta_model::operation_type v);

    masd::dogen::extraction::meta_model::operation_reason reason() const;
    void reason(const masd::dogen::extraction::meta_model::operation_reason v);

public:
    bool operator==(const operation& rhs) const;
    bool operator!=(const operation& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(operation& other) noexcept;
    operation& operator=(operation other);

private:
    masd::dogen::extraction::meta_model::operation_type type_;
    masd::dogen::extraction::meta_model::operation_reason reason_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::extraction::meta_model::operation& lhs,
    masd::dogen::extraction::meta_model::operation& rhs) {
    lhs.swap(rhs);
}

}

#endif
