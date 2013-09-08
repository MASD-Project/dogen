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
#ifndef DOGEN_OM_TYPES_MODELINE_GROUP_HYDRATOR_HPP
#define DOGEN_OM_TYPES_MODELINE_GROUP_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/om/types/modeline_field.hpp"
#include "dogen/om/types/modeline_group.hpp"

namespace dogen {
namespace om {

class modeline_group_hydrator {
public:
    modeline_group_hydrator() = delete;
    modeline_group_hydrator(const modeline_group_hydrator&) = default;
    modeline_group_hydrator& operator=(const modeline_group_hydrator&) = delete;
    modeline_group_hydrator(modeline_group_hydrator&& rhs) = default;

public:
    /**
     * @brief Initialises the hydrator.
     *
     * @param directories directories to load groups from.
     */
    explicit modeline_group_hydrator(
        const std::list<boost::filesystem::path>& directories);

private:
    /**
     * @brief Given a field value representing an editor enumeration,
     * returns the corresponding enum.
     */
    editors translate_editor_enum(const std::string value) const;

    /**
     * @brief Given a field value representing an location
     * enumeration, returns the corresponding enum.
     */
    modeline_locations translate_location_enum(const std::string value) const;

    /**
     * @brief Given a field value, we translate any of the well defined
     * special values.
     *
     * As the INI file format does not support spaces, tabs etc as
     * field values, we hacked a convention around it: to use the word
     * space for a space, etc. This method performs the translation.
     */
    std::string translate_special_values(const std::string value) const;

    /**
     * @brief Returns true if the name of the group is valid, false
     * otherwise.
     */
    bool is_group_name_valid(const std::string& n) const;

    /**
     * @brief Returns all files in the directory.
     */
    std::list<boost::filesystem::path>
    files_in_directory(const boost::filesystem::path& d) const;

    /**
     * @brief Hydrates an INI file.
     */
    modeline_group hydrate_file(const boost::filesystem::path& f) const;

public:
    /**
     * @brief Hydrate all the modeline groups found in the
     * directories.
     */
    std::unordered_map<std::string, modeline_group> hydrate() const;

private:
    const std::list<boost::filesystem::path>& directories_;
};

} }

#endif
