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
#include <list>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/om/io/modeline_group_io.hpp"
#include "dogen/om/types/hydration_workflow.hpp"
#include "dogen/om/types/modeline_group_hydrator.hpp"
#include "dogen/om/io/licence_io.hpp"
#include "dogen/om/types/licence_hydrator.hpp"
#include "dogen/om/types/workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("om.workflow"));
const std::string modeline_groups_dir("modeline_groups");
const std::string licence_dir("licences");

}

namespace dogen {
namespace om {

workflow::workflow(const boost::filesystem::path& data_files_directory)
    : data_files_directory_(data_files_directory) { }

void workflow::hydrate_modelines() {
    const std::list<boost::filesystem::path> d = {
        data_files_directory_ / modeline_groups_dir
    };

    hydration_workflow<modeline_group_hydrator> hw;
    modeline_groups_ = hw.hydrate(d);

    BOOST_LOG_SEV(lg, info) << "Loaded modeline groups. Found:  "
                            << modeline_groups_.size();
    BOOST_LOG_SEV(lg, debug) << "contents: " << modeline_groups_;
}

void workflow::hydrate_licences(const sml::model& m) {
    const std::list<boost::filesystem::path> d = {
        data_files_directory_ / licence_dir
    };

    std::list<std::string> copyright_holders;
    const auto i(m.complex_tags().find(sml::tags::copyright_holder));
    if (i != m.complex_tags().end())
        copyright_holders = i->second;

    licence_hydrator lh(copyright_holders);
    hydration_workflow<licence_hydrator> hw(lh);
    licences_ = hw.hydrate(d);

    BOOST_LOG_SEV(lg, info) << "Loaded licences. Found:  "
                            << licences_.size();
    BOOST_LOG_SEV(lg, debug) << "contents: " << licences_;
}

void workflow::load_data_activity(const sml::model& m) {
    hydrate_modelines();
    hydrate_licences(m);
}

std::map<boost::filesystem::path, std::string>
workflow::execute(const sml::model& m) {
    load_data_activity(m);
    std::map<boost::filesystem::path, std::string> r;
    return r;
}

} }
