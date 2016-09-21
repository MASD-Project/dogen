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
#ifndef DOGEN_QUILT_CPP_TYPES_PROPERTIES_HELPER_INSTANCES_REPOSITORY_FACTORY_HPP
#define DOGEN_QUILT_CPP_TYPES_PROPERTIES_HELPER_INSTANCES_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "dogen/yarn/types/model.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/annotations/helper_annotations_repository.hpp"
#include "dogen/quilt.cpp/types/annotations/streaming_annotations_repository.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

class helper_properties_repository_factory {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>>
    facets_for_family(const formatters::container& fc) const;

public:
    helper_properties_repository make(
        const annotations::helper_annotations_repository& hsrp,
        const annotations::streaming_annotations_repository& ssrp,
        const formatters::container& fc,
        const yarn::model& m) const;
};

} } } }

#endif
