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
#include <regex>
#include <forward_list>
#include <boost/range/combine.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/range/algorithm/set_algorithm.hpp>
#include "dogen.utility/log/logger.hpp"
#include "dogen.utility/io/set_io.hpp"
#include "dogen.utility/io/list_io.hpp"
#include "dogen.utility/io/forward_list_io.hpp"
#include "dogen.utility/filesystem/file.hpp"
#include "dogen.utility/io/forward_list_io.hpp"
#include "dogen.modeling/types/helpers/file_linter.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.helpers.file_linter"));

}

namespace dogen::modeling::helpers {

std::set<boost::filesystem::path> file_linter::
obtain_expected_files(const meta_model::text_model& tm) {
    std::set<boost::filesystem::path> r;
    for (const auto a : tm.artefacts()) {
        r.insert(a.path().generic_string());
        for (const auto& d : a.dependencies())
            r.insert(d.generic_string());
    }

    BOOST_LOG_SEV(lg, debug) << "Expected files: " << r;
    return r;
}

std::set<boost::filesystem::path> file_linter::obtain_actual_files(
    const std::list<boost::filesystem::path>& managed_directories) {
    using utility::filesystem::find_files;
    const auto r(find_files(managed_directories));
    BOOST_LOG_SEV(lg, debug) << "Actual files: " << r;
    return r;
}

std::list<boost::filesystem::path> file_linter::diff_expected_with_actual(
    const std::set<boost::filesystem::path>& expected,
    const std::set<boost::filesystem::path>& actual) {
    std::list<boost::filesystem::path> r;
    boost::set_difference(actual, expected, std::front_inserter(r));
    BOOST_LOG_SEV(lg, info) << "Difference between expected and actual: " << r;
    return r;
}

std::list<boost::filesystem::path>
file_linter::filter(const std::vector<std::string>& patterns,
    const std::list<boost::filesystem::path>& files) {

    std::vector<std::regex> regexes;
    regexes.reserve(patterns.size());
    for (const auto& p : patterns) {
        BOOST_LOG_SEV(lg, debug) << "Creating regex for pattern: " << p;
        regexes.push_back(std::regex(p));
    }

    std::list<boost::filesystem::path> r;
    for (const auto& f : files) {
        bool ignore(false);
        const auto gs(f.generic_string());
        for (unsigned int i(0); i < regexes.size(); ++i) {
            BOOST_LOG_SEV(lg, debug) << "Applying '" << patterns[i]
                                     << "' to '" << gs << "'.";

            if (std::regex_match(gs, regexes[i])) {
                BOOST_LOG_SEV(lg, debug) << "Regex matches, ignoring file.";
                ignore = true;
                break;
            }
        }

        if (ignore) {
            BOOST_LOG_SEV(lg, debug) << "Ignoring file: " << gs;
            continue;
        }

        BOOST_LOG_SEV(lg, debug) << "Not ignoring file: " << gs;
        r.push_front(f);
    }

    BOOST_LOG_SEV(lg, info) << "Delta after filtering ignores: " << r;
    return r;
}

std::list<boost::filesystem::path> file_linter::
lint(const std::vector<std::string>& patterns,
    const meta_model::text_model& tm) {
    BOOST_LOG_SEV(lg, info) << "Started linting text model.";

    /*
     * First we obtain the set of files expected, given the contents
     * of the text model.
     */
    const auto expected(obtain_expected_files(tm));

    /*
     * Then we find out which files are actually available in the file
     * system, in the directories managed by the text model.
     */
    const auto actual(obtain_actual_files(tm.managed_directories()));

    /*
     * We then compute the difference between the two sets.
     */
    auto delta(diff_expected_with_actual(expected, actual));

    /*
     * Finally, we can filter out any expected differences, as per
     * supplied regular expressions. Whatever is left is the model's
     * lint - candidates for removal.
     */
    const auto r(filter(patterns, delta));

    BOOST_LOG_SEV(lg, info) << "Finished linting text model. Lint: " << r;
    return r;
}

}
