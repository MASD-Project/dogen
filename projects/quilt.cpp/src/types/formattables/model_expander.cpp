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
#include "dogen/quilt.cpp/types/formattables/streaming_configuration_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/profile_group_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/enablement_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/canonical_formatter_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/decoration_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/aspect_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/reducer.hpp"
#include "dogen/quilt.cpp/types/formattables/file_path_and_guard_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/odb_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/facet_directory_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/model_expander.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

void model_expander::expand_streaming_configuration(
    const dynamic::repository& drp, model& fm) const {
    streaming_configuration_expander ex;
    ex.expand(drp, fm);
}

void model_expander::expand_profile_groups(
    const std::forward_list<boost::filesystem::path>& dirs,
    const dynamic::repository& drp, const dynamic::object& root_object,
    const formatters::container& fc, model& fm) const {
    profile_group_expander ex;
    ex.expand(dirs, drp, root_object, fc, fm);
}

void model_expander::expand_enablement(const dynamic::repository& drp,
    const dynamic::object& root_object, const formatters::container& fc,
    model& fm) const {
    enablement_expander ex;
    ex.expand(drp, root_object, fc, fm);
}

void model_expander::
expand_canonical_formatters(const formatters::container& fc, model& fm) const {
    canonical_formatter_expander ex;
    ex.expand(fc, fm);
}

void model_expander::expand_inclusion(
    const dynamic::repository& drp, const formatters::container& fc,
    const locator& l, model& fm) const {
    inclusion_expander ex;
    ex.expand(drp, fc, l, fm);
}

void model_expander::expand_decoration(
    const dogen::formatters::decoration_configuration_factory& dcf,
    model& fm) const {
    decoration_expander ex;
    ex.expand(dcf, fm);
}

void model_expander::expand_aspects(const dynamic::repository& drp,
    model& fm) const {
    aspect_expander ex;
    ex.expand(drp, fm);
}

void model_expander::expand_helpers(const dynamic::repository& drp,
    const formatters::container& fc, model& fm) const {
    helper_expander ex;
    ex.expand(drp, fc, fm);
}

void model_expander::reduce(model& fm) const {
    reducer rd;
    rd.reduce(fm);
}

void model_expander::expand_file_paths_and_guards(
    const formatters::container& fc, const locator& l, model& fm) const {
    file_path_and_guard_expander ex;
    ex.expand(fc, l, fm);
}

void model_expander::
expand_odb_configuration(const dynamic::repository& drp, model& fm) const {
    odb_expander ex;
    ex.expand(drp, fm);
}

void model_expander::
expand_facet_directories(const locator& l,model& fm) const {
    facet_directory_expander ex;
    ex.expand(l, fm);
}

void model_expander::expand(
    const std::forward_list<boost::filesystem::path>& dirs,
    const dynamic::repository& drp, const dynamic::object& root_object,
    const dogen::formatters::decoration_configuration_factory& dcf,
    const formatters::container& fc, const locator& l, model& fm) const {

    expand_streaming_configuration(drp, fm);
    expand_profile_groups(dirs, drp, root_object, fc, fm);
    expand_enablement(drp, root_object, fc, fm);
    expand_canonical_formatters(fc, fm);
    expand_inclusion(drp, fc, l, fm);
    expand_decoration(dcf, fm);
    expand_aspects(drp, fm);
    expand_helpers(drp, fc, fm);

    reduce(fm);

    expand_file_paths_and_guards(fc, l, fm);
    expand_odb_configuration(drp, fm);
    expand_facet_directories(l, fm);
}

} } } }
