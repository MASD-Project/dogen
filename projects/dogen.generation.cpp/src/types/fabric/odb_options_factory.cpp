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
#include <boost/make_shared.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/meta_model/structural/primitive.hpp"
#include "dogen.assets/types/helpers/name_factory.hpp"
#include "dogen.generation.cpp/types/fabric/building_error.hpp"
#include "dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "dogen.generation.cpp/types/fabric/common_odb_options.hpp"
#include "dogen.generation.cpp/types/fabric/odb_options_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quit.cpp.fabric.odb_options_factory"));

const std::string common_odb_options_name("common");

}

namespace dogen::generation::cpp::fabric {

using assets::meta_model::origin_types;
using assets::meta_model::technical_space;

std::list<boost::shared_ptr<assets::meta_model::element>>
odb_options_factory::make(const generation::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Generating ODB Options.";

    assets::helpers::name_factory nf;
    const auto n(nf.build_element_in_model(m.name(), common_odb_options_name));

    auto coo(boost::make_shared<common_odb_options>());
    coo->name(n);
    coo->meta_name(meta_name_factory::make_common_odb_options_name());
    coo->origin_type(origin_types::target);
    coo->intrinsic_technical_space(technical_space::odb);
    coo->configuration(
        boost::make_shared<variability::meta_model::configuration>());
    coo->configuration()->name().simple(coo->name().simple());
    coo->configuration()->name().qualified(coo->name().qualified().dot());

    std::list<boost::shared_ptr<assets::meta_model::element>> r;
    r.push_back(coo);

    BOOST_LOG_SEV(lg, debug) << "Generated ODB Options.";

    return r;
}

}
