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
#include <boost/pointer_cast.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.logical/types/entities/decoration/licence.hpp"
#include "dogen.logical/types/entities/decoration/generation_marker.hpp"
#include "dogen.logical/types/entities/decoration/modeline.hpp"
#include "dogen.logical/types/entities/decoration/modeline_group.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.generation/types/helpers/building_exception.hpp"
#include "dogen.generation/types/helpers/decoration_repository_factory.hpp"

namespace {

const std::string transform_id("assets.helpers.decoration_repository_factory");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string duplicate_licence("Duplicate id for licence: ");
const std::string duplicate_marker("Duplicate id for generation marker: ");
const std::string duplicate_technical_space(
    "More than one modeline defined for technical space: ");
const std::string duplicate_modeline_group(
    "Modeline group defined more than once: ");
const std::string inconsistent_meta_name(
    "Inconsistent meta-name for element: ");

}

namespace dogen::generation::helpers {

bool decoration_repository_factory::
is_meta_element(const logical::entities::name& me,
    const logical::entities::element& e) const {
    const auto mid(me.qualified().dot());
    const auto eid(e.meta_name().qualified().dot());
    return mid == eid;
}

void decoration_repository_factory::handle_licence(
    const boost::shared_ptr<logical::entities::element> e,
    decoration_repository& drp) const {

    BOOST_LOG_SEV(lg, trace) << "Processing licence.";
    const auto id(e->name().qualified().dot());
    using logical::entities::decoration::licence;
    const auto l(boost::dynamic_pointer_cast<licence>(e));
    if (!l) {
        BOOST_LOG_SEV(lg, error) << inconsistent_meta_name << id;
        BOOST_THROW_EXCEPTION(building_exception(inconsistent_meta_name + id));
    }

    const auto pair(std::make_pair(id, l));
    auto& map(drp.licences_by_name());
    const bool inserted(map.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_licence << id;
        BOOST_THROW_EXCEPTION(building_exception(duplicate_licence + id));
    }

    BOOST_LOG_SEV(lg, trace) << "Finished processing licence.";
}

void decoration_repository_factory::handle_generation_marker(
    const boost::shared_ptr<logical::entities::element> e,
    decoration_repository& drp) const {
    BOOST_LOG_SEV(lg, trace) << "Processing generation marker.";

    const auto id(e->name().qualified().dot());
    using logical::entities::decoration::generation_marker;
    const auto gm(boost::dynamic_pointer_cast<generation_marker>(e));
    if (!gm) {
        BOOST_LOG_SEV(lg, error) << inconsistent_meta_name << id;
        BOOST_THROW_EXCEPTION(building_exception(inconsistent_meta_name + id));
    }

    const auto pair(std::make_pair(id, gm));
    auto& map(drp.generation_markers_by_name());
    const bool inserted(map.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_marker << id;
        BOOST_THROW_EXCEPTION(building_exception(duplicate_marker + id));
    }

    BOOST_LOG_SEV(lg, trace) << "Finished processing generation marker.";
}

void decoration_repository_factory::handle_modeline_group(
    const boost::shared_ptr<logical::entities::element> e,
    decoration_repository& drp) const {

    BOOST_LOG_SEV(lg, trace) << "Processing modeline group.";

    const auto id(e->name().qualified().dot());
    using logical::entities::decoration::modeline_group;
    const auto mg(boost::dynamic_pointer_cast<modeline_group>(e));
    if (!mg) {
        BOOST_LOG_SEV(lg, error) << inconsistent_meta_name << id;
        BOOST_THROW_EXCEPTION(building_exception(inconsistent_meta_name + id));
    }

    using logical::entities::decoration::modeline;
    std::unordered_map<logical::entities::technical_space,
                       boost::shared_ptr<modeline>> map;

    for (const auto& ml : mg->modelines()) {
        const auto ts(ml->technical_space());
        const auto id(ml->name().qualified().dot());
        const auto pair(std::make_pair(ts, ml));
        const bool inserted(map.insert(pair).second);
        if (!inserted) {
            const auto ts_str(boost::lexical_cast<std::string>(ts));
            BOOST_LOG_SEV(lg, error) << duplicate_technical_space << ts_str
                                     << " For modeline: " << id;
            BOOST_THROW_EXCEPTION(
                building_exception(duplicate_technical_space + ts_str));
        }
    }

    BOOST_LOG_SEV(lg, trace) << "Total modelines for modeline group: "
                             << map.size();

    const auto gid(mg->name().qualified().dot());
    const auto pair(std::make_pair(gid, map));
    auto& ml_map(drp.modelines_by_modeline_group_by_technical_space());
    const bool inserted(ml_map.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_modeline_group << gid;
        BOOST_THROW_EXCEPTION(
            building_exception(duplicate_modeline_group + gid));
    }

    BOOST_LOG_SEV(lg, trace) << "Finished processing modeline group.";
}

decoration_repository
decoration_repository_factory::make(const entities::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Creating decoration repository for model: "
                             << m.name().qualified().dot();

    using mnf = logical::helpers::meta_name_factory;
    const auto licence_name(mnf::make_licence_name());
    const auto generation_marker_name(mnf::make_generation_marker_name());
    const auto modeline_group_name(mnf::make_modeline_group_name());

    decoration_repository r;
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        BOOST_LOG_SEV(lg, trace) << "Processing element: "
                                 << e.name().qualified().dot()
                                 << " meta-element name: "
                                 << e.meta_name().qualified().dot();

        if (is_meta_element(licence_name, e))
            handle_licence(ptr, r);
        else if (is_meta_element(generation_marker_name, e))
            handle_generation_marker(ptr, r);
        else if (is_meta_element(modeline_group_name, e))
            handle_modeline_group(ptr, r);
    }

    BOOST_LOG_SEV(lg, debug) << "Modeline groups: "
                             << r.modelines_by_modeline_group_by_technical_space()
        .size();
    BOOST_LOG_SEV(lg, debug) << "Licences: " << r.licences_by_name().size();
    BOOST_LOG_SEV(lg, debug) << "Generation markers: "
                             << r.generation_markers_by_name().size();

    BOOST_LOG_SEV(lg, debug) << "Finished creating decoration repository.";


    return r;
}

}
