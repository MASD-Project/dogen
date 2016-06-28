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
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/io/variant_helper_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace io {

std::string variant_helper::family() const {
    static std::string r("SmartPointer");
    return r;
}

std::list<std::string> variant_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        traits::class_implementation_formatter_name()
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

bool variant_helper::
is_enabled(const assistant& /*a*/, const bool /*in_inheritance*/) const {
    return true;
}

void variant_helper::
format(assistant& a, const properties::helper_properties& hp) const {
    {
        const auto d(hp.current());
        const auto nt_qn(d.name_tree_qualified());
        const auto n_qn(d.name_qualified());
        auto snf(a.make_scoped_namespace_formatter(d.namespaces()));
a.stream() << std::endl;
a.stream() << "struct " << d.name_tree_identifiable() << "_visitor : public boost::static_visitor<> {" << std::endl;
a.stream() << "    " << d.name_tree_identifiable() << "_visitor(std::ostream& s) : stream_(s) {" << std::endl;
a.stream() << "        s << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << d.name_qualified() << "\\\"\" << \", \";" << std::endl;
a.stream() << "        s << \"\\\"data\\\": \";" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    ~" << d.name_tree_identifiable() << "_visitor() { stream_ << \" }\"; }" << std::endl;
        for (const auto& dd : hp.direct_descendants()) {
a.stream() << std::endl;
a.stream() << "    void operator()(const " << dd.name_qualified() << (dd.is_primitive() ? "" : "&") << " v) const {" << std::endl;
            if (dd.is_primitive()) {
a.stream() << "        stream_ << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << dd.name_qualified() << "\\\"\" << \", \";" << std::endl;
a.stream() << "        stream_ << \"\\\"value\\\": \";" << std::endl;
a.stream() << "        stream_ << " << a.streaming_for_type(dd, "v") << ";" << std::endl;
a.stream() << "        stream_ << \" }\";" << std::endl;
            } else
a.stream() << "        stream_ << " << a.streaming_for_type(dd, "v") << ";" << std::endl;
a.stream() << "    }" << std::endl;
        }
a.stream() << std::endl;
a.stream() << "private:" << std::endl;
a.stream() << "    std::ostream& stream_;" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
a.stream() << "inline std::ostream& operator<<(std::ostream& s, const " << d.name_tree_qualified() << "& v) {" << std::endl;
a.stream() << "    boost::apply_visitor(" << d.name_tree_identifiable() << "_visitor(s), v);" << std::endl;
a.stream() << "    return s;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
    }
a.stream() << std::endl;
}

void variant_helper_stitch(
    nested_type_formatting_assistant& a,
    const properties::nested_type_info& t) {

    {
        auto snf(a.make_scoped_namespace_formatter(t.namespaces()));
a.stream() << std::endl;
a.stream() << "struct " << t.complete_identifiable_name() << "_visitor : public boost::static_visitor<> {" << std::endl;
a.stream() << "    " << t.complete_identifiable_name() << "_visitor(std::ostream& s) : stream_(s) {" << std::endl;
a.stream() << "        s << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << t.name() << "\\\"\" << \", \";" << std::endl;
a.stream() << "        s << \"\\\"data\\\": \";" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    ~" << t.complete_identifiable_name() << "_visitor() { stream_ << \" }\"; }" << std::endl;
        for (const auto& c : t.children()) {
a.stream() << std::endl;
a.stream() << "    void operator()(const " << c.name() << (c.is_primitive() ? "" : "&") << " v) const {" << std::endl;
            if (c.is_primitive()) {
a.stream() << "        stream_ << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << c.name() << "\\\"\" << \", \";" << std::endl;
a.stream() << "        stream_ << \"\\\"value\\\": \";" << std::endl;
a.stream() << "        stream_ << " << a.streaming_for_type(c, "v") << ";" << std::endl;
a.stream() << "        stream_ << \" }\";" << std::endl;
            } else
a.stream() << "        stream_ << " << a.streaming_for_type(c, "v") << ";" << std::endl;
a.stream() << "    }" << std::endl;
        }
a.stream() << std::endl;
a.stream() << "private:" << std::endl;
a.stream() << "    std::ostream& stream_;" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
a.stream() << "inline std::ostream& operator<<(std::ostream& s, const " << t.complete_name() << "& v) {" << std::endl;
a.stream() << "    boost::apply_visitor(" << t.complete_identifiable_name() << "_visitor(s), v);" << std::endl;
a.stream() << "    return s;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
    }
a.stream() << std::endl;
}
} } } } }
