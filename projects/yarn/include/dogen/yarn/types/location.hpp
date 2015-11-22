/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_YARN_TYPES_LOCATION_HPP
#define DOGEN_YARN_TYPES_LOCATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/yarn/serialization/location_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Represents a "URL" to a type within a model.
 */
class location final {
public:
    location() = default;
    location(const location&) = default;
    location(location&&) = default;
    ~location() = default;

public:
    location(
        const std::list<std::string>& external_module_path,
        const std::list<std::string>& model_module_path,
        const std::list<std::string>& internal_module_path);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const location& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, location& v, unsigned int version);

public:
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
     * @brief Path related to just the model itself.
     *
     * It is only different from the model name if the model name is composite;
     * that is, if the model name has multiple fields separated by dots, e.g. @ a.b.
     */
    /**@{*/
    const std::list<std::string>& model_module_path() const;
    std::list<std::string>& model_module_path();
    void model_module_path(const std::list<std::string>& v);
    void model_module_path(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Path of modules that contain this modeling element.
     */
    /**@{*/
    const std::list<std::string>& internal_module_path() const;
    std::list<std::string>& internal_module_path();
    void internal_module_path(const std::list<std::string>& v);
    void internal_module_path(const std::list<std::string>&& v);
    /**@}*/

public:
    bool operator==(const location& rhs) const;
    bool operator!=(const location& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(location& other) noexcept;
    location& operator=(location other);

private:
    std::list<std::string> external_module_path_;
    std::list<std::string> model_module_path_;
    std::list<std::string> internal_module_path_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::location& lhs,
    dogen::yarn::location& rhs) {
    lhs.swap(rhs);
}

}

#endif
