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
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/fabric/cmakelists.hpp"
#include "dogen/quilt.cpp/types/fabric/msbuild_targets.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_options_factory.hpp"
#include "dogen/quilt.cpp/types/fabric/build_files_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.fabric"));

const std::string cmakelists_name("CMakeLists");
const std::string msbuild_targets_name("msbuild_targets");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

boost::shared_ptr<yarn::element> build_files_factory::
make_cmakelists(const yarn::intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Generating CMakeLists.";

    yarn::helpers::name_factory nf;
    const auto n(nf.build_element_in_model(im.name(), cmakelists_name));
    auto r(boost::make_shared<cmakelists>());
    r->name(n);
    r->origin_type(im.origin_type());

    BOOST_LOG_SEV(lg, debug) << "Generated CMakeLists.";
    return r;
}

boost::shared_ptr<yarn::element> build_files_factory::
make_msbuild_targets(const yarn::intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Generating MSBuild Targets.";

    yarn::helpers::name_factory nf;
    const auto n(nf.build_element_in_model(im.name(), msbuild_targets_name));
    auto r(boost::make_shared<msbuild_targets>());
    r->name(n);
    r->origin_type(im.origin_type());

    BOOST_LOG_SEV(lg, debug) << "Generated MSBuild Targets.";
    return r;
}

std::list<boost::shared_ptr<yarn::element>> build_files_factory::
make(const yarn::intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Generating Build Files.";

    std::list<boost::shared_ptr<yarn::element>> r;
    r.push_back(make_cmakelists(im));
    r.push_back(make_msbuild_targets(im));

    BOOST_LOG_SEV(lg, debug) << "Generated Build Files.";
    return r;
}

} } } }
