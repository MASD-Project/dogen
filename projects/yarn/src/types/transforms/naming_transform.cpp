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
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/naming_transform.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.naming_transform"));

const std::string missing_root_module("Root module not found.");
const std::string missing_naming_configuration("Must supply model modules.");

}

namespace dogen {
namespace yarn {
namespace transforms {

std::ostream&
operator<<(std::ostream& s, const naming_transform::type_group& v) {
    s << " { "
      << "\"__type__\": " << "\"yarn::naming_transform::"
      << "type_group\"" << ", "
      << "\"external_modules\": " << v.external_modules << ", "
      << "\"model_modules\": " << v.model_modules
      << " }";
    return s;
}

naming_transform::type_group
naming_transform::make_type_group(const annotations::type_repository& atrp) {
    type_group r;

    const annotations::type_repository_selector rs(atrp);

    const auto& em(traits::external_modules());
    r.external_modules = rs.select_type_by_name(em);

    const auto& mm(traits::model_modules());
    r.model_modules = rs.select_type_by_name(mm);

    return r;
}

boost::optional<naming_configuration>
naming_transform::make_naming_configuration(const type_group& tg,
    const annotations::annotation& a) {

    const annotations::entry_selector s(a);
    naming_configuration r;
    bool found_any(false);

    if (s.has_entry(tg.external_modules)) {
        found_any = true;
        r.external_modules(s.get_text_content(tg.external_modules));
    }

    if (s.has_entry(tg.model_modules)) {
        found_any = true;
        r.model_modules(s.get_text_content(tg.model_modules));
    }

    if (found_any)
        return r;

    return boost::optional<naming_configuration>();
}

const annotations::annotation& naming_transform::
obtain_root_annotation(const meta_model::exogenous_model& em) {
    for (const auto& pair : em.modules()) {
        const auto& m(pair.second);
        if (m.is_root())
            return m.annotation();
    }

    BOOST_LOG_SEV(lg, error) << missing_root_module;
    BOOST_THROW_EXCEPTION(transformation_error(missing_root_module));
}

meta_model::location
naming_transform::create_location(const naming_configuration& /*cfg*/) {
    meta_model::location r;
    return r;
}

void naming_transform::update_names(const meta_model::location& /*l*/,
    meta_model::exogenous_model& /*em*/) {

}

void naming_transform::
transform(const context& ctx, meta_model::exogenous_model& em) {
    const auto ra(obtain_root_annotation(em));
    const auto& atrp(ctx.type_repository());
    const auto tg(make_type_group(atrp));
    const auto cfg(make_naming_configuration(tg, ra));

    if (!cfg) {
        BOOST_LOG_SEV(lg, error) << missing_naming_configuration;
        BOOST_THROW_EXCEPTION(
            transformation_error(missing_naming_configuration));
    }

    const auto l(create_location(*cfg));
    update_names(l, em);
}

} } }
