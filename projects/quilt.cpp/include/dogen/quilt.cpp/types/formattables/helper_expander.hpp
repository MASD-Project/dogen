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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_EXPANDER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/quilt.cpp/types/annotations/helper_annotations.hpp"
#include "dogen/quilt.cpp/types/annotations/streaming_annotations.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_configuration.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class helper_expander {
private:
    typedef std::unordered_map<std::string, annotations::helper_annotations>
    helper_annotations_type;

    typedef std::unordered_map<std::string, annotations::streaming_annotations>
    streaming_annotations_type;

    struct annotations {
        helper_annotations_type helper_annotations;
        streaming_annotations_type streaming_annotations;
    };

    friend std::ostream& operator<<(std::ostream& s, const annotations& v);

    annotations obtain_annotations(const dynamic::repository& drp,
        const std::unordered_map<std::string, formattable>& formattables) const;

private:
    typedef std::unordered_map<std::string, std::unordered_set<std::string>>
    facets_for_family_type;

    facets_for_family_type
    facets_for_family(const formatters::container& fc) const;

    bool requires_hashing_helper(const facets_for_family_type& fff,
        const std::string& family) const;

    const cpp::annotations::helper_annotations& helper_annotations_for_id(
        const annotations& a, const std::string& id) const;

    boost::optional<cpp::annotations::streaming_annotations>
    streaming_annotations_for_id(const annotations& a,
        const std::string& id) const;

    std::list<std::string> namespace_list(const yarn::name& n) const;

private:
    boost::optional<helper_descriptor>
    walk_name_tree(const annotations& a, const facets_for_family_type& fff,
        const bool in_inheritance_relationship,
        const bool inherit_opaqueness_from_parent, const yarn::name_tree& nt,
        std::unordered_set<std::string>& done,
        std::list<helper_configuration>& configuration) const;

    std::list<helper_configuration>
    compute_helper_configuration(const annotations& a,
        const facets_for_family_type& fff,
        const bool in_inheritance_relationship,
        const std::list<yarn::attribute>& attrs) const;

    void populate_helper_configuration(const annotations& a,
        const formatters::container& fc,
        std::unordered_map<std::string, formattable>& formattables) const;

public:
    void expand(const dynamic::repository& drp, const formatters::container& fc,
        std::unordered_map<std::string, formattable>& formattables) const;
};

} } } }

#endif
