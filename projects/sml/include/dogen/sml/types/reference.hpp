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
#ifndef DOGEN_SML_TYPES_REFERENCE_HPP
#define DOGEN_SML_TYPES_REFERENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/sml/serialization/reference_fwd_ser.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents a reference to a model.
 */
class reference final {
public:
    reference(const reference&) = default;
    reference(reference&&) = default;
    ~reference() = default;

public:
    reference();

public:
    reference(
        const std::string& model_name,
        const std::list<std::string>& external_module_path,
        const bool is_system);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const reference& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, reference& v, unsigned int version);

public:
    /**
     * @brief Model which we depend on.
     */
    /**@{*/
    const std::string& model_name() const;
    std::string& model_name();
    void model_name(const std::string& v);
    void model_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Path of modules that contain the dependent model.
     */
    /**@{*/
    const std::list<std::string>& external_module_path() const;
    std::list<std::string>& external_module_path();
    void external_module_path(const std::list<std::string>& v);
    void external_module_path(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief If true, the dependent model is a system model.
     */
    /**@{*/
    bool is_system() const;
    void is_system(const bool v);
    /**@}*/

public:
    bool operator==(const reference& rhs) const;
    bool operator!=(const reference& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(reference& other) noexcept;
    reference& operator=(reference other);

private:
    std::string model_name_;
    std::list<std::string> external_module_path_;
    bool is_system_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::reference& lhs,
    dogen::sml::reference& rhs) {
    lhs.swap(rhs);
}

}

#endif
