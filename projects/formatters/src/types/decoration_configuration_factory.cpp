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
#include "dogen/formatters/types/hydration_workflow.hpp"
#include "dogen/formatters/types/code_generation_marker_factory.hpp"
#include "dogen/formatters/types/building_error.hpp"
#include "dogen/formatters/types/decoration_configuration_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("formatters.decoration_configuration_factory"));

const std::string missing_context_ptr("Context pointer is null");
const std::string licence_not_found("Licence not found: ");
const std::string modeline_group_not_found("Modeline group not found: ");
const std::string modeline_not_found("Modeline not found: ");

}

namespace dogen {
namespace formatters {

decoration_configuration_factory::
decoration_configuration_factory(const repository& rp) : repository_(rp) { }

decoration_configuration_factory::decoration_configuration_factory(
    const repository& rp, const decoration_annotations& fallback)
    : repository_(rp),
      default_licence_text_(get_licence_text(fallback)),
      default_copyright_notices_(fallback.copyright_notices()),
      default_modeline_group_(get_modeline_group(fallback)),
      default_marker_(get_marker(fallback)),
      default_generate_preamble_(fallback.generate_preamble()) { }

boost::optional<std::string> decoration_configuration_factory::
get_licence_text(const decoration_annotations& fa) const {
    if (fa.licence_name().empty())
        return boost::optional<std::string>();

    const auto ln(fa.licence_name());
    const auto i(repository_.licence_texts().find(ln));
    if (i == repository_.licence_texts().end()) {
        BOOST_LOG_SEV(lg, error) << licence_not_found << ln;
        BOOST_THROW_EXCEPTION(building_error(licence_not_found + ln));
    }
    return i->second;
}

boost::optional<licence> decoration_configuration_factory::
get_licence(const decoration_annotations& fa) const {
    const auto overriden_licence_text(get_licence_text(fa));
    const auto overriden_copyright_notices(fa.copyright_notices());

    const bool has_text(overriden_licence_text || default_licence_text_);
    const bool has_notices(overriden_copyright_notices.empty());
    const bool has_licence(has_text || has_notices);
    if (!has_licence)
        return boost::optional<licence>();

    licence r;
    if (overriden_licence_text)
        r.text(*overriden_licence_text);
    else if (default_licence_text_)
        r.text(*default_licence_text_);

    if (!overriden_copyright_notices.empty())
        r.copyright_notices(overriden_copyright_notices);
    else if (default_copyright_notices_)
        r.copyright_notices(*default_copyright_notices_);

    return r;
}

boost::optional<modeline_group> decoration_configuration_factory::
get_modeline_group(const decoration_annotations& fa) const {
    if (fa.modeline_group_name().empty())
        return boost::optional<modeline_group>();

    const auto n(fa.modeline_group_name());
    const auto i(repository_.modeline_groups().find(n));
    if (i == repository_.modeline_groups().end()) {
        BOOST_LOG_SEV(lg, error) << modeline_group_not_found << n;
        BOOST_THROW_EXCEPTION(building_error(modeline_group_not_found + n));
    }
    return i->second;
}

modeline decoration_configuration_factory::get_modeline_from_group(
    const std::string& modeline_name, const modeline_group& mg) const {
    const auto i(mg.modelines().find(modeline_name));
    if (i == mg.modelines().end()) {
        BOOST_LOG_SEV(lg, error) << modeline_not_found << modeline_name;
        BOOST_THROW_EXCEPTION(
            building_error(modeline_not_found + modeline_name));
    }
    return i->second;
}

boost::optional<modeline>
decoration_configuration_factory::get_modeline(const std::string& modeline_name,
    const decoration_annotations& fa) const {

    const auto overridden_modeline_group(get_modeline_group(fa));
    if (!overridden_modeline_group && !default_modeline_group_)
        return boost::optional<modeline>();

    if (overridden_modeline_group) {
        return get_modeline_from_group(modeline_name,
            *overridden_modeline_group);
    }

    return get_modeline_from_group(modeline_name, *default_modeline_group_);
}

boost::optional<std::string> decoration_configuration_factory::
get_marker(const decoration_annotations& fa) const {

    const auto& msg(fa.marker_message());
    if (msg.empty())
        return std::string();

    const bool adt(*fa.marker_add_date_time());
    const bool aw(*fa.marker_add_warning());
    code_generation_marker_factory f(adt, aw, msg);
    return f.make();
}

std::string decoration_configuration_factory::
get_marker_or_default(const decoration_annotations& fa) const {
    const auto overridden_marker(get_marker(fa));
    if (overridden_marker)
        return *overridden_marker;

    if (default_marker_)
        return *default_marker_;

    return std::string();
}

bool decoration_configuration_factory::
get_generate_preamble_or_default(const decoration_annotations& fa) const {
    const auto overriden_generate_preamble(fa.generate_preamble());
    if (!overriden_generate_preamble && !default_generate_preamble_)
        return true; // FIXME: fairly random default.

    if (overriden_generate_preamble)
        return *overriden_generate_preamble;
    else
        return *default_generate_preamble_;
}

decoration_configuration
decoration_configuration_factory::make(const std::string& modeline_name,
    const decoration_annotations& fa) const {
    const auto modeline(get_modeline(modeline_name, fa));
    const auto licence(get_licence(fa));
    const auto marker(get_marker_or_default(fa));
    const decoration d(modeline, licence, marker);
    const bool gp(get_generate_preamble_or_default(fa));
    return decoration_configuration(gp, d);
}

} }
