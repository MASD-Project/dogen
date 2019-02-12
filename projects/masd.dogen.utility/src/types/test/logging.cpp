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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/test/results_collector.hpp>
#include "masd.dogen.utility/types/test/logging.hpp"

namespace masd::dogen::utility::test {

void log_if_test_has_failed() {
    using namespace masd::dogen::utility::log;
    logger lg(logger_factory("utility.test"));

    namespace ut = boost::unit_test;
    auto test_id(ut::framework::current_test_case().p_id);
    if (!ut::results_collector.results(test_id).passed())
        BOOST_LOG_SEV(lg, error) << "test failed.";
}

dogen::utility::log::scoped_lifecycle_manager
scoped_lifecycle_manager_factory(std::string test_module,
    std::string test_suite,
    std::string function_name) {
    std::ostringstream stream;

    stream << "log/" << test_module << "/" << test_suite
           << "/" << function_name;

    using namespace masd::dogen::utility::log;
    return scoped_lifecycle_manager(stream.str());
}

boost::filesystem::path tracing_directory_path(std::string test_module,
    std::string test_suite, std::string function_name){
    std::ostringstream s;
    s << "probe/" << test_module << "/" << test_suite
      << "/" << function_name;
    return s.str();
}

}
