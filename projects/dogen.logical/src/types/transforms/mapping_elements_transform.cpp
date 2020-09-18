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
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.logical/types/traits.hpp"
#include "dogen.logical/io/entities/input_model_set_io.hpp"
#include "dogen.logical/types/features/mapping.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/mapping/fixed_mappable.hpp"
#include "dogen.logical/types/entities/mapping/extensible_mappable.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/mapping_elements_transform.hpp"

namespace {

const std::string
transform_id("logical.transforms.mapping_elements_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;
const std::string duplicate_fm_id("Duplicate fixed mapping ID: ");

}

namespace dogen::logical::transforms {

using identification::entities::logical_id;

namespace {

/**
 * @brief Updates containment relationships in model.
 */
class destination_gatherer {
public:
    explicit destination_gatherer(const features::mapping::feature_group& fg)
        : feature_group_(fg), technical_space_() {}

public:
    void technical_space(const identification::entities::technical_space ts) {
        technical_space_ = ts;
    }

private:
    void gather(entities::element& e);

public:
    void operator()(entities::element&) { }
    void operator()(entities::structural::builtin& b) { gather(b); }
    void operator()(entities::structural::enumeration& e) {
        gather(e);
    }
    void operator()(entities::structural::primitive& p) { gather(p); }
    void operator()(entities::structural::object& o) { gather(o); }
    void operator()(entities::structural::exception& e) { gather(e); }

public:
    const std::unordered_map<logical_id,
                             std::list<entities::mapping::destination>>&
    result() const {
        return result_;
    }

public:
    const features::mapping::feature_group& feature_group_;
    identification::entities::technical_space technical_space_;
    std::unordered_map<logical_id,
                       std::list<entities::mapping::destination>>
    result_;
};

void destination_gatherer::gather(entities::element &e) {
    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, trace) << "Processing element: " << id;

    using features::mapping;
    const auto scfg(mapping::make_static_configuration(feature_group_, e));
    BOOST_LOG_SEV(lg, trace) << "Read target: " << scfg.target;

    using entities::mapping::destination;
    const destination dst(e.name(), technical_space_);
    logical_id target_id(scfg.target);
    result_[target_id].push_back(dst);
}

}

std::unordered_map<logical_id,
                   std::list<entities::mapping::destination>>
mapping_elements_transform::
make_destinations(const variability::entities::feature_model &fm,
    const entities::input_model_set &ms) {
    const auto fg(features::mapping::make_feature_group(fm));
    destination_gatherer dg(fg);
    dg.technical_space(ms.target().input_technical_space());

    using entities::elements_traversal;
    elements_traversal(ms.target(), dg);

    for (const auto &m : ms.references()) {
        dg.technical_space(m.input_technical_space());
        elements_traversal(m, dg);
    }

    return dg.result();
}

void mapping_elements_transform::
populate_extensible_mappables(const std::unordered_map<logical_id,
    std::list<entities::mapping::destination>>&
    destinations_for_target, entities::input_model_set& ms) {

    using entities::mapping::destination;
    const auto lambda([&](const logical_id& target,
            const std::list<destination>& dsts, entities::model& m) {
            auto& em(m.mapping_elements().extensible_mappables());
            const auto i(em.find(target));
            if (i == em.end())
                return;

            auto& mappable(*i->second);
            for (const auto& dst : dsts)
                mappable.destinations().push_back(dst);
        });

    for (const auto& pair : destinations_for_target) {
        const auto target(pair.first);
        const auto& dsts(pair.second);
        lambda(target, dsts, ms.target());
        for (auto& ref : ms.references())
            lambda(target, dsts, ref);
    }
}

void mapping_elements_transform::
populate_fixed_mappables(const variability::entities::feature_model& fm,
    entities::input_model_set& ms) {
    const auto fg(features::mapping::make_feature_group(fm));
    const auto lambda(
        [&](entities::model& m) {
            auto& maps(m.mapping_elements().fixed_mappables());
            for (auto& pair : maps) {
                auto& fm(*pair.second);
                using features::mapping;
                const auto scfg(mapping::make_static_configuration(fg, fm));
                fm.destination(scfg.destination);

                const auto fm_id(fm.name().qualified().colon());
                const auto fm_pair(std::make_pair(fm_id, scfg.destination));
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
apply(const context& ctx, entities::input_model_set& ms) {
    const auto& id(ms.target().name().qualified().dot());
    tracing::scoped_transform_tracer stp(lg, "mapping elements",
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
    const auto dsts(make_destinations(fm, ms));

    /*
     * Now we locate all of the targets of the mappings and add the
     * destinations.
     */
    populate_extensible_mappables(dsts, ms);

    /*
     * Finally we populate all of the fixed mappables.
     */
    populate_fixed_mappables(fm, ms);

    stp.end_transform(ms);
}

}
