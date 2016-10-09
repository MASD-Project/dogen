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
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"
#include "dogen/quilt.cpp/types/formattables/aspect_configuration.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class aspect_expander {
private:
    struct field_definitions {
        dynamic::field_definition requires_manual_default_constructor;
        dynamic::field_definition requires_manual_move_constructor;
        dynamic::field_definition requires_stream_manipulators;
    };

    friend std::ostream& operator<<(std::ostream& s,
        const field_definitions& v);

    field_definitions
    make_field_definitions(const dynamic::repository& drp) const;

    boost::optional<aspect_configuration> make_aspect_configuration(
        const field_definitions& fds, const dynamic::object& o) const;

private:
    typedef std::unordered_map<std::string, aspect_configuration>
    aspect_configurations_type;

    aspect_configurations_type
    obtain_aspect_configurations(const dynamic::repository& drp,
        const std::unordered_map<std::string, formattable>& formattables) const;

private:
    void walk_name_tree(const yarn::name_tree& nt, const bool is_top_level,
        const aspect_configurations_type& acs, aspect_configuration& ac) const;

    aspect_configuration compute_aspect_configuration(
        const aspect_configurations_type& acs,
        const std::list<yarn::attribute>& attr) const;

    void populate_aspect_configuration(
        const aspect_configurations_type& acs,
        std::unordered_map<std::string, formattable>& formattables) const;

public:
    void expand(const dynamic::repository& drp, model& fm) const;
};

} } } }

#endif
