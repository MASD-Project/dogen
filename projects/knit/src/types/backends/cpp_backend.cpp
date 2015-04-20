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
const bool perform_override_of_legacy_files(false);

const std::string duplicate_file_path("File path already exists: ");

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
    const dynamic::schema::repository& rp, const sml::model& m) const {
    dogen::backend::workflow w(o, rp);
    return w.execute(m);
}

std::forward_list<formatters::file> cpp_backend::override_legacy_files(
    const std::forward_list<formatters::file>& old_world,
    const std::forward_list<formatters::file>& new_world) const {

    if (!perform_override_of_legacy_files)
        return old_world;

    std::unordered_map<std::string, formatters::file> overrides;
    for (const auto& f : new_world) {
        const auto gs(f.path().generic_string());
        const auto result(overrides.insert(std::make_pair(gs, f)));
        if (!result.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_file_path << gs;
            BOOST_THROW_EXCEPTION(backend_error(duplicate_file_path + gs));
        }
    }

    std::forward_list<formatters::file> r;
    for (const auto& f : old_world) {
        const auto i(overrides.find(f.path().generic_string()));
        if (i != overrides.end())
            r.push_front(i->second);
        else
            r.push_front(f);
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
    const dynamic::schema::repository& rp,
    const sml::model& m) {

    const auto p(create_project(o, m));
    const auto old_world(format_files(o, p));
    const auto new_world(format_files(o, rp, m));
    const auto r(override_legacy_files(old_world, new_world));
    return r;
}

} } }
