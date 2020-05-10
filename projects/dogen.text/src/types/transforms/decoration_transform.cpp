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
#include <unordered_map>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/types/features/decoration.hpp"
#include "dogen.logical/types/helpers/decoration_repository.hpp"
#include "dogen.logical/types/helpers/decoration_configuration.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/decoration/licence.hpp"
#include "dogen.logical/types/entities/decoration/modeline_group.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/io/entities/decoration/element_properties_io.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.logical/hash/entities/technical_space_hash.hpp"
#include "dogen.text/types/helpers/decoration_repository_factory.hpp"
#include "dogen.logical/types/formatters/decoration_formatter.hpp"
#include "dogen.logical/io/helpers/decoration_configuration_io.hpp"
#include "dogen.logical/types/helpers/decoration_configuration_factory.hpp"
#include "dogen.logical/types/helpers/decoration_factory.hpp"
#include "dogen.text/io/entities/model_io.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/decoration_transform.hpp"

namespace {

const std::string transform_id("text.transforms.decoration_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;
const std::string technical_space_not_found("Technical space not found: ");
const std::string duplicate_technical_space(
    "Duplicate decoration for technical space: ");

}

namespace dogen::text::transforms {

using logical::entities::decoration::generation_marker;
using logical::entities::decoration::modeline;

bool decoration_transform::
is_generatable(const logical::entities::name& meta_name) {
    // FIXME: massive hack for now.
    using mnf = logical::helpers::meta_name_factory;
    static const auto otn(mnf::make_object_template_name());
    static const auto ln(mnf::make_licence_name());
    static const auto mln(mnf::make_modeline_name());
    static const auto mgn(mnf::make_modeline_group_name());
    static const auto gmn(mnf::make_generation_marker_name());

    const auto id(meta_name.qualified().dot());
    return
        id != otn.qualified().dot() &&
        id != ln.qualified().dot() &&
        id != mln.qualified().dot() &&
        id != mgn.qualified().dot() &&
        id != gmn.qualified().dot();
}

void decoration_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "decoration transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * We start by setting up the decoration repository, which has all
     * the required information to build decorations, indexed by the
     * keys we need.
     */
    helpers::decoration_repository_factory f;
    const auto drp(f.make(m));
    BOOST_LOG_SEV(lg, debug) << "Created decoration repository factory.";

    /*
     * Then we obtain the decoration configuration for the root
     * module, which is the default decoration configuration for all
     * model elements.
     */
    const auto& fm(*ctx.feature_model());
    const auto fg(logical::features::decoration::make_feature_group(fm));
    auto& rm(*m.root_module());
    const logical::helpers::decoration_configuration_factory dcf;
    const auto root_dc(dcf.make(fg, *rm.configuration()));

    /*
     * With the default configuration, we can create the global
     * decoration for each of the required technical spaces. We can
     * also apply the global configuration to the root module. Note
     * that we know that the root module does not need a technical
     * space override, so we can safely default it to the model
     * technical space.
     */
    const auto mts(m.output_technical_space());
    const auto gt(ctx.generation_timestamp());
    const auto h(m.origin_sha1_hash());
    logical::helpers::decoration_factory df(drp, gt, h);
    std::unordered_map<logical::entities::technical_space,
                       boost::optional<
                           logical::entities::decoration::element_properties>
        > root_decorations;
    BOOST_LOG_SEV(lg, trace) << "Generating all global decorations";
    for (const auto ts : m.all_technical_spaces()) {
        BOOST_LOG_SEV(lg, trace) << "Generating global decoration for "
                                 <<  "technical space: " << ts;

        const auto gd(df.make_global_decoration(root_dc, ts));
        root_decorations[ts] = gd;

        if (ts == mts && gd) {
            BOOST_LOG_SEV(lg, trace) << "Populating the root module "
                                     <<  "decoration.";

            auto pair(std::make_pair(ts, *gd));
            const auto inserted(rm.decoration().insert(pair).second);
            if (!inserted) {
                const auto s(boost::lexical_cast<std::string>(ts));
                BOOST_LOG_SEV(lg, error) << duplicate_technical_space << s;
                BOOST_THROW_EXCEPTION(
                    transformation_error(duplicate_technical_space + s ));
            }
        }
    }
    BOOST_LOG_SEV(lg, trace) << "Generated all global decorations.";

