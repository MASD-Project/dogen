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
#ifndef DOGEN_CODEC_TYPES_TRANSFORMS_ORG_ARTEFACT_TO_MODEL_TRANSFORM_HPP
#define DOGEN_CODEC_TYPES_TRANSFORMS_ORG_ARTEFACT_TO_MODEL_TRANSFORM_HPP

#include "dogen.org/types/entities/section.hpp"
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.org/types/entities/drawer.hpp"
#include "dogen.org/types/entities/headline.hpp"
#include "dogen.codec/types/entities/model.hpp"
#include "dogen.codec/types/entities/element.hpp"
#include "dogen.codec/types/entities/artefact.hpp"
#include "dogen.codec/types/transforms/context.hpp"

namespace dogen::codec::transforms {

/**
 * @brief Processes the artefact as if encoded as an org-mode
 * document, and converts it into an instance of the codec model.
 */
class org_artefact_to_model_transform final {
private:
    enum class headline_type {
        ignore,
        attribute,
        element,
        module
    };

    /**
     * @brief Reads the tags of a headline to determine its type with
     * regards to the codec model.
     */
    static headline_type get_headline_type(const org::entities::headline& h);

    /**
     * @brief Converts an org section into text.
     */
    static std::string section_to_text(const org::entities::section& s);

private:
    struct processed_drawer {
        std::string custom_id;
        std::list<identification::entities::tagged_value> tagged_values;
    };

    /**
     * @brief Reads the tagged values, if any exists.
     */
    static processed_drawer
    process_drawer(const std::list<org::entities::drawer>& drawers);

private:
    /**
     * @brief Processes the headline as if containing a codec
     * attribute.
     */
    static entities::attribute make_attribute(const org::entities::headline& h);

    /**
     * @brief Processes the headline as if containing a codec
     * element.
     */
    static entities::element make_element(const headline_type ht,
        const std::string& qualified_parent,
        const org::entities::headline& h);

    /**
     * @brief Processes the headline as if containing an element.
     */
    static std::list<entities::element> make_elements(
        const std::list<org::entities::headline>& headlines,
        entities::element& current);

    /**
     * @brief Processes headlines as if containing codec elements.
     */
    static std::list<entities::element>
    make_elements(const std::string& parent_name,
        const std::list<org::entities::headline>& headlines);


public:
    static entities::model
    apply(const transforms::context& ctx, const entities::artefact& a);
};

}

#endif
