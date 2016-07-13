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
#ifndef DOGEN_CPP_TYPES_SETTINGS_ASPECT_SETTINGS_FACTORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_ASPECT_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/quilt.cpp/types/settings/aspect_settings.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

/**
 * @brief Creates the element settings.
 */
class aspect_settings_factory {
public:
    aspect_settings_factory(const dynamic::repository& rp,
        const dynamic::object& root_object);

private:
    /**
     * @brief All field definitions we require.
     */
    struct field_definitions {
        dynamic::field_definition disable_complete_constructor;
        dynamic::field_definition disable_xml_serialization;
    };

    /**
     * @brief Creates all of field definitions.
     */
    field_definitions make_field_definitions(
        const dynamic::repository& rp) const;

private:
    /**
     * @brief Values for the fields in the root object.
     */
    struct root_object_field_values {
        bool disable_complete_constructor;
        bool disable_xml_serialization;
    };

    /**
     * @brief Reads the values for all relevant fields in the root
     * object.
     */
    root_object_field_values
    make_root_object_field_values(const field_definitions& fd,
        const dynamic::object& root_object) const;

private:
    /**
     * @brief Obtains the value of the supplied field. If not
     * available, uses the supplied root value.
     */
    bool obtain_field_value(const dynamic::field_selector& fs,
        const dynamic::field_definition& fd,
        const bool root_value) const;

public:
    /**
     * @brief Produces the element settings.
     */
    aspect_settings make(const dynamic::object& o) const;

    /**
     * @brief Produce the element settings based on root object
     * contents.
     */
    aspect_settings make() const;

private:
    const field_definitions field_definitions_;
    const root_object_field_values field_values_;
};

} } } }

#endif
