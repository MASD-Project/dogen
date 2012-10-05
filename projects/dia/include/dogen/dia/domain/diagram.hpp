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
#ifndef DOGEN_DIA_DOMAIN_DIAGRAM_HPP
#define DOGEN_DIA_DOMAIN_DIAGRAM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include "dogen/dia/domain/diagram_data.hpp"
#include "dogen/dia/domain/layer.hpp"

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class diagram_serializer; } }

/**
 * @brief Represents a diagram in Dia.
 */
class diagram {
public:
    diagram() = default;
    diagram(const diagram&) = default;
    ~diagram() = default;
    diagram(diagram&&) = default;
    diagram& operator=(const diagram&) = default;

private:
    friend class dogen::dia::serialization::detail::diagram_serializer;

public:
    diagram(dogen::dia::diagram_data diagram_data,
        std::vector<dogen::dia::layer> layers) :
        diagram_data_(diagram_data), layers_(layers) { }

    /**
     * @brief Basic diagram definitions.
     */
    /**@{*/
    dogen::dia::diagram_data diagram_data() const {
        return(diagram_data_);
    }

    void diagram_data(dogen::dia::diagram_data value) {
        diagram_data_ = value;
    }
    /**@}*/

    /**
     * @brief Visual layers on the diagram.
     */
    /**@{*/
    std::vector<dogen::dia::layer> layers() const { return(layers_); }
    void layers(std::vector<dogen::dia::layer> value) {
        layers_ = value;
    }
    /**@}*/

public:
    bool operator==(const dogen::dia::diagram& value) const;

    bool operator!=(const dogen::dia::diagram& value) const {
        return(!this->operator==(value));
    }

private:
    dogen::dia::diagram_data diagram_data_;
    std::vector<dogen::dia::layer> layers_;
};

} }

#endif
