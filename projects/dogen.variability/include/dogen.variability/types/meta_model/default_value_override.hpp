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
#ifndef DOGEN_VARIABILITY_TYPES_META_MODEL_DEFAULT_VALUE_OVERRIDE_HPP
#define DOGEN_VARIABILITY_TYPES_META_MODEL_DEFAULT_VALUE_OVERRIDE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.variability/types/meta_model/value_fwd.hpp"

namespace dogen::variability::meta_model {

/**
 * @brief Stores an override for a default value.
 */
class default_value_override final {
public:
    default_value_override() = default;
    default_value_override(const default_value_override&) = default;
    default_value_override(default_value_override&&) = default;
    ~default_value_override() = default;

public:
    default_value_override(
        const std::string& key,
        const boost::shared_ptr<dogen::variability::meta_model::value>& value);

public:
    const std::string& key() const;
    std::string& key();
    void key(const std::string& v);
    void key(const std::string&& v);

    const boost::shared_ptr<dogen::variability::meta_model::value>& value() const;
    boost::shared_ptr<dogen::variability::meta_model::value>& value();
    void value(const boost::shared_ptr<dogen::variability::meta_model::value>& v);
    void value(const boost::shared_ptr<dogen::variability::meta_model::value>&& v);

public:
    bool operator==(const default_value_override& rhs) const;
    bool operator!=(const default_value_override& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(default_value_override& other) noexcept;
    default_value_override& operator=(default_value_override other);

private:
    std::string key_;
    boost::shared_ptr<dogen::variability::meta_model::value> value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::meta_model::default_value_override& lhs,
    dogen::variability::meta_model::default_value_override& rhs) {
    lhs.swap(rhs);
}

}

#endif
