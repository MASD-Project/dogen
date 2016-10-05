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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/formatters/io/modeline_group_io.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/formatters/io/repository_io.hpp"
#include "dogen/formatters/types/hydration_workflow.hpp"
#include "dogen/formatters/types/modeline_group_hydrator.hpp"
#include "dogen/formatters/types/licence_text_hydrator.hpp"
#include "dogen/formatters/types/hydration_workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("formatters.hydration_workflow"));

const std::string modeline_groups_dir("modeline_groups");
const std::string licence_dir("licences");

}

namespace dogen {
namespace formatters {

std::forward_list<boost::filesystem::path>
hydration_workflow::create_directory_list(
    const std::forward_list<boost::filesystem::path>& dirs,
    const std::string& for_whom) const {
    std::forward_list<boost::filesystem::path> r;
    for (const auto& d : dirs)
        r.push_front(d / for_whom);
    return r;
}

std::unordered_map<std::string, modeline_group>
hydration_workflow::hydrate_modeline_groups(
    const std::forward_list<boost::filesystem::path>& dirs) const {
    BOOST_LOG_SEV(lg, debug) << "Hydrating modeline groups.";

    const auto d(create_directory_list(dirs, modeline_groups_dir));
    BOOST_LOG_SEV(lg, debug) << "Modelines directories: " << dirs;

    modeline_group_hydrator h;
    std::unordered_map<std::string, modeline_group> r;
    const auto files(dogen::utility::filesystem::find_files(d));
    for (const auto& f : files) {
        BOOST_LOG_SEV(lg, debug) << "Hydrating file: " << f.generic_string();
        const auto mg(h.hydrate(f));
        const auto pair(std::make_pair(mg.name(), mg));
        r.insert(pair);
    }

    if (r.empty()) {
        BOOST_LOG_SEV(lg, warn) << "Did not find any modeline groups.";
        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "Hydrated modeline groups. Found: " << r.size();
    return r;
}

std::unordered_map<std::string, std::string> hydration_workflow::
hydrate_licence_texts(
    const std::forward_list<boost::filesystem::path>& dirs) const {
    BOOST_LOG_SEV(lg, debug) << "Hydrating licence texts.";
    const auto d(create_directory_list(dirs, licence_dir));

    BOOST_LOG_SEV(lg, debug) << "Licence directories: " << d;

    licence_text_hydrator h;
    std::unordered_map<std::string, std::string> r;
    const auto files(dogen::utility::filesystem::find_files(d));
    for (const auto& f : files) {
        BOOST_LOG_SEV(lg, debug) << "Hydrating file: " << f.generic_string();
        const auto text(h.hydrate(f));
        const auto pair(std::make_pair(f.filename().generic_string(), text));
        r.insert(pair);
    }

    if (r.empty()) {
        BOOST_LOG_SEV(lg, warn) << "Did not find any licences.";
        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "Hydrating licences. Found: " << r.size();
    return r;
}

repository hydration_workflow::hydrate(
    const std::forward_list<boost::filesystem::path>& dirs) const {
    BOOST_LOG_SEV(lg, debug) << "Hydrating repository.";

    repository r;
    r.modeline_groups(hydrate_modeline_groups(dirs));
    r.licence_texts(hydrate_licence_texts(dirs));

    BOOST_LOG_SEV(lg, debug) << "Hydrated repository: " << r;
    return r;
}

} }
