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

#include <string>

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace view_models {

class property_view_model {
public:
    property_view_model(const property_view_model&) = default;
    ~property_view_model() = default;
    property_view_model(property_view_model&&) = default;
    property_view_model& operator=(const property_view_model&) = default;

public:
    property_view_model() : is_primitive_(false) {}
    explicit property_view_model(std::string name)
        : name_(name), is_primitive_(false) { }

public:
    /**
     * @brief Name of the property.
     */
    /**@{*/
    std::string name() const { return name_; }
    void name(std::string value) { name_ = value; }
    /**@}*/

    /**
     * @brief Type of the property.
     */
    /**@{*/
    std::string type() const { return type_; }
    void type(std::string value) { type_ = value; }
    /**@}*/

    /**
     * @brief If true, the meta type of the property is primitive.
     */
    /**@{*/
    bool is_primitive() const { return is_primitive_; }
    void is_primitive(bool value) { is_primitive_ = value; }
    /**@}*/


private:
    std::string name_;
    std::string type_;
    bool is_primitive_;
};

} } } } }

#endif
