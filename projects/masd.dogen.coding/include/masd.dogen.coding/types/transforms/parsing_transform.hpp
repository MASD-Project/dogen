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
#include "masd.dogen.annotations/types/type.hpp"
#include "masd.dogen.annotations/types/type_repository.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/languages.hpp"
#include "masd.dogen.coding/types/meta_model/name_tree.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"
#include "masd.dogen.coding/types/meta_model/attribute.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/endomodel.hpp"
#include "masd.dogen.coding/types/transforms/context_fwd.hpp"

namespace masd::dogen::coding::transforms {

/**
 * @brief Expands all encoded representations that require parsing
 * into their yarn form.
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
    struct type_group {
        annotations::type parent;
        annotations::type enumeration_underlying_element;
        annotations::type primitive_underlying_element;
    };

    static type_group make_type_group(const annotations::type_repository& atrp);

    static std::string make_parent(const type_group& tg,
        const annotations::annotation& a);

    static std::string make_enumeration_underlying_element(const type_group& tg,
        const annotations::annotation& a);

    static std::string make_primitive_underlying_element(const type_group& tg,
        const annotations::annotation& a);

private:
    static std::string
    obtain_value_attribute_simple_name(const meta_model::languages l);

private:
    /**
     * @brief Parses all attributes in the supplied attribute list..
     */
    static void parse_attributes(const meta_model::languages l,
        std::list<meta_model::attribute>& attrs);

    /**
     * @brief Parses parent name in the supplied object.
     */
    static void parse_parent(const type_group& tg, meta_model::object& o);

    /**
     * @brief Parses the underlying element in the supplied
     * enumeration.
     */
    static void parse_underlying_element(const type_group& tg,
        meta_model::enumeration& e);

    /**
     * @brief Parses underlying element in the supplied primitive.
     */
    static void parse_underlying_element(
        const type_group& tg, const meta_model::languages l,
        meta_model::primitive& p);

public:
    /**
     * Execute the property expansion against the model.
     */
    static void transform(const context& ctx, meta_model::endomodel& m);
};

}

#endif