    /*
     * Now we loop through all model elements. We obtain each
     * element's decoration configuration, if any, and use it and the
     * root decoration configuration to build the elements decoration.
     */
    const auto root_id(rm.name().qualified().dot());
    const auto ats(logical::entities::technical_space::agnostic);
    for (auto ea : m.elements()) {
        auto& e(*ea.element());
        const auto id(e.name().qualified().dot());
        BOOST_LOG_SEV(lg, trace) << "Processing element: " << id;

        if (e.origin_type() != logical::entities::origin_types::target) {
            BOOST_LOG_SEV(lg, trace) << "Element is not in target model.";
            continue;
        }

        /*
         * If the meta-element is intrinsically not generatable, there
         * is no point in creating a decoration for it.
         */
        if (!is_generatable(e.meta_name())) {
            BOOST_LOG_SEV(lg, trace) << "Element is not generatable: "
                                     << e.meta_name().qualified().dot();
            continue;
        }

        /*
         * The root module decoration was already handled and it is
         * different from the rest of the model elements; if we detect
         * it, we need to skip it.
         */
        if (e.name().qualified().dot() == root_id) {
            BOOST_LOG_SEV(lg, trace) << "Element is root module, skipping.";
            continue;
        }

        /*
         * For all elements (other than the root module), we need to
         * build the decoration based on the local configuration, and
         * the global configuration.
         */
        const auto& cfg(*e.configuration());
        logical::helpers::decoration_configuration_factory dcf;
        const auto dc(dcf.make(fg, cfg));
        auto lambda(
            [&](const logical::entities::technical_space nts) {
                const auto i(root_decorations.find(nts));
                if (i == root_decorations.end()) {
                    const auto s(boost::lexical_cast<std::string>(nts));
                    BOOST_LOG_SEV(lg, error) << technical_space_not_found << s;
                    BOOST_THROW_EXCEPTION(
                        transformation_error(technical_space_not_found + s));
                }
                const auto& gd(i->second);
                const auto ld(df.make_local_decoration(gd, root_dc, dc, nts));
                if (ld) {
                    auto pair(std::make_pair(nts, *ld));
                    const auto inserted(e.decoration().insert(pair).second);
                    if (!inserted) {
                        const auto s(boost::lexical_cast<std::string>(nts));
                        BOOST_LOG_SEV(lg, error) << duplicate_technical_space
                                                 << s;
                        BOOST_THROW_EXCEPTION(transformation_error(
                                duplicate_technical_space + s));
                    }
                }
            });

        /*
         * Model elements may not belong to the dominant technical
         * space. If that's the case, we need to ensure we use the
         * element's technical space instead.
         */
        const auto its(e.intrinsic_technical_space());
        const auto ts(its == ats ? mts : its);
        BOOST_LOG_SEV(lg, trace) << "Element intrinsic technical space: " << its
                                 << " Model technical space: " << mts;
        lambda(ts);

        /*
         * FIXME: hack for ODB options. We inject it regardless, just
         * so that when the formatters create the ODB options, it is
         * available.
         */
        const auto odb_ts(logical::entities::technical_space::odb);
        if (ts != odb_ts) {
            lambda(odb_ts);
            BOOST_LOG_SEV(lg, trace) << "Added decoration for ODB.";
        }

        /*
         * FIXME: hack for XML. We inject it regardless, just so that
         * that when the formatters need it, it is available.
         */
        const auto xml_ts(logical::entities::technical_space::xml);
        if (ts != xml_ts) {
            lambda(xml_ts);
            BOOST_LOG_SEV(lg, trace) << "Added decoration for XML.";
        }

        /*
         * FIXME: hack for CMake. We inject it regardless, just so
         * that when the formatters need it, it is available.
         */
        const auto cmake_ts(logical::entities::technical_space::cmake);
        if (ts != cmake_ts) {
            lambda(cmake_ts);
            BOOST_LOG_SEV(lg, trace) << "Added decoration for CMake.";
        }
    }
    stp.end_transform(m);
}

}
