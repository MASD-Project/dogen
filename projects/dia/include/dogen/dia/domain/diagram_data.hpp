/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
