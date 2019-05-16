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
#include "dogen.coding/types/helpers/mapping_actions.hpp"
#include "dogen.coding/types/helpers/mapping_value.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.coding/lexical_cast/meta_model/technical_space_lc.hpp"
#include "dogen.coding/io/meta_model/model_io.hpp"
#include "dogen.coding/types/meta_model/mapping/extensible_mappable.hpp"
#include "dogen.coding/io/helpers/mapping_io.hpp"
#include "dogen.coding/io/helpers/mapping_set_io.hpp"
#include "dogen.coding/io/helpers/mapping_actions_io.hpp"
#include "dogen.coding/io/helpers/mapping_set_repository_io.hpp"
#include "dogen.coding/types/helpers/mapper.hpp"
#include "dogen.coding/types/helpers/mappings_validator.hpp"
#include "dogen.coding/types/transforms/context.hpp"
#include "dogen.coding/types/transforms/transformation_error.hpp"
#include "dogen.coding/types/transforms/mapping_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.mapping_transform");
using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string default_mapping_set_name("default.mapping_set");
const std::string duplicate_agnostic_id("Duplicate agnostic id: ");
const std::string duplicate_technical_space(
    "Technical space mapped more than once: ");

}

namespace dogen::coding::transforms {

std::unordered_map<std::string, std::list<helpers::mapping>>
mapping_transform::obtain_mappings(const meta_model::model& m) {
    std::unordered_map<std::string, std::list<helpers::mapping>> r;

    const auto& ems(m.mapping_elements().extensible_mappables());
    for(const auto& pair : ems) {
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

void mapping_transform::validate_mappings(const std::unordered_map<std::string,
    std::list<helpers::mapping>>& mappings)  {
    helpers::mappings_validator v;
    v.validate(mappings);
}

void mapping_transform::insert(const std::string& agnostic_id,
    const meta_model::name& n, const meta_model::technical_space ts,
    std::unordered_map<meta_model::technical_space,
    std::unordered_map<std::string, meta_model::name>>& map) {

    auto& by_id(map[ts]);
    const auto pair(std::make_pair(agnostic_id, n));
    const auto inserted(by_id.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_agnostic_id << agnostic_id;
        BOOST_THROW_EXCEPTION(
            transformation_error(duplicate_agnostic_id + agnostic_id));
    }

    BOOST_LOG_SEV(lg, debug) << "Mapped: '" << agnostic_id
                             << "' to '" << n.qualified().dot() << "'";
}

void  mapping_transform::
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

helpers::mapping_set_repository
mapping_transform::create_repository(const std::unordered_map<std::string,
    std::list<helpers::mapping>>&
    mappings_by_set_name) {

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

bool mapping_transform::is_mappable(const meta_model::technical_space from,
    const meta_model::technical_space to) {
    return helpers::mapper::is_mappable(from, to);
}

meta_model::model mapping_transform::apply(const context& ctx,
    const meta_model::model& src, const meta_model::technical_space to) {
    tracing::scoped_transform_tracer stp(lg, "mapping transform",
        transform_id, src.name().qualified().dot(), *ctx.tracer(), src);

    const bool new_world(false);
    if (new_world) {
        const auto mappings(obtain_mappings(src));
        if (!mappings.empty()) {
            validate_mappings(mappings);
            const auto mrp(create_repository(mappings));
            const helpers::mapper mp(mrp);
            auto r(mp.map(src.input_technical_space(), to, src));
            stp.end_transform(r);
            return r;
        } else
            return src;
    } else {
        const helpers::mapper mp(*ctx.mapping_repository());
        auto r(mp.map(src.input_technical_space(), to, src));
        stp.end_transform(r);
        return r;
    }
}

}
