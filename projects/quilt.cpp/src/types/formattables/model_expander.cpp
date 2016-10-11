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
#include "dogen/quilt.cpp/types/formattables/streaming_expander.hpp"
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

void model_expander::
expand_streaming(const annotations::repository& arp, model& fm) const {
    streaming_expander ex;
    ex.expand(arp, fm);
}

void model_expander::expand_profile_groups(
    const std::forward_list<boost::filesystem::path>& dirs,
    const annotations::repository& arp, const annotations::annotation& root,
    const formatters::container& fc, model& fm) const {
    profile_group_expander ex;
    ex.expand(dirs, arp, root, fc, fm);
}

void model_expander::expand_enablement(const annotations::repository& arp,
    const annotations::annotation& root_object, const formatters::container& fc,
    model& fm) const {
    enablement_expander ex;
    ex.expand(arp, root_object, fc, fm);
}

void model_expander::
expand_canonical_formatters(const formatters::container& fc, model& fm) const {
    canonical_formatter_expander ex;
    ex.expand(fc, fm);
}

void model_expander::expand_inclusion(
    const annotations::repository& arp, const formatters::container& fc,
    const locator& l, model& fm) const {
    inclusion_expander ex;
    ex.expand(arp, fc, l, fm);
}

void model_expander::expand_decoration(
    const dogen::formatters::decoration_properties_factory& dpf,
    model& fm) const {
    decoration_expander ex;
    ex.expand(dpf, fm);
}

void model_expander::expand_aspects(const annotations::repository& arp,
    model& fm) const {
    aspect_expander ex;
    ex.expand(arp, fm);
}

void model_expander::expand_helpers(const annotations::repository& arp,
    const formatters::container& fc, model& fm) const {
    helper_expander ex;
    ex.expand(arp, fc, fm);
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
expand_odb(const annotations::repository& arp, model& fm) const {
    odb_expander ex;
    ex.expand(arp, fm);
}

void model_expander::
expand_facet_directories(const locator& l,model& fm) const {
    facet_directory_expander ex;
    ex.expand(l, fm);
}

void model_expander::expand(
    const std::forward_list<boost::filesystem::path>& dirs,
    const annotations::repository& arp, const annotations::annotation& root,
    const dogen::formatters::decoration_properties_factory& dpf,
    const formatters::container& fc, const locator& l, model& fm) const {

    /*
     * Streaming expansion must be done before helper expansion as the
     * helpers need the streaminging properties.
     */
    expand_streaming(arp, fm);
    expand_profile_groups(dirs, arp, root, fc, fm);

    /*
     * Enablement expansion must be done before inclusion because
     * inclusion relies on it to know which formatters are enabled.
     */
    expand_enablement(arp, root, fc, fm);

    /*
     * Canonical formatter expansion must be done before inclusion
     * because we use the canonical formatter notation to find
     * inclusion directives.
     */
    expand_canonical_formatters(fc, fm);
    expand_inclusion(arp, fc, l, fm);
    expand_decoration(dpf, fm);
    expand_aspects(arp, fm);
    expand_helpers(arp, fc, fm);

    /*
     * All of the above expansions must be performed prior to
     * reduction because we require types from external models.
     */
    reduce(fm);

    expand_file_paths_and_guards(fc, l, fm);
    expand_odb(arp, fm);
    expand_facet_directories(l, fm);
}

} } } }
