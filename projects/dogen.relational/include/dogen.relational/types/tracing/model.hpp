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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_MODEL_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen.relational/types/tracing/xml.hpp"
#include "dogen.relational/types/tracing/json.hpp"
#include "dogen.relational/types/tracing/model_id.hpp"
#include "dogen.relational/types/tracing/model_type.hpp"
#include "dogen.relational/types/tracing/model_set_id.hpp"

namespace dogen::relational::tracing {

class model final {
public:
    model(const model&) = default;
    ~model() = default;

public:
    model();

public:
    model(model&& rhs);

public:
    model(
        const dogen::relational::tracing::json& json_content,
        const dogen::relational::tracing::xml& xml_content,
        const dogen::relational::tracing::model_id& id,
        const dogen::relational::tracing::model_set_id& model_set_id,
        const std::string& qualified_name,
        const std::string& qualified_meta_name,
        const dogen::relational::tracing::model_type type,
        const boost::filesystem::path& source_file);

public:
    const dogen::relational::tracing::json& json_content() const;
    dogen::relational::tracing::json& json_content();
    void json_content(const dogen::relational::tracing::json& v);
    void json_content(const dogen::relational::tracing::json&& v);

    const dogen::relational::tracing::xml& xml_content() const;
    dogen::relational::tracing::xml& xml_content();
    void xml_content(const dogen::relational::tracing::xml& v);
    void xml_content(const dogen::relational::tracing::xml&& v);

    const dogen::relational::tracing::model_id& id() const;
    dogen::relational::tracing::model_id& id();
    void id(const dogen::relational::tracing::model_id& v);
    void id(const dogen::relational::tracing::model_id&& v);

    const dogen::relational::tracing::model_set_id& model_set_id() const;
    dogen::relational::tracing::model_set_id& model_set_id();
    void model_set_id(const dogen::relational::tracing::model_set_id& v);
    void model_set_id(const dogen::relational::tracing::model_set_id&& v);

    const std::string& qualified_name() const;
    std::string& qualified_name();
    void qualified_name(const std::string& v);
    void qualified_name(const std::string&& v);

    const std::string& qualified_meta_name() const;
    std::string& qualified_meta_name();
    void qualified_meta_name(const std::string& v);
    void qualified_meta_name(const std::string&& v);

    dogen::relational::tracing::model_type type() const;
    void type(const dogen::relational::tracing::model_type v);

    const boost::filesystem::path& source_file() const;
    boost::filesystem::path& source_file();
    void source_file(const boost::filesystem::path& v);
    void source_file(const boost::filesystem::path&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    dogen::relational::tracing::json json_content_;
    dogen::relational::tracing::xml xml_content_;
    dogen::relational::tracing::model_id id_;
    dogen::relational::tracing::model_set_id model_set_id_;
    std::string qualified_name_;
    std::string qualified_meta_name_;
    dogen::relational::tracing::model_type type_;
    boost::filesystem::path source_file_;
};

}

namespace std {

template<>
inline void swap(
    dogen::relational::tracing::model& lhs,
    dogen::relational::tracing::model& rhs) {
    lhs.swap(rhs);
}

}

#endif
