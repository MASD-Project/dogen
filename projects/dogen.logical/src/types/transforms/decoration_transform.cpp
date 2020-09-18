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
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.logical/types/features/decoration.hpp"
#include "dogen.logical/types/helpers/decoration_repository.hpp"
#include "dogen.logical/types/helpers/decoration_configuration.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/decoration/licence.hpp"
#include "dogen.logical/types/entities/decoration/modeline_group.hpp"
#include "dogen.logical/io/entities/decoration/element_properties_io.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.identification/hash/entities/technical_space_hash.hpp"
#include "dogen.logical/types/helpers/decoration_repository_factory.hpp"
#include "dogen.logical/types/formatters/decoration_formatter.hpp"
#include "dogen.logical/io/helpers/decoration_configuration_io.hpp"
#include "dogen.logical/types/helpers/decoration_configuration_factory.hpp"
#include "dogen.logical/types/helpers/decoration_factory.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/transforms/decoration_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.decoration_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;
const std::string technical_space_not_found("Technical space not found: ");
const std::string duplicate_technical_space(
    "Duplicate decoration for technical space: ");
const std::string unexpected_output_ts(
    "Unexpected number of output technical spaces: ");

}

namespace dogen::logical::transforms {

using helpers::decoration_configuration;
using identification::entities::technical_space;
using identification::entities::logical_meta_name;

typedef std::unordered_map<technical_space,
                           boost::optional<
                               entities::decoration::element_properties>
                           > root_decorations_type;

/**
 * @brief Updates the decorations of relevant elements.
 */
class decoration_updater {
public:
    decoration_updater(const root_decorations_type& root_decorations,
        const helpers::decoration_factory& df,
        const boost::optional<decoration_configuration>& root_dc,
        const std::string& root_id,
        const features::decoration::feature_group& fg,
        const technical_space output_technical_space);

private:
    /**
     * @brief Returns true the meta-model element is intrinsically
     * generatable false otherwise.
     */
    bool is_generatable(const logical_meta_name& meta_name) const;

    /**
     * @brief Returns true if the type needs decorations.
     */
    bool requires_decorations(entities::element& e) const;

