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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_CLASS_VIEW_MODEL_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_CLASS_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/tuple/tuple.hpp>
#include "dogen/generator/backends/cpp/view_models/property_view_model.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace view_models {

class class_view_model {
public:
    class_view_model(const class_view_model&) = default;
    ~class_view_model() = default;
    class_view_model(class_view_model&&) = default;
    class_view_model& operator=(const class_view_model&) = default;

public:
    class_view_model() : has_primitive_properties_(false),
                         has_boolean_properties_(false) {}

    explicit class_view_model(std::string name)
        : name_(name),
          has_primitive_properties_(false),
          has_boolean_properties_(false) { }

public:
    /**
     * @brief List of all namespaces containing the class.
     */
    /**@{*/
    std::list<std::string> namespaces() const { return namespaces_; }
    void namespaces(const std::list<std::string>& value) {
        namespaces_ = value;
    }
    /**@}*/

    /**
     * @brief Name of the class.
     */
    /**@{*/
    std::string name() const { return name_; }
    void name(std::string value) { name_ = value; }
    /**@}*/

    /**
     * @brief Properties of the class.
     */
    /**@{*/
    std::list<property_view_model> properties() const {
        return properties_;
    }
    void properties(std::list<property_view_model> value) {
        properties_ = value;
    }
    /**@}*/

    /**
     * @brief True if the class has at least one property which is a
     * primitive, false otherwise.
     */
    /**@{*/
    bool has_primitive_properties() const {
        return(has_primitive_properties_);
    }
    void has_primitive_properties(bool value) {
        has_primitive_properties_ = value;
    }
    /**@}*/

    /**
     * @brief True if the class has at least one boolean property,
     * false otherwise.
     */
    /**@{*/
    bool has_boolean_properties() const {
        return(has_boolean_properties_);
    }
    void has_boolean_properties(bool value) {
        has_boolean_properties_ = value;
    }
    /**@}*/

    /**
     * @brief Name to be used in the context of database operations.
     */
    /**@{*/
    std::string database_name() const { return database_name_; }
    void database_name(std::string value) { database_name_ = value; }
    /**@}*/

    /**
     * @brief Name of the database schema to which database entities
     * belong to.
     */
    /**@{*/
    std::string schema_name() const { return schema_name_; }
    void schema_name(std::string value) { schema_name_ = value; }
    /**@}*/

private:
    std::list<std::string> namespaces_;
    std::list<property_view_model> properties_;
    std::string name_;
    bool has_primitive_properties_;
    bool has_boolean_properties_;
    std::string database_name_;
    std::string schema_name_;
};

} } } } }

#endif
