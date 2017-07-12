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
#include "dogen/yarn/io/meta_model/languages_io.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/quilt.cpp/types/fabric/injector.hpp"
#include "dogen/quilt.cpp/types/fabric/decoration_expander.hpp"
#include "dogen/quilt.cpp/types/fabric/external_transform.hpp"

namespace {

const std::string id("quilt.cpp.fabric.external_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

const std::string too_many_output_languages(
    "Expected only one output language");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

bool external_transform::
requires_expansion(const yarn::meta_model::intermediate_model& im) const {
    if (im.output_languages().size() != 1) {
        BOOST_LOG_SEV(lg, error) << too_many_output_languages;
        BOOST_THROW_EXCEPTION(
            yarn::transforms::transformation_error(too_many_output_languages));
    }

    const auto l(im.output_languages().front());
    const auto r(l == yarn::meta_model::languages::cpp);
    if (!r) {
        BOOST_LOG_SEV(lg, debug) << "Expansion not required: "
                                 << im.name().id() << " for language: " << l;
    }
    return r;
}

void external_transform::expand_injection(
    const annotations::type_repository& atrp,
    yarn::meta_model::intermediate_model& im) const {
    injector i;
    i.inject(atrp, im);
}

void external_transform::expand_decoration(
    const dogen::formatters::decoration_properties_factory& dpf,
    yarn::meta_model::intermediate_model& im) const {
    decoration_expander de;
    de.expand(dpf, im);
}

std::string external_transform::id() const {
    return ::id;
}

void external_transform::transform(const yarn::transforms::context& ctx,
    const dogen::formatters::decoration_properties_factory& dpf,
    yarn::meta_model::intermediate_model& im) const {

    if (!requires_expansion(im))
        return;

    expand_injection(ctx.type_repository(), im);
    expand_decoration(dpf, im);
}

} } } }
