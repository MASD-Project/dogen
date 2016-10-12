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
#include "dogen/annotations/types/type_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/io/formattables/odb_properties_io.hpp"
#include "dogen/quilt.cpp/types/formattables/odb_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("quilt.cpp.formattables.odb_expander"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::ostream& operator<<(std::ostream& s,
    const odb_expander::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "odb_expander::type_group\"" << ", "
      << "\"odb_pragma\": " << v.odb_pragma
      << " }";

    return s;
}

odb_expander::type_group odb_expander::
make_type_group(const annotations::type_repository& atrp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating field definitions.";

    type_group r;
    const annotations::type_repository_selector s(atrp);
    const auto& cc(formatters::odb::traits::odb_pragma());
    r.odb_pragma = s.select_type_by_name(cc);

    BOOST_LOG_SEV(lg, debug) << "Created field definitions. Result: " << r;
    return r;
}

std::list<std::string> odb_expander::make_odb_pragmas(
    const type_group& tg, const annotations::annotation& o) const {

    const annotations::type_selector s(o);
    if (!s.has_field(tg.odb_pragma))
        return std::list<std::string>();

    return s.get_text_collection_content(tg.odb_pragma);
}

boost::optional<odb_properties>
odb_expander::compute_odb_configuration(
    const type_group& tg, const yarn::object& o) const {

    odb_properties r;
    r.top_level_odb_pragmas(make_odb_pragmas(tg, o.annotation()));
    for (const auto& attr : o.local_attributes()) {
        const auto id(attr.name().id());
        const auto pragmas(make_odb_pragmas(tg, attr.annotation()));
        if (pragmas.empty())
            continue;

        r.attribute_level_odb_pragmas()[id] = pragmas;
    }

    const bool has_top_level_pragmas(!r.top_level_odb_pragmas().empty());
    const bool has_attribute_pragmas(!r.attribute_level_odb_pragmas().empty());
    const bool has_pragmas(has_top_level_pragmas || has_attribute_pragmas);
    if (has_pragmas)
        return r;

    return boost::optional<odb_properties>();
}

void odb_expander::
expand(const annotations::type_repository& atrp, model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started expanding odb configuration.";
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

        /*
         * We are only interested in yarn objects; all other
         * element types do not need helpers.
         */
        const auto ptr(dynamic_cast<const yarn::object*>(segment.get()));
        if (ptr == nullptr)
            continue;

        /*
         * We only need to generate the aspect configuration for
         * elements of the target model. However, we can't perform
         * this after reduction because the aspect configurations must
         * be build prior to reduction or else we will not get aspects
         * for referenced models.
         */
        if (ptr->generation_type() == yarn::generation_types::no_generation)
            continue;

        const auto& o(*ptr);
        auto& eprops(formattable.element_properties());
        eprops.odb_properties(compute_odb_configuration(tg, o));
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding odb configuration. ";
}

} } } }
