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
    const dynamic::repository_selector rs(rp);
    typedef traits::cpp::aspect aspect;

    const auto& cc(aspect::disable_complete_constructor());
    r.disable_complete_constructor = rs.select_field_by_name(cc);

    const auto& xs(aspect::disable_xml_serialization());
    r.disable_xml_serialization = rs.select_field_by_name(xs);

    const auto& rmdc(aspect::requires_manual_default_constructor());
    r.requires_manual_default_constructor = rs.select_field_by_name(rmdc);

    const auto& rmmc(aspect::requires_manual_move_constructor());
    r.requires_manual_move_constructor = rs.select_field_by_name(rmmc);

    const auto& rsm(aspect::requires_stream_manipulators());
    r.requires_stream_manipulators = rs.select_field_by_name(rsm);

    return r;
}

aspect_settings_factory::root_object_field_values aspect_settings_factory::
make_root_object_field_values(const field_definitions& fd,
    const dynamic::object& root_object) const {

    root_object_field_values r;
    const dynamic::field_selector fs(root_object);
    r.disable_complete_constructor = fs.get_boolean_content_or_default(
        fd.disable_complete_constructor);
    r.disable_xml_serialization = fs.get_boolean_content_or_default(
        fd.disable_xml_serialization);
    return r;
}

bool aspect_settings_factory::
obtain_field_value(const dynamic::field_selector& fs,
    const dynamic::field_definition& fd,
    const bool root_object_value) const {

    if (fs.has_field(fd))
        return fs.get_boolean_content(fd);

    return root_object_value;
}

aspect_settings
aspect_settings_factory::make(const dynamic::object& o) const {
    aspect_settings r;

    const dynamic::field_selector fs(o);
    const auto& fd(field_definitions_);
    const auto& fv(field_values_);

    r.disable_complete_constructor(
        obtain_field_value(fs, fd.disable_complete_constructor,
            fv.disable_complete_constructor));

    r.disable_xml_serialization(
        obtain_field_value(fs, fd.disable_xml_serialization,
            fv.disable_xml_serialization));

    r.requires_manual_default_constructor(
        fs.get_boolean_content_or_default(
            fd.requires_manual_default_constructor));

    r.requires_manual_move_constructor(
        fs.get_boolean_content_or_default(
            fd.requires_manual_move_constructor));

    r.requires_stream_manipulators(
        fs.get_boolean_content_or_default(
            fd.requires_stream_manipulators));

    return r;
}

aspect_settings aspect_settings_factory::make() const {
    aspect_settings r;
    r.disable_complete_constructor(field_values_.disable_complete_constructor);
    r.disable_xml_serialization(field_values_.disable_xml_serialization);
    return r;
}

} } } }
