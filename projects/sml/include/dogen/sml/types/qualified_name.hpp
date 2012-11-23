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
#ifndef DOGEN_SML_TYPES_QUALIFIED_NAME_HPP
#define DOGEN_SML_TYPES_QUALIFIED_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/sml/serialization/qualified_name_fwd_ser.hpp"
#include "dogen/sml/types/meta_types.hpp"

namespace dogen {
namespace sml {

/*
 * @brief Represents a "URL" to a type within SML.
 */
class qualified_name final {
public:
    qualified_name(const qualified_name&) = default;
    qualified_name(qualified_name&&) = default;
    ~qualified_name() = default;

public:
    qualified_name();

public:
    qualified_name(
        const std::string& model_name,
        const std::list<std::string>& external_package_path,
        const std::list<std::string>& package_path,
        const std::string& type_name,
        const dogen::sml::meta_types& meta_type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const qualified_name& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, qualified_name& v, unsigned int version);

public:
    /*
     * @brief Model to which the type belongs to.
     */
    /**@{*/
    std::string model_name() const {
        return model_name_;
    }

    void model_name(const std::string& v) {
        model_name_ = v;
    }
    /**@}*/

    /*
     * @brief Path of packages that contain the model from where the type came from.
     */
    /**@{*/
    std::list<std::string> external_package_path() const {
        return external_package_path_;
    }

    void external_package_path(const std::list<std::string>& v) {
        external_package_path_ = v;
    }
    /**@}*/

    /*
     * @brief Path of packages that contain this type.
     */
    /**@{*/
    std::list<std::string> package_path() const {
        return package_path_;
    }

    void package_path(const std::list<std::string>& v) {
        package_path_ = v;
    }
    /**@}*/

    /*
     * @brief Non-qualified type name.
     */
    /**@{*/
    std::string type_name() const {
        return type_name_;
    }

    void type_name(const std::string& v) {
        type_name_ = v;
    }
    /**@}*/

    /*
     * @brief Type of the type (e.g. its meta-type).
     *
     * This is only needed because we don't have a type base class.
     */
    /**@{*/
    dogen::sml::meta_types meta_type() const {
        return meta_type_;
    }

    void meta_type(const dogen::sml::meta_types& v) {
        meta_type_ = v;
    }
    /**@}*/

public:
    bool operator==(const qualified_name& rhs) const;
    bool operator!=(const qualified_name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(qualified_name& other) noexcept;
    qualified_name& operator=(qualified_name other);

private:
    std::string model_name_;
    std::list<std::string> external_package_path_;
    std::list<std::string> package_path_;
    std::string type_name_;
    dogen::sml::meta_types meta_type_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::qualified_name& lhs,
    dogen::sml::qualified_name& rhs) {
    lhs.swap(rhs);
}

}

#endif
