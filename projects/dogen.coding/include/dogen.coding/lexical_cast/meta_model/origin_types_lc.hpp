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
#ifndef DOGEN_CODING_LEXICAL_CAST_META_MODEL_ORIGIN_TYPES_LC_HPP
#define DOGEN_CODING_LEXICAL_CAST_META_MODEL_ORIGIN_TYPES_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.coding/types/meta_model/origin_types.hpp"

namespace boost {

template<>
std::string lexical_cast(const dogen::coding::meta_model::origin_types& v) {
    using dogen::coding::meta_model::origin_types;

    switch (v) {
    case origin_types::invalid:
        return "origin_types::invalid";
    case origin_types::target:
        return "origin_types::target";
    case origin_types::proxy_reference:
        return "origin_types::proxy_reference";
    case origin_types::non_proxy_reference:
        return "origin_types::non_proxy_reference";
    case origin_types::not_yet_determined:
        return "origin_types::not_yet_determined";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
dogen::coding::meta_model::origin_types lexical_cast(const std::string & s) {
    using dogen::coding::meta_model::origin_types;

    if (s == "invalid" || s == "origin_types::invalid")
        return origin_types::invalid;
    if (s == "target" || s == "origin_types::target")
        return origin_types::target;
    if (s == "proxy_reference" || s == "origin_types::proxy_reference")
        return origin_types::proxy_reference;
    if (s == "non_proxy_reference" || s == "origin_types::non_proxy_reference")
        return origin_types::non_proxy_reference;
    if (s == "not_yet_determined" || s == "origin_types::not_yet_determined")
        return origin_types::not_yet_determined;
    throw boost::bad_lexical_cast();
}

}

#endif
