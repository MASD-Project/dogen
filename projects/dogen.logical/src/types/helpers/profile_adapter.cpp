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
#include "dogen.variability/lexical_cast/entities/binding_point_lc.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/configuration_points_factory.hpp"
#include "dogen.logical/types/helpers/adaptation_exception.hpp"
#include "dogen.logical/types/helpers/profile_adapter.hpp"

namespace {

const std::string transform_id("logical.helpers.profile_adapter");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;
const std::string missing_feature("Feature not found: ");
const std::string duplicate_configuration_point(
    "Found more than one configuration point for the same feature: ");

}

namespace dogen::logical::helpers {

variability::entities::profile_template
profile_adapter::adapt(const entities::variability::profile_template& pt) {
    const auto sn(pt.name().simple());
    const auto qn(pt.name().qualified().dot());
    BOOST_LOG_SEV(lg, trace) << "Adapting profile template: "
                             << sn << " (" << qn << ")";

    variability::entities::profile_template r;
    r.name().simple(sn);
    r.name().qualified(qn);
    r.stereotype(pt.stereotype());

    for (const auto& n : pt.parents())
        r.parents().push_back(n.qualified().dot());

    for (const auto& e : pt.entries()) {
        const auto& k(e.key());
        BOOST_LOG_SEV(lg, trace) << "Adapting entry: " << k;

        variability::entities::configuration_point_template cpt;
        cpt.name().simple(k);
        cpt.instantiation_domain_name(e.instantiation_domain_name());
        cpt.untyped_value(e.value());
        r.templates().push_back(cpt);
    }

    return r;
}

variability::entities::profile
profile_adapter::adapt(const variability::entities::feature_model& fm,
    const entities::variability::profile& p, const bool compatibility_mode) {
    const auto sn(p.name().simple());
    const auto qn(p.name().qualified().dot());
    BOOST_LOG_SEV(lg, trace) << "Adapting profile: " << sn << " (" << qn << ")";

    /*
     * First, populate all the trivial attributes which are just copy
     * and paste.
     */
    variability::entities::profile r;
    r.name().simple(sn);
    r.name().qualified(qn);
    r.stereotype(p.stereotype());

    /*
     * Populate parents.
     */
    for (const auto& n : p.parents())
        r.parents().push_back(n.qualified().dot());

    /*
     * Create a tagged values container in the expected format by the
     * variability sub-system. Note that for collections we can have a
     * single entry with multiple values to make logical
     * representation more sensible; instead of having several
     * attributes with the same name and differing values, users can
     * associate multiple values with the same attribute
     * name. However, here we need to project this representation back
     * into a flat list with multiple KVP entries per attribute.
     */
    using identification::entities::tagged_value;
    std::list<tagged_value> tvs;
    for (const auto& e : p.entries()) {
        for (const auto& v : e.value())
            tvs.push_back(tagged_value(e.key(), v));
    }

    /*
     * Now obtain the profile's binding point. This must be populated.
     * it.
     *
     * FIXME: for now we don't actually make use of this. This is
     * because we have not yet properly implemented biding points in
     * profiles.
     */
    /*
      using boost::lexical_cast;
      using variability::entities::binding_point;
      const auto bp(lexical_cast<binding_point>(p.binding_point()));
    */

    /*
     * Finally, we can convert the list of entries into configuration
     * points and slot it in to our profile.
     */
    using variability::helpers::configuration_points_factory;
    configuration_points_factory cpf(fm, compatibility_mode);
    r.configuration_points(cpf.make(tvs));

    return r;
}

std::list<variability::entities::profile_template> profile_adapter::
adapt_profile_templates(const logical::entities::input_model_set& ms) {
    std::list<variability::entities::profile_template> r;

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

std::list<variability::entities::profile>
profile_adapter::adapt_profiles(const variability::entities::feature_model& fm,
    const logical::entities::input_model_set& ms,
    const bool compatibility_mode) {
    std::list<variability::entities::profile> r;

    const auto lambda(
        [&](auto& map) {
            for (const auto& pair : map)
                r.push_back(adapt(fm, *pair.second, compatibility_mode));
        });

    lambda(ms.target().variability_elements().profiles());
    for (const auto& m : ms.references())
        lambda(m.variability_elements().profiles());

    return r;
}

variability::transforms::profile_repository_inputs
profile_adapter::adapt(const variability::entities::feature_model& fm,
    const entities::input_model_set& ms, const bool compatibility_mode) {
    variability::transforms::profile_repository_inputs r;
    r.profiles(adapt_profiles(fm, ms, compatibility_mode));
    r.templates(adapt_profile_templates(ms));
    return r;
}

}
