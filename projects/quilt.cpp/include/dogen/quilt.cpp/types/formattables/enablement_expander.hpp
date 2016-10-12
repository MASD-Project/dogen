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
#include <boost/optional.hpp>
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/type.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/local_enablement_configuration.hpp"
#include "dogen/quilt.cpp/types/formattables/global_enablement_configuration.hpp"
#include "dogen/quilt.cpp/types/formattables/profile_group.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class enablement_expander {
private:
    struct global_type_group {
        annotations::type model_enabled;
        annotations::type facet_enabled;
        annotations::type formatter_enabled;
    };

    friend std::ostream& operator<<(std::ostream& s,
        const global_type_group& v);

    typedef std::unordered_map<std::string, global_type_group>
    global_type_group_type;

    global_type_group_type make_global_type_group(
        const annotations::type_repository& atrp,
        const formatters::container& fc) const;

private:
    typedef std::unordered_map<std::string, global_enablement_configuration>
    global_enablement_configurations_type;

    global_enablement_configurations_type obtain_global_configurations(
        const global_type_group_type& gtg,
        const annotations::annotation& root, const formatters::container& fc,
        const profile_group& gpg) const;

    void update_facet_enablement(const formatters::container& fc,
        const global_enablement_configurations_type& gcs, model& fm) const;

private:
    struct local_type_group {
        annotations::type facet_enabled;
        annotations::type formatter_enabled;
        annotations::type facet_supported;
    };

    friend std::ostream& operator<<(std::ostream& s,
        const local_type_group& v);

    typedef std::unordered_map<std::string, local_type_group>
    local_type_group_type;

    local_type_group_type
    make_local_type_group(const annotations::type_repository& rp,
        const formatters::container& fc) const;

    std::unordered_map<std::type_index, local_type_group_type>
    bucket_local_type_group_by_type_index(
        const local_type_group_type& unbucketed_ltgs,
        const formatters::container& fc) const;

private:
    typedef std::unordered_map<std::string, local_enablement_configuration>
    local_enablement_configurations_type;

    local_enablement_configurations_type obtain_local_configurations(
        const local_type_group_type& ltg,
        const annotations::annotation& o, const formatters::container& fc,
        const boost::optional<profile_group>& lpg) const;

private:
    bool has_user_defined_service(
        const std::list<boost::shared_ptr<yarn::element>>&
        element_segments) const;

    void compute_enablement(
        const global_enablement_configurations_type& gcs,
        const local_enablement_configurations_type& lcs,
        formattable& fbl) const;

public:
    void expand(const annotations::type_repository& atrp,
        const annotations::annotation& root, const formatters::container& fc,
        model& fm) const;
};

} } } }

#endif
