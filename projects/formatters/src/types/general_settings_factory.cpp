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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/dynamic/schema/types/text.hpp"
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/formatters/types/traits.hpp"
#include "dogen/formatters/types/hydration_workflow.hpp"
#include "dogen/formatters/io/modeline_group_io.hpp"
#include "dogen/formatters/types/hydration_workflow.hpp"
#include "dogen/formatters/types/modeline_group_hydrator.hpp"
#include "dogen/formatters/io/licence_io.hpp"
#include "dogen/formatters/types/licence_hydrator.hpp"
#include "dogen/formatters/types/code_generation_marker_factory.hpp"
#include "dogen/formatters/types/building_error.hpp"
#include "dogen/formatters/types/general_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("formatters.general_settings_factory"));

const std::string missing_context_ptr("Context pointer is null");
const std::string modeline_groups_dir("modeline_groups");
const std::string licence_dir("licences");
const std::string cpp_modeline("c++");

}

namespace dogen {
namespace formatters {

general_settings_factory::general_settings_factory(
    const std::forward_list<boost::filesystem::path>& data_files_dirs) :
    data_files_directories_(data_files_dirs) {
    BOOST_LOG_SEV(lg, debug) << "Initialised with data files directories: "
                             << data_files_dirs;
}

void general_settings_factory::
throw_missing_item(const std::string& msg, const std::string& n) const {
    BOOST_LOG_SEV(lg, error) << msg << n;
    BOOST_THROW_EXCEPTION(building_error(msg + n));
}

boost::optional<licence> general_settings_factory::
extract_licence(const dynamic::schema::object& o) const {
    using namespace dynamic::schema;
    const field_selector fs(o);
    if (!fs.has_field(traits::licence_name()))
        return boost::optional<licence>();

    const auto ln(fs.get_text_content(traits::licence_name()));
    const auto i(licences_.find(ln));
    if (i == licences_.end())
        throw_missing_item("Licence not found: ", ln);

    if (!fs.has_field(traits::copyright_notices()))
        return i->second;

    licence l(i->second);
    const auto ch(fs.get_text_collection_content(traits::copyright_notices()));
    l.copyright_notices(ch);
    return l;
}

boost::optional<modeline> general_settings_factory::
extract_modeline(const dynamic::schema::object& o) const {
    using namespace dynamic::schema;
    const field_selector fs(o);
    if (!fs.has_field(traits::modeline_group_name()))
        return boost::optional<modeline>();

    const auto n(fs.get_text_content(traits::modeline_group_name()));
    const auto i(modeline_groups_.find(n));
    if (i == modeline_groups_.end())
        throw_missing_item("Modeline group not found: ", n);

    // FIXME: we should be looking for a backend supplied modeline.
    const auto modeline_group(i->second);
    const auto j(modeline_group.modelines().find(cpp_modeline));
    if (j == modeline_group.modelines().end())
        throw_missing_item("Modeline not found: ", cpp_modeline);

    return j->second;
}

std::string general_settings_factory::
extract_marker(const dynamic::schema::object& o) const {
    using namespace dynamic::schema;
    using cgm = traits::code_generation_marker;

    const field_selector fs(o);
    if (!fs.has_field(cgm::message()))
        return std::string();

    const auto message(fs.get_text_content(cgm::message()));
    if (message.empty())
        return message;

    const bool add_date_time(fs.get_boolean_content(cgm::add_date_time()));
    const bool add_warning(fs.get_boolean_content(cgm::add_warning()));
    code_generation_marker_factory f(add_date_time, add_warning, message);

    return f.make();
}

std::forward_list<boost::filesystem::path> general_settings_factory::
create_directory_list(const std::string& for_whom) const {
    std::forward_list<boost::filesystem::path> r;
    for (const auto& d : data_files_directories_)
        r.push_front(d / for_whom);
    return r;
}

void general_settings_factory::hydrate_modelines() {
    BOOST_LOG_SEV(lg, debug) << "Hydrating modelines.";
    const auto dirs(create_directory_list(modeline_groups_dir));
    BOOST_LOG_SEV(lg, debug) << "Modelines directories: " << dirs;

    hydration_workflow<modeline_group_hydrator> hw;
    modeline_groups_ = hw.hydrate(dirs);

    if (modeline_groups_.empty()) {
        BOOST_LOG_SEV(lg, warn) << "Did not find any modeline groups.";
        return;
    }

    BOOST_LOG_SEV(lg, debug) << "Hydrated modeline groups. Found: "
                             << modeline_groups_.size();
    BOOST_LOG_SEV(lg, debug) << "contents: " << modeline_groups_;
}

void general_settings_factory::hydrate_licences() {
    BOOST_LOG_SEV(lg, debug) << "Hydrating licences.";
    const auto dirs(create_directory_list(licence_dir));

    BOOST_LOG_SEV(lg, debug) << "Licence directories: " << dirs;
    hydration_workflow<licence_hydrator> hw;
    licences_ = hw.hydrate(dirs);

    if (licences_.empty()) {
        BOOST_LOG_SEV(lg, warn) << "Did not find any licences.";
        return;
    }

    BOOST_LOG_SEV(lg, debug) << "Hydrating licences. Found: "
                             << licences_.size();
    BOOST_LOG_SEV(lg, debug) << "contents: " << licences_;
}

bool general_settings_factory::empty() const {
    return modeline_groups_.empty() && licences_.empty();
}

void general_settings_factory::load_reference_data() {
    BOOST_LOG_SEV(lg, debug) << "Loading reference data.";

    hydrate_modelines();
    hydrate_licences();

    BOOST_LOG_SEV(lg, debug) << "Finished loading reference data.";
}

general_settings
general_settings_factory::make(const dynamic::schema::object& o) const {
    const auto modeline(extract_modeline(o));
    const auto licence(extract_licence(o));
    const auto marker(extract_marker(o));
    const annotation a(modeline, licence, marker);

    const bool generate_preamble(false); // FIXME: read from dynamic object
    return general_settings(generate_preamble, a);
}

boost::optional<general_settings> general_settings_factory::
make_only_if_overriden(const dynamic::schema::object& o) const {
    const auto modeline(extract_modeline(o));
    const auto licence(extract_licence(o));
    const auto marker(extract_marker(o));

    if (!modeline && !licence && marker.empty())
        return boost::optional<general_settings>();

    const annotation a(modeline, licence, marker);
    const bool generate_preamble(false); // FIXME: read from dynamic object
    return general_settings(generate_preamble, a);
}

} }
