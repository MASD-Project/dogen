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

#include <list>
#include <string>
#include <algorithm>
#include "dogen/sml/serialization/qname_fwd_ser.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents a "URL" to a type within SML.
 */
class qname final {
public:
    qname() = default;
    qname(const qname&) = default;
    qname(qname&&) = default;
    ~qname() = default;

public:
    qname(
        const std::string& model_name,
        const std::list<std::string>& external_module_path,
        const std::list<std::string>& module_path,
        const std::string& simple_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const qname& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, qname& v, unsigned int version);

public:
    /**
     * @brief Model to which the modeling element belongs to.
     */
    /**@{*/
    const std::string& model_name() const;
    std::string& model_name();
    void model_name(const std::string& v);
    void model_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Path of modules that contain the model from where the modeling element
     * came from.
     */
    /**@{*/
    const std::list<std::string>& external_module_path() const;
    std::list<std::string>& external_module_path();
    void external_module_path(const std::list<std::string>& v);
    void external_module_path(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Path of modules that contain this modeling element.
     */
    /**@{*/
    const std::list<std::string>& module_path() const;
    std::list<std::string>& module_path();
    void module_path(const std::list<std::string>& v);
    void module_path(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Non-qualified name of the modeling element.
     */
    /**@{*/
    const std::string& simple_name() const;
    std::string& simple_name();
    void simple_name(const std::string& v);
    void simple_name(const std::string&& v);
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
    std::string simple_name_;
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
