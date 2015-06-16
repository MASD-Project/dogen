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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/cpp_formatters/types/qname.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp"
#include "dogen/cpp_formatters/types/inserter_implementation.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("cpp_formatters.inserter_implementation"));

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
const std::string invalid_optional_type(
    "Optional types have exactly one type argument");
const std::string invalid_associative_container(
    "Associative containers have one or two type arguments");
const std::string invalid_smart_pointer(
    "Smart pointers have exactly one type argument");
const std::string invalid_variant("Variants should have at least one type");
const std::string invalid_pair_type(
    "Pair types have exactly two type arguments");
const std::string invalid_ptree("Ptree's should have no type arguments");

std::string parent_tag(const unsigned int number) {
    std::ostringstream s;
    s << parent << number << underscore << underscore;
    return s.str();
}

}

namespace dogen {
namespace cpp_formatters {

inserter_implementation::
inserter_implementation(std::ostream& stream, indenter& indenter,
    const bool is_inside_class)
    : is_inside_class_(is_inside_class), stream_(stream), indenter_(indenter),
      utility_(stream_, indenter_) {
}

void inserter_implementation::
sequence_container_helper(const cpp::formattables::nested_type_info& nti) {
    const auto children(nti.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << invalid_sequence_container;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_sequence_container));
    }

    const auto container(nti);
    const auto containee(children.front());

