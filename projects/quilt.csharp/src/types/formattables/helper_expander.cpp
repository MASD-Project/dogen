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
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/quilt.csharp/io/formattables/helper_configuration_io.hpp"
#include "dogen/quilt.csharp/types/formattables/helper_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.csharp.formattables.helper_expander"));

}

namespace dogen {
namespace quilt {
namespace csharp {
namespace formattables {

helper_expander::type_group helper_expander::
make_type_group(const annotations::type_repository& atrp) const {
    const annotations::type_repository_selector s(atrp);
    const auto hf(traits::csharp::helper::family());
    type_group r;
    r.family = s.select_type_by_name(hf);
    return r;
}

helper_configuration helper_expander::
make_configuration(const type_group& tg, const model& fm) const {

    BOOST_LOG_SEV(lg, debug) << "Started making the configuration.";
    helper_configuration r;

    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& e(*formattable.element());
        const annotations::entry_selector s(e.annotation());
        const auto fam(s.get_text_content_or_default(tg.family));
        r.helper_families()[id] = fam;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished making the configuration. Result:"
                             << r;

    return r;
}

void helper_expander::expand(const annotations::type_repository& atrp,
    const formatters::repository& /*frp*/, model& fm) const {
    const auto tg(make_type_group(atrp));
    /*const auto cfg(*/make_configuration(tg, fm)/*)*/;
    // populate_helper_properties(cfg, frp, fm.formattables());
}

} } } }
