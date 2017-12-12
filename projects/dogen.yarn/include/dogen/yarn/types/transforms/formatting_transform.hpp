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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_FORMATTING_TRANSFORM_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_FORMATTING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.annotations/types/type.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/meta_model/model.hpp"
#include "dogen/yarn/types/meta_model/formatting_styles.hpp"
#include "dogen/yarn/types/transforms/formatting_configuration.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class formatting_transform final {
private:
    static meta_model::formatting_styles
    to_formatting_style(const std::string& s);

private:
    struct type_group {
        annotations::type formatting_style;
        annotations::type formatting_input;
    };
    friend std::ostream& operator<<(std::ostream& s, const type_group& v);

    static std::unordered_map<std::string, type_group>
    make_type_groups(const annotations::type_repository& atrp,
        const std::list<annotations::archetype_location>& als);

    static std::unordered_map<std::string, formatting_configuration>
    make_formatting_configuration(
        const std::unordered_map<std::string, type_group>& tgs,
        const annotations::annotation& a);

    static void transform_element(
        const std::unordered_map<std::string, type_group> tgs,
        meta_model::element& e);

public:
    static void transform(const context& ctx, meta_model::model& m);
};

} } }

#endif
