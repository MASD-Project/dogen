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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/set_io.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/forward_list_io.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/io/forward_list_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/io/helpers/files_by_status_io.hpp"
#include "dogen.physical/types/helpers/file_status_collector.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("physical.helpers.file_status_collector"));

}

namespace dogen::physical::helpers {

std::set<boost::filesystem::path> file_status_collector::
obtain_expected_files(const entities::model& m) {
    std::set<boost::filesystem::path> r;
    for (const auto& as_pair : m.artefact_sets_by_logical_id()) {
        const auto& as(as_pair.second);
        for (const auto& a_pair : as.artefacts_by_archetype()) {
            const auto& a(*a_pair.second);
            r.insert(a.name().qualified().generic_string());
            for (const auto& d : a.dependencies())
                r.insert(d.generic_string());
        }
    }

    for (const auto& aptr : m.orphan_artefacts()) {
        const auto& a(*aptr);
        r.insert(a.name().qualified().generic_string());
        for (const auto& d : a.dependencies())
            r.insert(d.generic_string());
    }

    BOOST_LOG_SEV(lg, debug) << "Expected files: " << r;
    return r;
}

std::list<boost::filesystem::path> file_status_collector::
filter_by_existence(const std::list<boost::filesystem::path>& dirs) {
    std::list<boost::filesystem::path> r;
    for (const auto& d : dirs) {
        if (boost::filesystem::exists(d))
            r.push_back(d);
    }
    return r;
}

std::set<boost::filesystem::path> file_status_collector::obtain_actual_files(
    const std::list<boost::filesystem::path>& dirs) {
    using utility::filesystem::find_files;
    const auto r(find_files(dirs));
    BOOST_LOG_SEV(lg, debug) << "Actual files: " << r;
    return r;
}

std::list<boost::filesystem::path>
file_status_collector::diff_expected_with_actual(
    const std::set<boost::filesystem::path>& expected,
    const std::set<boost::filesystem::path>& actual) {
    std::list<boost::filesystem::path> r;
    boost::set_difference(actual, expected, std::front_inserter(r));
    BOOST_LOG_SEV(lg, info) << "Difference between expected and actual: " << r;
    return r;
}

files_by_status file_status_collector::
bucket_by_status(const std::vector<std::string>& patterns,
    const std::list<boost::filesystem::path>& files) {

    std::vector<std::regex> regexes;
    regexes.reserve(patterns.size());
    for (const auto& p : patterns) {
        BOOST_LOG_SEV(lg, debug) << "Creating regex for pattern: " << p;
        regexes.push_back(std::regex(p));
    }

    files_by_status r;
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
            r.ignored().push_back(f);
            BOOST_LOG_SEV(lg, debug) << "Ignoring file: " << gs;
            continue;
        }

        BOOST_LOG_SEV(lg, debug) << "Not ignoring file: " << gs;
        r.unexpected().push_back(f);
    }

    return r;
}

files_by_status
file_status_collector::collect(const entities::model& m) {
    BOOST_LOG_SEV(lg, info) << "Started collecting status for model: "
                            << m.name().simple();
    BOOST_LOG_SEV(lg, debug) << "Initial directories: "
                             << m.managed_directories();

    /*
     * We only care about those directories that exist. This handles
     * the case where we are generating the model for the first time.
     */
    const auto dirs(filter_by_existence(m.managed_directories()));
    BOOST_LOG_SEV(lg, debug) << "Filtered directories: " << dirs;
    if (dirs.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No directories to analyse.";
        return files_by_status();
    }

    /*
     * First we obtain the set of files expected, given the contents
     * of the text model.
     */
    const auto expected(obtain_expected_files(m));

    /*
     * Then we find out which files are actually available in the file
     * system, in the directories managed by the text model.
     */
    const auto actual(obtain_actual_files(dirs));

    /*
     * We then compute the difference between the two sets.
     */
    auto delta(diff_expected_with_actual(expected, actual));

    /*
     * Finally, we can filter out any expected differences, as per
     * supplied regular expressions. Whatever is left is the model's
     * lint - candidates for removal, bucketed by status.
     */
    const auto ifmr(m.outputting_properties().ignore_files_matching_regex());
    const auto r(bucket_by_status(ifmr, delta));
    BOOST_LOG_SEV(lg, info) << "Finished collecting status. Result: " << r;
    return r;
}

}
