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
#include "dogen/dynamic/schema/types/content_extensions.hpp"
#include "dogen/cpp/types/settings/building_error.hpp"
#include "dogen/cpp/io/formattables/family_types_io.hpp"
#include "dogen/cpp/types/settings/field_definitions.hpp"
#include "dogen/cpp/types/settings/type_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.type_settings_factory"));

const std::string character_family_type("character");
const std::string string_family_type("string");
const std::string boolean_family_type("boolean");
const std::string integer_family_type("integer");
const std::string floating_point_family_type("floating_point");
const std::string smart_pointer_family_type("smart_pointer");
const std::string ordered_container_family_type("ordered_container");
const std::string sequence_container_family_type("sequence_container");
const std::string hash_container_family_type("hash_container");
const std::string other_family_type("other");

const std::string unsupported_family_type("Family type is not supported: ");

}

namespace dogen {
namespace cpp {
namespace settings {

formattables::family_types type_settings_factory::
to_family_type(const std::string s) const {
    using ft = formattables::family_types;
    if (s == character_family_type)
        return ft::character;
    else if (s == string_family_type)
        return ft::string;
    else if (s == boolean_family_type)
        return ft::boolean;
    else if (s == integer_family_type)
        return ft::integer;
    else if (s == floating_point_family_type)
        return ft::floating_point;
    else if (s == smart_pointer_family_type)
        return ft::smart_pointer;
    else if (s == ordered_container_family_type)
        return ft::ordered_container;
    else if (s == sequence_container_family_type)
        return ft::sequence_container;
    else if (s == hash_container_family_type)
        return ft::hash_container;
    else if (s == other_family_type)
        return ft::other;

    BOOST_LOG_SEV(lg, error) << unsupported_family_type << s;
    BOOST_THROW_EXCEPTION(building_error(unsupported_family_type + s));
}

boost::optional<type_settings> type_settings_factory::
make(const dynamic::schema::object& o) const {
    using namespace dynamic::schema;

    type_settings r;
    using fd = field_definitions::type;
    bool found_any_field(false);
    if (has_field(o, fd::family())) {
        found_any_field = true;
        r.family_type(to_family_type(get_text_content(o, fd::family())));
    }

    if (has_field(o, fd::requires_manual_default_constructor())) {
        found_any_field = true;
        r.requires_manual_default_constructor(
            get_boolean_content(o, fd::requires_manual_default_constructor()));
    }

    if (has_field(o, fd::requires_manual_move_constructor())) {
        found_any_field = true;
        r.requires_manual_move_constructor(
            get_boolean_content(o, fd::requires_manual_move_constructor()));
    }

    if (has_field(o, fd::inclusion_required())) {
        found_any_field = true;
        r.inclusion_required(get_boolean_content(o, fd::inclusion_required()));
    }

    if (found_any_field)
        return r;

    return boost::optional<type_settings>();
}

} } }
