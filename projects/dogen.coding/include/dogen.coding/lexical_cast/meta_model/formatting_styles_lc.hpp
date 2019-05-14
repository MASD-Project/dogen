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
#ifndef DOGEN_CODING_LEXICAL_CAST_META_MODEL_FORMATTING_STYLES_LC_HPP
#define DOGEN_CODING_LEXICAL_CAST_META_MODEL_FORMATTING_STYLES_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.coding/types/meta_model/formatting_styles.hpp"

namespace boost {

template<>
std::string lexical_cast(const dogen::coding::meta_model::formatting_styles& v) {
    using dogen::coding::meta_model::formatting_styles;

    switch (v) {
    case formatting_styles::invalid:
        return "formatting_styles::invalid";
    case formatting_styles::stock:
        return "formatting_styles::stock";
    case formatting_styles::wale:
        return "formatting_styles::wale";
    case formatting_styles::stitch:
        return "formatting_styles::stitch";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
dogen::coding::meta_model::formatting_styles lexical_cast(const std::string & s) {
    using dogen::coding::meta_model::formatting_styles;

    if (s == "invalid" || s == "formatting_styles::invalid")
        return formatting_styles::invalid;
    if (s == "stock" || s == "formatting_styles::stock")
        return formatting_styles::stock;
    if (s == "wale" || s == "formatting_styles::wale")
        return formatting_styles::wale;
    if (s == "stitch" || s == "formatting_styles::stitch")
        return formatting_styles::stitch;
    throw boost::bad_lexical_cast();
}

}

#endif
