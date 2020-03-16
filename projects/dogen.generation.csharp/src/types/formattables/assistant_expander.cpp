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
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.generation.csharp/types/traits.hpp"
#include "dogen.generation.csharp/types/formattables/assistant_expander.hpp"

namespace dogen::generation::csharp::formattables {

assistant_expander::feature_group assistant_expander::
make_feature_group(const variability::entities::feature_model& fm) const {
    feature_group r;
    const variability::helpers::feature_selector s(fm);

    const auto ra(traits::csharp::assistant::requires_assistance());
    r.requires_assistance = s.get_by_name(ra);

    const auto amp(traits::csharp::assistant::method_postfix());
    r.method_postfix = s.get_by_name(amp);

    return r;
}

boost::optional<assistant_properties>
assistant_expander::make_assistant_properties(const feature_group& fg,
    const variability::entities::configuration& cfg) const {

    assistant_properties r;
    bool has_properties(false);

    const variability::helpers::configuration_selector s(cfg);
    const auto& ra(fg.requires_assistance);
    if (s.has_configuration_point(ra)) {
        has_properties = true;
        r.requires_assistance(s.get_boolean_content(ra));
    }

    const auto amp(fg.method_postfix);
    if (s.has_configuration_point(amp)) {
        has_properties = true;
        r.method_postfix(s.get_text_content(amp));
    }

    if (has_properties)
        return r;

    return boost::optional<assistant_properties>();
}

void assistant_expander::
expand(const variability::entities::feature_model& feature_model,
    model& fm) const {
    const auto fg(make_feature_group(feature_model));

    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);
        const auto& e(*formattable.element());
        const auto cfg(*e.configuration());
        const auto oap(make_assistant_properties(fg, cfg));

        if (!oap)
            continue;

        const auto id(pair.first);
        const auto& ap(*oap);
        fm.assistant_properties()[id] = ap;
    }
}

}
