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
#include <boost/throw_exception.hpp>
#include <boost/filesystem/operations.hpp>
#include <unordered_set>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.codec/types/helpers/reference_resolution_exception.hpp"
#include "dogen.codec/types/helpers/references_resolver.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("codec.helpers.references_resolver"));

const std::string reference_missing("Reference not found: ");
const std::string reference_ambiguous("Reference is ambiguous: ");
const std::string no_extensions("No extensions supplied.");
const std::string no_dirs("No directories supplied.");

}

namespace dogen::codec::helpers {

const std::list<boost::filesystem::path>
references_resolver::deduplicate_directories(
    const std::list<boost::filesystem::path> directories) {
    std::unordered_set<std::string> unique;
    for (const auto& d : directories)
        unique.insert(d.generic_string());

    std::list<boost::filesystem::path> r;
    for( const auto& s : unique)
        r.push_back(boost::filesystem::path(s));
    return r;
}

references_resolver::references_resolver(
        const std::list<std::string>& extensions,
        const std::list<boost::filesystem::path>& directories)
    : extensions_(extensions),
      directories_(deduplicate_directories(directories)) {

    if (extensions_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_extensions;
        BOOST_THROW_EXCEPTION(reference_resolution_exception(no_extensions));
    }
    BOOST_LOG_SEV(lg, debug) << "Extensions: " << extensions;

    if (directories_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_dirs;
        BOOST_THROW_EXCEPTION(reference_resolution_exception(no_dirs));
    }

    BOOST_LOG_SEV(lg, debug) << "Directories: " << directories_;
}

boost::filesystem::path
references_resolver::resolve(const std::string& ref) const {
    BOOST_LOG_SEV(lg, debug) << "Finding reference: " << ref;

    /*
     * For each directory and each registered extension, construct a
     * an absolute path and check to see if it results in a valid
     * file. If so, add it to our list.
     */
    std::list<boost::filesystem::path> resolved;
    for (const auto& d : directories_) {
        for (const auto& e : extensions_) {
            const auto fn(ref + e);
            const auto p(d / fn);
            if (boost::filesystem::exists(p) &&
                boost::filesystem::is_regular_file(p)) {
                resolved.push_back(p);
            } else
                BOOST_LOG_SEV(lg, trace) << "Failed to resolve:" <<p.generic();
        }
    }

    /*
     * Ensure the reference resolves to one and only one path.
     */
    if (resolved.size() == 0) {
        BOOST_LOG_SEV(lg, error) << reference_missing << ref;
        BOOST_THROW_EXCEPTION(
            reference_resolution_exception(reference_missing + ref));
    } else if (resolved.size() > 1) {
        BOOST_LOG_SEV(lg, error) << reference_ambiguous << ref
                                 << " Directories: " << resolved;
        BOOST_THROW_EXCEPTION(
            reference_resolution_exception(reference_ambiguous + ref));
    }

    BOOST_LOG_SEV(lg, debug) << "Found user reference: "
                             << resolved.front().generic();
    return resolved.front();
}

std::list<boost::filesystem::path> references_resolver::
resolve(const std::list<std::string>& references) const {
    std::list<boost::filesystem::path> r;
    BOOST_LOG_SEV(lg, debug) << "Finding references: " << references;

    for (const auto& s : references)
        r.push_back(resolve(s));

    BOOST_LOG_SEV(lg, debug) << "Found references: " << r;
    return r;
}

}
