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
#ifndef DOGEN_CPP_TYPES_SETTINGS_TYPE_SETTINGS_FACTORY_FWD_HPP
#define DOGEN_CPP_TYPES_SETTINGS_TYPE_SETTINGS_FACTORY_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/dynamic/schema/types/field_definition.hpp"
#include "dogen/cpp/types/settings/type_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class type_settings_factory {
public:
    type_settings_factory(const dynamic::schema::repository& rp,
        const dynamic::schema::object& root_object);

private:
    /**
     * @brief All relevant properties we need to remember.
     */
    struct properties {
        bool root_disable_complete_constructor;
        dynamic::schema::field_definition disable_complete_constructor;
    };

    /**
     * @brief Creates the properties.
     */
    properties make_properties(const dynamic::schema::repository& rp,
        const dynamic::schema::object& root_object) const;

public:
    /**
     * @brief Produces the type settings.
     */
    type_settings make(const dynamic::schema::object& o) const;

private:
    const properties properties_;
};

} } }

#endif
