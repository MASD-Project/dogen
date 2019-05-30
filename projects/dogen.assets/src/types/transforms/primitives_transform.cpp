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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.assets/types/traits.hpp"
#include "dogen.assets/io/meta_model/technical_space_io.hpp"
#include "dogen.assets/types/helpers/name_factory.hpp"
#include "dogen.assets/types/features/primitive.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/transforms/primitives_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.primitives_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string csharp_value("Value");
const std::string cpp_value("value");
const std::string documentation("Obtain the underlying value.");

const std::string unsupported_technical_space(
    "Invalid or unsupported technical space: ");
const std::string missing_underlier(
    "Primitive does not have an underlying element name: ");

}

namespace dogen::assets::transforms {

std::string primitives_transform::
obtain_value_attribute_simple_name(const meta_model::technical_space ts) {
    using meta_model::technical_space;
    switch(ts) {
    case technical_space::csharp: return csharp_value;
    case technical_space::cpp: return cpp_value;
    default: {
        const auto s(boost::lexical_cast<std::string>(ts));
        BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
        BOOST_THROW_EXCEPTION(
            transformation_error(unsupported_technical_space + s));
    } }
}

primitives_transform::feature_group primitives_transform::
make_feature_group(const variability::meta_model::feature_model& fm) {
    BOOST_LOG_SEV(lg, debug) << "Creating feature group.";

    feature_group r;

    const variability::helpers::feature_selector s(fm);

    const auto in(traits::primitive::is_nullable());
    r.is_nullable = s.get_by_name(in);

    const auto uta(traits::primitive::use_type_aliasing());
    r.use_type_aliasing = s.get_by_name(uta);

    BOOST_LOG_SEV(lg, debug) << "Created feature group.";
    return r;
}

void primitives_transform::
populate_from_configuration(const feature_group& fg,
    meta_model::structural::primitive& p) {
    const auto& cfg(*p.configuration());
    const variability::helpers::configuration_selector s(cfg);
    p.is_nullable(s.get_boolean_content_or_default(fg.is_nullable));
    p.use_type_aliasing(s.get_boolean_content_or_default(fg.use_type_aliasing));
}

void primitives_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "primitives transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    // const auto fg(make_feature_group(*ctx.feature_model()));
    const auto& fm(*ctx.feature_model());
    const auto fg(features::primitive::make_feature_group(fm));
    const auto its(m.input_technical_space());
    for (auto& pair : m.structural_elements().primitives()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Transforming: " << id;

        auto& p(*pair.second);
        const auto& cfg(*p.configuration());
        const auto scfg(features::primitive::make_static_configuration(fg, cfg));

        p.is_nullable(scfg.is_nullable);
        p.use_type_aliasing(scfg.use_type_aliasing);

        /*
         * Obtain the underlying element name from the meta-data. If there
         * isn't one, bomb out as primitives require it.
         */
        const auto ue(boost::algorithm::trim_copy(scfg.underlying_element));
        if (ue.empty()) {
            BOOST_LOG_SEV(lg, error) << missing_underlier << id;
            BOOST_THROW_EXCEPTION(transformation_error(missing_underlier + id));
        }

        /*
         * Create the value attribute.
         */
        helpers::name_factory nf;
        const auto& n(p.name());
        const auto sn(obtain_value_attribute_simple_name(its));

        meta_model::attribute attr;
        attr.name(nf.build_attribute_name(n, sn));
        attr.unparsed_type(ue);
        attr.documentation(documentation);

        p.value_attribute(attr);
    }

    stp.end_transform(m);
}

}
