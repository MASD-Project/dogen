/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_MODEL_ID_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_MODEL_ID_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.identification/serialization/entities/model_id_fwd_ser.hpp"

namespace dogen::identification::entities {
/**
 * @brief ID for a model.
 */
class model_id final {
public:
    model_id() = default;
    model_id(const model_id&) = default;
    model_id(model_id&&) = default;
    ~model_id() = default;
public:
    explicit model_id(const std::string& value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::identification::entities::model_id& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::identification::entities::model_id& v, unsigned int version);

public:
    /**
     * @brief Obtain the underlying value.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    explicit operator std::string() const {
        return value_;
    }

public:
    bool operator==(const model_id& rhs) const;
    bool operator!=(const model_id& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model_id& other) noexcept;
    model_id& operator=(model_id other);

private:
    std::string value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::model_id& lhs,
    dogen::identification::entities::model_id& rhs) {
    lhs.swap(rhs);
}

}

#endif