    /**
     * @brief Processes the decoration for the supplied element,
     * against the supplied technical space.
     */
    void process_element(const technical_space ts,
        const boost::optional<decoration_configuration>& dc,
        entities::element& e);

public:
    void operator()(entities::element& e);

private:
    const root_decorations_type& root_decorations_;
    const helpers::decoration_factory& decoration_factory_;
    const boost::optional<decoration_configuration> root_dc_;
    const std::string root_id_;
    const features::decoration::feature_group& feature_group_;
    const technical_space output_technical_space_;
};

decoration_updater::decoration_updater(
    const root_decorations_type& root_decorations,
    const helpers::decoration_factory& df,
    const boost::optional<decoration_configuration>& root_dc,
    const std::string& root_id,
    const features::decoration::feature_group& fg,
    const technical_space ots)
    : root_decorations_(root_decorations), decoration_factory_(df),
      root_dc_(root_dc), root_id_(root_id), feature_group_(fg),
      output_technical_space_(ots) {}

bool decoration_updater::
is_generatable(const logical_meta_name& meta_name) const {
    // FIXME: massive hack for now.
    using mnf = identification::helpers::logical_meta_name_factory;
    static const auto otn(mnf::make_object_template_name());
    static const auto ln(mnf::make_licence_name());
    static const auto mln(mnf::make_modeline_name());
    static const auto mgn(mnf::make_modeline_group_name());
    static const auto gmn(mnf::make_generation_marker_name());

    const auto id(meta_name.id().value());
    return
        id != otn.id().value() &&
        id != ln.id().value() &&
        id != mln.id().value() &&
        id != mgn.id().value() &&
        id != gmn.id().value();
}

bool decoration_updater::requires_decorations(entities::element& e) const {
    /*
     * We don't need to generate decorations for any elements which
     * are not part of the target model.
     */
    using identification::entities::model_type;
    if (e.provenance().model_type() != model_type::target) {
        BOOST_LOG_SEV(lg, trace) << "Element is not in target model.";
        return false;
    }

    /*
     * If the meta-element is intrinsically not generatable, there
     * is no point in creating a decoration for it.
     */
    if (!is_generatable(e.meta_name())) {
        BOOST_LOG_SEV(lg, trace) << "Element is not generatable: "
                                 << e.meta_name().id();
        return false;
    }

    /*
     * The root module decoration was already handled and it is
     * different from the rest of the model elements; if we detect
     * it, we need to skip it.
     */
    if (e.name().qualified().dot() == root_id_) {
        BOOST_LOG_SEV(lg, trace) << "Element is root module, skipping.";
        return false;
    }
    return true;
}

void decoration_updater::
process_element(const technical_space ts,
    const boost::optional<decoration_configuration>& dc,
    entities::element& e) {
    const auto i(root_decorations_.find(ts));
    if (i == root_decorations_.end()) {
        const auto s(boost::lexical_cast<std::string>(ts));
        BOOST_LOG_SEV(lg, error) << technical_space_not_found << s;
        BOOST_THROW_EXCEPTION(
            transformation_error(technical_space_not_found + s));
    }

    const auto& gd(i->second);
    const auto& df(decoration_factory_);
    const auto ld(df.make_local_decoration(gd, root_dc_, dc, ts));
    if (ld) {
        auto pair(std::make_pair(ts, *ld));
        const auto inserted(e.decoration().insert(pair).second);
        if (!inserted) {
            const auto s(boost::lexical_cast<std::string>(ts));
            BOOST_LOG_SEV(lg, error) << duplicate_technical_space << s;
            BOOST_THROW_EXCEPTION(transformation_error(
                    duplicate_technical_space + s));
        }
    }
}

void decoration_updater::operator()(entities::element& e) {
    const auto id(e.name().qualified().dot());
    BOOST_LOG_SEV(lg, trace) << "Processing element: " << id;

    /*
     * If we do not require decorations, there is no point in
     * proceeding.
     */
    if (!requires_decorations(e))
        return;

    /*
     * For all elements (other than the root module), we need to
     * build the decoration based on the local configuration, and
     * the global configuration.
     */
    const auto& cfg(*e.configuration());
    helpers::decoration_configuration_factory dcf;
    const auto dc(dcf.make(feature_group_, cfg));

    /*
     * Model elements may not belong to the dominant technical
     * space. If that's the case, we need to ensure we use the
     * element's technical space instead.
     */
    const auto its(e.intrinsic_technical_space());
    const auto ats(technical_space::agnostic);
    const auto ts(its == ats ? output_technical_space_ : its);
    BOOST_LOG_SEV(lg, trace) << "Element intrinsic technical space: " << its
                             << " Model technical space: "
                             << output_technical_space_;
    process_element(ts, dc, e);

    /*
     * FIXME: hack for ODB options. We inject it regardless, just
     * so that when the formatters create the ODB options, it is
     * available.
     */
    const auto odb_ts(technical_space::odb);
    if (ts != odb_ts) {
        process_element(odb_ts, dc, e);
        BOOST_LOG_SEV(lg, trace) << "Added decoration for ODB.";
    }

    /*
     * FIXME: hack for XML. We inject it regardless, just so that
     * that when the formatters need it, it is available.
     */
    const auto xml_ts(technical_space::xml);
    if (ts != xml_ts) {
        process_element(xml_ts, dc, e);
        BOOST_LOG_SEV(lg, trace) << "Added decoration for XML.";
    }

    /*
     * FIXME: hack for CMake. We inject it regardless, just so
     * that when the formatters need it, it is available.
     */
    const auto cmake_ts(technical_space::cmake);
    if (ts != cmake_ts) {
        process_element(cmake_ts, dc, e);
        BOOST_LOG_SEV(lg, trace) << "Added decoration for CMake.";
    }
}

void decoration_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "decoration",
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
    const auto fg(features::decoration::make_feature_group(fm));
    auto& rm(*m.root_module());
    const helpers::decoration_configuration_factory dcf;
    const auto root_dc(dcf.make(fg, *rm.configuration()));

    const auto mts([&]() {
            const auto& ots(m.output_technical_spaces());
            const auto sz(ots.size());
            if (sz != 1) {
                std::ostringstream os;
                os << unexpected_output_ts << sz;
                const auto msg(os.str());
                BOOST_LOG_SEV(lg, error) << msg;
                BOOST_THROW_EXCEPTION(transformation_error(msg));
            }
            return m.output_technical_spaces().front();
        }());

    /*
     * With the default configuration, we can create the global
     * decoration for each of the required technical spaces. We can
     * also apply the global configuration to the root module. Note
     * that we know that the root module does not need a technical
     * space override, so we can safely default it to the model
     * technical space.
     */
    const auto gt(ctx.activity_timestamp());
    const auto h(m.provenance().model_sha1_hash());
    helpers::decoration_factory df(drp, gt, h.value());
    root_decorations_type root_decorations;
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
    decoration_updater u(root_decorations, df, root_dc, root_id, fg, mts);
    entities::elements_traversal(m, u);

    stp.end_transform(m);
}

}
