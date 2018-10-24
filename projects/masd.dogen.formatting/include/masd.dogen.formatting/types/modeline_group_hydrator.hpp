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
#ifndef MASD_DOGEN_FORMATTNG_TYPES_MODELINE_GROUP_HYDRATOR_HPP
#define MASD_DOGEN_FORMATTNG_TYPES_MODELINE_GROUP_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif


#include <string>
#include <istream>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "masd.dogen.formatting/types/modeline_field.hpp"
#include "masd.dogen.formatting/types/modeline_group.hpp"

namespace masd::dogen::formatting {

/**
 * @brief Hydrates a modeline group in a stream.
 */
class modeline_group_hydrator {
private:
    /**
     * @brief Given a field value representing an editor enumeration,
     * returns the corresponding enum.
     */
    editors to_editor(const std::string value) const;

    /**
     * @brief Given a field value representing an location
     * enumeration, returns the corresponding enum.
     */
    modeline_locations to_modeline_location(const std::string value) const;

private:
    /**
     * @brief Reads a modeline from the property tree.
     */
    modeline read_modeline(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Parse the stream using INI syntax.
     */
    modeline_group read_stream(std::istream& s) const;

public:
    /**
     * @brief Hydrate all the modeline groups found in the stream.
     */
    modeline_group hydrate(std::istream& s) const;

    /**
     * @brief Hydrate all the modeline groups from the supplied path.
     */
    modeline_group hydrate(const boost::filesystem::path& p) const;
};

}

#endif
