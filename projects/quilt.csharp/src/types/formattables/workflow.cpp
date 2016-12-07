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
#include "dogen/quilt.csharp/types/formattables/transformer.hpp"
#include "dogen/quilt.csharp/types/formattables/model_expander.hpp"
#include "dogen/quilt.csharp/types/formattables/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.csharp.formattables.workflow"));

}

namespace dogen {
namespace quilt {
namespace csharp {
namespace formattables {

model workflow::
make_model(const formatters::repository& frp, const yarn::model& m) const {
    model r;
    r.name(m.name());

    transformer t;
    r.formattables(t.transform(frp, m));

    return r;
}

void workflow::expand_model(
    const annotations::type_repository& atrp,
    const annotations::annotation& ra,
    const dogen::formatters::decoration_properties_factory& dpf,
    const formatters::repository& frp, const locator& l, model& fm) const {
    model_expander ex;
    ex.expand(atrp, ra, dpf, frp, l, fm);
}

model workflow::execute(
    const options::knitting_options& ko,
    const annotations::type_repository& atrp,
    const annotations::annotation& ra,
    const dogen::formatters::decoration_properties_factory& dpf,
    const formatters::repository& frp, const bool enable_kernel_directories,
    const yarn::model& m) const {

    auto r(make_model(frp, m));
    const auto odp(ko.output_directory_path());
    const auto rkd(enable_kernel_directories);
    const locator l(odp, atrp, frp, ra, m.name(), m.module_ids(), rkd);
    expand_model(atrp, ra, dpf, frp, l, r);

    return r;
}

} } } }
