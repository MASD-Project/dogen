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
#include "dogen/formatters/types/general_settings_factory.hpp"
#include "dogen/stitch/types/stitching_settings_factory.hpp"
#include "dogen/stitch/types/settings_bundle_factory.hpp"

namespace {

const std::string cpp_modeline_name("cpp");

}

namespace dogen {
namespace stitch {

settings_bundle_factory::
settings_bundle_factory(const dynamic::repository& dynamic_repository,
    const dogen::formatters::repository& formatters_repository)
    : dynamic_repository_(dynamic_repository),
      formatters_repository_(formatters_repository) {}

boost::optional<formatters::general_settings> settings_bundle_factory::
make_general_settings(const dynamic::object& o) const {
    using dogen::formatters::general_settings_factory;
    general_settings_factory f(formatters_repository_);
    return f.make(cpp_modeline_name, o);
}

stitching_settings settings_bundle_factory::
make_stitching_settings(const dynamic::object& o) const {
    stitching_settings_factory f(dynamic_repository_);
    return f.make(o);
}

settings_bundle
settings_bundle_factory::make(const dynamic::object& o) const {
    settings_bundle r;
    r.general_settings(make_general_settings(o));
    r.stitching_settings(make_stitching_settings(o));
    return r;
}

} }
