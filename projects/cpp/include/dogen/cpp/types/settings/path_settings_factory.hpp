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
#ifndef DOGEN_CPP_TYPES_SETTINGS_PATH_SETTINGS_FACTORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_PATH_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/cpp/types/settings/path_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Produces the path settings for all formatters.
 */
class path_settings_factory {
public:
    explicit path_settings_factory(const dynamic::schema::repository& rp);

private:
    /**
     * @brief If the field has not been found, throws.
     */
    void ensure_field_is_present(
        const bool found, const std::string& name) const;

    /**
     * @brief Creates the path settings for a given formatter.
     */
    path_settings create_settings_for_formatter(
        const std::list<dynamic::schema::field_definition>&
        formatter_fields, const dynamic::schema::object& o) const;

public:
    /**
     * @brief Produce the path settings.
     */
    std::unordered_map<std::string, path_settings>
    make(const dynamic::schema::object& o) const;

private:
    const dynamic::schema::repository& repository_;
};

} } }

#endif
