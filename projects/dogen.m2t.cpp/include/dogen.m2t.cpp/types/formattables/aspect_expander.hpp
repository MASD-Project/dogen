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
#ifndef DOGEN_M2T_CPP_TYPES_FORMATTABLES_ASPECT_EXPANDER_HPP
#define DOGEN_M2T_CPP_TYPES_FORMATTABLES_ASPECT_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.logical/types/entities/name_tree.hpp"
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.m2t.cpp/types/formattables/formattable.hpp"
#include "dogen.m2t.cpp/types/formattables/aspect_properties.hpp"
#include "dogen.m2t.cpp/types/formattables/model.hpp"

namespace dogen::m2t::cpp::formattables {

class aspect_expander {
private:
    struct feature_group {
        variability::entities::feature requires_manual_default_constructor;
        variability::entities::feature requires_manual_move_constructor;
        variability::entities::feature requires_stream_manipulators;
    };

    feature_group make_feature_group(
        const variability::entities::feature_model& fm) const;

    boost::optional<aspect_properties>
    make_aspect_properties(const feature_group& fg,
        const variability::entities::configuration& cfg) const;

private:
    typedef std::unordered_map<std::string, aspect_properties>
    aspect_properties_type;

    aspect_properties_type
    obtain_aspect_properties(
        const variability::entities::feature_model& feature_model,
        const std::unordered_map<std::string, formattable>& formattables) const;

private:
    void walk_name_tree(const logical::entities::name_tree& nt,
        const bool is_top_level, const aspect_properties_type& element_aps,
        aspect_properties& ap) const;

    aspect_properties compute_aspect_properties(
        const aspect_properties_type& element_aps,
        const std::list<logical::entities::attribute>& attrs) const;

    void populate_aspect_properties(const std::string& element_id,
        const aspect_properties_type& element_aps,
        formattable& formattable) const;

    void populate_aspect_properties(
        const aspect_properties_type& element_aps,
        std::unordered_map<std::string, formattable>& formattables) const;

public:
    void expand(const variability::entities::feature_model& feature_model,
        model& fm) const;
};

}

#endif
