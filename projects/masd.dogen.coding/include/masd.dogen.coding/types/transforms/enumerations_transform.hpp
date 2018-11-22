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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_ENUMERATIONS_TRANSFORM_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_ENUMERATIONS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <iosfwd>
#include "masd.dogen.annotations/types/type.hpp"
#include "masd.dogen.annotations/types/annotation.hpp"
#include "masd.dogen.annotations/types/type_repository.hpp"
#include "masd.dogen.coding/types/meta_model/languages.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/endomodel.hpp"
#include "masd.dogen.coding/types/transforms/context_fwd.hpp"

namespace masd::dogen::coding::transforms {

/**
 * @brief Expands all enumerations in model.
 */
class enumerations_transform final {
private:
    struct enumeration_type_group {
        annotations::type use_implementation_defined_underlying_element;
        annotations::type use_implementation_defined_enumerator_values;
        annotations::type add_invalid_enumerator;
    };
    friend std::ostream& operator<<(std::ostream& s,
        const enumeration_type_group& v);

    struct enumerator_type_group {
        annotations::type value;
    };
    friend std::ostream& operator<<(std::ostream& s,
        const enumerator_type_group& v);

    struct type_group {
        enumeration_type_group enumeration;
        enumerator_type_group enumerator;
    };
    friend std::ostream& operator<<(std::ostream& s, const type_group& v);

    static enumeration_type_group make_enumeration_type_group(
        const annotations::type_repository& atrp);

    static enumerator_type_group make_enumerator_type_group(
        const annotations::type_repository& atrp);

    static type_group make_type_group(const annotations::type_repository& atrp);

private:
    static void populate_from_annotations(const enumeration_type_group& tg,
        meta_model::enumeration& e);
    static void populate_from_annotations(const enumerator_type_group& tg,
        meta_model::enumerator& e);

private:
    static meta_model::name obtain_enumeration_default_underlying_element_name(
        const meta_model::endomodel& em);
    static std::string obtain_invalid_enumerator_simple_name(
        const meta_model::languages l);
    static meta_model::enumerator make_invalid_enumerator(
        const meta_model::name& n, const meta_model::languages l);

    static void expand_default_underlying_element(
        const meta_model::name& default_underlying_element_name,
        meta_model::enumeration& e);
    static void expand_enumerators(const enumerator_type_group& tg,
        const meta_model::languages l, meta_model::enumeration& e);

public:
    static void transform(const context& ctx, meta_model::endomodel& em);
};

}

#endif
