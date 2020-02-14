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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.assets/types/helpers/name_factory.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/fabric/cmakelists.hpp"
#include "dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "dogen.generation.cpp/types/fabric/build_files_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.cpp.fabric"));

const std::string cmakelists_name("CMakeLists");

}

namespace dogen::generation::cpp::fabric {

using assets::meta_model::origin_types;
using assets::meta_model::technical_space;

boost::shared_ptr<assets::meta_model::element> build_files_factory::
make_cmakelists(const generation::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Generating CMakeLists.";

    assets::helpers::name_factory nf;
    const auto n(nf.build_element_in_model(m.name(), cmakelists_name));
    auto r(boost::make_shared<cmakelists>());
    r->name(n);
    r->meta_name(meta_name_factory::make_cmakelists_name());
    r->origin_type(origin_types::target);
    r->intrinsic_technical_space(technical_space::cmake);
    r->configuration(
        boost::make_shared<variability::meta_model::configuration>());
    r->configuration()->name().simple(n.simple());
    r->configuration()->name().qualified(n.qualified().dot());

    BOOST_LOG_SEV(lg, debug) << "Generated CMakeLists.";
    return r;
}

std::list<boost::shared_ptr<assets::meta_model::element>> build_files_factory::
make(const generation::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Generating Build Files.";

    std::list<boost::shared_ptr<assets::meta_model::element>> r;
    r.push_back(make_cmakelists(m));

    BOOST_LOG_SEV(lg, debug) << "Generated Build Files.";
    return r;
}

}
