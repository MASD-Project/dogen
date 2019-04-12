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
#ifndef MASD_DOGEN_GENERATION_TYPES_TRANSFORMS_ARCHETYPE_LOCATION_PROPERTIES_TRANSFORM_HPP
#define MASD_DOGEN_GENERATION_TYPES_TRANSFORMS_ARCHETYPE_LOCATION_PROPERTIES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/optional.hpp>
#include "masd.dogen.variability/types/type.hpp"
#include "masd.dogen.variability/types/archetype_location_repository.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.generation/types/meta_model/element_archetype.hpp"
#include "masd.dogen.generation/types/meta_model/backend_properties.hpp"
#include "masd.dogen.generation/types/meta_model/facet_properties.hpp"
#include "masd.dogen.generation/types/meta_model/archetype_properties.hpp"
#include "masd.dogen.generation/types/transforms/context.hpp"
#include "masd.dogen.generation/types/meta_model/model.hpp"


namespace masd::dogen::generation::transforms {

class archetype_location_properties_transform final {
private:
    struct backend_type_group {
        variability::type enabled;
        variability::type directory;
    };

    friend std::ostream&
    operator<<(std::ostream& s, const backend_type_group& v);

    struct facet_type_group {
        variability::type enabled;
        variability::type overwrite;
        boost::optional<variability::type> directory;
        boost::optional<variability::type> postfix;
    };

    friend std::ostream& operator<<(std::ostream& s, const facet_type_group& v);

    struct global_archetype_type_group {
        variability::type enabled;
        variability::type overwrite;
        variability::type postfix;
    };

    friend std::ostream&
    operator<<(std::ostream& s, const global_archetype_type_group& v);

    struct local_archetype_type_group {
        variability::type facet_enabled;
        variability::type archetype_enabled;
        variability::type facet_overwrite;
        variability::type archetype_overwrite;
    };

    friend std::ostream&
    operator<<(std::ostream& s, const local_archetype_type_group& v);

private:
    static std::unordered_map<std::string, backend_type_group>
    make_backend_type_group(const variability::type_repository& atrp,
        const variability::archetype_location_repository& alrp);

    static std::unordered_map<std::string, facet_type_group>
    make_facet_type_group(const variability::type_repository& atrp,
        const variability::archetype_location_repository& alrp);

    static std::unordered_map<std::string, global_archetype_type_group>
    make_global_archetype_type_group(const variability::type_repository& atrp,
        const variability::archetype_location_repository& alrp);

    static std::unordered_map<std::string, local_archetype_type_group>
    make_local_archetype_type_group(const variability::type_repository& atrp,
        const variability::archetype_location_repository& alrp);

private:
    static std::unordered_map<std::string, meta_model::backend_properties>
    obtain_backend_properties(
        const std::unordered_map<std::string, backend_type_group>& tgs,
        const variability::annotation& ra);

    static std::unordered_map<std::string, meta_model::facet_properties>
    obtain_facet_properties(
        const std::unordered_map<std::string, facet_type_group>& tgs,
        const variability::annotation& ra);

    static std::unordered_map<std::string, meta_model::archetype_properties>
    obtain_archetype_properties(
        const std::unordered_map<std::string, global_archetype_type_group>& tgs,
        const variability::annotation& ra);

    static void populate_global_archetype_location_properties(
        const variability::type_repository& atrp,
        const variability::archetype_location_repository& alrp,
        meta_model::model& m);

    static std::unordered_map<
        std::string,
        coding::meta_model::local_archetype_location_properties>
    obtain_local_archetype_location_properties(
        const std::unordered_map<std::string, local_archetype_type_group>& tgs,
        const std::list<variability::archetype_location>& als,
        const variability::annotation& a);

    static void populate_local_archetype_location_properties(
        const variability::type_repository& atrp,
        const variability::archetype_location_repository& alrp,
        meta_model::model& m);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
