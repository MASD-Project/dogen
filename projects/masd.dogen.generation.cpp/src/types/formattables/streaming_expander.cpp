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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/unordered_map_io.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.variability/types/entry_selector.hpp"
#include "masd.dogen.variability/types/type_repository_selector.hpp"
#include "masd.dogen.variability/io/type_io.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.generation.cpp/io/formattables/streaming_properties_io.hpp"
#include "masd.dogen.generation.cpp/types/formattables/streaming_expander.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("generation.cpp.formattables.streaming_expander"));

}

namespace masd::dogen::generation::cpp::formattables {

std::ostream& operator<<(std::ostream& s,
    const streaming_expander::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"masd.dogen::generation::cpp::formattables::"
      << "streaming_expander::type_group\"" << ", "
      << "\"requires_quoting\": " << v.requires_quoting << ", "
      << "\"string_conversion_method\": " << v.string_conversion_method << ", "
      << "\"remove_unprintable_characters\": "
      << v.remove_unprintable_characters
      << " }";

    return s;
}

streaming_expander::type_group
streaming_expander::make_type_group(
    const variability::type_repository& atrp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating type group.";

    type_group r;

    const variability::type_repository_selector s(atrp);
    const auto scm(traits::cpp::streaming::string_conversion_method());
    r.string_conversion_method = s.select_type_by_name(scm);

    const auto rq(traits::cpp::streaming::requires_quoting());
    r.requires_quoting = s.select_type_by_name(rq);

    const auto ruc(traits::cpp::streaming::remove_unprintable_characters());
    r.remove_unprintable_characters = s.select_type_by_name(ruc);

    BOOST_LOG_SEV(lg, debug) << "Created type group. Result: " << r;

    return r;
}

boost::optional<streaming_properties>
streaming_expander::make_streaming_properties(
    const type_group& tg, const variability::annotation& a) const {

    BOOST_LOG_SEV(lg, debug) << "Creating streaming properties.";
    bool found_any(false);
    streaming_properties r;
    const variability::entry_selector s(a);

    const auto& rq(tg.requires_quoting);
    if (s.has_entry(rq)) {
        r.requires_quoting(s.get_boolean_content_or_default(rq));
        found_any = true;
    }

    const auto& scm(tg.string_conversion_method);
    if (s.has_entry(scm)) {
        r.string_conversion_method(s.get_text_content_or_default(scm));
        found_any = true;
    }

    const auto& ruc(tg.remove_unprintable_characters);
    if (s.has_entry(ruc)) {
        r.remove_unprintable_characters(s.get_boolean_content_or_default(ruc));
        found_any = true;
    }

    if (!found_any)
        return boost::optional<streaming_properties>();

    BOOST_LOG_SEV(lg, debug) << "Created streaming properties. "
                             << "Result: " << r;
    return r;
}

void streaming_expander::
expand(const variability::type_repository& atrp, model& fm) const {

    BOOST_LOG_SEV(lg, debug) << "Started expanding streaming properties.";
    const auto tg(make_type_group(atrp));
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);

        /*
         * We only want to process the master segment; the element
         * extensions can be ignored.
         */
        auto segment(formattable.master_segment());
        const auto& e(*segment);
        const auto sp(make_streaming_properties(tg, e.annotation()));
        if (!sp)
            continue;

        fm.streaming_properties()[id] = *sp;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding streaming properties. "
                             << "Result: "<< fm.streaming_properties();
}

}
