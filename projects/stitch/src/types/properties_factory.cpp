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
#include "dogen/formatters/types/decoration_configuration_factory.hpp"
#include "dogen/stitch/types/stitching_settings_factory.hpp"
#include "dogen/stitch/types/properties_factory.hpp"

namespace {

const std::string cpp_modeline_name("cpp");

}

namespace dogen {
namespace stitch {

properties_factory::
properties_factory(const dynamic::repository& dynamic_repository,
    const dogen::formatters::repository& formatters_repository)
    : dynamic_repository_(dynamic_repository),
      formatters_repository_(formatters_repository) {}

boost::optional<formatters::decoration_configuration> properties_factory::
make_decoration_configuration(const dynamic::object& o) const {
    using dogen::formatters::decoration_configuration_factory;
    const auto& drp(dynamic_repository_);
    decoration_configuration_factory f(drp, formatters_repository_);
    return f.make(cpp_modeline_name, o);
}

stitching_settings properties_factory::
make_stitching_settings(const dynamic::object& o) const {
    stitching_settings_factory f(dynamic_repository_);
    return f.make(o);
}

properties
properties_factory::make(const dynamic::object& o) const {
    properties r;
    r.decoration_configuration(make_decoration_configuration(o));
    r.stitching_settings(make_stitching_settings(o));
    return r;
}

} }
