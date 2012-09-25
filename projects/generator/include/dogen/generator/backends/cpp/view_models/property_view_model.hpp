/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
