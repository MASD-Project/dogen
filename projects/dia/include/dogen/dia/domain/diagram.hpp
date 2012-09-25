/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
