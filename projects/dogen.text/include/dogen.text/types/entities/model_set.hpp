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
#ifndef DOGEN_TEXT_TYPES_ENTITIES_MODEL_SET_HPP
#define DOGEN_TEXT_TYPES_ENTITIES_MODEL_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.text/types/entities/model.hpp"
#include "dogen.logical/types/entities/name.hpp"

namespace dogen::text::entities {

/**
 * @brief Represents a set of related models.
 */
class model_set final {
public:
    model_set() = default;
    model_set(const model_set&) = default;
    model_set(model_set&&) = default;
    ~model_set() = default;

public:
    model_set(
        const dogen::logical::entities::name& name,
        const std::list<dogen::text::entities::model>& models);

public:
    const dogen::logical::entities::name& name() const;
    dogen::logical::entities::name& name();
    void name(const dogen::logical::entities::name& v);
    void name(const dogen::logical::entities::name&& v);

    /**
     * @brief Models that belong to this set.
     */
    /**@{*/
    const std::list<dogen::text::entities::model>& models() const;
    std::list<dogen::text::entities::model>& models();
    void models(const std::list<dogen::text::entities::model>& v);
    void models(const std::list<dogen::text::entities::model>&& v);
    /**@}*/

public:
    bool operator==(const model_set& rhs) const;
    bool operator!=(const model_set& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model_set& other) noexcept;
    model_set& operator=(model_set other);

private:
    dogen::logical::entities::name name_;
    std::list<dogen::text::entities::model> models_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::entities::model_set& lhs,
    dogen::text::entities::model_set& rhs) {
    lhs.swap(rhs);
}

}

#endif
