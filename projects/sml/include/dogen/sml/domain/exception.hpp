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
#ifndef DOGEN_SML_DOMAIN_EXCEPTION_HPP
#define DOGEN_SML_DOMAIN_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include "dogen/sml/domain/qualified_name.hpp"

namespace dogen {
namespace sml {

class exception_serializer;

class exception {
public:
    exception(const exception&) = default;
    ~exception() = default;
    exception(exception&&) = default;
    exception& operator=(const exception&) = default;

private:
    friend class exception_serializer;

public:
    exception() : generate_(false) { }
    exception(const qualified_name& name, const bool generate,
        const std::string& documentation)
        : name_(name), generate_(generate), documentation_(documentation) { }

public:
    /**
     * @brief Qualified name for the type.
     */
    /**@{*/
    qualified_name name() const { return name_; }
    void name(qualified_name value) { name_ = value; }
    /**@}*/

    /**
     * @brief Returns true if this type is to be code generated, false
     * otherwise.
     */
    /**@{*/
    bool generate() const { return generate_; }
    void generate(bool value) { generate_ = value; }
    /**@}*/

    /**
     * @brief Doxygen documentation for the type.
     */
    /**@{*/
    std::string documentation() const { return documentation_; }
    void documentation(const std::string& value) { documentation_ = value; }
    /**@}*/

public:
    void to_stream(std::ostream& stream) const;

public:
    bool operator==(const exception& rhs) const;

    bool operator!=(const exception& rhs) const {
        return(!this->operator==(rhs));
    }

private:
    qualified_name name_;
    bool generate_;
    std::string documentation_;
};

} }

#endif
