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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.variability/types/entry_selector.hpp"
#include "masd.dogen.variability/types/type_repository_selector.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/io/meta_model/technical_space_io.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/elements_traversal.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/technical_space_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.technical_space_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string cpp_technical_space("cpp");
const std::string csharp_technical_space("csharp");
const std::string agnostic_technical_space("agnostic");

const std::string technical_space_not_set("Input technical space must be set.");
const std::string unsupported_technical_space(
    "Technical space is not supported: ");

}

namespace masd::dogen::coding::transforms {

using meta_model::technical_space;

meta_model::technical_space
technical_space_transform::to_technical_space(const std::string& s) {
    if (s == cpp_technical_space)
        return technical_space::cpp;
    else if (s == csharp_technical_space)
        return technical_space::csharp;
    else if (s == agnostic_technical_space)
        return technical_space::agnostic;

    BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
    BOOST_THROW_EXCEPTION(
        transformation_error(unsupported_technical_space + s));
}

technical_space_transform::type_group technical_space_transform::
make_type_group(const variability::type_repository& atrp) {
    type_group r;
    const variability::type_repository_selector s(atrp);
    r.output_technical_space =
        s.select_type_by_name(traits::output_technical_space());
    return r;
}

std::list<meta_model::technical_space>
technical_space_transform::make_output_technical_space(const type_group& tg,
    const variability::annotation& a) {
    const variability::entry_selector s(a);

    std::list<meta_model::technical_space> r;
    if (!s.has_entry(tg.output_technical_space))
        return r;

    const auto ots(s.get_text_collection_content(tg.output_technical_space));
    for (const auto ts : ots)
        r.push_back(to_technical_space(ts));

    return r;
}

technical_space_transform::feature_group technical_space_transform::
make_feature_group(const variability::meta_model::feature_model& fm) {
    feature_group r;
    const variability::helpers::feature_selector s(fm);
    r.output_technical_space =
        s.get_by_name(traits::output_technical_space());
    return r;
}

std::list<meta_model::technical_space>
technical_space_transform::make_output_technical_space(const feature_group& tg,
    const variability::meta_model::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);

    std::list<meta_model::technical_space> r;
    if (!s.has_configuration_point(tg.output_technical_space))
        return r;

    const auto ots(s.get_text_collection_content(tg.output_technical_space));
    for (const auto ts : ots)
        r.push_back(to_technical_space(ts));

    return r;
}

void technical_space_transform::
setup_intrinsic_technical_space(meta_model::model& m) {
    meta_model::elements_traversal(m,
        [](meta_model::element& e) {
            e.intrinsic_technical_space(technical_space::agnostic);
        });
}

void technical_space_transform::
apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "technical space transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * Update the intrinsic technical space on all modeling elements
     * available thus far.
     */
    setup_intrinsic_technical_space(m);

    /*
     * Ensure the input technical space has been set by now.
     */
    const auto inv(meta_model::technical_space::invalid);
    const bool has_input_ts(m.input_technical_space() != inv);
    if (!has_input_ts) {
        BOOST_LOG_SEV(lg, error) << technical_space_not_set;
        BOOST_THROW_EXCEPTION(transformation_error(technical_space_not_set));
    }

    /*
     * If we've already got output technical_space, there is no work
     * required.
     */
    if (!m.output_technical_spaces().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Model has output technical spaces set: "
                                 << m.output_technical_spaces();
        return; // not ending tracing by design as there are no changes.
    }

    /*
     * Read the output technical_space requested by the user.
     */
    const auto& ra(m.root_module()->annotation());
    const auto& cfg(*m.root_module()->configuration());
    const auto tg(make_type_group(*ctx.type_repository()));
    const auto fg(make_feature_group(*ctx.feature_model()));
    const auto ol(ctx.use_configuration() ?
        make_output_technical_space(fg, cfg) :
        make_output_technical_space(tg, ra));

    /*
     * If the user did not set an output technical space, assume the
     * input as output. Validator will ensure this technical space is
     * legal - e.g. the output technical space is not abstract but can
     * be extracted into a concrete technical space.
     */
    if (ol.empty()) {
        m.output_technical_spaces().push_back(m.input_technical_space());
        BOOST_LOG_SEV(lg, debug) << "No overrides for output technical space "
                                 << "  found. Defaulting to input: "
                                 << m.output_technical_spaces();
    } else {
        m.output_technical_spaces(ol);
        BOOST_LOG_SEV(lg, debug) << "Expanded output technical spaces to: "
                                 << m.output_technical_spaces();
    }

    stp.end_transform(m);
}

}
