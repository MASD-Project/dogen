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
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/settings/building_error.hpp"
#include "dogen/quilt.cpp/types/settings/aspect_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.settings.aspect_settings_factory"));

const std::string empty_formatter_name("Formatter name is empty.");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

aspect_settings_factory::aspect_settings_factory(const dynamic::repository& rp,
    const dynamic::object& root_object)
    : field_definitions_(make_field_definitions(rp)),
      field_values_(
          make_root_object_field_values(field_definitions_, root_object)) {}

aspect_settings_factory::field_definitions aspect_settings_factory::
make_field_definitions(const dynamic::repository& rp) const {

    field_definitions r;
    const dynamic::repository_selector s(rp);
    const auto& cc(traits::disable_complete_constructor());
    r.disable_complete_constructor = s.select_field_by_name(cc);

    const auto& xs(traits::disable_xml_serialization());
    r.disable_xml_serialization = s.select_field_by_name(xs);

    return r;
}

aspect_settings_factory::root_object_field_values aspect_settings_factory::
make_root_object_field_values(const field_definitions& fd,
    const dynamic::object& root_object) const {

    root_object_field_values r;
    r.disable_complete_constructor =
        obtain_field_value(fd.disable_complete_constructor, root_object);
    r.disable_xml_serialization =
        obtain_field_value(fd.disable_xml_serialization, root_object);
    return r;
}

bool aspect_settings_factory::
obtain_field_value(const dynamic::field_definition& fd,
    const dynamic::object& o) const {
    using namespace dynamic;
    const field_selector fs(o);
    const auto r(fs.get_boolean_content_or_default(fd));
    return r;
}

bool aspect_settings_factory::
obtain_field_value(const dynamic::field_definition& fd,
    const bool root_object_value, const dynamic::object& o) const {

    const dynamic::field_selector fs(o);
    if (fs.has_field(fd))
        return fs.get_boolean_content(fd);

    return root_object_value;
}

aspect_settings aspect_settings_factory::make(const dynamic::object& o) const {
    aspect_settings r;
    r.disable_complete_constructor(
        obtain_field_value(field_definitions_.disable_complete_constructor,
            field_values_.disable_complete_constructor, o));

    r.disable_xml_serialization(
        obtain_field_value(field_definitions_.disable_xml_serialization,
            field_values_.disable_xml_serialization, o));

    return r;
}

aspect_settings aspect_settings_factory::make() const {
    aspect_settings r;
    r.disable_complete_constructor(field_values_.disable_complete_constructor);
    r.disable_xml_serialization(field_values_.disable_xml_serialization);
    return r;
}

} } } }
