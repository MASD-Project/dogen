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
#include "dogen.logical/types/helpers/mapping_actions.hpp"
#include "dogen.logical/types/helpers/mapping_value.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/lexical_cast/entities/technical_space_lc.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/io/entities/input_model_set_io.hpp"
#include "dogen.logical/types/entities/mapping/extensible_mappable.hpp"
#include "dogen.logical/io/helpers/mapping_io.hpp"
#include "dogen.logical/io/helpers/mapping_set_io.hpp"
#include "dogen.logical/io/helpers/mapping_actions_io.hpp"
#include "dogen.logical/io/helpers/mapping_set_repository_io.hpp"
#include "dogen.logical/types/helpers/mapper.hpp"
#include "dogen.logical/types/helpers/mappings_validator.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/extensible_mapping_transform.hpp"

namespace {

const std::string transform_id(
    "logical.transforms.extensible_mapping_transform");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string default_mapping_set_name("default.mapping_set");
const std::string duplicate_mappable_id("Duplicate extensible mappable id: ");
const std::string duplicate_agnostic_id("Duplicate agnostic id: ");
const std::string duplicate_technical_space(
    "Technical space mapped more than once: ");

}

namespace dogen::logical::transforms {

std::unordered_map<identification::entities::logical_id,
                   boost::shared_ptr<
                       entities::mapping::extensible_mappable>
                   >
extensible_mapping_transform::
obtain_mappables(const logical::entities::input_model_set& ms) {
    auto r(ms.target().mapping_elements().extensible_mappables());
    for (const auto& ref : ms.references()) {
        for (const auto& pair : ref.mapping_elements().extensible_mappables()) {
            const auto inserted(r.insert(pair).second);
            if (!inserted) {
                const auto s(pair.first);
                BOOST_LOG_SEV(lg, error) << duplicate_mappable_id << s;
                BOOST_THROW_EXCEPTION(
                    transformation_error(duplicate_mappable_id + s.value()));
            }
        }
    }
    return r;
}

std::unordered_map<std::string, std::list<helpers::mapping>>
extensible_mapping_transform::create_mappings(const std::unordered_map<
    identification::entities::logical_id,
    boost::shared_ptr<entities::mapping::extensible_mappable>>&
    mappables) {

    std::unordered_map<std::string, std::list<helpers::mapping>> r;
    for(const auto& pair : mappables) {
        const auto id(pair.first);
        helpers::mapping mapping;
        mapping.agnostic_id(id);

        const auto& em(*pair.second);
        auto& mts(mapping.by_technical_space());
        for (const auto& dest : em.destinations()) {
            helpers::mapping_value mv;
            mv.mapping_action(helpers::mapping_actions::translate);
            mv.default_name(dest.name());

            const auto ts(dest.technical_space());
            const auto pair(std::make_pair(ts, mv));
            const auto inserted(mts.insert(pair).second);
            if (!inserted) {
                const auto s(boost::lexical_cast<std::string>(ts));
                BOOST_LOG_SEV(lg, error) << duplicate_technical_space << s;
                BOOST_THROW_EXCEPTION(
                    transformation_error(duplicate_technical_space + s));
            }
        }

        r[default_mapping_set_name].push_back(mapping);
    }
    return r;
}

void extensible_mapping_transform::validate_mappings(const std::unordered_map<
    std::string, std::list<helpers::mapping>>& mappings)  {
    helpers::mappings_validator v;
    v.validate(mappings);
}

void extensible_mapping_transform::
insert(const identification::entities::logical_id& agnostic_id,
    const identification::entities::logical_name& n,
    const identification::entities::technical_space ts,
    std::unordered_map<identification::entities::technical_space,
    std::unordered_map<identification::entities::logical_id,
    identification::entities::logical_name>>& map) {

    auto& by_id(map[ts]);
    const auto pair(std::make_pair(agnostic_id, n));
    const auto inserted(by_id.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_agnostic_id << agnostic_id;
        BOOST_THROW_EXCEPTION(
            transformation_error(duplicate_agnostic_id + agnostic_id.value()));
    }

    BOOST_LOG_SEV(lg, debug) << "Mapped: '" << agnostic_id
                             << "' to '" << n.id() << "'";
}

void extensible_mapping_transform::
populate_mapping_set(const std::list<helpers::mapping>& mappings,
    helpers::mapping_set& ms) {

    for (const auto& mapping : mappings) {
        const auto agnostic_id(mapping.agnostic_id());

        for (const auto& pair : mapping.by_technical_space()) {
            const auto l(pair.first);
            const auto& mv(pair.second);

            BOOST_LOG_SEV(lg, debug) << "Processing mapping action: "
                                     << mv.mapping_action();

            if (mv.mapping_action() == helpers::mapping_actions::erase) {
                ms.erasures_by_technical_space()[l].insert(agnostic_id);
                continue;
            }

            const auto n(*mv.default_name());
            insert(agnostic_id, n, l, ms.by_agnostic_id());
        }
    }
}

helpers::mapping_set_repository extensible_mapping_transform::
create_repository(const std::unordered_map<std::string,
    std::list<helpers::mapping>>& mappings_by_set_name) {

    BOOST_LOG_SEV(lg, debug) << "Started creating mapping set repository.";
    helpers::mapping_set_repository r;

    /*
     * Loop through each supplied list of mappings - pertaining to
     * different files originally - and add each one to the mapping
     * repository as a different mapping set.
     */
    for (const auto& pair : mappings_by_set_name) {
        const auto& n(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Populating mapping set: " << n;

        /*
         * The default mapping set is special, and has its own place
         * in the repository. All other mapping sets are stored by
         * their names.
         */
        const auto& mappings(pair.second);
        const auto& is_default(n == default_mapping_set_name);
        auto& ms(is_default ? r.default_mapping_set() : r.by_name()[n]);
        populate_mapping_set(mappings, ms);

        BOOST_LOG_SEV(lg, debug) << "Finished populating mapping set.";
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating mapping set repository.";
    return r;
}

entities::model extensible_mapping_transform::
map(const helpers::mapping_set_repository& msrp, const entities::model& src,
    const identification::entities::technical_space to) {

    const helpers::mapper mp(msrp);
    auto r(mp.map(src.input_technical_space(), to, src));
    return r;
}

logical::entities::input_model_set
extensible_mapping_transform::apply(const context& ctx,
    const logical::entities::input_model_set& src,
    const identification::entities::technical_space to) {
    const auto id(src.target().name().qualified().dot());
    tracing::scoped_transform_tracer stp(lg, "mapping transform", transform_id,
        id, *ctx.tracer(), src);

    /*
     * First we retrieve all mappables across the model set.
     */
    const auto mappables(obtain_mappables(src));

    /*
     * We then use the mappables to create the mappings. If there are
     * no mappings we needn't bother to validate them.
     */
    const auto mappings(create_mappings(mappables));
    if (mappings.empty())
        BOOST_LOG_SEV(lg, debug) << "No mappings, skipping validation.";
    else
        validate_mappings(mappings);

    /*
     * Now we can create a repository with all the mappings.
     */
    const auto msrp(create_repository(mappings));

    /*
     * Perform all the technical space mapping required for the target
     * model.
     */
    logical::entities::input_model_set r;
    r.target(map(msrp, src.target(), to));

    /*
     * Now do the same for the references.
     */
    std::list<entities::model> mapped_refs;
    for (const auto& ref : src.references()) {
        /*
         * Note that we have all references for all the output
         * technical spaces requested by the target model. We are only
         * concerned with those that require mapping into ts - i.e., a
         * subset of that set. We need to exclude all models which are
         * not mappable to ts, such as for example the system models.
         */
        const auto from(ref.input_technical_space());
        if (!helpers::mapper::is_mappable(from, to)) {
            BOOST_LOG_SEV(lg, debug) << "Skipping non-mappable reference: "
                                     << ref.name().qualified().dot();
            continue;
        }
        r.references().push_back(map(msrp, ref, to));
    }
    stp.end_transform(r);
    return r;
}

}
