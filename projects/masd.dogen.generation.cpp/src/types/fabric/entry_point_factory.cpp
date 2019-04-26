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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.coding/types/helpers/name_factory.hpp"
#include "masd.dogen.generation.cpp/types/fabric/entry_point.hpp"
#include "masd.dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "masd.dogen.generation.cpp/types/fabric/entry_point_factory.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("generation.cpp.fabric.entry_point_factory"));

const std::string simple_name("entry_point");

}

namespace masd::dogen::generation::cpp::fabric {

using coding::meta_model::origin_types;
using coding::meta_model::technical_space;

boost::shared_ptr<fabric::entry_point> entry_point_factory::
make(const coding::meta_model::name& model_name) const {
    coding::helpers::name_factory nf;
    const auto n(nf.build_element_in_model(model_name, simple_name));
    auto r(boost::make_shared<entry_point>());
    r->name(n);
    r->meta_name(meta_name_factory::make_entry_point_name());
    r->origin_type(origin_types::target);
    r->intrinsic_technical_space(technical_space::agnostic);
    r->configuration(
        boost::make_shared<variability::meta_model::configuration>());
    r->configuration()->name().simple(n.simple());
    r->configuration()->name().qualified(n.qualified().dot());

    return r;
}

boost::shared_ptr<coding::meta_model::element> entry_point_factory::
make(const generation::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Generating entry point.";

    const auto r(make(m.name()));

    BOOST_LOG_SEV(lg, debug) << "Finished generating entry point.";
    return r;
}

}
