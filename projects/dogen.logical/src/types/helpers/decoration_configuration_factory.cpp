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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.logical/types/helpers/decoration_configuration_factory.hpp"

namespace {

const std::string transform_id(
    "logical.helpers.decoration_configuration_factory");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::logical::helpers {

boost::optional<decoration_configuration>
decoration_configuration_factory::
make(const features::decoration::feature_group& fg,
    const variability::entities::configuration& cfg) {

    bool has_configuration(false);
    const auto scfg(features::decoration::make_static_configuration(fg, cfg));
    decoration_configuration r;
    if (scfg.enabled) {
        r.enabled(scfg.enabled);
        has_configuration = true;
    }

    if (!scfg.copyright_notice.empty()) {
        r.copyright_notices(scfg.copyright_notice);
        has_configuration = true;
    }

    using identification::entities::logical_id;
    if (!scfg.licence_name.empty()) {
        r.licence_name(logical_id(scfg.licence_name));
        has_configuration = true;
    }

    if (!scfg.modeline_group_name.empty()) {
        r.modeline_group_name(logical_id(scfg.modeline_group_name));
        has_configuration = true;
    }

    if (!scfg.marker_name.empty()) {
        r.marker_name(logical_id(scfg.marker_name));
        has_configuration = true;
    }

    if (has_configuration) {
        BOOST_LOG_SEV(lg, debug) << "Read decoration configuration.";
        return r;
    }

    return boost::optional<decoration_configuration>();
}

}
