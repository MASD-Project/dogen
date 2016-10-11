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

#include <list>
#include <string>
#include <unordered_map>
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/repository.hpp"
#include "dogen/annotations/types/type.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"
#include "dogen/quilt.cpp/types/formattables/aspect_properties.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class aspect_expander {
private:
    struct type_group {
        annotations::type requires_manual_default_constructor;
        annotations::type requires_manual_move_constructor;
        annotations::type requires_stream_manipulators;
    };

    friend std::ostream& operator<<(std::ostream& s, const type_group& v);

    type_group make_type_group(const annotations::type_repository& atrp) const;

    boost::optional<aspect_properties> make_aspect_properties(
        const type_group& tg, const annotations::annotation& a) const;

private:
    typedef std::unordered_map<std::string, aspect_properties>
    aspect_properties_type;

    aspect_properties_type
    obtain_aspect_properties(const annotations::type_repository& atrp,
        const std::unordered_map<std::string, formattable>& formattables) const;

private:
    void walk_name_tree(const yarn::name_tree& nt, const bool is_top_level,
        const aspect_properties_type& element_aps, aspect_properties& ac) const;

    aspect_properties compute_aspect_properties(
        const aspect_properties_type& element_aps,
        const std::list<yarn::attribute>& attr) const;

    void populate_aspect_properties(
        const aspect_properties_type& element_aps,
        std::unordered_map<std::string, formattable>& formattables) const;

public:
    void expand(const annotations::type_repository& atrp, model& fm) const;
};

} } } }

#endif
