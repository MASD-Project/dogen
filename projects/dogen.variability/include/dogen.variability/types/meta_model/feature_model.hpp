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
#ifndef DOGEN_VARIABILITY_TYPES_META_MODEL_FEATURE_MODEL_HPP
#define DOGEN_VARIABILITY_TYPES_META_MODEL_FEATURE_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.variability/types/meta_model/feature.hpp"

namespace dogen::variability::meta_model {

/**
 * @brief Container of all available features, organised for querying.
 */
class feature_model final {
public:
    feature_model() = default;
    feature_model(const feature_model&) = default;
    feature_model(feature_model&&) = default;
    ~feature_model() = default;

public:
    feature_model(
        const std::list<dogen::variability::meta_model::feature>& all,
        const std::unordered_map<std::string, dogen::variability::meta_model::feature>& by_name,
        const std::unordered_map<std::string, dogen::variability::meta_model::feature>& partially_matchable);

public:
    const std::list<dogen::variability::meta_model::feature>& all() const;
    std::list<dogen::variability::meta_model::feature>& all();
    void all(const std::list<dogen::variability::meta_model::feature>& v);
    void all(const std::list<dogen::variability::meta_model::feature>&& v);

    /**
     * @brief Features by qualified name.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::variability::meta_model::feature>& by_name() const;
    std::unordered_map<std::string, dogen::variability::meta_model::feature>& by_name();
    void by_name(const std::unordered_map<std::string, dogen::variability::meta_model::feature>& v);
    void by_name(const std::unordered_map<std::string, dogen::variability::meta_model::feature>&& v);
    /**@}*/

    /**
     * @brief Features that can be partially matcheable, by qualified name.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::variability::meta_model::feature>& partially_matchable() const;
    std::unordered_map<std::string, dogen::variability::meta_model::feature>& partially_matchable();
    void partially_matchable(const std::unordered_map<std::string, dogen::variability::meta_model::feature>& v);
    void partially_matchable(const std::unordered_map<std::string, dogen::variability::meta_model::feature>&& v);
    /**@}*/

public:
    bool operator==(const feature_model& rhs) const;
    bool operator!=(const feature_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(feature_model& other) noexcept;
    feature_model& operator=(feature_model other);

private:
    std::list<dogen::variability::meta_model::feature> all_;
    std::unordered_map<std::string, dogen::variability::meta_model::feature> by_name_;
    std::unordered_map<std::string, dogen::variability::meta_model::feature> partially_matchable_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::meta_model::feature_model& lhs,
    dogen::variability::meta_model::feature_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
