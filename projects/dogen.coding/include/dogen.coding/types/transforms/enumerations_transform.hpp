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
#ifndef DOGEN_CODING_TYPES_TRANSFORMS_ENUMERATIONS_TRANSFORM_HPP
#define DOGEN_CODING_TYPES_TRANSFORMS_ENUMERATIONS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <iosfwd>
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.coding/types/meta_model/technical_space.hpp"
#include "dogen.coding/types/meta_model/structural/enumeration.hpp"
#include "dogen.coding/types/meta_model/model.hpp"
#include "dogen.coding/types/transforms/context_fwd.hpp"

namespace dogen::coding::transforms {

/**
 * @brief Expands all enumerations in model.
 */
class enumerations_transform final {
private:
    struct enumeration_feature_group {
        variability::meta_model::feature
        use_implementation_defined_underlying_element;
        variability::meta_model::feature
        use_implementation_defined_enumerator_values;
        variability::meta_model::feature add_invalid_enumerator;
    };

    struct enumerator_feature_group {
        variability::meta_model::feature value;
    };

    struct feature_group {
        enumeration_feature_group enumeration;
        enumerator_feature_group enumerator;
    };

    static enumeration_feature_group make_enumeration_feature_group(
        const variability::meta_model::feature_model& fm);

    static enumerator_feature_group make_enumerator_feature_group(
        const variability::meta_model::feature_model& fm);

    static feature_group make_feature_group(
        const variability::meta_model::feature_model& fm);

private:
    static void populate_from_configuration(const enumeration_feature_group& fg,
        meta_model::structural::enumeration& e);
    static void populate_from_configuration(const enumerator_feature_group& fg,
        meta_model::structural::enumerator& e);

private:
    static meta_model::name obtain_enumeration_default_underlying_element_name(
        const meta_model::model& m);
    static std::string obtain_invalid_enumerator_simple_name(
        const meta_model::technical_space ts);
    static meta_model::structural::enumerator make_invalid_enumerator(
        const meta_model::name& n, const meta_model::technical_space ts);

    static void expand_default_underlying_element(
        const meta_model::name& default_underlying_element_name,
        meta_model::structural::enumeration& e);
    static void expand_enumerators(const enumerator_feature_group& fg,
        const meta_model::technical_space ts,
        meta_model::structural::enumeration& e);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
