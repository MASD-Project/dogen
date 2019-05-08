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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_PARSING_TRANSFORM_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_PARSING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.coding/types/meta_model/structural/object.hpp"
#include "masd.dogen.coding/types/meta_model/technical_space.hpp"
#include "masd.dogen.coding/types/meta_model/attribute.hpp"
#include "masd.dogen.coding/types/meta_model/name_tree.hpp"
#include "masd.dogen.coding/types/meta_model/structural/primitive.hpp"
#include "masd.dogen.coding/types/meta_model/structural/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/transforms/context_fwd.hpp"

namespace masd::dogen::coding::transforms {

/**
 * @brief Expands all encoded representations that require parsing
 * into their coding form.
 *
 * As an example, all local attributes have unparsed types - strings
 * following a well defined notation - that need to be parsed into
 * name trees. All such forms of encoding are processed by this
 * expander.
 *
 * It is also responsible for reading all meta-data that requires
 * parsing such as parent names, enumeration underlying types and so
 * forth.
 */
class parsing_transform final {
private:
    struct feature_group {
        variability::meta_model::feature parent;
        variability::meta_model::feature enumeration_underlying_element;
        variability::meta_model::feature primitive_underlying_element;
    };

    static feature_group make_feature_group(
        const variability::meta_model::feature_model& fm);

    static std::string make_parent(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::string make_enumeration_underlying_element(
        const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::string make_primitive_underlying_element(
        const feature_group& fg,
        const variability::meta_model::configuration& cfg);

private:
    static std::string
    obtain_value_attribute_simple_name(const meta_model::technical_space ts);

private:
    /**
     * @brief Parses all attributes in the supplied attribute list..
     */
    static void parse_attributes(const meta_model::technical_space ts,
        std::list<meta_model::attribute>& attrs);

    /**
     * @brief Parses parent name in the supplied object.
     */
    static void parse_parent(const feature_group& fg,
        meta_model::structural::object& o);

    /**
     * @brief Parses the underlying element in the supplied
     * enumeration.
     */
    static void parse_underlying_element(const feature_group& fg,
        meta_model::structural::enumeration& e);

    /**
     * @brief Parses underlying element in the supplied primitive.
     */
    static void parse_underlying_element(
        const feature_group& fg, const meta_model::technical_space ts,
        meta_model::structural::primitive& p);

public:
    /**
     * Execute the property expansion against the model.
     */
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
