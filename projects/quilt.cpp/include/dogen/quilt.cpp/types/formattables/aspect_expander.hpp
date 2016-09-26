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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_ASPECT_EXPANDER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_ASPECT_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"
#include "dogen/quilt.cpp/types/annotations/aspect_annotations.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class aspect_expander {
private:
    typedef std::unordered_map<std::string, annotations::aspect_annotations>
    aspect_annotations_type;

    aspect_annotations_type
    obtain_aspect_annotations(const dynamic::repository& drp,
        const std::unordered_map<std::string, formattable>& formattables) const;

    void walk_name_tree(const yarn::name_tree& nt, const bool is_top_level,
        const aspect_annotations_type& aa, aspect_configuration& ac) const;

    aspect_configuration compute_aspect_configuration(
        const aspect_annotations_type& aa,
        const std::list<yarn::attribute>& attributes) const;

    void populate_aspect_configuration(
        const aspect_annotations_type& aa,
        std::unordered_map<std::string, formattable>& formattables) const;

public:
    void expand(const dynamic::repository& drp,
        std::unordered_map<std::string, formattable>& formattables) const;

};

} } } }

#endif
