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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_ENABLEMENT_TRANSFORM_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_ENABLEMENT_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/element_archetype.hpp"
#include "dogen/yarn/types/meta_model/model.hpp"
#include "dogen/yarn/types/transforms/local_enablement_configuration.hpp"
#include "dogen/yarn/types/transforms/global_enablement_configuration.hpp"
#include "dogen/yarn/types/transforms/context.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class enablement_transform final {
private:
    struct global_type_group {
        annotations::type backend_enabled;
        annotations::type facet_enabled;
        annotations::type archetype_enabled;
        annotations::type facet_overwrite;
        annotations::type archetype_overwrite;
    };

    friend std::ostream& operator<<(std::ostream& s,
        const global_type_group& v);

    typedef std::unordered_map<std::string, global_type_group>
    global_type_group_type;

    static global_type_group_type make_global_type_group(
        const annotations::type_repository& atrp,
        const std::list<annotations::archetype_location>& als);

private:
    typedef std::unordered_map<std::string, global_enablement_configuration>
    global_enablement_configurations_type;

    static global_enablement_configurations_type
    obtain_global_configurations(const global_type_group_type& gtg,
        const annotations::annotation& ra);

    static void update_facet_enablement(
        const std::list<annotations::archetype_location>& als,
        const global_enablement_configurations_type& gcs,
        meta_model::model& m);

private:
    struct local_type_group {
        annotations::type facet_enabled;
        annotations::type archetype_enabled;
        annotations::type facet_supported;
        annotations::type facet_overwrite;
        annotations::type archetype_overwrite;
    };

    friend std::ostream& operator<<(std::ostream& s,
        const local_type_group& v);

    typedef std::unordered_map<std::string, local_type_group>
    local_type_group_type;

    static local_type_group_type
    make_local_type_group(const annotations::type_repository& atrp,
        const std::list<annotations::archetype_location>& als);

    static std::unordered_map<std::string, local_type_group_type>
    bucket_local_type_group_by_meta_name(
        const local_type_group_type& unbucketed_ltgs, const std::unordered_map<
        std::string, annotations::archetype_locations_group>&
        archetype_locations_by_meta_name);

private:
    typedef std::unordered_map<std::string, local_enablement_configuration>
    local_enablement_configurations_type;

    static local_enablement_configurations_type
    obtain_local_configurations(const local_type_group_type& ltg,
        const annotations::annotation& o);

private:
    static bool is_element_disabled(const meta_model::element& e);

    static void compute_enablement_for_artefact_properties(
        const global_enablement_configurations_type& gcs,
        const local_enablement_configurations_type& lcs,
        const std::string& archetype,
        meta_model::artefact_properties& ap);

    static void compute_enablement_for_element(
        const global_enablement_configurations_type& gcs,
        const std::unordered_map<std::string, local_type_group_type>& ltgmt,
        const std::unordered_map<std::string,
        annotations::archetype_locations_group>&
        archetype_locations_by_meta_name,
        std::unordered_set<meta_model::element_archetype>&
        enabled_archetype_for_element, meta_model::element& e);

public:
    static void transform(const context& ctx, meta_model::model& m);
};

} } }

#endif
