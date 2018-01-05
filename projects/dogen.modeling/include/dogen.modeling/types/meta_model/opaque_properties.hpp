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
#ifndef DOGEN_MODELING_TYPES_META_MODEL_OPAQUE_PROPERTIES_HPP
#define DOGEN_MODELING_TYPES_META_MODEL_OPAQUE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.modeling/serialization/meta_model/opaque_properties_fwd_ser.hpp"

namespace dogen {
namespace modeling {
namespace meta_model {

/**
 * @brief Base class for any properties that are not known to modeling.
 */
class opaque_properties final {
public:
    opaque_properties() = default;
    opaque_properties(const opaque_properties&) = default;
    opaque_properties(opaque_properties&&) = default;
    ~opaque_properties() = default;
    opaque_properties& operator=(const opaque_properties&) = default;

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::modeling::meta_model::opaque_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::modeling::meta_model::opaque_properties& v, unsigned int version);

public:
    bool operator==(const opaque_properties& rhs) const;
    bool operator!=(const opaque_properties& rhs) const {
        return !this->operator==(rhs);
    }

};

} } }

#endif
