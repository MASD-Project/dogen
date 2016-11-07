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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/yarn/io/descriptor_io.hpp"
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/types/descriptor_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.descriptor_factory"));

const std::string library_dir("library");

}

namespace dogen {
namespace yarn {

std::vector<boost::filesystem::path> descriptor_factory::to_library_dirs(
    const std::vector<boost::filesystem::path>& data_dirs) const {

    std::vector<boost::filesystem::path> r;
    r.reserve(data_dirs.size());
    for (const auto& dir : data_dirs)
        r.push_back(dir / library_dir);
    return r;
}

std::list<descriptor> descriptor_factory::
make(const std::vector<boost::filesystem::path>& dirs) const {

    BOOST_LOG_SEV(lg, debug) << "Creating descriptors for library models.";
    std::list<descriptor> r;
    for (const auto& dir : dirs) {
        BOOST_LOG_SEV(lg, trace) << "Directory: " << dir.generic_string();

        using namespace dogen::utility::filesystem;
        const auto files(find_files(dir));
        BOOST_LOG_SEV(lg, trace) << "Found " << files.size()
                                 << " paths to library models.";

        for (const auto& f: files) {
            BOOST_LOG_SEV(lg, trace) << "Library model: " << f.generic_string();

            descriptor d;
            d.path(f);
            d.is_target(false);
            d.extension(f.extension().string());
            r.push_back(d);
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Created descriptors for library models: " << r;
    return r;
}

std::list<descriptor>
descriptor_factory::make(const std::list<options::input>& refs) const {
    BOOST_LOG_SEV(lg, debug) << "Creating descriptors for reference models.";
    BOOST_LOG_SEV(lg, debug) << "Found " << refs.size() << " reference models.";

    std::list<descriptor> r;
    for (const auto ref: refs) {
        BOOST_LOG_SEV(lg, trace) << "Reference model: "
                                 << ref.path().generic_string();

        descriptor d;
        d.path(ref.path());
        d.external_modules(ref.external_modules());
        d.is_target(false);
        d.extension(ref.path().extension().string());
        r.push_back(d);
    }
    BOOST_LOG_SEV(lg, debug) << "Created descriptors for reference models: "
                             << r;
    return r;
}

descriptor descriptor_factory::make(const options::input& tg) const {
    BOOST_LOG_SEV(lg, debug) << "Creating descriptor for target model.";

    descriptor r;
    r.path(tg.path());
    r.is_target(true);
    r.external_modules(tg.external_modules());
    r.extension(tg.path().extension().string());

    BOOST_LOG_SEV(lg, trace) << "Added target model: " << r.path();
    BOOST_LOG_SEV(lg, debug) << "Created descriptor for target model: " << r;
    return r;
}

std::list<descriptor> descriptor_factory::
make(const std::vector<boost::filesystem::path>& data_dirs,
    const options::input_options& io,
    const annotations::annotation& /*a*/) const {

    const auto library_dirs(to_library_dirs(data_dirs));
    auto r(make(library_dirs));
    r.splice(r.end(), make(io.references()));
    return r;
}

} }
