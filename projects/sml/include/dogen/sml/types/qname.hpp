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
#ifndef DOGEN_SML_TYPES_QNAME_HPP
#define DOGEN_SML_TYPES_QNAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/sml/serialization/qname_fwd_ser.hpp"
#include "dogen/sml/types/meta_types.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents a "URL" to a type within SML.
 */
class qname final {
public:
    qname(const qname&) = default;
    qname(qname&&) = default;
    ~qname() = default;

public:
    qname();

public:
    qname(
        const std::string& model_name,
        const std::list<std::string>& external_module_path,
        const std::list<std::string>& module_path,
        const std::string& type_name,
        const dogen::sml::meta_types& meta_type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const qname& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, qname& v, unsigned int version);

public:
    /**
     * @brief Model to which the type belongs to.
     */
    /**@{*/
    const std::string& model_name() const;
    std::string& model_name();
    void model_name(const std::string& v);
    void model_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Path of modules that contain the model from where the type came from.
     */
    /**@{*/
    const std::list<std::string>& external_module_path() const;
    std::list<std::string>& external_module_path();
    void external_module_path(const std::list<std::string>& v);
    void external_module_path(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Path of modules that contain this type.
     */
    /**@{*/
    const std::list<std::string>& module_path() const;
    std::list<std::string>& module_path();
    void module_path(const std::list<std::string>& v);
    void module_path(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Non-qualified type name.
     */
    /**@{*/
    const std::string& type_name() const;
    std::string& type_name();
    void type_name(const std::string& v);
    void type_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Type of the type (e.g. its meta-type).
     *
     * This is only needed because we don't have a type base class.
     */
    /**@{*/
    dogen::sml::meta_types meta_type() const;
    void meta_type(const dogen::sml::meta_types& v);
    /**@}*/

public:
    bool operator==(const qname& rhs) const;
    bool operator!=(const qname& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(qname& other) noexcept;
    qname& operator=(qname other);

private:
    std::string model_name_;
    std::list<std::string> external_module_path_;
    std::list<std::string> module_path_;
    std::string type_name_;
    dogen::sml::meta_types meta_type_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::qname& lhs,
    dogen::sml::qname& rhs) {
    lhs.swap(rhs);
}

}

#endif
