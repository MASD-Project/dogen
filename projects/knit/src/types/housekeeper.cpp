/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <iostream>
#include <boost/filesystem/operations.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm/set_algorithm.hpp>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/set_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/knit/types/housekeeper.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("knit.housekeeper"));

using boost::filesystem::path;
inline void log_ignoring_file(path p) {
    BOOST_LOG_SEV(lg, warn) << "Ignoring file: " << p.string();
}

inline void log_deleting_extra_file(path p) {
    BOOST_LOG_SEV(lg, warn) << "Removing extra file: " << p.string();
}

inline void log_expected_actual(std::set<path> e, std::set<path> a) {
    BOOST_LOG_SEV(lg, debug) << "expected files: " << e;
    BOOST_LOG_SEV(lg, debug) << "actual files: " << a;
}

inline void log_no_extra_files() {
    BOOST_LOG_SEV(lg, info) << "no extra files found.";
}

inline void log_extra_files(std::list<path> delta) {
    BOOST_LOG_SEV(lg, debug) << "Found extra files: " << delta;
}

}

namespace dogen {
namespace knit {

housekeeper::housekeeper(
    const std::vector<std::string>& ignore_patterns,
    std::vector<boost::filesystem::path> managed_directories,
    std::set<boost::filesystem::path> expected_files, delete_fn fn) :
    ignore_patterns_(ignore_patterns),
    managed_directories_(managed_directories),
    expected_files_(expected_files),
    delete_fn_(fn) {

    BOOST_LOG_SEV(lg, info) << "initial configuration: "
                            << "ignore patterns: " << ignore_patterns
                            << " managed directories: " << managed_directories;

    if (delete_fn_)
        return;

    delete_fn_ = std::bind(&housekeeper::delete_files, this,
        std::placeholders::_1);
}

std::set<boost::filesystem::path>
housekeeper::files_in_directory(boost::filesystem::path dir) const {
    using namespace boost::filesystem;
    std::set<path> r;

    for (recursive_directory_iterator end, i(dir); i != end; ++i) {
        const path p(*i);
        if (is_regular_file(p))
            r.insert(p);
    }

    return r;
}

std::set<boost::filesystem::path> housekeeper::find_actual_files() const {
    std::set<boost::filesystem::path> r;

    for (const auto d : managed_directories_) {
        const auto f(files_in_directory(d));
        r.insert(f.begin(), f.end());
    }

    return r;
}

void housekeeper::delete_files(std::list<boost::filesystem::path> files) const {
    for (const auto f : files) {
        log_deleting_extra_file(f);
        boost::filesystem::remove(f);
    }
}

std::list<boost::filesystem::path> housekeeper::
remove_ignores(std::list<boost::filesystem::path> files) const {
    std::list<boost::filesystem::path> r;
    for (const auto f : files) {
        bool ignore(false);
        for (auto ip : ignore_patterns_) {
            BOOST_LOG_SEV(lg, debug) << "Applying regex: " << ip << " to "
                                     << f.generic_string();

            std::regex expr(ip);
            if (std::regex_match(f.generic_string(), expr)) {
                BOOST_LOG_SEV(lg, debug) << "Regex matches";
                ignore = true;
                continue;
            }
        }

        if (ignore)
            log_ignoring_file(f);
        else {
            BOOST_LOG_SEV(lg, debug) << "Not ignoring file: " << f;
            r.push_back(f);
        }
    }
    return r;
}

void housekeeper::tidy_up() const {
    const auto af(find_actual_files());
    log_expected_actual(expected_files_, af);

    std::list<boost::filesystem::path> delta;
    boost::set_difference(af, expected_files_, std::back_inserter(delta));

    if (delta.empty()) {
        log_no_extra_files();
        return;
    }

    log_extra_files(delta);
    delete_fn_(remove_ignores(delta));
}

} }
