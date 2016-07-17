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
#include "dogen/quilt.cpp/types/properties/helper_properties.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/variant_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace hash {


std::string variant_helper::id() const {
    static auto r(std::string("<") + traits::facet_name() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string variant_helper::family() const {
    static std::string r("AssociativeContainer");
    return r;
}

std::list<std::string>
variant_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        hash::traits::class_implementation_formatter_name()
    });
    return r;
}

std::list<std::string>
variant_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        hash::traits::facet_name()
    });
    return r;
}

bool variant_helper::requires_explicit_call() const {
    return false;
}

std::string variant_helper::function_name() const {
    static std::string r("operator==");
    return r;
}

std::string variant_helper::helper_name() const {
    static std::string r("variant_helper");
    return r;
}

bool variant_helper::is_enabled(const assistant& /*a*/,
    const properties::helper_properties& /*hp*/) const {
    return true;
}

void variant_helper::
format(assistant& a, const properties::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());
    const auto key(hp.direct_descendants().front());
    const auto value(hp.direct_descendants().back());
a.stream() << std::endl;
a.stream() << "struct " << ident << "_visitor : public boost::static_visitor<> {" << std::endl;
a.stream() << "    " << ident << "_visitor() : hash(0) {}" << std::endl;
    for (const auto& dd : hp.direct_descendants()) {
a.stream() << "    void operator()(const " << dd.name_qualified() << (dd.is_primitive() ? "" : "&") << " v) const {" << std::endl;
        if (!dd.requires_hashing_helper())
a.stream() << "        combine(hash, v);" << std::endl;
        else
a.stream() << "        combine(hash, hash_" << dd.name_tree_identifiable() << "(v));" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
    }
a.stream() << "    mutable std::size_t hash;" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
a.stream() << "inline std::size_t hash_" << ident << "(const " << qn << "& v) {" << std::endl;
a.stream() << "    " << ident << "_visitor vis;" << std::endl;
a.stream() << "    boost::apply_visitor(vis, v);" << std::endl;
a.stream() << "    return vis.hash;" << std::endl;
a.stream() << "}" << std::endl;
}

void variant_helper_stitch(
    nested_type_formatting_assistant& a,
    const properties::nested_type_info& t) {
a.stream() << std::endl;
a.stream() << "struct " << t.complete_identifiable_name() << "_visitor : public boost::static_visitor<> {" << std::endl;
a.stream() << "    " << t.complete_identifiable_name() << "_visitor() : hash(0) {}" << std::endl;
    const auto children(t.children());
    for (const auto& c : children) {
a.stream() << "    void operator()(const " << c.name() << (c.is_primitive() ? "" : "&") << " v) const {" << std::endl;
        if (!a.requires_hashing_helper_method(c))
a.stream() << "        combine(hash, v);" << std::endl;
        else
a.stream() << "        combine(hash, hash_" << c.complete_identifiable_name() << "(v));" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
    }
a.stream() << "    mutable std::size_t hash;" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
a.stream() << "inline std::size_t hash_" << t.complete_identifiable_name() << "(const " << t.complete_name() << "& v) {" << std::endl;
a.stream() << "    " << t.complete_identifiable_name() << "_visitor vis;" << std::endl;
a.stream() << "    boost::apply_visitor(vis, v);" << std::endl;
a.stream() << "    return vis.hash;" << std::endl;
a.stream() << "}" << std::endl;
}
} } } } }
