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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_SML_DOMAIN_PACKAGE_HPP
#define DOGEN_SML_DOMAIN_PACKAGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/shared_ptr.hpp>
#include "dogen/sml/domain/qualified_name.hpp"

namespace dogen {
namespace sml {

class package_serializer;

/**
 * @brief Represents a namespace.
 */
class package {
public:
    package() = default;
    package(const package&) = default;
    ~package() = default;
    package(package&&) = default;
    package& operator=(const package&) = default;

public:
    friend class package_serializer;

public:
    /**
     * @brief Initialises the structure.
     *
     * @param name Identifier for the package.
     */
    package(dogen::sml::qualified_name name) : name_(name) { }

public:
    /**
     * @brief Identifier for the package.
     */
    /**@{*/
    dogen::sml::qualified_name name() const { return name_; }
    void name(dogen::sml::qualified_name name) { name_ = name; }
    /**@}*/

public:
    void to_stream(std::ostream& stream) const;

public:
    bool operator==(const package& rhs) const;

    bool operator!=(const package& rhs) const {
        return(!this->operator==(rhs));
    }

private:
    dogen::sml::qualified_name name_;
};

} }

#endif
