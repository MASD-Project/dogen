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
#ifndef DOGEN_SML_TYPES_PACKAGE_HPP
#define DOGEN_SML_TYPES_PACKAGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/sml/serialization/package_fwd_ser.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

/*
 * @brief Groups types, and provides a namespace for the grouped types.
 */
class package final {
public:
    package() = default;
    package(const package&) = default;
    package(package&&) = default;
    ~package() = default;

public:
    package(
        const dogen::sml::qname& name,
        const std::string& documentation);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const package& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, package& v, unsigned int version);

public:
    /*
     * @brief Qualified name for the package.
     */
    /**@{*/
    const dogen::sml::qname& name() const;
    dogen::sml::qname& name();
    void name(const dogen::sml::qname& v);
    void name(const dogen::sml::qname&& v);
    /**@}*/

    /*
     * @brief Doxygen documentation for the package.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

public:
    bool operator==(const package& rhs) const;
    bool operator!=(const package& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(package& other) noexcept;
    package& operator=(package other);

private:
    dogen::sml::qname name_;
    std::string documentation_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::package& lhs,
    dogen::sml::package& rhs) {
    lhs.swap(rhs);
}

}

#endif
