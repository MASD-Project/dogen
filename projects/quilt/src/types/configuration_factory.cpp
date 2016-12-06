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
#include "dogen/quilt/types/traits.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/quilt/types/configuration_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.configuration_factory"));

}

namespace dogen {
namespace quilt {

configuration_factory::type_group configuration_factory::
make_type_group(const annotations::type_repository& atrp,
    const std::list<annotations::archetype_location>& als) const {
    type_group r;

    const annotations::type_repository_selector rs(atrp);
    const auto ekd(traits::enable_kernel_directories());
    r.enable_kernel_directories = rs.select_type_by_name(ekd);

    const auto en(traits::enabled());
    for (const auto al : als) {
        type_group tg;
        const auto kernel(al.kernel());
        r.enabled.push_back(rs.select_type_by_name(kernel, en));
    }

    return r;
}

std::unordered_set<std::string>
configuration_factory::obtain_enabled_kernels(const type_group& tg,
    const annotations::annotation& ra) const {

    std::unordered_set<std::string> r;
    const annotations::entry_selector s(ra);
    for (const auto& t : tg.enabled) {
        const bool enabled(s.get_boolean_content_or_default(t));
        if (!enabled)
            continue;

        r.insert(t.archetype_location().kernel());
    }

    return r;
}

bool configuration_factory::obtain_enable_kernel_directories(
    const type_group& tg, const annotations::annotation& ra) const {
    const annotations::entry_selector s(ra);
    return s.get_boolean_content_or_default(tg.enable_kernel_directories);
}

configuration
configuration_factory::make(const annotations::type_repository& atrp,
    const std::list<annotations::archetype_location>& als,
    const annotations::annotation& ra) const {

    configuration r;
    const auto tg(make_type_group(atrp, als));
    r.enabled_kernels(obtain_enabled_kernels(tg, ra));
    if (r.enabled_kernels().size() > 1) {
        BOOST_LOG_SEV(lg, warn) << "More than one kernel is enabled: "
                                << r.enabled_kernels().size()
                                << ". Forcing enable_kernel_directories.";
        r.enable_kernel_directories(true);
    } else
        r.enable_kernel_directories(obtain_enable_kernel_directories(tg, ra));

    return r;
}

} }
