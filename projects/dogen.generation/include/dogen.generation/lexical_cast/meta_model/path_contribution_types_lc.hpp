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
#ifndef DOGEN_GENERATION_LEXICAL_CAST_META_MODEL_PATH_CONTRIBUTION_TYPES_LC_HPP
#define DOGEN_GENERATION_LEXICAL_CAST_META_MODEL_PATH_CONTRIBUTION_TYPES_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.generation/types/meta_model/path_contribution_types.hpp"

namespace boost {

template<>
std::string lexical_cast(const dogen::generation::meta_model::path_contribution_types& v) {
    using dogen::generation::meta_model::path_contribution_types;

    switch (v) {
    case path_contribution_types::invalid:
        return "path_contribution_types::invalid";
    case path_contribution_types::none:
        return "path_contribution_types::none";
    case path_contribution_types::as_folders:
        return "path_contribution_types::as_folders";
    case path_contribution_types::as_path_components:
        return "path_contribution_types::as_path_components";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
dogen::generation::meta_model::path_contribution_types lexical_cast(const std::string & s) {
    using dogen::generation::meta_model::path_contribution_types;

    if (s == "invalid" || s == "path_contribution_types::invalid")
        return path_contribution_types::invalid;
    if (s == "none" || s == "path_contribution_types::none")
        return path_contribution_types::none;
    if (s == "as_folders" || s == "path_contribution_types::as_folders")
        return path_contribution_types::as_folders;
    if (s == "as_path_components" || s == "path_contribution_types::as_path_components")
        return path_contribution_types::as_path_components;
    throw boost::bad_lexical_cast();
}

}

#endif
