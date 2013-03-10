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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_PROPERTY_VIEW_MODEL_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_PROPERTY_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <string>
#include <utility>
#include "dogen/generator/backends/cpp/view_models/nested_type_view_model.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace view_models {

class property_view_model {
public:
    property_view_model() = default;
    property_view_model(const property_view_model&) = default;
    ~property_view_model() = default;
    property_view_model(property_view_model&&) = default;
    property_view_model& operator=(const property_view_model&) = default;

public:
    explicit property_view_model(const std::string& name) : name_(name) {}

public:
    /**
     * @brief Name of the property.
     */
    /**@{*/
    std::string name() const { return name_; }
    void name(const std::string& value) { name_ = value; }
    /**@}*/

    /**
     * @brief Type of the property.
     */
    /**@{*/
    nested_type_view_model type() const { return type_; }
    void type(nested_type_view_model value) { type_ = value; }
    /**@}*/

    /**
     * @brief Documentation for the property
     */
    /**@{*/
    std::string documentation() const { return documentation_; }
    void documentation(const std::string& v) { documentation_ = v; }
    /**@}*/

    /*
     * @brief Parameters associated with the pod.
     */
    /**@{*/
    std::vector<std::pair<std::string, std::string> >
    implementation_specific_parameters() const {
        return implementation_specific_parameters_;
    }
    void implementation_specific_parameters(
        const std::vector<std::pair<std::string, std::string> >& v) {
        implementation_specific_parameters_ = v;
    }
    /**@}*/

private:
    std::string name_;
    nested_type_view_model type_;
    std::string documentation_;
    std::vector<std::pair<std::string, std::string> >
    implementation_specific_parameters_;
};

} } } } }

#endif
