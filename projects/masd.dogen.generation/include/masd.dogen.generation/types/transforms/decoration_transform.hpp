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
#ifndef MASD_DOGEN_GENERATION_TYPES_TRANSFORMS_DECORATION_TRANSFORM_HPP
#define MASD_DOGEN_GENERATION_TYPES_TRANSFORMS_DECORATION_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif


#include <list>
#include <string>
#include <boost/optional.hpp>
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/element_properties.hpp"
#include "masd.dogen.generation/types/transforms/context.hpp"
#include "masd.dogen.generation/types/helpers/decoration_repository.hpp"
#include "masd.dogen.generation/types/transforms/decoration_configuration.hpp"
#include "masd.dogen.generation/types/meta_model/model.hpp"

namespace masd::dogen::generation::transforms {

/**
 * @brief Updates the decoration of all modeling elements.
 */
class decoration_transform final {
private:
    struct feature_group {
        variability::meta_model::feature enabled;
        variability::meta_model::feature copyright_notice;
        variability::meta_model::feature licence_name;
        variability::meta_model::feature modeline_group_name;
        variability::meta_model::feature marker_name;
    };

    /**
     * @brief Creates the feature group for decoration.
     */
    static feature_group make_feature_group(
        const variability::meta_model::feature_model& fm);

    /**
     * @brief Reads the decoration configuration from the supplied annotation.
     */
    static boost::optional<decoration_configuration>
    read_decoration_configuration(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

private:
    /**
     * @brief Obtains the short-form licence text for a given licence
     * name.
     *
     * @pre If non-empty, licence name must exist in the decoration
     * repository.
     */
    static std::string
    get_short_form_licence(const helpers::decoration_repository drp,
        const std::string& licence_name);

    /**
     * @brief Retrieves the modeline for the supplied technical space
     * and modeline group.
     */
    static boost::shared_ptr<coding::meta_model::decoration::modeline>
    get_modeline(const helpers::decoration_repository drp,
        const std::string& modeline_group_name,
        const coding::meta_model::technical_space ts);

    /**
     * @brief Retrieves the generation marker for the supplied name.
     */
    static boost::shared_ptr<coding::meta_model::decoration::generation_marker>
    get_generation_marker(const helpers::decoration_repository drp,
        const std::string& generation_marker_name);

private:
    /**
     * @brief Returns true if the meta-model element can be generated,
     * false otherwise.
     */
    static bool is_generatable(const coding::meta_model::name& meta_name);

private:
    static boost::optional<coding::meta_model::decoration::element_properties>
    make_decoration(const std::string& licence_text,
        const boost::shared_ptr<coding::meta_model::decoration::modeline> ml,
        const boost::shared_ptr<
        coding::meta_model::decoration::generation_marker> gm,
        const std::list<std::string>& copyright_notices,
        const coding::meta_model::technical_space ts);

private:
    /**
     * @brief Creates the global decoration.
     */
    static boost::optional<coding::meta_model::decoration::element_properties>
    make_global_decoration(const helpers::decoration_repository drp,
        const boost::optional<decoration_configuration> root_dc,
        const coding::meta_model::technical_space ts);

    /**
     * @brief Creates a local decoration.
     */
    static boost::optional<coding::meta_model::decoration::element_properties>
    make_local_decoration(const helpers::decoration_repository drp,
        const boost::optional<decoration_configuration> root_dc,
        const boost::optional<
        coding::meta_model::decoration::element_properties> global_decoration,
        const boost::optional<decoration_configuration> element_dc,
        const coding::meta_model::technical_space ts);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
