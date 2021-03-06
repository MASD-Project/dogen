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
#ifndef DOGEN_PHYSICAL_LEXICAL_CAST_ENTITIES_RELATION_STATUS_LC_HPP
#define DOGEN_PHYSICAL_LEXICAL_CAST_ENTITIES_RELATION_STATUS_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.physical/types/entities/relation_status.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::physical::entities::relation_status& v) {
    using dogen::physical::entities::relation_status;

    switch (v) {
    case relation_status::invalid:
        return "relation_status::invalid";
    case relation_status::not_relatable:
        return "relation_status::not_relatable";
    case relation_status::relatable:
        return "relation_status::relatable";
    case relation_status::facet_default:
        return "relation_status::facet_default";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::physical::entities::relation_status lexical_cast(const std::string & s) {
    using dogen::physical::entities::relation_status;

    if (s == "invalid" || s == "relation_status::invalid")
        return relation_status::invalid;
    if (s == "not_relatable" || s == "relation_status::not_relatable")
        return relation_status::not_relatable;
    if (s == "relatable" || s == "relation_status::relatable")
        return relation_status::relatable;
    if (s == "facet_default" || s == "relation_status::facet_default")
        return relation_status::facet_default;
    throw boost::bad_lexical_cast();
}

}

#endif
