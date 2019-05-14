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
#ifndef DOGEN_GENERATION_LEXICAL_CAST_META_MODEL_DIRECTORY_STRUCTURE_STYLES_LC_HPP
#define DOGEN_GENERATION_LEXICAL_CAST_META_MODEL_DIRECTORY_STRUCTURE_STYLES_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.generation/types/meta_model/directory_structure_styles.hpp"

namespace boost {

template<>
inline std::string lexical_cast(const dogen::generation::meta_model::directory_structure_styles& v) {
    using dogen::generation::meta_model::directory_structure_styles;

    switch (v) {
    case directory_structure_styles::invalid:
        return "directory_structure_styles::invalid";
    case directory_structure_styles::structured:
        return "directory_structure_styles::structured";
    case directory_structure_styles::completely_flat:
        return "directory_structure_styles::completely_flat";
    case directory_structure_styles::flatten_facets:
        return "directory_structure_styles::flatten_facets";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
inline dogen::generation::meta_model::directory_structure_styles lexical_cast(const std::string & s) {
    using dogen::generation::meta_model::directory_structure_styles;

    if (s == "invalid" || s == "directory_structure_styles::invalid")
        return directory_structure_styles::invalid;
    if (s == "structured" || s == "directory_structure_styles::structured")
        return directory_structure_styles::structured;
    if (s == "completely_flat" || s == "directory_structure_styles::completely_flat")
        return directory_structure_styles::completely_flat;
    if (s == "flatten_facets" || s == "directory_structure_styles::flatten_facets")
        return directory_structure_styles::flatten_facets;
    throw boost::bad_lexical_cast();
}

}

#endif
