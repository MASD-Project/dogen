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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_ASPECT_EXPANDER_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_ASPECT_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include <boost/optional.hpp>
#include "masd.dogen.variability/types/type.hpp"
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.coding/types/meta_model/name_tree.hpp"
#include "masd.dogen.coding/types/meta_model/attribute.hpp"
#include "masd.dogen.generation.cpp/types/formattables/formattable.hpp"
#include "masd.dogen.generation.cpp/types/formattables/aspect_properties.hpp"
#include "masd.dogen.generation.cpp/types/formattables/model.hpp"

namespace masd::dogen::generation::cpp::formattables {

class aspect_expander {
private:
    struct type_group {
        variability::type requires_manual_default_constructor;
        variability::type requires_manual_move_constructor;
        variability::type requires_stream_manipulators;
    };

    friend std::ostream& operator<<(std::ostream& s, const type_group& v);

    type_group make_type_group(const variability::type_repository& atrp) const;

    boost::optional<aspect_properties> make_aspect_properties(
        const type_group& tg, const variability::annotation& a) const;


private:
    struct feature_group {
        variability::meta_model::feature requires_manual_default_constructor;
        variability::meta_model::feature requires_manual_move_constructor;
        variability::meta_model::feature requires_stream_manipulators;
    };

    feature_group make_feature_group(
        const variability::meta_model::feature_model& fm) const;

    boost::optional<aspect_properties>
    make_aspect_properties(const feature_group& fg,
        const variability::meta_model::configuration& cfg) const;

private:
    typedef std::unordered_map<std::string, aspect_properties>
    aspect_properties_type;

    aspect_properties_type
    obtain_aspect_properties(const variability::type_repository& atrp,
        const variability::meta_model::feature_model& feature_model,
        const bool use_configuration,
        const std::unordered_map<std::string, formattable>& formattables) const;

private:
    void walk_name_tree(const coding::meta_model::name_tree& nt,
        const bool is_top_level, const aspect_properties_type& element_aps,
        aspect_properties& ap) const;

    aspect_properties compute_aspect_properties(
        const aspect_properties_type& element_aps,
        const std::list<coding::meta_model::attribute>& attrs) const;

    void populate_aspect_properties(const std::string& element_id,
        const aspect_properties_type& element_aps,
        formattable& formattable) const;

    void populate_aspect_properties(
        const aspect_properties_type& element_aps,
        std::unordered_map<std::string, formattable>& formattables) const;

public:
    void expand(const variability::type_repository& atrp,
        const variability::meta_model::feature_model& feature_model,
        const bool use_configuration, model& fm) const;
};

}

#endif