    {
        using dogen::formatters::cpp::scoped_namespace_formatter;
        scoped_namespace_formatter nsh(stream_, container.namespaces());

        utility_.blank_line();
        stream_ << indenter_ << "inline std::ostream& operator<<"
                << "(std::ostream& s, const "
                << container.complete_name() << "& v) ";

        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote("[ ") << ";" << std::endl;
            stream_ << indenter_
                    << "for (auto i(v.begin()); i != v.end(); ++i) ";
            utility_.open_scope();
            {
                positive_indenter_scope s(indenter_);
                stream_ << indenter_ << "if (i != v.begin()) s"
                        << space_inserter << utility_.quote(", ")
                        << ";" << std::endl;

                if (containee.is_date() || containee.is_ptime() ||
                    containee.is_time_duration()) {
                    stream_ << indenter_ << "s" << space_inserter
                            << utility_.quote_escaped_streamed("*i")
                            << ";" << std::endl;
                } else if (containee.is_string_like()) {
                    const std::string tus(nti.is_char_like() ? "*i" :
                        "tidy_up_string(*i)");
                    stream_ << indenter_ << "s" << space_inserter
                            << utility_.quote_escaped_streamed(tus)
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

void inserter_implementation::
associative_container_helper(const cpp::formattables::nested_type_info& nti) {
    const auto children(nti.children());
    if (children.size() != 1 && children.size() != 2) {
        BOOST_LOG_SEV(lg, error) << invalid_associative_container;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_associative_container));
    }

    if (children.size() == 1) {
        sequence_container_helper(nti);
        return;
    }

    const auto container(nti);
    {
        using dogen::formatters::cpp::scoped_namespace_formatter;
        scoped_namespace_formatter nsh(stream_, container.namespaces());

        utility_.blank_line();
        stream_ << indenter_ << "inline std::ostream& operator<<"
                << "(std::ostream& s, const "
                << container.complete_name() << "& v) ";

        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote("[") << ";" << std::endl;
            stream_ << indenter_
                    << "for (auto i(v.begin()); i != v.end(); ++i) ";
            utility_.open_scope();
            {
                positive_indenter_scope s(indenter_);
                stream_ << indenter_ << "if (i != v.begin()) s"
                        << space_inserter << utility_.quote(", ") << ";"
                        << std::endl;

                stream_ << indenter_ << "s" << space_inserter
                        << utility_.quote("[ { ") << space_inserter
                        << utility_.quote(utility_.quote_escaped(type) + colon)
                        << space_inserter
                        << utility_.quote(utility_.quote_escaped("key"))
                        << space_inserter << utility_.quote(spaced_comma)
                        << space_inserter
                        << utility_.quote(utility_.quote_escaped("data") +
                            colon) << ";" << std::endl;

                const auto key(children.front());
                if (key.is_date() || key.is_ptime() || key.is_time_duration()) {
                    stream_ << indenter_ << "s" << space_inserter
                            << utility_.quote_escaped_streamed("i->first")
                            << ";" << std::endl;
                } else if (key.is_string_like()) {
                    const std::string tus(nti.is_char_like() ? "i->first" :
                        "tidy_up_string(i->first)");
                    stream_ << indenter_ << "s" << space_inserter
                            << utility_.quote_escaped_streamed(tus)
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
                if (value.is_date() || value.is_ptime() ||
                    value.is_time_duration()) {
                    stream_ << indenter_ << "s" << space_inserter
                            << utility_.quote_escaped_streamed("i->second")
                            << ";" << std::endl;
                } else if (value.is_string_like()) {
                    const std::string tus(nti.is_char_like() ? "i->second" :
                        "tidy_up_string(i->second)");
                    stream_ << indenter_ << "s" << space_inserter
                            << utility_.quote_escaped_streamed(tus)
                            << ";" << std::endl;
                } else
                    stream_ << indenter_ << "s << i->second;" << std::endl;

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

void inserter_implementation::
smart_pointer_helper(const cpp::formattables::nested_type_info& nti) {
    const auto children(nti.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << invalid_smart_pointer;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_smart_pointer));
    }

    const auto container(nti);
    {
        using dogen::formatters::cpp::scoped_namespace_formatter;
        scoped_namespace_formatter nsh(stream_, container.namespaces());

        utility_.blank_line();
        stream_ << indenter_ << "inline std::ostream& operator<<"
                << "(std::ostream& s, const "
                << container.complete_name() << "& v) ";

        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote("{ ") << space_inserter
                    << utility_.quote(utility_.quote_escaped(type) + colon)
                    << space_inserter
                    << utility_.quote(utility_.quote_escaped(nti.name()))
                    << space_inserter << utility_.quote(spaced_comma)
                    << std::endl;

            stream_ << indenter_ << special_indent << inserter
                    << utility_.quote(utility_.quote_escaped("memory") +
                        colon)
                    << space_inserter
                    << utility_.quote_escaped_streamed(
                        "static_cast<void*>(v.get())")
                    << space_inserter << utility_.quote(spaced_comma) << ";"
                    << std::endl;

            utility_.blank_line();
            stream_ << indenter_ << "if (v)" << std::endl;
            {
                positive_indenter_scope s(indenter_);
                const auto containee(children.front());
                stream_ << indenter_ << "s" << space_inserter
                        << utility_.quote(utility_.quote_escaped("data") +
                            colon);
                if (containee.is_string_like()) {
                    const std::string tus(nti.is_char_like() ? "*v" :
                        "tidy_up_string(*v)");

                    stream_ << space_inserter
                            << utility_.quote_escaped_streamed(tus)
                            << ";" << std::endl;
                } else
                    stream_ << space_inserter << "*v;" << std::endl;
            }
            stream_ << indenter_ << "else" << std::endl;
            {
                positive_indenter_scope s(indenter_);

                stream_ << indenter_ << "s" << space_inserter
                        << utility_.quote(utility_.quote_escaped("data") +
                            colon)
                        << utility_.quote(utility_.quote_escaped("<empty>"))
                        << ";" << std::endl;
            }
            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote(" }")
                    << ";";
            utility_.blank_line();
            stream_ << indenter_ << "return s;" << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void inserter_implementation::
optional_helper(const cpp::formattables::nested_type_info& nti) {
    const auto children(nti.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << invalid_optional_type;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_optional_type));
    }

    const auto container(nti);
    {
        using dogen::formatters::cpp::scoped_namespace_formatter;
        scoped_namespace_formatter nsh(stream_, container.namespaces());

        utility_.blank_line();
        stream_ << indenter_ << "inline std::ostream& operator<<"
                << "(std::ostream& s, const "
                << container.complete_name() << "& v) ";

        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote("{ ") << space_inserter
                    << utility_.quote(utility_.quote_escaped(type) + colon)
                    << space_inserter
                    << utility_.quote(utility_.quote_escaped(nti.name()))
                    << space_inserter << utility_.quote(spaced_comma)
                    << ";"
                    << std::endl;

            utility_.blank_line();
            stream_ << indenter_ << "if (v)" << std::endl;
            {
                positive_indenter_scope s(indenter_);
                const auto containee(children.front());
                stream_ << indenter_ << "s" << space_inserter
                        << utility_.quote(utility_.quote_escaped("data") +
                            colon);

                if (containee.is_string_like()) {
                    const std::string tus(nti.is_char_like() ? "*v" :
                        "tidy_up_string(*v)");

                    stream_ << space_inserter
                            << utility_.quote_escaped_streamed(tus)
                            << ";" << std::endl;
                } else
                    stream_ << space_inserter << "*v;" << std::endl;
            }
            stream_ << indenter_ << "else" << std::endl;
            {
                positive_indenter_scope s(indenter_);

                stream_ << indenter_ << "s" << space_inserter
                        << utility_.quote(utility_.quote_escaped("data") +
                            colon)
                        << utility_.quote(utility_.quote_escaped("<empty>"))
                        << ";" << std::endl;
            }
            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote(" }")
                    << ";";
            utility_.blank_line();
            stream_ << indenter_ << "return s;" << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void inserter_implementation::
pair_helper(const cpp::formattables::nested_type_info& nti) {
    const auto children(nti.children());
    if (children.size() != 2) {
        BOOST_LOG_SEV(lg, error) << invalid_pair_type;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_pair_type));
    }

    const auto container(nti);
    {
        using dogen::formatters::cpp::scoped_namespace_formatter;
        scoped_namespace_formatter nsh(stream_, container.namespaces());

        utility_.blank_line();
        stream_ << indenter_ << "inline std::ostream& operator<<"
                << "(std::ostream& s, const "
                << container.complete_name() << "& v) ";

        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote("{ ") << space_inserter
                    << utility_.quote(utility_.quote_escaped(type) + colon)
                    << space_inserter
                    << utility_.quote(utility_.quote_escaped(nti.name()))
                    << space_inserter << utility_.quote(spaced_comma)
                    << ";"
                    << std::endl;

            utility_.blank_line();
            const auto first(children.front());
            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote(utility_.quote_escaped("first") + colon);

            if (first.is_string_like()) {
                const std::string tus(nti.is_char_like() ? "v.first" :
                    "tidy_up_string(v.first)");

                stream_ << space_inserter
                        << utility_.quote_escaped_streamed(tus)
                        << space_inserter << utility_.quote(spaced_comma)
                        << ";" << std::endl;
            } else
                stream_ << space_inserter << "v.first"
                        << space_inserter << utility_.quote(spaced_comma) << ";"
                        << std::endl;

            const auto second(children.back());
            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote(utility_.quote_escaped("second") + colon);

            if (second.is_string_like()) {
                const std::string tus(nti.is_char_like() ? "v.second" :
                    "tidy_up_string(v.second)");

                stream_ << space_inserter
                        << utility_.quote_escaped_streamed(tus)
                        << ";" << std::endl;
            } else
                stream_ << space_inserter << "v.second;" << std::endl;

            stream_ << indenter_ << "s" << space_inserter
                    << utility_.quote(" }")
                    << ";";
            utility_.blank_line();
            stream_ << indenter_ << "return s;" << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void inserter_implementation::
variant_helper(const cpp::formattables::nested_type_info& nti) {
    const auto children(nti.children());
    if (children.empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_variant;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_variant));
    }

    const auto container(nti);
    {
        using dogen::formatters::cpp::scoped_namespace_formatter;
        scoped_namespace_formatter nsh(stream_, container.namespaces());

        utility_.blank_line();
        stream_ << indenter_
                << "struct " << nti.complete_identifiable_name()
                << "_visitor : public boost::static_visitor<> ";

        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << nti.complete_identifiable_name()
                    << "_visitor(std::ostream& s) : stream_(s) ";
            utility_.open_scope();
            {
                positive_indenter_scope s(indenter_);
                stream_ << indenter_ << "s" << space_inserter
                        << utility_.quote("{ ") << space_inserter
                        << utility_.quote(utility_.quote_escaped(type) + colon)
                        << space_inserter
                        << utility_.quote(utility_.quote_escaped(nti.name()))
                        << space_inserter << utility_.quote(spaced_comma)
                        << ";"
                        << std::endl;

                stream_ << indenter_ << "s" << space_inserter
                        << utility_.quote(utility_.quote_escaped("data") +
                            colon) << ";" << std::endl;
            }
            utility_.close_scope();
            utility_.blank_line();

            stream_ << indenter_ << "~" << nti.complete_identifiable_name()
                    << "_visitor() { stream_" << space_inserter
                    << utility_.quote(" }") << "; }" << std::endl;
            utility_.blank_line();

            for (const auto& c : children) {
                stream_ << indenter_
                        << "void operator()(const " << c.name()
                        << (c.is_primitive() ? "" : "&")
                        << " v) const ";

                utility_.open_scope();
                {
                    positive_indenter_scope s(indenter_);
                    if (c.is_primitive()) {
                        stream_ << indenter_ << "stream_" << space_inserter
                                << utility_.quote("{ ") << space_inserter
                                << utility_.quote(utility_.quote_escaped(type) +
                                    colon)
                                << space_inserter
                                << utility_.quote(utility_.quote_escaped(
                                        c.name()))
                                << space_inserter << utility_.quote(
                                    spaced_comma)
                                << ";" << std::endl;

                        stream_ << indenter_ << "stream_" << space_inserter
                                << utility_.quote(utility_.quote_escaped("value")
                                    + colon)
                                << ";"
                                << std::endl;

                        stream_ << indenter_ << "stream_" << space_inserter
                                << "v;" << std::endl;

                        stream_ << indenter_ << "stream_" << space_inserter
                                << utility_.quote(" }") << ";"
                                << std::endl;
                    } else if (c.is_string_like() || c.is_char_like()) {
                        const std::string tus(c.is_char_like() ? "v" :
                            "tidy_up_string(v)");

                        stream_ << indenter_ << "stream_" << space_inserter
                                << utility_.quote_escaped_streamed(tus) << ";"
                                << std::endl;
                    } else
                        stream_ << indenter_ << "stream_ << v;" << std::endl;
                }
                utility_.close_scope();
                utility_.blank_line();
            }
            utility_.private_access_specifier();
            stream_ << indenter_ << "std::ostream& stream_;" << std::endl;
        }
        stream_ << indenter_ << "};" << std::endl;

        utility_.blank_line();
        stream_ << indenter_ << "inline std::ostream& operator<<"
                << "(std::ostream& s, const "
                << container.complete_name() << "& v) ";

        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_
                    << "boost::apply_visitor("
                    << nti.complete_identifiable_name()
                    << "_visitor(s), v);" << std::endl;
            stream_ << indenter_ << "return s;" << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void inserter_implementation::ptree_helper(
    const cpp::formattables::nested_type_info& nti) {
    const auto children(nti.children());
    if (!children.empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_ptree;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_ptree));
    }

    {
        using dogen::formatters::cpp::scoped_namespace_formatter;
        scoped_namespace_formatter nsh(stream_, nti.namespaces());

        utility_.blank_line();
        stream_ << indenter_ << "inline std::ostream& operator<<"
                << "(std::ostream& s, const "
                << nti.complete_name() << "& v) ";

        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "std::ostringstream ss;" << std::endl
                    << indenter_ << "boost::property_tree::write_json(ss, v);"
                    << std::endl << std::endl
                    << indenter_ << "std::string content(ss.str());"
                    << std::endl
                    << indenter_
                    << "boost::replace_all(content, \"\\r\\n\", \"\");"
                    << std::endl
                    << indenter_
                    << "boost::replace_all(content, \"\\n\", \"\");"
                    << std::endl << std::endl
                    << indenter_ << "s << content;" << std::endl
                    << indenter_ << "return s;" << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
    }
    utility_.blank_line(2);
}

void inserter_implementation::
tidy_up_string_method() {
    stream_ << indenter_ << "inline std::string tidy_up_string"
            << "(std::string s) ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_
                << "boost::replace_all(s, \"\\r\\n\", \"<new_line>\");"
                << std::endl
                << indenter_
                << "boost::replace_all(s, \"\\n\", \"<new_line>\");"
                << std::endl
                << indenter_
                << "boost::replace_all(s, \"\\\"\", \"<quote>\");"
                << std::endl
                << indenter_ << "return s;"
                << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void inserter_implementation::
recursive_helper_method_creator(const cpp::formattables::nested_type_info& nti,
    std::unordered_set<std::string>& types_done) {

    if (types_done.find(nti.complete_identifiable_name()) != types_done.end())
        return;

    const auto children(nti.children());
    for (const auto c : children)
        recursive_helper_method_creator(c, types_done);

    if (nti.is_sequence_container())
        sequence_container_helper(nti);
    else if (nti.is_associative_container())
        associative_container_helper(nti);
    else if (nti.is_smart_pointer())
        smart_pointer_helper(nti);
    else if (nti.is_optional_like())
        optional_helper(nti);
    else if (nti.is_pair())
        pair_helper(nti);
    else if (nti.is_variant_like())
        variant_helper(nti);
    else if (nti.is_ptree())
        ptree_helper(nti);
    else if (nti.is_string_like() && !nti.is_char_like())
        tidy_up_string_method();

    types_done.insert(nti.complete_identifiable_name());
}

void inserter_implementation::
format_helper_methods(const cpp::formattables::class_info& ci) {
    const auto props(ci.properties());
    if (props.empty())
        return;

    std::unordered_set<std::string> types_done;
    for (const auto p : props)
        recursive_helper_method_creator(p.type(), types_done);
}

void inserter_implementation::
format_inserter_implementation(const cpp::formattables::class_info& ci) {
    if (ci.requires_stream_manipulators()) {
        stream_ << indenter_ << "boost::io::ios_flags_saver ifs(s);"
                << std::endl
                << indenter_ << "s.setf(std::ios_base::boolalpha);"
                << std::endl
                << indenter_ << "s.setf(std::ios::fixed, std::ios::floatfield);"
                << std::endl
                << indenter_ << "s.precision(6);"
                << std::endl
                << indenter_ << "s.setf(std::ios::showpoint);"
                << std::endl;
        utility_.blank_line();
    }

    stream_ << indenter_ << "s " << inserter
            << utility_.quote(" { ")
            << std::endl;

    std::ostringstream ss;
    qname qname(ss);
    qname.format(ci);

    stream_ << indenter_ << special_indent << inserter
            << utility_.quote(utility_.quote_escaped(type) + colon)
            << space_inserter
            << utility_.quote(utility_.quote_escaped(ss.str()));

    unsigned int i(0);
    const auto parents(ci.parents());
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

    const auto props(ci.properties());
    if (!parents.empty())
        stream_ << indenter_ << "s";

    for (const auto p : props) {
        stream_ << space_inserter << utility_.quote(spaced_comma) << std::endl;

        stream_ << indenter_ << special_indent << inserter
                << utility_.quote(utility_.quote_escaped(p.name())
                    + colon) << space_inserter;

        std::ostringstream ss;
        if (p.type().is_string_like() && !p.type().is_char_like())
            ss << "tidy_up_string(";

        if (is_inside_class_)
            ss << utility_.as_member_variable(p.name());
        else
            ss << "v." << utility_.as_getter(p.name());

        if (p.type().is_filesystem_path()) {
            ss << ".generic_string()";
            stream_ << utility_.quote_escaped_streamed(ss.str());
        } else if (p.type().is_date() || p.type().is_ptime() ||
            p.type().is_time_duration()) {
            stream_ << utility_.quote_escaped_streamed(ss.str());
        } else if (p.type().is_string_like()) {

            if (!p.type().is_char_like())
                ss << ")";

            stream_ << utility_.quote_escaped_streamed(ss.str());
        } else if (p.type().is_primitive())
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

} }
