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
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/quilt.cpp/types/fabric/building_error.hpp"
#include "dogen/quilt.cpp/types/fabric/common_odb_options.hpp"
#include "dogen/quilt.cpp/types/fabric/object_odb_options.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_options_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quit.cpp.fabric.odb_options_factory"));

const std::string common_odb_options_name("common");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

std::list<boost::shared_ptr<yarn::element>>
odb_options_factory::make(const yarn::intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Generating ODB Options.";

    std::list<boost::shared_ptr<yarn::element>> r;
    for (const auto& pair : im.objects()) {
        const auto& o(pair.second);

        /*
         * We only care about objects which have ORM enabled.
         */
        if (!o.orm_properties())
            continue;

        const auto id(o.name().id());
        BOOST_LOG_SEV(lg, debug) << "Processing: " << id;

        auto ooo(boost::make_shared<object_odb_options>());
        ooo->name(o.name());
        ooo->origin_type(o.origin_type());
        ooo->annotation(o.annotation());
        ooo->is_element_extension(true);
        r.push_back(ooo);
    }

    /*
     * We need at least one object with needs ORM support in order to
     * generate the common options.
     */
    if (r.empty())
        return r;

    yarn::helpers::name_factory nf;
    const auto n(nf.build_element_in_model(im.name(), common_odb_options_name));

    auto coo(boost::make_shared<common_odb_options>());
    coo->name(n);
    coo->origin_type(im.origin_type());
    r.push_back(coo);

    BOOST_LOG_SEV(lg, debug) << "Generated ODB Options.";

    return r;
}

} } } }
