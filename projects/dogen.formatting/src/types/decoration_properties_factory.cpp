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
#include "dogen.utility/log/logger.hpp"
#include "dogen.annotations/types/entry_selector.hpp"
#include "dogen.annotations/types/type_repository_selector.hpp"
#include "dogen.formatting/types/traits.hpp"
#include "dogen.formatting/types/repository_factory.hpp"
#include "dogen.formatting/types/code_generation_marker_factory.hpp"
#include "dogen.formatting/types/building_error.hpp"
#include "dogen.formatting/types/decoration_properties_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("formatting.decoration_properties_factory"));

const std::string missing_context_ptr("Context pointer is null");
const std::string licence_not_found("Licence not found: ");
const std::string modeline_group_not_found("Modeline group not found: ");
const std::string modeline_not_found("Modeline not found: ");

}

namespace dogen {
namespace formatting {

decoration_properties_factory::
decoration_properties_factory(const annotations::type_repository& drp,
    const repository& rp) : repository_(rp),
                            field_definitions_(make_field_definitions(drp)),
                            default_configuration_() { }

decoration_properties_factory::
decoration_properties_factory(const annotations::type_repository& drp,
    const repository& rp, const annotations::annotation& fallback)
    : repository_(rp),
      field_definitions_(make_field_definitions(drp)),
      default_configuration_(make_decoration_configuration(fallback)),
      default_generate_decoration_(
          default_configuration_.generate_decoration()),
      default_licence_text_(get_licence_text(default_configuration_)),
      default_copyright_notices_(default_configuration_.copyright_notices()),
      default_modeline_group_(get_modeline_group(default_configuration_)),
      default_marker_(get_marker(default_configuration_)) {}

decoration_properties_factory::field_definitions
decoration_properties_factory::
make_field_definitions(const annotations::type_repository& rp) const {
    const annotations::type_repository_selector s(rp);

    field_definitions r;
    const auto gd(traits::decoration::generate_decoration());
    r.generate_decoration = s.select_type_by_name(gd);

    const auto cn(traits::decoration::copyright_notices());
    r.copyright_notice = s.select_type_by_name(cn);

    const auto ln(traits::decoration::licence_name());
    r.licence_name = s.select_type_by_name(ln);

    const auto& mlgn(traits::decoration::modeline_group_name());
    r. modeline_group_name = s.select_type_by_name(mlgn);

    using cgm = traits::decoration::code_generation_marker;
    r. marker_add_date_time = s.select_type_by_name(cgm::add_date_time());
    r. marker_add_warning = s.select_type_by_name(cgm::add_warning());
    r. marker_message = s.select_type_by_name(cgm::message());

    return r;
}

decoration_configuration decoration_properties_factory::
make_decoration_configuration(const annotations::annotation& a) const {
    const annotations::entry_selector s(a);

    decoration_configuration r;
    const auto& gd(field_definitions_.generate_decoration);
    if (s.has_entry(gd))
        r.generate_decoration(s.get_boolean_content(gd));

    const auto& cn(field_definitions_.copyright_notice);
    if (s.has_entry(cn))
        r.copyright_notices(s.get_text_collection_content(cn));

    const auto& ln(field_definitions_.licence_name);
    if (s.has_entry(ln))
        r.licence_name(s.get_text_content(ln));

    const auto& mlgn(field_definitions_.modeline_group_name);
    if (s.has_entry(mlgn))
        r.modeline_group_name(s.get_text_content(mlgn));

    const auto madt(field_definitions_.marker_add_date_time);
    if (s.has_entry(madt))
        r.marker_add_date_time(s.get_boolean_content(madt));

    const auto maw(field_definitions_.marker_add_warning);
    if (s.has_entry(maw))
        r.marker_add_date_time(s.get_boolean_content(maw));

    const auto msg(field_definitions_.marker_message);
    if (s.has_entry(msg))
        r.marker_message(s.get_text_content(msg));

    return r;
}

boost::optional<std::string> decoration_properties_factory::
get_licence_text(const decoration_configuration& fa) const {
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

boost::optional<licence> decoration_properties_factory::
get_licence(const decoration_configuration& fa) const {
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

boost::optional<modeline_group> decoration_properties_factory::
get_modeline_group(const decoration_configuration& fa) const {
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

modeline decoration_properties_factory::get_modeline_from_group(
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
decoration_properties_factory::get_modeline(const std::string& modeline_name,
    const decoration_configuration& fa) const {

    const auto overridden_modeline_group(get_modeline_group(fa));
    if (!overridden_modeline_group && !default_modeline_group_)
        return boost::optional<modeline>();

    if (overridden_modeline_group) {
        return get_modeline_from_group(modeline_name,
            *overridden_modeline_group);
    }

    return get_modeline_from_group(modeline_name, *default_modeline_group_);
}

boost::optional<std::string> decoration_properties_factory::
get_marker(const decoration_configuration& fa) const {

    const auto& msg(fa.marker_message());
    if (msg.empty())
        return std::string();

    const bool adt(*fa.marker_add_date_time());
    const bool aw(*fa.marker_add_warning());
    code_generation_marker_factory f(adt, aw, msg);
    return f.make();
}

std::string decoration_properties_factory::
get_marker_or_default(const decoration_configuration& fa) const {
    const auto overridden_marker(get_marker(fa));
    if (overridden_marker)
        return *overridden_marker;

    if (default_marker_)
        return *default_marker_;

    return std::string();
}

bool decoration_properties_factory::
get_generate_decoration_or_default(const decoration_configuration& fa) const {
    const auto overriden_generate_decoration(fa.generate_decoration());
    if (!overriden_generate_decoration && !default_generate_decoration_)
        return true; // FIXME: fairly random default.

    if (overriden_generate_decoration)
        return *overriden_generate_decoration;
    else
        return *default_generate_decoration_;
}

decoration_properties
decoration_properties_factory::make(const std::string& modeline_name,
    const decoration_configuration& fa) const {
    const auto modeline(get_modeline(modeline_name, fa));
    const auto licence(get_licence(fa));
    const auto marker(get_marker_or_default(fa));
    const bool gd(get_generate_decoration_or_default(fa));
    decoration_properties r(gd, modeline, licence, marker);
    return r;
}

decoration_properties decoration_properties_factory::
make(const std::string& modeline_name) const {
    const auto da = decoration_configuration();
    return make(modeline_name, da);
}

decoration_properties decoration_properties_factory::make(
    const std::string& modeline_name, const annotations::annotation& o) const {
    const auto dc(make_decoration_configuration(o));
    return make(modeline_name, dc);
}

} }
