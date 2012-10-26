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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_ENUMERATION_VIEW_MODEL_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_ENUMERATION_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include <boost/tuple/tuple.hpp>
#include "dogen/generator/backends/cpp/view_models/enumerator_view_model.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace view_models {

class enumeration_view_model {
public:
    enumeration_view_model() = default;
    enumeration_view_model(const enumeration_view_model&) = default;
    ~enumeration_view_model() = default;
    enumeration_view_model(enumeration_view_model&&) = default;
    enumeration_view_model& operator=(const enumeration_view_model&) = default;

public:
    explicit enumeration_view_model(const std::string& name)
        : name_(name) { }

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
    void name(const std::string& value) { name_ = value; }
    /**@}*/

    /**
     * @brief Properties of the class itself (e.g. excludes inherited
     * properties).
     */
    /**@{*/
    std::list<enumerator_view_model> enumerators() const {
        return enumerators_;
    }
    void enumerators(std::list<enumerator_view_model> v) {
        enumerators_ = v;
    }
    /**@}*/

    /**
     * @brief Documentation for the property
     */
    /**@{*/
    std::string documentation() const { return documentation_; }
    void documentation(const std::string& v) { documentation_ = v; }
    /**@}*/

private:
    std::list<std::string> namespaces_;
    std::list<enumerator_view_model> enumerators_;
    std::string name_;
    std::string documentation_;
};

} } } } }

#endif
