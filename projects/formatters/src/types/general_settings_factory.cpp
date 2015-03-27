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
#include "dogen/dynamic/schema/types/text.hpp"
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/formatters/types/traits.hpp"
#include "dogen/formatters/types/hydration_workflow.hpp"
#include "dogen/formatters/types/code_generation_marker_factory.hpp"
#include "dogen/formatters/types/building_error.hpp"
#include "dogen/formatters/types/general_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("formatters.general_settings_factory"));

const std::string missing_context_ptr("Context pointer is null");
const std::string cpp_modeline("c++");

}

namespace dogen {
namespace formatters {

general_settings_factory::general_settings_factory(const repository& rp)
    : repository_(rp) { }

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
    const auto i(repository_.licence_texts().find(ln));
    if (i == repository_.licence_texts().end())
        throw_missing_item("Licence not found: ", ln);

    licence r;
    r.text(i->second);

    if (!fs.has_field(traits::copyright_notices()))
        return r;

    const auto cn(fs.get_text_collection_content(traits::copyright_notices()));
    r.copyright_notices(cn);
    return r;
}

boost::optional<modeline> general_settings_factory::
extract_modeline(const dynamic::schema::object& o) const {
    using namespace dynamic::schema;
    const field_selector fs(o);
    if (!fs.has_field(traits::modeline_group_name()))
        return boost::optional<modeline>();

    const auto n(fs.get_text_content(traits::modeline_group_name()));
    const auto i(repository_.modeline_groups().find(n));
    if (i == repository_.modeline_groups().end())
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

general_settings
general_settings_factory::make(const dynamic::schema::object& o) const {
    const auto modeline(extract_modeline(o));
    const auto licence(extract_licence(o));
    const auto marker(extract_marker(o));
    const annotation a(modeline, licence, marker);

    const bool generate_preamble(false); // FIXME: read from dynamic object
    return general_settings(generate_preamble, a);
}

} }
