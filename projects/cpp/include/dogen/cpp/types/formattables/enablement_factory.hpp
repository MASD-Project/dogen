/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_ENABLEMENT_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_ENABLEMENT_FACTORY_HPP

#include <string>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formattables/global_enablement_properties.hpp"

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Creates the enablement for all formatters.
 */
class enablement_factory {
public:
    enablement_factory(
        const dynamic::repository& srp,
        const formatters::container& fc,
        const std::unordered_map<std::string,
                                 global_enablement_properties>& gep);

private:
    struct field_definitions {
        dynamic::field_definition enabled;
        dynamic::field_definition supported;
    };

    /**
     * @brief Creates the field definitions for all formatters.
     */
    std::unordered_map<std::string, field_definitions>
    create_field_definitions(const dynamic::repository& rp,
        const formatters::container& fc) const;

private:
    struct local_enablement_properties {
        boost::optional<bool> enabled;
        bool supported;
    };

    /**
     * @brief Creates the local enablement properties for all
     * formatters.
     */
    std::unordered_map<std::string, local_enablement_properties>
    obtain_local_properties(const dynamic::object& o) const;

    /**
     * @brief Computes the final enablement value for each formatter.
     */
    std::unordered_map<std::string, bool>
    compute_enablement_value(
        const std::unordered_map<std::string, local_enablement_properties>&
        lep, const bool partial_generation) const;

public:
    /**
     *  @brief Create the enablement for all formatters.
     */
    std::unordered_map<std::string, bool>
    make(const dynamic::object& o, const bool partial_generation = false) const;

private:
    const std::unordered_map<std::string, global_enablement_properties>&
    global_enablement_properties_;
    const std::unordered_map<std::string, field_definitions>
    field_definitions_;
};

} } }

#endif
