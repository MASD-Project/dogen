/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <ostream>
#include <sstream>
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_inserter_implementation.hpp"

namespace {

// FIXME: until we add support to indenter.
const std::string special_indent("  ");
const std::string parent("__parent_");
const std::string type("__type__");
const std::string inserter("<< ");
const std::string space_inserter(" << ");
const std::string open_bracket(" {");
const std::string close_bracket(" }");
const std::string colon(": ");
const std::string semi_colon(";");
const std::string space(" ");
const std::string underscore("_");
const std::string spaced_comma(", ");

const std::string invalid_sequence_container(
    "Sequence containers have exactly one type argument");
const std::string invalid_associative_container(
    "Associative containers have one or two type arguments");

std::string parent_tag(const unsigned int number) {
    std::ostringstream s;
    s << parent << number << underscore << underscore;
    return s.str();
}

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

cpp_inserter_implementation::
cpp_inserter_implementation(std::ostream& stream, cpp_indenter& indenter,
    const bool is_inside_class)
    : is_inside_class_(is_inside_class), stream_(stream), indenter_(indenter),
      utility_(stream_, indenter_) {
}

bool cpp_inserter_implementation::
is_insertable(const nested_type_view_model& vm) {
    return !vm.is_sequence_container() && !vm.is_associative_container();
}

void cpp_inserter_implementation::
sequence_container_helper(const nested_type_view_model& vm) {
    const auto children(vm.children());
    if (children.size() != 1)
        throw generation_failure(invalid_sequence_container);

    const auto container(vm);
    const auto containee(children.front());

    {
        namespace_helper ns_helper(stream_, container.namespaces());

        utility_.blank_line();
        stream_ << indenter_ << "inline std::ostream& operator<<"
                << "(std::ostream& s, const "
                << container.complete_name() << "& v) ";

        utility_.open_scope();
        {
            cpp_positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote("[ ") << ";" << std::endl;
            stream_ << indenter_
                    << "for (auto i(v.begin()); i != v.end(); ++i) ";
            utility_.open_scope();
            {
                cpp_positive_indenter_scope s(indenter_);
                stream_ << indenter_ << "if (i != v.begin()) s" << space_inserter
                        << utility_.quote(", ") << ";" << std::endl;

                if (containee.is_string_like()) {
                    stream_ << indenter_ << "s" << space_inserter
                            << utility_.quote_escaped_streamed("*i")
                            << ";" << std::endl;
                } else
                    stream_ << indenter_ << "s << *i;" << std::endl;
            }
            utility_.close_scope();
            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote("] ") << ";" << std::endl;
            stream_ << indenter_ << "return s;" << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void cpp_inserter_implementation::
associative_container_helper(const nested_type_view_model& vm) {
    const auto children(vm.children());
    if (children.size() != 1 && children.size() != 2)
        throw generation_failure(invalid_associative_container);

    if (children.size() == 1) {
        sequence_container_helper(vm);
        return;
    }

    const auto container(vm);
    {
        namespace_helper ns_helper(stream_, container.namespaces());

        utility_.blank_line();
        stream_ << indenter_ << "inline std::ostream& operator<<"
                << "(std::ostream& s, const "
                << container.complete_name() << "& v) ";

        utility_.open_scope();
        {
            cpp_positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote("[") << ";" << std::endl;
            stream_ << indenter_
                    << "for (auto i(v.begin()); i != v.end(); ++i) ";
            utility_.open_scope();
            {
                cpp_positive_indenter_scope s(indenter_);
                stream_ << indenter_ << "if (i != v.begin()) s" << space_inserter
                        << utility_.quote(", ") << ";" << std::endl;


                stream_ << indenter_ << "s" << space_inserter
                        << utility_.quote(" [ { ") << space_inserter
                        << utility_.quote(utility_.quote_escaped(type) + colon)
                        << space_inserter
                        << utility_.quote(utility_.quote_escaped("key"))
                        << space_inserter << utility_.quote(spaced_comma)
                        << space_inserter
                        << utility_.quote(utility_.quote_escaped("data") +
                            colon) << ";" << std::endl;

                const auto key(children.front());
                if (key.is_string_like()) {
                    stream_ << indenter_ << "s" << space_inserter
                            << utility_.quote_escaped_streamed("i->first")
                            << ";" << std::endl;
                } else
                    stream_ << indenter_ << "s << i->first;" << std::endl;

                stream_ << indenter_ << "s" << space_inserter
                        << utility_.quote(" }, { ") << space_inserter
                        << utility_.quote(utility_.quote_escaped(type) + colon)
                        << space_inserter
                        << utility_.quote(utility_.quote_escaped("value"))
                        << space_inserter << utility_.quote(spaced_comma)
                        << space_inserter
                        << utility_.quote(utility_.quote_escaped("data") +
                            colon) << ";" << std::endl;

                const auto value(children.back());
                if (value.is_string_like()) {
                    stream_ << indenter_ << "s" << space_inserter
                            << utility_.quote_escaped_streamed("i->first")
                            << ";" << std::endl;
                } else
                    stream_ << indenter_ << "s << i->first;" << std::endl;

                stream_ << indenter_ << "s" << space_inserter
                        << utility_.quote(" } ]") << ";"
                        << std::endl;
            }
            utility_.close_scope();
            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote(" ] ") << ";" << std::endl;
            stream_ << indenter_ << "return s;" << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void cpp_inserter_implementation::
recursive_helper_method_creator(const nested_type_view_model& vm,
    std::unordered_set<std::string>& types_done) {

    if (types_done.find(vm.complete_identifiable_name()) != types_done.end())
        return;

    const auto children(vm.children());
    for (const auto c : children)
        recursive_helper_method_creator(c, types_done);

    if (vm.is_sequence_container())
        sequence_container_helper(vm);
    else if (vm.is_associative_container())
        associative_container_helper(vm);

    types_done.insert(vm.complete_identifiable_name());
}

void cpp_inserter_implementation::
format_helper_methods(const class_view_model& vm) {
    const auto props(vm.properties());
    if (props.empty())
        return;

    std::unordered_set<std::string> types_done;
    for (const auto p : props)
        recursive_helper_method_creator(p.type(), types_done);
}

void cpp_inserter_implementation::
format_inserter_implementation(const class_view_model& vm) {
    if (vm.requires_stream_manipulators()) {
        stream_ << indenter_ << "boost::io::ios_flags_saver ifs(s);"
                << std::endl;
        stream_ << indenter_ << "s << std::boolalpha;"
                << std::endl;
        utility_.blank_line();
    }

    stream_ << indenter_ << "s " << inserter
            << utility_.quote(" { ")
            << std::endl;

    stream_ << indenter_ << special_indent << inserter
            << utility_.quote(utility_.quote_escaped(type) + colon)
            << space_inserter
            << utility_.quote(utility_.quote_escaped(vm.name()));

    unsigned int i(0);
    const auto parents(vm.parents());
    for (const auto p : parents) {
        if (i != 0)
            stream_ << indenter_ << "s";

        stream_ << space_inserter << utility_.quote(spaced_comma) << std::endl;

        stream_ << indenter_ << special_indent << inserter
                << utility_.quote(utility_.quote_escaped(parent_tag(i)) +
                    colon) << semi_colon << std::endl;

        stream_ << indenter_ << p.name() << "::to_stream(s);" << std::endl;
        ++i;
    }

    const auto props(vm.properties());
    if (!parents.empty())
        stream_ << indenter_ << "s";

    for (const auto p : props) {
        stream_ << space_inserter << utility_.quote(spaced_comma) << std::endl;

        stream_ << indenter_ << special_indent << inserter
                << utility_.quote(utility_.quote_escaped(p.name())
                    + colon) << space_inserter;

        std::ostringstream ss;
        if (is_inside_class_)
            ss << utility_.as_member_variable(p.name());
        else
            ss << "v." << utility_.as_getter(p.name());

        if (p.type().is_string_like())
            stream_ << utility_.quote_escaped_streamed(ss.str());
        else if (p.type().is_primitive())
            stream_ << ss.str();
        else
            stream_ << ss.str();
    }

    if (!props.empty()) {
        stream_ << std::endl
                << indenter_ << special_indent << inserter;
    } else
        stream_ << space_inserter;

    stream_ << utility_.quote(close_bracket) << semi_colon << std::endl;
    if (!is_inside_class_)
        stream_ << indenter_ << "return(s);" << std::endl;
}


} } } } }
