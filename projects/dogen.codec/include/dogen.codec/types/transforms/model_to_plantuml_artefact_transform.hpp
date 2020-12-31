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
#ifndef DOGEN_CODEC_TYPES_TRANSFORMS_MODEL_TO_PLANTUML_ARTEFACT_TRANSFORM_HPP
#define DOGEN_CODEC_TYPES_TRANSFORMS_MODEL_TO_PLANTUML_ARTEFACT_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <ostream>
#include <boost/filesystem/path.hpp>
#include "dogen.codec/types/entities/element.hpp"
#include "dogen.codec/types/entities/attribute.hpp"
#include "dogen.codec/types/entities/model.hpp"
#include "dogen.codec/types/entities/artefact.hpp"
#include "dogen.codec/types/transforms/context.hpp"

namespace dogen::codec::transforms {

/**
 * @brief Transforms a codec model into an artefact in PlantUML
 * syntax.
 */
class model_to_plantuml_artefact_transform final {
private:
    struct properties {
        std::string parents;
        std::string stereotypes;
        std::string type;
    };

private:
    static properties extract_properties(
        const std::list<identification::entities::tagged_value>& tvs);
    static std::string stereotype_to_colour(const std::string& stereotypes);

private:
    static void walk_parent_to_child(std::ostream& os, const unsigned int level,
        const std::string& id, const std::unordered_map<std::string,
        std::list<entities::element>>& parent_to_child_map);

public:
    static entities::artefact
    apply(const transforms::context& ctx, const boost::filesystem::path& p,
        const entities::model& m);
};

}

#endif
