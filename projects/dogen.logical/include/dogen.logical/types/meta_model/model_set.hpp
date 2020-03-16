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
#ifndef DOGEN_LOGICAL_TYPES_META_MODEL_MODEL_SET_HPP
#define DOGEN_LOGICAL_TYPES_META_MODEL_MODEL_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.logical/types/meta_model/model.hpp"

namespace dogen::logical::meta_model {

class model_set final {
public:
    model_set() = default;
    model_set(const model_set&) = default;
    model_set(model_set&&) = default;
    ~model_set() = default;

public:
    model_set(
        const dogen::logical::meta_model::model& target,
        const std::list<dogen::logical::meta_model::model>& references,
        const std::unordered_map<std::string, std::string>& fixed_mappings);

public:
    const dogen::logical::meta_model::model& target() const;
    dogen::logical::meta_model::model& target();
    void target(const dogen::logical::meta_model::model& v);
    void target(const dogen::logical::meta_model::model&& v);

    const std::list<dogen::logical::meta_model::model>& references() const;
    std::list<dogen::logical::meta_model::model>& references();
    void references(const std::list<dogen::logical::meta_model::model>& v);
    void references(const std::list<dogen::logical::meta_model::model>&& v);

    /**
     * @brief Maps a fixed mappable name, using the scope notation, to its destination.
     */
    /**@{*/
    const std::unordered_map<std::string, std::string>& fixed_mappings() const;
    std::unordered_map<std::string, std::string>& fixed_mappings();
    void fixed_mappings(const std::unordered_map<std::string, std::string>& v);
    void fixed_mappings(const std::unordered_map<std::string, std::string>&& v);
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
    dogen::logical::meta_model::model target_;
    std::list<dogen::logical::meta_model::model> references_;
    std::unordered_map<std::string, std::string> fixed_mappings_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::meta_model::model_set& lhs,
    dogen::logical::meta_model::model_set& rhs) {
    lhs.swap(rhs);
}

}

#endif
