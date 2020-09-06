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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_DECORATION_FACTORY_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_DECORATION_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.logical/types/entities/decoration/element_properties.hpp"
#include "dogen.logical/types/helpers/decoration_repository.hpp"
#include "dogen.logical/types/helpers/decoration_configuration.hpp"

namespace dogen::logical::helpers {

class decoration_factory final {
public:
    decoration_factory(const helpers::decoration_repository& drp,
        const std::string& activity_timestamp,
        const std::string& origin_sha1_hash);

private:
    /**
     * @brief Obtains the short-form licence text for a given licence
     * name.
     *
     * @pre If non-empty, licence name must exist in the decoration
     * repository.
     */
    std::string get_short_form_licence(
        const identification::entities::logical_id& licence_name) const;

    /**
     * @brief Retrieves the modeline for the supplied technical space
     * and modeline group.
     */
    boost::shared_ptr<entities::decoration::modeline> get_modeline(
        const identification::entities::logical_id& modeline_group_name,
        const identification::entities::technical_space ts) const;

    /**
     * @brief Retrieves the generation marker for the supplied name.
     */
    boost::shared_ptr<entities::decoration::generation_marker>
    get_generation_marker(const identification::entities::logical_id&
        generation_marker_name) const;

private:
    boost::optional<logical::entities::decoration::element_properties>
    make_decoration(const std::string& licence_text,
        const boost::shared_ptr<logical::entities::decoration::modeline> ml,
        const boost::shared_ptr<
        logical::entities::decoration::generation_marker> gm,
        const std::list<std::string>& copyright_notices,
        const identification::entities::technical_space ts) const;

public:
    /**
     * @brief Creates the global decoration.
     */
    boost::optional<entities::decoration::element_properties>
    make_global_decoration(
        const boost::optional<helpers::decoration_configuration> root_dc,
        const identification::entities::technical_space ts) const;

    /**
     * @brief Creates a local decoration.
     */
    boost::optional<entities::decoration::element_properties>
    make_local_decoration(const boost::optional<
        entities::decoration::element_properties> global_decoration,
        const boost::optional<helpers::decoration_configuration>& root_dc,
        const boost::optional<helpers::decoration_configuration> element_dc,
        const identification::entities::technical_space ts) const;

private:
    const helpers::decoration_repository& decoration_repository_;
    const std::string& activity_timestamp_;
    const std::string& origin_sha1_hash_;
};

}

#endif
