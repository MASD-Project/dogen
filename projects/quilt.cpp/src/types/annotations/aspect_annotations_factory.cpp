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
#include "dogen/quilt.cpp/types/annotations/building_error.hpp"
#include "dogen/quilt.cpp/types/annotations/aspect_annotations_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.annotations.aspect_annotations_factory"));

const std::string empty_formatter_name("Formatter name is empty.");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

aspect_annotations_factory::
aspect_annotations_factory(const dynamic::repository& rp)
    : field_definitions_(make_field_definitions(rp)) {}

aspect_annotations_factory::field_definitions aspect_annotations_factory::
make_field_definitions(const dynamic::repository& rp) const {

    field_definitions r;
    const dynamic::repository_selector rs(rp);
    typedef traits::cpp::aspect aspect;

    const auto& rmdc(aspect::requires_manual_default_constructor());
    r.requires_manual_default_constructor = rs.select_field_by_name(rmdc);

    const auto& rmmc(aspect::requires_manual_move_constructor());
    r.requires_manual_move_constructor = rs.select_field_by_name(rmmc);

    const auto& rsm(aspect::requires_stream_manipulators());
    r.requires_stream_manipulators = rs.select_field_by_name(rsm);

    return r;
}

boost::optional<aspect_annotations>
aspect_annotations_factory::make(const dynamic::object& o) const {
    aspect_annotations r;

    const dynamic::field_selector fs(o);
    const auto& fd(field_definitions_);
    bool found(false);

    if (fs.has_field(fd.requires_manual_default_constructor))
        found = true;

    r.requires_manual_default_constructor(
        fs.get_boolean_content_or_default(
            fd.requires_manual_default_constructor));

    if (fs.has_field(fd.requires_manual_move_constructor))
        found = true;

    r.requires_manual_move_constructor(
        fs.get_boolean_content_or_default(
            fd.requires_manual_move_constructor));

    if (fs.has_field(fd.requires_stream_manipulators))
        found = true;

    r.requires_stream_manipulators(
        fs.get_boolean_content_or_default(
            fd.requires_stream_manipulators));

    if (found)
        return r;

    return boost::optional<aspect_annotations>();
}

} } } }
