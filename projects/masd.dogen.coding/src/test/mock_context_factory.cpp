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
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/filesystem/path.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.annotations/types/annotation_factory.hpp"
#include "masd.dogen.annotations/types/type_repository_factory.hpp"
#include "masd.dogen.annotations/types/archetype_location_repository_builder.hpp"
#include "masd.dogen.extraction/types/repository_factory.hpp"
#include "masd.dogen.tracing/types/tracer.hpp"
#include "masd.dogen.coding/types/helpers/mapping_set_repository_factory.hpp"
#include "masd.dogen.coding/test/mock_context_factory.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("coding.transforms.mock_context_factory"));

}

namespace masd::dogen::coding::test {

transforms::context mock_context_factory::make() {
    BOOST_LOG_SEV(lg, debug) << "Creating the mock context.";

    masd::dogen::coding::transforms::options o;

    auto alrp(boost::make_shared<annotations::archetype_location_repository>());

    /*
     * Obtain all the data structures required to make a context, and
     * create the context.
     */
    const auto data_dir(utility::filesystem::data_files_directory());
    const auto data_dirs(std::vector<boost::filesystem::path>{ data_dir });

    helpers::mapping_set_repository_factory msrpf;
    const auto msrp(boost::make_shared<
        helpers::mapping_set_repository>(msrpf.make(data_dirs)));

    annotations::type_repository_factory atrpf;
    const auto atrp(boost::make_shared<annotations::type_repository>(
            atrpf.make(*alrp, data_dirs)));

    extraction::repository_factory frpf;
    const auto frp(boost::make_shared<extraction::repository>(
            frpf.make(data_dirs)));

    auto tracer(boost::make_shared<tracing::tracer>(
            *alrp, *atrp, o.probe_directory(), o.tracing()));

    const auto af(boost::make_shared<annotations::annotation_factory>(
                *alrp, *atrp, o.compatibility_mode()));

    transforms::context r;
    r.data_directories(data_dirs);
    r.transform_options(o);
    r.archetype_location_repository(alrp);
    r.type_repository(atrp);
    r.mapping_repository(msrp);
    r.formatting_repository(frp);
    r.tracer(tracer);

    BOOST_LOG_SEV(lg, debug) << "Created the context.";
    return r;
}

}
