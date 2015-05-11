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
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/dynamic/schema/types/repository_selector.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/settings/building_error.hpp"
#include "dogen/cpp/types/settings/inclusion_directives_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.settings.inclusion_directives_settings_factory"));

const std::string field_definition_not_found(
    "Could not find expected field definition: ");
const std::string empty_formatter_name("Formatter name is empty.");

}

namespace dogen {
namespace cpp {
namespace settings {

inclusion_directives_settings_factory::
inclusion_directives_settings_factory(const dynamic::schema::repository& rp,
    const formatters::container& fc)
    : formatter_properties_(make_formatter_properties(rp, fc)),
      inclusion_required_(get_inclusion_required_field(rp)) {}

void inclusion_directives_settings_factory::
setup_formatter_fields(const dynamic::schema::repository& rp,
    const std::string& formatter_name,
    formatter_properties& fp) const {

    bool found(false);
    const dynamic::schema::repository_selector s(rp);
    for (const auto fd : s.select_fields_by_formatter_name(formatter_name)) {
        if (fd.name().simple() == traits::inclusion_directive()) {
            fp.inclusion_directive = fd;
            found = true;
        }
    }

    if (!found) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::inclusion_directive()
                                 << "' for formatter: "
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(building_error(field_definition_not_found +
                traits::inclusion_directive()));
    }
}

inclusion_directives_settings_factory::formatter_properties
inclusion_directives_settings_factory::make_formatter_properties(
    const dynamic::schema::repository& rp,
    const formatters::formatter_interface& f) const {

    formatter_properties r;
    const auto oh(f.ownership_hierarchy());
    r.formatter_name = oh.formatter_name();
    setup_formatter_fields(rp, oh.formatter_name(), r);
    return r;
}

std::unordered_map<
    std::string,
    inclusion_directives_settings_factory::formatter_properties
    >
inclusion_directives_settings_factory::
make_formatter_properties(const dynamic::schema::repository& rp,
    const formatters::container& fc) const {
    std::unordered_map<std::string, formatter_properties> r;

    for (const auto f : fc.all_formatters()) {
        const auto& oh(f->ownership_hierarchy());
        if (oh.formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(building_error(empty_formatter_name));
        }
        r[oh.formatter_name()] = make_formatter_properties(rp, *f);
    }

    return r;
}

dynamic::schema::field_definition inclusion_directives_settings_factory::
get_inclusion_required_field(const dynamic::schema::repository& rp) const {
    const dynamic::schema::repository_selector s(rp);
    return s.select_field_by_name(traits::cpp::inclusion_required());
}

boost::optional<std::string> inclusion_directives_settings_factory::
obtain_inclusion_directive_for_formatter(const formatter_properties& fp,
    const dynamic::schema::object& o) const {
    boost::optional<std::string> r;

    using namespace dynamic::schema;
    const field_selector fs(o);
    if (!fs.has_field(fp.inclusion_directive))
        return r;

    r = fs.get_text_content(fp.inclusion_directive);
    return r;
}

bool inclusion_directives_settings_factory::
obtain_inclusion_required(const dynamic::schema::object& o) const {
    using namespace dynamic::schema;
    const field_selector fs(o);
    return fs.get_boolean_content_or_default(inclusion_required_);
}

inclusion_directives_settings inclusion_directives_settings_factory::make(
    const dynamic::schema::object& o) const {
    inclusion_directives_settings r;

    const auto inclusion_required(obtain_inclusion_required(o));
    for (const auto& pair : formatter_properties_) {
        const auto& fp(pair.second);
        const auto id(obtain_inclusion_directive_for_formatter(fp, o));
        if (!id)
            continue;

        r.inclusion_directives().insert(std::make_pair(fp.formatter_name, *id));
        r.inclusion_required(inclusion_required);
    }
    return r;
}

} } }
