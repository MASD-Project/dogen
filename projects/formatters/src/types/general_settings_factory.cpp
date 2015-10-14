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
#include "dogen/dynamic/types/text.hpp"
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/formatters/types/traits.hpp"
#include "dogen/formatters/types/hydration_workflow.hpp"
#include "dogen/formatters/types/code_generation_marker_factory.hpp"
#include "dogen/formatters/types/building_error.hpp"
#include "dogen/formatters/types/general_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("formatters.general_settings_factory"));

const std::string missing_context_ptr("Context pointer is null");
const std::string licence_not_found("Licence not found: ");
const std::string modeline_group_not_found("Modeline group not found: ");
const std::string modeline_not_found("Modeline not found: ");

}

namespace dogen {
namespace formatters {

general_settings_factory::general_settings_factory(const repository& rp)
    : repository_(rp) { }

general_settings_factory::general_settings_factory(const repository& rp,
    const dynamic::object& fallback)
    : repository_(rp),
      default_licence_text_(extract_licence_text(fallback)),
      default_copyright_notices_(extract_copyright_notices(fallback)),
      default_modeline_group_(extract_modeline_group(fallback)),
      default_marker_(extract_marker(fallback)),
      default_generate_preamble_(extract_generate_preamble(fallback)) { }

boost::optional<std::string> general_settings_factory::
extract_licence_text(const dynamic::object& o) const {
    using namespace dynamic;
    const field_selector fs(o);
    if (!fs.has_field(traits::licence_name()))
        return boost::optional<std::string>();

    const auto ln(fs.get_text_content(traits::licence_name()));
    const auto i(repository_.licence_texts().find(ln));
    if (i == repository_.licence_texts().end()) {
        BOOST_LOG_SEV(lg, error) << licence_not_found << ln;
        BOOST_THROW_EXCEPTION(building_error(licence_not_found + ln));
    }
    return i->second;
}

boost::optional<std::list<std::string> > general_settings_factory::
extract_copyright_notices(const dynamic::object& o) const {
    using namespace dynamic;
    const field_selector fs(o);

    if (!fs.has_field(traits::copyright_notices()))
        return boost::optional<std::list<std::string> >();

    return fs.get_text_collection_content(traits::copyright_notices());
}

boost::optional<licence> general_settings_factory::
extract_licence(const dynamic::object& o) const {
    const auto overriden_licence_text(extract_licence_text(o));
    const auto overriden_copyright_notices(extract_copyright_notices(o));

    const bool has_licence(overriden_licence_text || default_licence_text_ ||
        overriden_copyright_notices);
    if (!has_licence)
        return boost::optional<licence>();

    licence r;
    if (overriden_licence_text)
        r.text(*overriden_licence_text);
    else if (default_licence_text_)
        r.text(*default_licence_text_);

    if (overriden_copyright_notices)
        r.copyright_notices(*overriden_copyright_notices);
    else if (default_copyright_notices_)
        r.copyright_notices(*default_copyright_notices_);

    return r;
}

boost::optional<modeline_group> general_settings_factory::
extract_modeline_group(const dynamic::object& o) const {
    using namespace dynamic;
    const field_selector fs(o);
    if (!fs.has_field(traits::modeline_group_name()))
        return boost::optional<modeline_group>();

    const auto n(fs.get_text_content(traits::modeline_group_name()));
    const auto i(repository_.modeline_groups().find(n));
    if (i == repository_.modeline_groups().end()) {
        BOOST_LOG_SEV(lg, error) << modeline_group_not_found << n;
        BOOST_THROW_EXCEPTION(building_error(modeline_group_not_found + n));
    }
    return i->second;
}

modeline general_settings_factory::get_modeline_from_group(
    const std::string& modeline_name, const modeline_group& mg) const {
    const auto i(mg.modelines().find(modeline_name));
    if (i == mg.modelines().end()) {
        BOOST_LOG_SEV(lg, error) << modeline_not_found << modeline_name;
        BOOST_THROW_EXCEPTION(
            building_error(modeline_not_found + modeline_name));
    }
    return i->second;
}

boost::optional<modeline> general_settings_factory::
extract_modeline(const std::string& modeline_name,
    const dynamic::object& o) const {

    const auto overridden_modeline_group(extract_modeline_group(o));
    if (!overridden_modeline_group && !default_modeline_group_)
        return boost::optional<modeline>();

    if (overridden_modeline_group) {
        return get_modeline_from_group(modeline_name,
            *overridden_modeline_group);
    }

    return get_modeline_from_group(modeline_name, *default_modeline_group_);
}

boost::optional<std::string> general_settings_factory::
extract_marker(const dynamic::object& o) const {
    using namespace dynamic;
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

std::string general_settings_factory::
extract_marker_or_default(const dynamic::object& o) const {
    const auto overridden_marker(extract_marker(o));
    if (overridden_marker)
        return *overridden_marker;
    if (default_marker_)
        return *default_marker_;

    return std::string();
}

boost::optional<bool> general_settings_factory::
extract_generate_preamble(const dynamic::object& o) const {
    using namespace dynamic;
    const field_selector fs(o);
    if (!fs.has_field(traits::generate_preamble()))
        return boost::optional<bool>();

    return fs.get_boolean_content(traits::generate_preamble());
}

bool general_settings_factory::
extract_generate_preamble_or_default(const dynamic::object& o) const {
    const auto overriden_generate_preamble(extract_generate_preamble(o));
    if (!overriden_generate_preamble && !default_generate_preamble_)
        return true; // random default.

    if (overriden_generate_preamble)
        return *overriden_generate_preamble;
    else
        return *default_generate_preamble_;
}

general_settings
general_settings_factory::make(const std::string& modeline_name,
    const dynamic::object& o) const {
    const auto modeline(extract_modeline(modeline_name, o));
    const auto licence(extract_licence(o));
    const auto marker(extract_marker_or_default(o));
    const annotation a(modeline, licence, marker);
    const bool gp(extract_generate_preamble_or_default(o));
    return general_settings(gp, a);
}


} }
