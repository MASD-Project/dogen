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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_NAMING_TRANSFORM_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_NAMING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <vector>
#include <unordered_map>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/yarn/types/transforms/naming_configuration.hpp"
#include "dogen/yarn/types/meta_model/exogenous_model.hpp"
#include "dogen/yarn/types/transforms/context_fwd.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class naming_transform final {
private:
    struct type_group {
        annotations::type external_modules;
        annotations::type model_modules;
    };

    friend std::ostream& operator<<(std::ostream& s, const type_group& v);

    static type_group make_type_group(const annotations::type_repository& atrp);

    static boost::optional<naming_configuration>
    make_naming_configuration(const type_group& tg,
        const annotations::annotation& a);

private:
    static const annotations::annotation&
    obtain_root_annotation(const meta_model::exogenous_model& em);

    static meta_model::location
    create_location(const naming_configuration& cfg);

    static void update_names(const meta_model::location& l,
        meta_model::exogenous_model& em);

public:
    static void transform(const context& ctx, meta_model::exogenous_model& em);
};

} } }

#endif
