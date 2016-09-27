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
#include "dogen/quilt.cpp/types/formattables/transformer.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/enablement_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/decoration_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/aspect_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/pre_reduction_workflow.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::unordered_map<std::string, formattable> pre_reduction_workflow::
transform(const formatters::container& fc, const yarn::model& m) const {
    transformer t;
    return t.transform(fc, m);
}

void pre_reduction_workflow::expand_enablement(const dynamic::repository& drp,
    const dynamic::object& root_object, const formatters::container& fc,
    std::unordered_map<std::string, formattable>& formattables) const {
    enablement_expander ex;
    ex.expand(drp, root_object, fc, formattables);
}

void pre_reduction_workflow::expand_inclusion(
    const dynamic::repository& drp, const formatters::container& fc,
    const locator& l,
    std::unordered_map<std::string, formattable>& formattables) const {

    inclusion_expander ex;
    ex.expand(drp, fc, l, formattables);
}

void pre_reduction_workflow::expand_decoration(
    const dogen::formatters::decoration_configuration_factory& dcf,
    std::unordered_map<std::string, formattable>& formattables) const {
    decoration_expander ex;
    ex.expand(dcf, formattables);
}

void pre_reduction_workflow::expand_aspects(const dynamic::repository& drp,
    std::unordered_map<std::string, formattable>& formattables) const {
    aspect_expander ex;
    ex.expand(drp, formattables);
}

void pre_reduction_workflow::expand_helpers(const dynamic::repository& drp,
    const formatters::container& fc,
    std::unordered_map<std::string, formattable>& formattables) const {
    helper_expander ex;
    ex.expand(drp, fc, formattables);
}

std::unordered_map<std::string, formattable> pre_reduction_workflow::
execute(const dynamic::repository& drp, const dynamic::object& root_object,
    const dogen::formatters::decoration_configuration_factory& dcf,
    const formatters::container& fc, const locator& l,
    const yarn::model& m) const {

    auto r(transform(fc, m));

    expand_enablement(drp, root_object, fc, r);
    expand_inclusion(drp, fc, l, r);
    expand_decoration(dcf, r);
    expand_aspects(drp, r);
    expand_helpers(drp, fc, r);

    return r;
}

} } } }
