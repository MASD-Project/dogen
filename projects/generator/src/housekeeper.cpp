/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
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
#include "dogen/generator/housekeeper.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("housekeeper"));

using boost::filesystem::path;
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

inline void log_managed_dirs(std::vector<path> dirs) {
    BOOST_LOG_SEV(lg, info) << "Managed directories: " << dirs;
}

}

namespace dogen {
namespace generator {

housekeeper::housekeeper(
    std::vector<boost::filesystem::path> managed_directories,
    std::set<boost::filesystem::path> expected_files, bool verbose,
    delete_fn fn) :
    managed_directories_(managed_directories),
    expected_files_(expected_files),
    verbose_(verbose),
    delete_fn_(fn) {

    log_managed_dirs(managed_directories_);
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
    delete_fn_(delta);
}

} }
