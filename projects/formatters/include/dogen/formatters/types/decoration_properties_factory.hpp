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
#ifndef DOGEN_FORMATTERS_TYPES_DECORATION_PROPERTIES_FACTORY_HPP
#define DOGEN_FORMATTERS_TYPES_DECORATION_PROPERTIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/optional.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/formatters/types/licence.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/formatters/types/modeline_group.hpp"
#include "dogen/formatters/types/decoration_configuration.hpp"
#include "dogen/formatters/types/decoration_properties.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Creates the decoration configuration.
 */
class decoration_properties_factory {
public:
    /**
     * @brief Initialise a new decoration configuration factory,
     * without access to fallbacks. This constructor is used by
     * stitch.
     *
     * @param rp where to look up reference data.
     */
    decoration_properties_factory(const dynamic::repository& drp,
        const repository& rp);

    /**
     * @brief Initialise a new decoration configuration factory, with
     * access to fallbacks. This constructor is used by quilt.cpp.
     *
     * @param rp where to look up reference data.
     * @param fallback object to use to construct defaults, if any.
     */
    decoration_properties_factory(const dynamic::repository& drp,
        const repository& rp, const dynamic::object& fallback);

private:
    struct field_definitions {
        dynamic::field_definition generate_decoration;
        dynamic::field_definition copyright_notice;
        dynamic::field_definition licence_name;
        dynamic::field_definition modeline_group_name;
        dynamic::field_definition marker_add_date_time;
        dynamic::field_definition marker_add_warning;
        dynamic::field_definition marker_message;
    };

    field_definitions
    make_field_definitions(const dynamic::repository& rp) const;

    decoration_configuration
    make_decoration_configuration(const dynamic::object& o) const;

private:
    /**
     * @brief Obtains the licence text.
     */
    boost::optional<std::string>
    get_licence_text(const decoration_configuration& dc) const;

    /**
     * @brief Obtains a licence.
     */
    boost::optional<licence>
    get_licence(const decoration_configuration& dc) const;

    /**
     * @brief Obtains the modeline group name.
     */
    boost::optional<modeline_group>
    get_modeline_group(const decoration_configuration& fa) const;

    /**
     * @brief Returns the modeline for the supplied modeline name.
     *
     * @pre Modeline name must exist.
     */
    modeline get_modeline_from_group(const std::string& modeline_name,
        const modeline_group& mg) const;

    /**
     * @brief Obtains the modeline given a modeline name.
     */
    boost::optional<modeline>
    get_modeline(const std::string& modeline_name,
        const decoration_configuration& fa) const;

    /**
     * @brief Obtains a code generation marker.
     */
    boost::optional<std::string>
    get_marker(const decoration_configuration& fa) const;

    /**
     * @brief Obtains the marker from the decoration configuration; if
     * none is found, uses the default.
     */
    std::string get_marker_or_default(const decoration_configuration& dc) const;

    /**
     * @brief Obtains the generate decoration field value, if
     * available; if not, uses the default value.
     */
    bool get_generate_decoration_or_default(
        const decoration_configuration& dc) const;

private:
    /**
     * @brief Internal method to generate the decoration
     * configuration.
     */
    decoration_properties make(const std::string& modeline_name,
        const decoration_configuration& dc) const;

public:
    /**
     * @brief Generates the decoration configuration.
     */
    /**@{*/
    decoration_properties make(const std::string& modeline_name) const;
    decoration_properties make(const std::string& modeline_name,
        const dynamic::object& o) const;
    /**@}*/

private:
    const repository& repository_;
    const field_definitions field_definitions_;
    const decoration_configuration default_configuration_;
    const boost::optional<bool> default_generate_decoration_;
    const boost::optional<std::string> default_licence_text_;
    const boost::optional<std::list<std::string>> default_copyright_notices_;
    const boost::optional<modeline_group> default_modeline_group_;
    const boost::optional<std::string> default_marker_;
};

} }

#endif
