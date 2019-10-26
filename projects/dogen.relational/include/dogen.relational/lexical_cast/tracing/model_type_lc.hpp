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
#ifndef DOGEN_RELATIONAL_LEXICAL_CAST_TRACING_MODEL_TYPE_LC_HPP
#define DOGEN_RELATIONAL_LEXICAL_CAST_TRACING_MODEL_TYPE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.relational/types/tracing/model_type.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::relational::tracing::model_type& v) {
    using dogen::relational::tracing::model_type;

    switch (v) {
    case model_type::invalid:
        return "model_type::invalid";
    case model_type::injection_json:
        return "model_type::injection_json";
    case model_type::injection_dia:
        return "model_type::injection_dia";
    case model_type::assets:
        return "model_type::assets";
    case model_type::generation:
        return "model_type::generation";
    case model_type::extraction:
        return "model_type::extraction";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::relational::tracing::model_type lexical_cast(const std::string & s) {
    using dogen::relational::tracing::model_type;

    if (s == "invalid" || s == "model_type::invalid")
        return model_type::invalid;
    if (s == "injection_json" || s == "model_type::injection_json")
        return model_type::injection_json;
    if (s == "injection_dia" || s == "model_type::injection_dia")
        return model_type::injection_dia;
    if (s == "assets" || s == "model_type::assets")
        return model_type::assets;
    if (s == "generation" || s == "model_type::generation")
        return model_type::generation;
    if (s == "extraction" || s == "model_type::extraction")
        return model_type::extraction;
    throw boost::bad_lexical_cast();
}

}

#endif
