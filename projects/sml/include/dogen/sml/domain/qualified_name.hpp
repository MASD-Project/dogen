/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_SML_DOMAIN_QUALIFIED_NAME_HPP
#define DOGEN_SML_DOMAIN_QUALIFIED_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen/sml/domain/meta_types.hpp"

namespace dogen {
namespace sml {

class qualified_name_serializer;

class qualified_name {
public:
    qualified_name(const qualified_name&) = default;
    ~qualified_name() = default;
    qualified_name(qualified_name&&) = default;
    qualified_name& operator=(const qualified_name&) = default;

private:
    friend class qualified_name_serializer;

public:
    qualified_name() : meta_type_(meta_types::invalid) { }

    qualified_name(std::string model_name,
        std::list<std::string> external_package_path,
        std::list<std::string> package_path,
        std::string type_name,
        meta_types meta_type) :
        model_name_(model_name),
        external_package_path_(external_package_path),
        package_path_(package_path),
        type_name_(type_name),
        meta_type_(meta_type) { }

public:
    /**
     * @brief Model to which the type belongs to.
     */
    std::string model_name() const { return(model_name_); }
    void model_name(std::string value) { model_name_ = value; }

    /**
     * @brief Path of packages that contain this model.
     */
    std::list<std::string> external_package_path() const {
        return(external_package_path_);
    }
    void external_package_path(std::list<std::string> value) {
        external_package_path_ = value;
    }

    /**
     * @brief Path of packages that contain this type.
     */
    std::list<std::string> package_path() const {
        return(package_path_);
    }
    void package_path(std::list<std::string> value) { package_path_ = value; }

    /**
     * @brief Non-qualified type name.
     */
    std::string type_name() const { return(type_name_); }
    void type_name(const std::string& value) { type_name_ = value; }

    /**
     * @brief Type of the type (e.g. its meta-type).
     */
    meta_types meta_type() const { return(meta_type_); }
    void meta_type(const meta_types& value) { meta_type_ = value; }

public:
    void to_stream(std::ostream& stream) const;

public:
    bool operator==(const qualified_name& rhs) const;

    bool operator!=(const qualified_name& rhs) const {
        return(!this->operator==(rhs));
    }

private:
    std::string model_name_;
    std::list<std::string> external_package_path_;
    std::list<std::string> package_path_;
    std::string type_name_;
    meta_types meta_type_;
};

} }

#endif
