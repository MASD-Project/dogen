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
#include <sstream>
#include "dogen.utility/types/formatters/utility_formatter.hpp"
#include "dogen.text/types/transforms/helper_transform.hpp"

namespace dogen::text::transforms {

using identification::entities::physical_meta_id;
using identification::entities::logical_meta_physical_id;

helper_transform::~helper_transform() noexcept {}

formatters::scoped_namespace_formatter helper_transform::
make_scoped_namespace_formatter(std::ostream& os,
    const logical::entities::model& m, const std::list<std::string>& ns) const {
    const auto ts(m.output_technical_spaces().front());
    const auto tsv(m.technical_space_version());
    using identification::entities::technical_space;
    using identification::entities::technical_space_version;
    const bool use_nesting(ts == technical_space::csharp ||
        (ts == technical_space::cpp && tsv == technical_space_version::cpp_17));
    return formatters::scoped_namespace_formatter(
        os, ts, ns, true/*add_new_line*/, use_nesting);
}

std::string helper_transform::
streaming_for_type(const logical::entities::streaming_properties& sp,
    const std::string& s) const {
    std::ostringstream stream;
    utility::formatters::utility_formatter uf(stream);
    if (sp.remove_unprintable_characters())
        uf.insert_streamed("tidy_up_string(" + s + ")");
    else if (!sp.string_conversion_method().empty()) {
        // FIXME: hack to determine if we are being dereferenced.
        std::string s1(s);
        const auto i(s1.find('*'));
        if (i != std::string::npos)
            s1 = "(" + s + ")";
        uf.insert_streamed(s1 + "." + sp.string_conversion_method());
    } else if (sp.requires_quoting())
        uf.insert_streamed(s);
    else
        uf.insert(s);

    return stream.str();
}

std::string
helper_transform::streaming_for_type(const logical::entities::model& m,
    const identification::entities::logical_name& n,
    const std::string& s) const {
    const auto str_propss(m.streaming_properties());
    const auto i(str_propss.find(n.id()));
    if (i == str_propss.end())
        return s;

    return streaming_for_type(i->second, s);
}

std::string helper_transform::
streaming_for_type(const logical::entities::helper_descriptor& hd,
    const std::string& s) const {

    const auto sp(hd.streaming_properties());
    if (!sp)
        return s;

    return streaming_for_type(*sp, s);
}

bool helper_transform::is_streaming_enabled(const physical::entities::model& m,
    const logical::entities::element& e,
    const physical::entities::artefact& a,
    const logical::entities::helper_properties& hp) const {

    /*
     * If the IO facet is globally disabled, we don't need streaming.
     */
    const auto& mmp(m.meta_model_properties());
    const auto& eafe(mmp.enabled_archetype_for_element());
    const physical_meta_id pmid("masd.cpp.io.canonical_archetype");
    const logical_meta_physical_id ea(e.name().id(), pmid);
    const auto i(eafe.find(ea));
    bool is_io_enabled(i != eafe.end());
    if (!is_io_enabled)
        return false;

    /*
     * If we are in the IO facet, and we are not in an inheritance
     * relationship we need streaming.
     */
    const auto is_io(a.meta_name().location().facet() == "io");
    if (is_io && !hp.in_inheritance_relationship())
        return true;

    /*
     * If we are in the types class implementation and we are in an
     * inheritance relationship, we'll need streaming.
     */
    bool in_types_class_implementation(a.meta_name().id() ==
        physical_meta_id("masd.cpp.types.class_implementation"));
    return in_types_class_implementation && hp.in_inheritance_relationship();
}

bool helper_transform::operator==(const helper_transform& /*rhs*/) const {
    return true;
}

}
