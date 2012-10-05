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
#ifndef DOGEN_DIA_DOMAIN_DIAGRAM_DATA_HPP
#define DOGEN_DIA_DOMAIN_DIAGRAM_DATA_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include "dogen/dia/domain/attribute.hpp"

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class diagram_data_serializer; } }

class diagram_data {
public:
    diagram_data() = default;
    diagram_data(const diagram_data&) = default;
    ~diagram_data() = default;
    diagram_data(diagram_data&&) = default;
    diagram_data& operator=(const diagram_data&) = default;

private:
    friend class dogen::dia::serialization::detail::diagram_data_serializer;

public:
    explicit diagram_data(std::vector<attribute> attributes)
        : attributes_(attributes) { }

    /**
     * @brief All attributes associated with the diagram data.
     */
    /**@{*/
    std::vector<attribute> attributes() const { return(attributes_); }
    void attributes(std::vector<attribute> value) {
        attributes_ = value;
    }
    /**@}*/

public:
    bool operator==(const diagram_data& value) const;

    bool operator!=(const diagram_data& value) const {
        return(!this->operator==(value));
    }

private:
    std::vector<attribute> attributes_;
};

} }

#endif
