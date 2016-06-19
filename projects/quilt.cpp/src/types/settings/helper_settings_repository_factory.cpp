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
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/settings/helper_settings_factory.hpp"
#include "dogen/quilt.cpp/io/settings/helper_settings_repository_io.hpp"
#include "dogen/quilt.cpp/types/settings/helper_settings_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.settings.helper_settings_repository_factory"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

helper_settings_repository helper_settings_repository_factory::
make(const dynamic::repository& rp, const yarn::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started making helper settings.";

    helper_settings_repository r;
    helper_settings_factory f(rp);
    for (const auto& pair : m.elements()) {
        const auto& e(*pair.second);
        const auto hs(f.make(e.extensions()));
        if (!hs)
            continue;

        r.helper_settings_by_name()[e.name().id()] = *hs;
    }
    BOOST_LOG_SEV(lg, debug) << "Finished making helper settings" << r;
    return r;
}

} } } }
