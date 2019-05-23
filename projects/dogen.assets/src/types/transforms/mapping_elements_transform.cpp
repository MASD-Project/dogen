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
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.assets/types/traits.hpp"
#include "dogen.assets/io/meta_model/model_set_io.hpp"
#include "dogen.assets/types/meta_model/technical_space.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/meta_model/structural/builtin.hpp"
#include "dogen.assets/types/meta_model/structural/primitive.hpp"
#include "dogen.assets/types/meta_model/structural/exception.hpp"
#include "dogen.assets/types/meta_model/structural/enumeration.hpp"
#include "dogen.assets/types/meta_model/mapping/fixed_mappable.hpp"
#include "dogen.assets/types/meta_model/mapping/extensible_mappable.hpp"
#include "dogen.assets/types/meta_model/elements_traversal.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/transforms/mapping_elements_transform.hpp"

namespace {

const std::string
transform_id("assets.transforms.mapping_elements_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;
const std::string duplicate_fm_id("Duplicate fixed mapping ID: ");

}

namespace dogen::assets::transforms {

namespace {

struct feature_group {
    variability::meta_model::feature target;
    variability::meta_model::feature destination;
};

inline feature_group
make_feature_group(const variability::meta_model::feature_model& fm) {
    const variability::helpers::feature_selector s(fm);

    feature_group r;
    r.target = s.get_by_name(assets::traits::mapping::target());
    r.destination  = s.get_by_name(assets::traits::mapping::destination());
    return r;
}

/**
 * @brief Updates containment relationships in model.
 */
class destination_gatherer {
public:
    explicit destination_gatherer(const feature_group& fg)
        : feature_group_(fg), technical_space_() {}

public:
    void technical_space(const assets::meta_model::technical_space ts) {
        technical_space_ = ts;
    }

private:
    void gather(assets::meta_model::element& e);

public:
    void operator()(assets::meta_model::element&) { }
    void operator()(assets::meta_model::structural::builtin& b) { gather(b); }
    void operator()(assets::meta_model::structural::enumeration& e) {
        gather(e);
    }
    void operator()(assets::meta_model::structural::primitive& p) { gather(p); }
    void operator()(assets::meta_model::structural::object& o) { gather(o); }
    void operator()(assets::meta_model::structural::exception& e) { gather(e); }

public:
    const std::unordered_map<std::string,
                              std::list<
                                  assets::meta_model::mapping::destination>
                              >&
    result() const {
        return result_;
    }

public:
    const feature_group& feature_group_;
    assets::meta_model::technical_space technical_space_;
    std::unordered_map<std::string,
                       std::list<
                           assets::meta_model::mapping::destination>
                       >
    result_;
};

void destination_gatherer::gather(assets::meta_model::element &e) {
    BOOST_LOG_SEV(lg, trace) << "Processing element: "
                             << e.name().qualified().dot();

    const auto& cfg(*e.configuration());
    const variability::helpers::configuration_selector s(cfg);

    if (!s.has_configuration_point(feature_group_.target))
        return;

    assets::meta_model::mapping::destination d;
    d.name(e.name());
    d.technical_space(technical_space_);

    const auto target(s.get_text_content(feature_group_.target));
    BOOST_LOG_SEV(lg, trace) << "Read target: " << target;

    result_[target].push_back(d);
}

}

std::unordered_map<std::string,
                   std::list<
                       assets::meta_model::mapping::destination>
                   >
mapping_elements_transform::make_destinations(
    const variability::meta_model::feature_model &fm,
    const assets::meta_model::model_set &ms) {

    const auto fg(make_feature_group(fm));
    destination_gatherer dg(fg);
    using assets::meta_model::elements_traversal;

    dg.technical_space(ms.target().input_technical_space());
    elements_traversal(ms.target(), dg);

    for (const auto &m : ms.references()) {
        dg.technical_space(m.input_technical_space());
        elements_traversal(m, dg);
    }

    return dg.result();
}

void mapping_elements_transform::populate_extensible_mappables(
    const std::unordered_map<std::string,
    std::list<assets::meta_model::mapping::destination>>&
    destinations_for_target, assets::meta_model::model_set& ms) {

    const auto lambda(
        [&](const std::string& target,
            const std::list<assets::meta_model::mapping::destination>& dests,
            assets::meta_model::model& m) {
            auto& em(m.mapping_elements().extensible_mappables());
            const auto i(em.find(target));
            if (i == em.end())
                return;

            auto& mappable(*i->second);
            for (const auto& dest : dests)
                mappable.destinations().push_back(dest);
        });

    for (const auto& pair : destinations_for_target) {
        const auto target(pair.first);
        const auto& dests(pair.second);
        lambda(target, dests, ms.target());
        for (auto& ref : ms.references())
            lambda(target, dests, ref);
    }
}

void mapping_elements_transform::populate_fixed_mappables(
    const variability::meta_model::feature_model& fm,
    assets::meta_model::model_set& ms) {

    const auto fg(make_feature_group(fm));
    const auto lambda(
        [&](assets::meta_model::model& m) {
            auto& maps(m.mapping_elements().fixed_mappables());
            for (auto& pair : maps) {
                auto& mm(*pair.second);
                const auto& cfg(*mm.configuration());
                const variability::helpers::configuration_selector s(cfg);
                const auto dst(s.get_text_content(fg.destination));
                mm.destination(dst);

                const auto fm_id(mm.name().qualified().colon());
                const auto fm_pair(std::make_pair(fm_id, dst));
                const auto inserted(ms.fixed_mappings().insert(fm_pair).second);
                if (!inserted) {
                    BOOST_LOG_SEV(lg, error) << duplicate_fm_id << fm_id;
                    BOOST_THROW_EXCEPTION(
                        transformation_error(duplicate_fm_id + fm_id));
                }
            }
        });

    lambda(ms.target());
    for (auto& ref : ms.references())
        lambda(ref);
}

void mapping_elements_transform::
apply(const context& ctx, assets::meta_model::model_set& ms) {
    const auto& id(ms.target().name().qualified().dot());
    tracing::scoped_transform_tracer stp(lg, "mapping elements transform",
        transform_id, id, *ctx.tracer(), ms);

    /*
     * First we obtain all of the model elements which have been
     * mapped to a extensible mappable element. Note that we could
     * have a very simple optimisation here: if there are no
     * extensible mappable elements (i.e. the target of the mapping)
     * then we don't need to bother to do anything at all. However, we
     * have not done this because in the future, we want to make all
     * types that "request" mapping, so that we can figure out if
     * there are any missing mappings.
     */
    const auto& fm(*ctx.feature_model());
    const auto dests(make_destinations(fm, ms));

    /*
     * Now we locate all of the targets of the mappings and add the
     * destinations.
     */
    populate_extensible_mappables(dests, ms);

    /*
     * Finally we populate all of the fixed mappables.
     */
    populate_fixed_mappables(fm, ms);

    stp.end_transform(ms);
}

}
