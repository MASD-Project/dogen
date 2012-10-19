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
    property_view_model() : is_primitive_(false), is_string_like_(false),
                            is_char_like_(false), is_int_like_(false) {}

    explicit property_view_model(const std::string& name)
        : name_(name), is_primitive_(false), is_string_like_(false),
          is_char_like_(false), is_int_like_(false) {}

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
    std::string type() const { return type_; }
    void type(std::string value) { type_ = value; }
    /**@}*/

    /**
     * @brief Representation of the type name which is usable to
     * concatenate to generate identifier names.
     *
     * For example, if the type is unsigned long, its identifiable
     * type is unsigned_long.
     */
    /**@{*/
    std::string identifiable_type() const { return identifiable_type_; }
    void identifiable_type(std::string value) { identifiable_type_ = value; }
    /**@}*/

    /**
     * @brief If true, the meta type of the property is primitive.
     */
    /**@{*/
    bool is_primitive() const { return is_primitive_; }
    void is_primitive(bool value) { is_primitive_ = value; }
    /**@}*/

    /**
     * @brief If true, the type of the property is either string,
     * char or unsigned char.
     */
    /**@{*/
    bool is_string_like() const { return is_string_like_; }
    void is_string_like(bool value) { is_string_like_ = value; }
    /**@}*/

    /**
     * @brief If true, the meta type of the property is either char or
     * unsigned char.
     */
    /**@{*/
    bool is_char_like() const { return is_char_like_; }
    void is_char_like(bool value) { is_char_like_ = value; }
    /**@}*/

    /**
     * @brief If true, the meta type of the property is short, int,
     * long, long long or their unsigned counterparts.
     */
    /**@{*/
    bool is_int_like() const { return is_int_like_; }
    void is_int_like(bool value) { is_int_like_ = value; }
    /**@}*/

private:
    std::string name_;
    std::string type_;
    std::string identifiable_type_;
    bool is_primitive_;
    bool is_string_like_;
    bool is_char_like_;
    bool is_int_like_;
};

} } } } }

#endif
