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
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.logical/types/helpers/adaptation_exception.hpp"
#include "dogen.logical/types/helpers/profile_adapter.hpp"

namespace {

const std::string transform_id("assets.helpers.profile_adapter");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;
const std::string missing_feature("Feature not found: ");
const std::string duplicate_configuration_point(
    "Found more than one configuration point for the same feature: ");

}

namespace dogen::logical::helpers {

variability::meta_model::profile_template
profile_adapter::adapt(const meta_model::variability::profile_template& pt) {
    const auto sn(pt.name().simple());
    const auto qn(pt.name().qualified().dot());
    BOOST_LOG_SEV(lg, trace) << "Adapting profile template: "
                             << sn << " (" << qn << ")";

    variability::meta_model::profile_template r;
    r.name().simple(sn);
    r.name().qualified(qn);
    r.stereotype(pt.stereotype());

    for (const auto& n : pt.parents())
        r.parents().push_back(n.qualified().dot());

    for (const auto& e : pt.entries()) {
        const auto& k(e.key());
        BOOST_LOG_SEV(lg, trace) << "Adapting entry: " << k;

        variability::meta_model::configuration_point_template cpt;
        cpt.name().simple(k);
        cpt.instantiation_domain_name(e.instantiation_domain_name());
        cpt.untyped_value(e.value());
        r.templates().push_back(cpt);
    }

    return r;
}

variability::meta_model::profile
profile_adapter::adapt(const variability::meta_model::feature_model& fm,
    const meta_model::variability::profile& p) {
    const auto sn(p.name().simple());
    const auto qn(p.name().qualified().dot());
    BOOST_LOG_SEV(lg, trace) << "Adapting profile: " << sn << " (" << qn << ")";

    variability::meta_model::profile r;
    r.name().simple(sn);
    r.name().qualified(qn);
    r.stereotype(p.stereotype());

    for (const auto& n : p.parents())
        r.parents().push_back(n.qualified().dot());

    for (const auto& e : p.entries()) {
        const auto& k(e.key());
        BOOST_LOG_SEV(lg, trace) << "Adapting entry: " << k;

        /*
         * Locate the feature for this configuration point template.
         */
        const auto& bn(fm.by_name());
        BOOST_LOG_SEV(lg, trace) << "Feature qualified name: " << k;
        const auto i(bn.find(k));
        if (i == bn.end()) {
            BOOST_LOG_SEV(lg, error) << missing_feature << k;
            BOOST_THROW_EXCEPTION(adaptation_exception(missing_feature + k));
        }

        /*
         * Now we can populate the name of the point from the point
         * template's associated feature, and, if supplied, the owner.
         */
        const auto& feature(i->second);
        variability::meta_model::configuration_point cp;
        cp.name().simple(feature.name().simple());
        cp.name().qualified(feature.name().qualified());

        /*
         * Finally we can create the value.
         */
        variability::helpers::value_factory vf;
        cp.value(vf.make(feature, e.value()));

        const auto cpqn(cp.name().qualified());
        const auto pair(std::make_pair(cpqn, cp));
        const auto inserted(r.configuration_points().insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_configuration_point << cpqn;
            BOOST_THROW_EXCEPTION(adaptation_exception(
                    duplicate_configuration_point + cpqn));
        }
    }
    return r;
}

std::list<variability::meta_model::profile_template> profile_adapter::
adapt_profile_templates(const logical::meta_model::model_set& ms) {
    std::list<variability::meta_model::profile_template> r;

    const auto lambda(
        [&](auto& map) {
            for (const auto& pair : map)
                r.push_back(adapt(*pair.second));
        });

    lambda(ms.target().variability_elements().profile_templates());
    for (const auto& m : ms.references())
        lambda(m.variability_elements().profile_templates());

    return r;
}

std::list<variability::meta_model::profile> profile_adapter::
adapt_profiles(const variability::meta_model::feature_model& fm,
    const logical::meta_model::model_set& ms) {
    std::list<variability::meta_model::profile> r;

    const auto lambda(
        [&](auto& map) {
            for (const auto& pair : map)
                r.push_back(adapt(fm, *pair.second));
        });

    lambda(ms.target().variability_elements().profiles());
    for (const auto& m : ms.references())
        lambda(m.variability_elements().profiles());

    return r;
}

variability::transforms::profile_repository_inputs
profile_adapter::adapt(const variability::meta_model::feature_model& fm,
    const meta_model::model_set& ms) {
    variability::transforms::profile_repository_inputs r;
    r.profiles(adapt_profiles(fm, ms));
    r.templates(adapt_profile_templates(ms));
    return r;
}

}
