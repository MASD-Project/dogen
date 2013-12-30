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
#include <boost/filesystem/path.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/meta_data_reader.hpp"
#include "dogen/om/types/workflow.hpp"
#include "dogen/engine/types/backends/om_backend.hpp"

using dogen::utility::filesystem::data_files_directory;
using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("engine.backends.om_backend"));

}
namespace dogen {
namespace engine {
namespace backends {

om_backend::
om_backend(const config::settings& settings, const sml::model& model)
    : settings_(settings), model_(model) { }

backend::ptr om_backend::
create(const config::settings& settings, const sml::model& model) {
    return backend::ptr(new om_backend(settings, model));
}

backend::value_type om_backend::generate() {
    boost::filesystem::path project_directory;
    boost::filesystem::path cpp_source_directory;
    boost::filesystem::path cpp_include_directory;
    std::list<boost::filesystem::path> data_files_directories;

    const auto mn(model_.name().simple_name());
    const auto& cpp(settings_.cpp());
    if (settings_.cpp().split_project()) {
        cpp_source_directory = cpp.source_directory();
        cpp_include_directory = cpp.include_directory();

        managed_directories_.reserve(2);
        managed_directories_.push_back(cpp_source_directory / mn);
        managed_directories_.push_back(cpp_include_directory / mn);
    } else {
        sml::meta_data_reader reader(model_.meta_data());
        const auto src_dir(reader.get(sml::tags::cpp::source_directory));

        const auto pd(settings_.cpp().project_directory());
        cpp_source_directory = pd / mn / src_dir;

        const auto inc_dir(reader.get(sml::tags::cpp::include_directory));
        cpp_include_directory = pd / mn / inc_dir;
        managed_directories_.push_back(cpp.project_directory() / mn);
    }

    BOOST_LOG_SEV(lg, debug) << "Directories used: source_directory_: "
                             << cpp_source_directory << " include_directory: "
                             << cpp_include_directory;

    om::workflow wk(project_directory, cpp_source_directory,
        cpp_include_directory, data_files_directories);

    const auto files(wk.execute(model_));

    backend::value_type r;
    for (const auto& f : files)
        r.insert(std::make_pair(f.absolute_path(), f.contents()));

    return r;
}

std::vector<boost::filesystem::path> om_backend::managed_directories() const {
    std::vector<boost::filesystem::path> r;

    const auto mn(model_.name().simple_name());
    if (settings_.cpp().split_project()) {
        r.reserve(2);
    } else {
    }
    return r;
}

} } }
