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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_ENABLEMENT_REPOSITORY_FACTORY_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_ENABLEMENT_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/global_enablement_properties.hpp"
#include "dogen/quilt.cpp/types/formattables/enablement_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief Creates the enablement repository.
 */
class enablement_repository_factory {
private:
    struct field_definitions {
        dynamic::field_definition model_enabled;
        dynamic::field_definition facet_enabled;
        dynamic::field_definition formatter_enabled;
    };

    /**
     * @brief Creates the field definitions for all formatters.
     */
    std::unordered_map<std::string, field_definitions>
    create_field_definitions(const dynamic::repository& rp,
        const formatters::container& fc) const;

private:
    /**
     * @brief Creates the global enablement properties for all
     * formatter names.
     */
    std::unordered_map<std::string, global_enablement_properties>
    obtain_global_properties(
        const std::unordered_map<std::string, field_definitions>&
        field_definitions,
        const dynamic::object& root_object) const;

public:
    /**
     * @brief Create the enablement repository.
     */
    enablement_repository make(
        const dynamic::repository& rp,
        const dynamic::object& root_object,
        const formatters::container& fc,
        const yarn::model& m) const;
};

} } } }

#endif
