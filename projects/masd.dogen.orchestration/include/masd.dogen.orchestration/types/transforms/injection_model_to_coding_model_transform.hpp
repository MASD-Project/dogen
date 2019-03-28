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
#ifndef MASD_DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_INJECTION_MODEL_TO_CODING_MODEL_TRANSFORM_HPP
#define MASD_DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_INJECTION_MODEL_TO_CODING_MODEL_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <vector>
#include <unordered_map>
#include "masd.dogen.annotations/types/type.hpp"
#include "masd.dogen.annotations/types/annotation.hpp"
#include "masd.dogen.annotations/types/type_repository.hpp"
#include "masd.dogen.injection/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/location.hpp"
#include "masd.dogen.coding/types/meta_model/attribute.hpp"
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.orchestration/types/transforms/context_fwd.hpp"
#include "masd.dogen.orchestration/types/helpers/adapter.hpp"
#include "masd.dogen.orchestration/types/transforms/naming_configuration.hpp"

namespace masd::dogen::orchestration::transforms {

class injection_model_to_coding_model_transform final {
private:
    struct type_group {
        annotations::type external_modules;
        annotations::type model_modules;
    };

    friend std::ostream& operator<<(std::ostream& s, const type_group& v);

    static type_group
    make_type_group(const annotations::type_repository& atrp);

    static naming_configuration make_naming_configuration(const type_group& tg,
        const annotations::annotation& a);

    static coding::meta_model::location
    create_location(const naming_configuration& nc);

    static coding::meta_model::static_stereotypes compute_element_type(
        const std::list<coding::meta_model::static_stereotypes>& st,
        const std::string& fallback_element_type);

    static void process_element(const helpers::adapter& ad,
        const coding::meta_model::location& l,
        const injection::meta_model::element& ie,
        coding::meta_model::model& cm);

public:
    static coding::meta_model::model
    apply(const context& ctx, const injection::meta_model::model& m);
};

}

#endif
