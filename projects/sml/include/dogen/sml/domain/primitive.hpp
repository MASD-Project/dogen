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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_SML_DOMAIN_PRIMITIVE_HPP
#define DOGEN_SML_DOMAIN_PRIMITIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/sml/domain/qualified_name.hpp"

namespace dogen {
namespace sml {

class primitive_serializer;

class primitive {
public:
    primitive() = default;
    primitive(const primitive&) = default;
    ~primitive() = default;
    primitive(primitive&&) = default;
    primitive& operator=(const primitive&) = default;

private:
    friend class primitive_serializer;

public:
    /**
     * @brief Qualified name for the type.
     */
    /**@{*/
    qualified_name name() const { return name_; }
    void name(qualified_name value) { name_ = value; }
    /**@}*/

public:
    void to_stream(std::ostream& stream) const;

public:
    bool operator==(const primitive& rhs) const;

    bool operator!=(const primitive& rhs) const {
        return(!this->operator==(rhs));
    }

private:
    qualified_name name_;
};

} }

#endif
