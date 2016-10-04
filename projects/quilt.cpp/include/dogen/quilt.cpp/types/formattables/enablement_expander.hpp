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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_ENABLEMENT_EXPANDER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_ENABLEMENT_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <typeindex>
#include <unordered_map>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/local_enablement_configuration.hpp"
#include "dogen/quilt.cpp/types/formattables/global_enablement_configuration.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class enablement_expander {
private:
    struct global_field_definitions {
        dynamic::field_definition model_enabled;
        dynamic::field_definition facet_enabled;
        dynamic::field_definition formatter_enabled;
    };

    friend std::ostream& operator<<(std::ostream& s,
        const global_field_definitions& v);

    typedef std::unordered_map<std::string, global_field_definitions>
    global_field_definitions_type;

    global_field_definitions_type make_global_field_definitions(
        const dynamic::repository& drp, const formatters::container& fc) const;

private:
    typedef std::unordered_map<std::string, global_enablement_configuration>
    global_enablement_configurations_type;

    global_enablement_configurations_type obtain_global_configurations(
        const global_field_definitions_type& gfds,
        const dynamic::object& root_object) const;

    void update_facet_enablement(const formatters::container& fc,
        const global_enablement_configurations_type& gcs, model& fm) const;

private:
    struct local_field_definitions {
        dynamic::field_definition enabled;
        dynamic::field_definition supported;
    };

    friend std::ostream& operator<<(std::ostream& s,
        const local_field_definitions& v);

    typedef std::unordered_map<std::string, local_field_definitions>
    local_field_definitions_type;

    local_field_definitions_type make_local_field_definitions(
        const dynamic::repository& rp, const formatters::container& fc) const;

    std::unordered_map<std::type_index, local_field_definitions_type>
    bucket_local_field_definitions_by_type_index(
        const local_field_definitions_type& lfds,
        const formatters::container& fc) const;

private:
    typedef std::unordered_map<std::string, local_enablement_configuration>
    local_enablement_configurations_type;

    local_enablement_configurations_type obtain_local_configurations(
        const local_field_definitions_type& lfds,
        const dynamic::object& o) const;

private:
    bool has_user_defined_service(
        const std::list<boost::shared_ptr<yarn::element>>&
        element_segments) const;

    void compute_enablement(
        const global_enablement_configurations_type& gcs,
        const local_enablement_configurations_type& lcs,
        formattable& fbl) const;

public:
    void expand(const dynamic::repository& drp,
        const dynamic::object& root_object, const formatters::container& fc,
        model& fm) const;
};

} } } }

#endif
