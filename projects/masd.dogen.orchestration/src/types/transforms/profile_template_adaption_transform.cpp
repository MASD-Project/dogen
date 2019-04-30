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
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.orchestration/types/traits.hpp"
#include "masd.dogen.orchestration/types/transforms/transform_exception.hpp"
#include "masd.dogen.orchestration/types/transforms/profile_template_adaption_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.profile_template_adaption_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;
const std::string binding_point_any("any");
const std::string binding_point_global("global");
const std::string binding_point_element("element");
const std::string binding_point_property("property");
const std::string binding_point_operation("operation");
const std::string template_kind_instance("instance");
const std::string template_kind_recursive_template("recursive_template");
const std::string template_kind_backend_template("backend_template");
const std::string template_kind_facet_template("facet_template");
const std::string template_kind_archetype_template("archetype_template");

const std::string invalid_binding_point("Invalid binding point: ");
const std::string invalid_template_type("Invalid template type: ");

}

namespace masd::dogen::orchestration::transforms {

profile_template_adaption_transform::feature_group
profile_template_adaption_transform::make_feature_group(
    const variability::meta_model::feature_model& fm) {

    feature_group r;
    const variability::helpers::feature_selector s(fm);
    r.binding_point = s.get_by_name(traits::variability::binding_point());
    r.labels = s.get_by_name(traits::variability::labels());
    r.archetype_location_kernel = s.get_by_name(
        traits::variability::archetype_location_kernel());
    r.archetype_location_backend = s.get_by_name(
        traits::variability::archetype_location_backend());
    r.template_kind = s.get_by_name(traits::variability::template_kind());

    return r;
}

variability::meta_model::binding_point profile_template_adaption_transform::
make_binding_point(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    const auto tc(s.get_text_content(fg.binding_point));
    BOOST_LOG_SEV(lg, trace) << "Read binding point: " << tc;

    using variability::meta_model::binding_point;
    if (tc == binding_point_any)
        return binding_point::global;
    else if (tc == binding_point_global)
        return binding_point::global;
    else if (tc == binding_point_element)
        return binding_point::element;
    else if (tc == binding_point_property)
        return binding_point::property;
    else if (tc == binding_point_operation)
        return binding_point::operation;

    BOOST_LOG_SEV(lg, error) << invalid_binding_point << tc;
    BOOST_THROW_EXCEPTION(
        transform_exception(invalid_binding_point + tc));
}

std::list<std::string> profile_template_adaption_transform::
make_labels(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.labels)) {
        const auto r(s.get_text_collection_content(fg.labels));
        BOOST_LOG_SEV(lg, trace) << "Read labels: " << r;
        return r;
    }

    return std::list<std::string>{};
}

std::string profile_template_adaption_transform::
make_archetype_location_kernel(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    const auto r(s.get_text_content(fg.archetype_location_kernel));
    BOOST_LOG_SEV(lg, trace) << "Read kernel: " << r;
    return r;
}

std::string profile_template_adaption_transform::
archetype_location_backend(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.archetype_location_backend)) {
        const auto r(s.get_text_content(fg.archetype_location_backend));
        BOOST_LOG_SEV(lg, trace) << "Read backend: " << r;
        return r;
    }

    return empty;
}

variability::meta_model::template_kind profile_template_adaption_transform::
make_template_kind(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    const auto tc(s.get_text_content(fg.binding_point));
    BOOST_LOG_SEV(lg, trace) << "Read template kind: " << tc;

    using variability::meta_model::template_kind;
    if (tc == template_kind_instance)
        return template_kind::instance;
    else if (tc == template_kind_recursive_template)
        return template_kind::recursive_template;
    else if (tc == template_kind_backend_template)
        return template_kind::backend_template;
    else if (tc == template_kind_facet_template)
        return template_kind::facet_template;
    else if (tc == template_kind_archetype_template)
        return template_kind::archetype_template;

    BOOST_LOG_SEV(lg, error) << invalid_template_type << tc;
    BOOST_THROW_EXCEPTION(
        transform_exception(invalid_template_type + tc));
}

variability::meta_model::profile_template profile_template_adaption_transform::
adapt(const coding::meta_model::variability_profile_template& /*vpt*/) {
    variability::meta_model::profile_template r;
    return r;
}

std::list<variability::meta_model::profile_template>
profile_template_adaption_transform::
apply(const context& /*ctx*/, const coding::meta_model::model_set& /*ms*/) {
    std::list<variability::meta_model::profile_template> r;
    return r;
}

}
