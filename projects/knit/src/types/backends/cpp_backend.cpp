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
#include <unordered_map>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml_to_cpp/types/workflow.hpp"
#include "dogen/cpp_formatters/types/workflow.hpp"
#include "dogen/backend/types/workflow.hpp" // FIXME
#include "dogen/knit/types/backends/backend_error.hpp"
#include "dogen/knit/types/backends/cpp_backend.hpp"

namespace  {

using namespace dogen::utility::log;
auto lg(logger_factory("knit.backends.cpp_backend"));

// FIXME: massive hack for now.
// set it to true to use new formatters.
const bool perform_override_of_legacy_files(true);
const bool ignore_legacy_files(true);

const std::string duplicate_file_path("File path already exists: ");
const std::string unexpected_overrides_found("Found unexpected overrides: ");
}

namespace dogen {
namespace knit {
namespace backends {

cpp_backend::~cpp_backend() noexcept {}

cpp::formattables::project cpp_backend::create_project(
    const config::knitting_options& o, const sml::model& model) const {
    sml_to_cpp::workflow w(model, o);
    return w.execute();
}

std::forward_list<formatters::file> cpp_backend::
format_files(const config::knitting_options& o,
    const cpp::formattables::project& p) const {
    cpp_formatters::workflow w(o);
    return w.execute(p);
}

std::forward_list<formatters::file> cpp_backend::
format_files(const config::knitting_options& o,
    const dynamic::repository& rp, const sml::model& m) const {
    dogen::backend::workflow w(o, rp);
    return w.execute(m);
}

std::forward_list<formatters::file> cpp_backend::override_legacy_files(
    const std::forward_list<formatters::file>& old_world,
    const std::forward_list<formatters::file>& new_world) const {

    if (ignore_legacy_files)
        return new_world;

    if (!perform_override_of_legacy_files)
        return old_world;

    std::unordered_map<std::string, formatters::file> overrides;
    for (const auto& f : new_world) {
        const auto gs(f.path().generic_string());

        // FIXME: for now some of the formatters are generating blank
        // files. we do not want these to interfere with the rest so
        // we skip them.
        if (gs.empty()) {
            BOOST_LOG_SEV(lg, debug) << "Ignoring empty override: " << gs;
            continue;
        }

        if (!f.overwrite()) {
            BOOST_LOG_SEV(lg, debug) << "Skipping override: " << gs;
            continue;
        }

        BOOST_LOG_SEV(lg, debug) << "Adding override: '" << gs << "'";

        const auto result(overrides.insert(std::make_pair(gs, f)));
        if (!result.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_file_path << gs;
            BOOST_THROW_EXCEPTION(backend_error(duplicate_file_path + gs));
        }
    }

    std::forward_list<formatters::file> r;
    auto old_world_reverted(old_world);
    old_world_reverted.reverse();
    for (const auto& f : old_world_reverted) {
        const auto gs(f.path().generic_string());
        const auto i(overrides.find(gs));
        if (i != overrides.end()) {
            BOOST_LOG_SEV(lg, debug) << "File has been overriden: " << gs;
            r.push_front(i->second);
            overrides.erase(i);
        } else {
            BOOST_LOG_SEV(lg, debug) << "Using legacy for file: " << gs;
            r.push_front(f);
        }
    }

    if (!overrides.empty()) {
        BOOST_LOG_SEV(lg, error) << unexpected_overrides_found
                                 << overrides.size();

        for (const auto& pair : overrides)
            BOOST_LOG_SEV(lg, debug) << pair.first;

        BOOST_THROW_EXCEPTION(backend_error(unexpected_overrides_found
                + boost::lexical_cast<std::string>(overrides.size())));
    }

    return r;
}

std::forward_list<boost::filesystem::path> cpp_backend::
managed_directories(const config::knitting_options& o,
    const sml::model& m) const {
    sml_to_cpp::workflow w(m, o);
    return w.managed_directories();
}

std::forward_list<formatters::file> cpp_backend::
generate(const config::knitting_options& o,
    const dynamic::repository& rp,
    const sml::model& m) {

    // const auto p(create_project(o, m));
    // const auto old_world(format_files(o, p));
    const auto new_world(format_files(o, rp, m));
    // const auto r(override_legacy_files(old_world, new_world));
    return new_world;
}

} } }
