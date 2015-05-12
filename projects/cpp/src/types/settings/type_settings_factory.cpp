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
#include "dogen/cpp/types/settings/type_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.type_settings_factory"));

}

namespace dogen {
namespace cpp {
namespace settings {

type_settings_factory::
type_settings_factory(const dynamic::schema::repository& rp,
    const dynamic::schema::object& root_object)
    : properties_(make_properties(rp, root_object)) {}

type_settings_factory::properties type_settings_factory::make_properties(
    const dynamic::schema::repository& rp,
    const dynamic::schema::object& root_object) const {
    properties r;
    const dynamic::schema::repository_selector s(rp);
    const auto dcc(traits::cpp::type::disable_complete_constructor());
    r.disable_complete_constructor = s.select_field_by_name(dcc);

    const dynamic::schema::field_selector fs(root_object);
    r.root_disable_complete_constructor =
        fs.get_boolean_content_or_default(r.disable_complete_constructor);

    return r;
}

type_settings type_settings_factory::
make(const dynamic::schema::object& o) const {
    const dynamic::schema::field_selector fs(o);
    type_settings r;
    const auto& fd(properties_.disable_complete_constructor);
    if (fs.has_field(fd)) {
        r.disable_complete_constructor(
            fs.get_boolean_content_or_default(fd));
    } else {
        r.disable_complete_constructor(
            properties_.root_disable_complete_constructor);
    }

    return r;
}

} } }
