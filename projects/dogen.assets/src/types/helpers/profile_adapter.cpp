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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.variability/types/helpers/enum_mapper.hpp"
#include "dogen.assets/types/helpers/adaptation_exception.hpp"
#include "dogen.assets/types/helpers/profile_adapter.hpp"

namespace {

const std::string transform_id("assets.helpers.profile_adapter");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;

}

namespace dogen::assets::helpers {

variability::meta_model::profile_template
profile_adapter::adapt(const meta_model::variability::profile_template& pt) {
    const auto sn(pt.name().simple());
    const auto qn(pt.name().qualified().dot());
    BOOST_LOG_SEV(lg, trace) << "Adapting: " << sn << " (" << qn << ")";

    variability::meta_model::profile_template r;
    r.name().simple(sn);
    r.name().qualified(qn);
    r.labels(pt.labels());

    for (const auto& n : pt.parents())
        r.parents().push_back(n.qualified().dot());

    for (const auto& e : pt.entries()) {
        const auto& k(e.key());
        BOOST_LOG_SEV(lg, trace) << "Adapting entry: " << k;

        variability::meta_model::configuration_point_template cpt;
        cpt.name().simple(k);
        cpt.kind(e.template_kind());

        using variability::meta_model::template_kind;
        if (cpt.kind() == template_kind::instance)
            cpt.name().qualified(k);

        cpt.location(e.location());
        cpt.untyped_value(e.value());
        r.templates().push_back(cpt);
    }

    return r;
}

std::list<variability::meta_model::profile_template> profile_adapter::
adapt_profile_templates(const assets::meta_model::model_set& ms) {
    std::list<variability::meta_model::profile_template> r;

    auto lambda(
        [&](auto& map) {
            for (const auto& pair : map) {
                const auto& pt(*pair.second);
                r.push_back(adapt(pt));
            }
        });

    lambda(ms.target().variability_elements().profile_templates());
    for (const auto& m : ms.references())
        lambda(m.variability_elements().profile_templates());

    return r;
}

}
