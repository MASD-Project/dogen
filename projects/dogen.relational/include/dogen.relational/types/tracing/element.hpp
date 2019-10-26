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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_ELEMENT_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_ELEMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.relational/types/tracing/json.hpp"
#include "dogen.relational/types/tracing/model_id.hpp"
#include "dogen.relational/types/tracing/element_id.hpp"

namespace dogen::relational::tracing {

class element final {
public:
    element() = default;
    element(const element&) = default;
    element(element&&) = default;
    ~element() = default;

public:
    element(
        const dogen::relational::tracing::json& json_content,
        const dogen::relational::tracing::element_id& id,
        const dogen::relational::tracing::model_id& model_id,
        const std::string& qualified_name,
        const std::string& qualified_meta_name);

public:
    const dogen::relational::tracing::json& json_content() const;
    dogen::relational::tracing::json& json_content();
    void json_content(const dogen::relational::tracing::json& v);
    void json_content(const dogen::relational::tracing::json&& v);

    const dogen::relational::tracing::element_id& id() const;
    dogen::relational::tracing::element_id& id();
    void id(const dogen::relational::tracing::element_id& v);
    void id(const dogen::relational::tracing::element_id&& v);

    const dogen::relational::tracing::model_id& model_id() const;
    dogen::relational::tracing::model_id& model_id();
    void model_id(const dogen::relational::tracing::model_id& v);
    void model_id(const dogen::relational::tracing::model_id&& v);

    const std::string& qualified_name() const;
    std::string& qualified_name();
    void qualified_name(const std::string& v);
    void qualified_name(const std::string&& v);

    const std::string& qualified_meta_name() const;
    std::string& qualified_meta_name();
    void qualified_meta_name(const std::string& v);
    void qualified_meta_name(const std::string&& v);

public:
    bool operator==(const element& rhs) const;
    bool operator!=(const element& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element& other) noexcept;
    element& operator=(element other);

private:
    dogen::relational::tracing::json json_content_;
    dogen::relational::tracing::element_id id_;
    dogen::relational::tracing::model_id model_id_;
    std::string qualified_name_;
    std::string qualified_meta_name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::element& lhs,
    dogen::relational::tracing::element& rhs) {
    lhs.swap(rhs);
}

}

#endif
