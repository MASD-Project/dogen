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
#ifndef DOGEN_CPP_TYPES_VIEW_MODELS_PROPERTY_VIEW_MODEL_HPP
#define DOGEN_CPP_TYPES_VIEW_MODELS_PROPERTY_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include "dogen/cpp/serialization/view_models/property_view_model_fwd_ser.hpp"
#include "dogen/cpp/types/view_models/nested_type_view_model.hpp"

namespace dogen {
namespace cpp {
namespace view_models {

class property_view_model final {
public:
    property_view_model() = default;
    property_view_model(const property_view_model&) = default;
    property_view_model(property_view_model&&) = default;
    ~property_view_model() = default;

public:
    property_view_model(
        const std::string& name,
        const dogen::cpp::view_models::nested_type_view_model& type,
        const std::string& documentation,
        const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const property_view_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, property_view_model& v, unsigned int version);

public:
    /**
     * @brief Name of the property.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Type of the property.
     */
    /**@{*/
    const dogen::cpp::view_models::nested_type_view_model& type() const;
    dogen::cpp::view_models::nested_type_view_model& type();
    void type(const dogen::cpp::view_models::nested_type_view_model& v);
    void type(const dogen::cpp::view_models::nested_type_view_model&& v);
    /**@}*/

    /**
     * @brief Documentation for the property
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters() const;
    std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters();
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v);
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v);

public:
    bool operator==(const property_view_model& rhs) const;
    bool operator!=(const property_view_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(property_view_model& other) noexcept;
    property_view_model& operator=(property_view_model other);

private:
    std::string name_;
    dogen::cpp::view_models::nested_type_view_model type_;
    std::string documentation_;
    std::vector<std::pair<std::string, std::string> > implementation_specific_parameters_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::view_models::property_view_model& lhs,
    dogen::cpp::view_models::property_view_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
