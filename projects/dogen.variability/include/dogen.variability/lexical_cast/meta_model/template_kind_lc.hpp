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
#ifndef DOGEN_VARIABILITY_LEXICAL_CAST_META_MODEL_TEMPLATE_KIND_LC_HPP
#define DOGEN_VARIABILITY_LEXICAL_CAST_META_MODEL_TEMPLATE_KIND_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.variability/types/meta_model/template_kind.hpp"

namespace boost {

template<>
std::string lexical_cast(const dogen::variability::meta_model::template_kind& v) {
    using dogen::variability::meta_model::template_kind;

    switch (v) {
    case template_kind::invalid:
        return "template_kind::invalid";
    case template_kind::instance:
        return "template_kind::instance";
    case template_kind::recursive_template:
        return "template_kind::recursive_template";
    case template_kind::backend_template:
        return "template_kind::backend_template";
    case template_kind::facet_template:
        return "template_kind::facet_template";
    case template_kind::archetype_template:
        return "template_kind::archetype_template";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
dogen::variability::meta_model::template_kind lexical_cast(const std::string & s) {
    using dogen::variability::meta_model::template_kind;

    if (s == "invalid" || s == "template_kind::invalid")
        return template_kind::invalid;
    if (s == "instance" || s == "template_kind::instance")
        return template_kind::instance;
    if (s == "recursive_template" || s == "template_kind::recursive_template")
        return template_kind::recursive_template;
    if (s == "backend_template" || s == "template_kind::backend_template")
        return template_kind::backend_template;
    if (s == "facet_template" || s == "template_kind::facet_template")
        return template_kind::facet_template;
    if (s == "archetype_template" || s == "template_kind::archetype_template")
        return template_kind::archetype_template;
    throw boost::bad_lexical_cast();
}

}

#endif
