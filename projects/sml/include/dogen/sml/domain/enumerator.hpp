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
#ifndef DOGEN_SML_DOMAIN_ENUMERATOR_HPP
#define DOGEN_SML_DOMAIN_ENUMERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace sml {

class enumerator_serializer;

class enumerator {
public:
    enumerator() = default;
    enumerator(const enumerator&) = default;
    ~enumerator() = default;
    enumerator(enumerator&&) = default;
    enumerator& operator=(const enumerator&) = default;

private:
    friend class enumerator_serializer;

public:
    enumerator(const std::string& name, const std::string& v,
        const std::string& documentation)
        : name_(name), value_(v), documentation_(documentation) { }

public:
    /**
     * @brief Qualified name for the type.
     */
    /**@{*/
    std::string name() const { return name_; }
    void name(const std::string& value) { name_ = value; }
    /**@}*/

    /**
     * @brief Value for the enumerator. It must be an instance of the
     * type defined in the enumeration.
     */
    /**@{*/
    std::string value() const { return value_; }
    void value(bool v) { value_ = v; }
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
    bool operator==(const enumerator& rhs) const;

    bool operator!=(const enumerator& rhs) const {
        return(!this->operator==(rhs));
    }

private:
    std::string name_;
    std::string value_;
    std::string documentation_;
};

} }

#endif
