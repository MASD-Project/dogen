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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.coding/types/meta_model/modeline.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_group.hpp"
#include "masd.dogen.coding/io/meta_model/technical_space_io.hpp"
#include "masd.dogen.coding/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.generation/types/helpers/building_exception.hpp"
#include "masd.dogen.generation/types/helpers/decoration_repository_factory.hpp"

namespace {

const std::string transform_id("coding.transforms.technical_space_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string duplicate_technical_space(
    "More than one modeline defined for technical space: ");
const std::string duplicate_modeline_group(
    "Modeline group defined more than once: ");
const std::string inconsistent_meta_name(
    "Inconsistent meta-name for element: ");

}

namespace masd::dogen::generation::helpers {

bool decoration_repository_factory::
is_meta_element(const coding::meta_model::name& me,
    const coding::meta_model::element& e) const {

    const auto mid(me.qualified().dot());
    const auto eid(e.meta_name().qualified().dot());
    return mid == eid;
}

void decoration_repository_factory::handle_licence(
    const boost::shared_ptr<coding::meta_model::element> /*e*/,
    decoration_repository& /*drp*/) const {


}

void decoration_repository_factory::handle_generation_marker(
    const boost::shared_ptr<coding::meta_model::element> /*e*/,
    decoration_repository& /*drp*/) const {


}

void decoration_repository_factory::handle_modeline_group(
    const boost::shared_ptr<coding::meta_model::element> e,
    decoration_repository& drp) const {

    const auto id(e->name().qualified().dot());
    using coding::meta_model::modeline_group;
    const auto mg(boost::dynamic_pointer_cast<modeline_group>(e));
    if (!mg) {
        BOOST_LOG_SEV(lg, error) << inconsistent_meta_name << id;
        BOOST_THROW_EXCEPTION(building_exception(inconsistent_meta_name + id));
    }

    std::unordered_map<coding::meta_model::technical_space,
                       boost::shared_ptr<coding::meta_model::modeline>> map;

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

    const auto gid(mg->name().qualified().dot());
    const auto pair(std::make_pair(gid, map));
    auto& ml_map(drp.modelines_by_modeline_group_by_technical_space());
    const bool inserted(ml_map.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_modeline_group << gid;
        BOOST_THROW_EXCEPTION(
            building_exception(duplicate_modeline_group + gid));
    }
}

decoration_repository
decoration_repository_factory::make(const meta_model::model& m) const {
    using mnf = coding::helpers::meta_name_factory;
    const auto licence_name(mnf::make_licence_name());
    const auto generation_marker_name(mnf::make_generation_marker_name());
    const auto modeline_group_name(mnf::make_modeline_group_name());

    decoration_repository r;
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        if (is_meta_element(licence_name, e))
            handle_licence(ptr, r);
        else if (is_meta_element(generation_marker_name, e))
            handle_generation_marker(ptr, r);
        else if (is_meta_element(modeline_group_name, e))
            handle_modeline_group(ptr, r);
    }
    return r;
}

}
