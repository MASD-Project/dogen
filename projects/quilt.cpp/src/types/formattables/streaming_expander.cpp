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
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/annotations/types/field_selector.hpp"
#include "dogen/annotations/types/repository_selector.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.cpp/io/formattables/streaming_properties_io.hpp"
#include "dogen/quilt.cpp/types/formattables/streaming_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("quilt.cpp.formattables.streaming_expander"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::ostream& operator<<(std::ostream& s,
    const streaming_expander::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
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
    const annotations::type_repository& atrp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating field definitions.";

    type_group r;

    const annotations::repository_selector s(atrp);
    const auto scm(traits::cpp::streaming::string_conversion_method());
    r.string_conversion_method = s.select_field_by_name(scm);

    const auto rq(traits::cpp::streaming::requires_quoting());
    r.requires_quoting = s.select_field_by_name(rq);

    const auto ruc(traits::cpp::streaming::remove_unprintable_characters());
    r.remove_unprintable_characters = s.select_field_by_name(ruc);

    BOOST_LOG_SEV(lg, debug) << "Created field definitions. Result: " << r;

    return r;
}

boost::optional<streaming_properties>
streaming_expander::make_streaming_properties(
    const type_group& tg, const annotations::annotation& a) const {

    BOOST_LOG_SEV(lg, debug) << "Creating streaming configuration.";
    bool found_any(false);
    streaming_properties r;
    const annotations::field_selector fs(a);

    const auto& rq(tg.requires_quoting);
    if (fs.has_field(rq)) {
        r.requires_quoting(fs.get_boolean_content_or_default(rq));
        found_any = true;
    }

    const auto& scm(tg.string_conversion_method);
    if (fs.has_field(scm)) {
        r.string_conversion_method(fs.get_text_content_or_default(scm));
        found_any = true;
    }

    const auto& ruc(tg.remove_unprintable_characters);
    if (fs.has_field(ruc)) {
        r.remove_unprintable_characters(fs.get_boolean_content_or_default(ruc));
        found_any = true;
    }

    if (!found_any)
        return boost::optional<streaming_properties>();

    BOOST_LOG_SEV(lg, debug) << "Created streaming configuration. "
                             << "Result: " << r;
    return r;
}

void streaming_expander::
expand(const annotations::type_repository& atrp, model& fm) const {

    BOOST_LOG_SEV(lg, debug) << "Started expanding streaming configuration.";
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
        const auto sc(make_streaming_properties(tg, e.annotation()));
        if (!sc)
            continue;

        fm.streaming_properties()[id] = *sc;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding streaming configuration. "
                             << "Result: "<< fm.streaming_properties();
}

} } } }
