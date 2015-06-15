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
#include <boost/pointer_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/cpp/types/formattables/enum_info.hpp"
#include "dogen/cpp/types/formattables/class_info.hpp"
#include "dogen/cpp/types/formattables/exception_info.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp"
#include "dogen/cpp_formatters/types/qname.hpp"
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/header_guards.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"
#include "dogen/cpp_formatters/types/qname.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/hash_implementation.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp_formatters.hash_implementation"));

const std::string std_ns("std");

const std::string invalid_sequence_container(
    "Sequence containers have exactly one type argument: ");
const std::string invalid_associative_container(
    "Associative containers have one or two type arguments");
const std::string invalid_smart_pointer(
    "Smart pointers have exactly one type argument");
const std::string missing_class_info("Class info is empty");
const std::string missing_enum_info("Enumeration info is empty");
const std::string enum_info_not_supported(
    "Enumerations do not have an implementation");

}

namespace dogen {
namespace cpp_formatters {

hash_implementation::hash_implementation(std::ostream& stream) :
    stream_(stream), utility_(stream_, indenter_) { }

file_formatter::shared_ptr hash_implementation::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new hash_implementation(stream));
}

bool hash_implementation::is_hashable(
    const cpp::formattables::nested_type_info& nti) {
    return
        !nti.is_sequence_container() &&
        !nti.is_associative_container() &&
        !nti.is_smart_pointer() &&
        !nti.is_pair() &&
        !nti.is_optional_like() &&
        !nti.is_variant_like() &&
        !nti.is_date() &&
        !nti.is_ptime() &&
        !nti.is_time_duration() &&
        !nti.is_filesystem_path() &&
        !nti.is_ptree();
}

void hash_implementation::combine_function(
    const cpp::formattables::class_info& ci) {
    if (ci.properties().empty() && ci.parents().empty())
        return;

    stream_ << indenter_ << "template <typename HashableType>" << std::endl
            << indenter_ << "inline void combine(std::size_t& seed, "
            << "const HashableType& value) ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::hash<HashableType> hasher;" << std::endl
                << indenter_ << "seed ^= hasher(value) + 0x9e3779b9 + "
                << "(seed << 6) + (seed >> 2);" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::path_helper(
    const cpp::formattables::nested_type_info& nti) {
    const std::string identifiable_type_name(nti.complete_identifiable_name());
    const std::string type_name(nti.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_" << identifiable_type_name
            << "(const " << type_name << "& v) ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::size_t seed(0);"
                << std::endl;

        stream_ << indenter_
                << "combine(seed, v.generic_string());" << std::endl;
        stream_ << indenter_ << "return seed;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::pair_helper(
    const cpp::formattables::nested_type_info& nti) {
    const auto children(nti.children());
    if (children.size() != 2) {
        BOOST_LOG_SEV(lg, error) << "Children container has unexpected size: "
                                 << children.size() << " in nested type: "
                                 << nti.name();

        BOOST_THROW_EXCEPTION(formatting_error(invalid_sequence_container
                + nti.name()));
    }

    const std::string container_identifiable_type_name(
        nti.complete_identifiable_name());
    const std::string container_type_name(nti.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_"
            << container_identifiable_type_name
            << "(const " << container_type_name << "& v)";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::size_t seed(0);"
                << std::endl;

        utility_.blank_line();
        const auto first(children.front());
        if (is_hashable(first)) {
            stream_ << indenter_ << "combine(seed, v.first);" << std::endl;
        } else {
            stream_ << indenter_ << "combine(seed, "
                    << "hash_" << first.complete_identifiable_name()
                    << "(v.first));" << std::endl;
        }

        const auto second(children.front());
        if (is_hashable(second)) {
            stream_ << indenter_ << "combine(seed, v.second);" << std::endl;
        } else {
            stream_ << indenter_ << "combine(seed, "
                    << "hash_" << second.complete_identifiable_name()
                    << "(v.second));" << std::endl;
        }

        stream_ << indenter_ << "return seed;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::optional_helper(
    const cpp::formattables::nested_type_info& nti) {
    const auto children(nti.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Children container has unexpected size: "
                                 << children.size() << " in nested type: "
                                 << nti.name();

        BOOST_THROW_EXCEPTION(formatting_error(invalid_sequence_container
                + nti.name()));
    }

    const std::string container_identifiable_type_name(
        nti.complete_identifiable_name());
    const std::string container_type_name(nti.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_"
            << container_identifiable_type_name
            << "(const " << container_type_name << "& v) ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::size_t seed(0);"
                << std::endl;

        utility_.blank_line();
        stream_ << indenter_ << "if (!v)" << std::endl;
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "return seed;" << std::endl;
        }

        utility_.blank_line();
        const auto containee(children.front());
        if (is_hashable(containee)) {
            stream_ << indenter_ << "combine(seed, *v);" << std::endl;
        } else {
            stream_ << indenter_ << "combine(seed, "
                    << "hash_" << containee.complete_identifiable_name()
                    << "(*v));" << std::endl;
        }
        stream_ << indenter_ << "return seed;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::variant_helper(
    const cpp::formattables::nested_type_info& nti) {
    const auto children(nti.children());
    if (children.empty()) {
        BOOST_LOG_SEV(lg, error) << "Children container has unexpected size: "
                                 << children.size() << " in nested type: "
                                 << nti.name();

        BOOST_THROW_EXCEPTION(formatting_error(invalid_sequence_container
                + nti.name()));
    }

    const std::string container_identifiable_type_name(
        nti.complete_identifiable_name());
    const std::string container_type_name(nti.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "struct "
            << nti.complete_identifiable_name()
            << "_visitor : public boost::static_visitor<> ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << nti.complete_identifiable_name()
                << "_visitor() : hash(0) {}" << std::endl;

        for (const auto& c : children) {
            stream_ << indenter_
                    << "void operator()(const " << c.name()
                    << (c.is_primitive() ? "" : "&")
                    << " v) const ";

            utility_.open_scope();
            {
                positive_indenter_scope s(indenter_);
                if (is_hashable(c)) {
                    stream_ << indenter_ << "combine(hash, v);" << std::endl;
                } else {
                    stream_ << indenter_ << "combine(hash, "
                            << "hash_" << c.complete_identifiable_name()
                            << "(v));" << std::endl;
                }
            }
            utility_.close_scope();
            utility_.blank_line();
        }
        stream_ << indenter_ << "mutable std::size_t hash;" << std::endl;
    }
    stream_ << indenter_ << "};" << std::endl;

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_"
            << container_identifiable_type_name
            << "(const " << container_type_name << "& v) ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << nti.complete_identifiable_name()
                << "_visitor vis;" << std::endl
                << indenter_ << "boost::apply_visitor(vis, v);" << std::endl
                << indenter_ << "return vis.hash;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::
sequence_container_helper(const cpp::formattables::nested_type_info& nti) {
    const auto children(nti.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Children container has unexpected size: "
                                 << children.size() << " in nested type: "
                                 << nti.name();

        BOOST_THROW_EXCEPTION(formatting_error(invalid_sequence_container
                + nti.name()));
    }

    const std::string container_identifiable_type_name(
        nti.complete_identifiable_name());
    const std::string container_type_name(nti.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_"
            << container_identifiable_type_name
            << "(const " << container_type_name << "& v) ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::size_t seed(0);"
                << std::endl;
        stream_ << indenter_ << "for (const auto i : v) ";
        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            const auto containee(children.front());
            if (is_hashable(containee)) {
                stream_ << indenter_ << "combine(seed, i);" << std::endl;
            } else {
                stream_ << indenter_ << "combine(seed, "
                        << "hash_" << containee.complete_identifiable_name()
                        << "(i));" << std::endl;
            }
        }
        utility_.close_scope();
        stream_ << indenter_ << "return seed;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::
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

    const std::string container_identifiable_type_name(
        nti.complete_identifiable_name());
    const std::string container_type_name(nti.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_"
            << container_identifiable_type_name
            << "(const " << container_type_name << "& v) ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::size_t seed(0);"
                << std::endl;
        stream_ << indenter_ << "for (const auto i : v) ";
        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            const auto key(children.front());
            const auto value(children.back());

            if (is_hashable(key)) {
                stream_ << indenter_ << "combine(seed, i.first);" << std::endl;
            } else {
                stream_ << indenter_ << "combine(seed, "
                        << "hash_" << key.complete_identifiable_name()
                        << "(i.first));" << std::endl;
            }

            if (is_hashable(value)) {
                stream_ << indenter_ << "combine(seed, i.second);" << std::endl;
            } else {
                stream_ << indenter_ << "combine(seed, "
                        << "hash_" << value.complete_identifiable_name()
                        << "(i.second));" << std::endl;
            }
        }
        utility_.close_scope();
        stream_ << indenter_ << "return seed;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::
smart_pointer_helper(const cpp::formattables::nested_type_info& nti) {
    const auto children(nti.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << invalid_smart_pointer;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_smart_pointer));
    }

    const std::string container_identifiable_type_name(
        nti.complete_identifiable_name());
    const std::string container_type_name(nti.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_"
            << container_identifiable_type_name
            << "(const " << container_type_name << "& v) ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::size_t seed(0);"
                << std::endl;

        const auto containee(children.front());
        if (is_hashable(containee)) {
            stream_ << indenter_ << "combine(seed, *v);" << std::endl;
        } else {
            stream_ << indenter_ << "combine(seed, "
                    << "hash_" << containee.complete_identifiable_name()
                    << "(*v));" << std::endl;
        }
        stream_ << indenter_ << "return seed;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::date_helper(
    const cpp::formattables::nested_type_info& nti) {
    const std::string identifiable_type_name(
        nti.complete_identifiable_name());
    const std::string type_name(nti.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_" << identifiable_type_name
            << "(const " << type_name << "& v) ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::size_t seed(0);"
                << std::endl;

        stream_ << indenter_
                << "combine(seed, v.modjulian_day());"
                << std::endl;

        stream_ << indenter_ << "return seed;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::ptime_helper(
    const cpp::formattables::nested_type_info& nti) {
    const std::string identifiable_type_name(
        nti.complete_identifiable_name());
    const std::string type_name(nti.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_" << identifiable_type_name
            << "(const " << type_name << "& v) ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::size_t seed(0);"
                << std::endl;

        stream_ << indenter_
                << "const boost::posix_time::ptime"
                << " epoch(boost::gregorian::date(1970, 1, 1));"
                << std::endl
                << indenter_ << "boost::posix_time::time_duration d(v - epoch);"
                << std::endl
                << indenter_
                << "seed = static_cast<std::size_t>(d.total_seconds());"
                << std::endl;
        stream_ << indenter_ << "return seed;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::
time_duration_helper(const cpp::formattables::nested_type_info& nti) {
    const std::string identifiable_type_name(
        nti.complete_identifiable_name());
    const std::string type_name(nti.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_" << identifiable_type_name
            << "(const " << type_name << "& v) ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::size_t seed(0);"
                << std::endl;

        stream_ << indenter_
                << "seed = static_cast<std::size_t>(v.total_seconds());"
                << std::endl;
        stream_ << indenter_ << "return seed;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::ptree_helper(
    const cpp::formattables::nested_type_info& nti) {
    const std::string identifiable_type_name(
        nti.complete_identifiable_name());
    const std::string type_name(nti.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_" << identifiable_type_name
            << "(const " << type_name << "& v) ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::size_t seed(0);"
                << std::endl;

        stream_ << indenter_
                << "for (const auto& node : v) ";

        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "combine(seed, node.first);" << std::endl
                    << indenter_ << "combine(seed, node.second.data());"
                    << std::endl
                    << indenter_ << "combine(seed, hash_"
                    << identifiable_type_name << "(node.second));" << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
        stream_ << indenter_ << "return seed;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::
recursive_helper_method_creator(const cpp::formattables::nested_type_info& nti,
    std::unordered_set<std::string>& types_done) {
    BOOST_LOG_SEV(lg, debug) << "Creating helper methods for " << nti.name();

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
    else if (nti.is_pair())
        pair_helper(nti);
    else if (nti.is_optional_like())
        optional_helper(nti);
    else if (nti.is_variant_like())
        variant_helper(nti);
    else if (nti.is_date())
        date_helper(nti);
    else if (nti.is_ptime())
        ptime_helper(nti);
    else if (nti.is_time_duration())
        time_duration_helper(nti);
    else if (nti.is_ptree())
        ptree_helper(nti);
    else if (nti.is_filesystem_path())
        path_helper(nti);

    types_done.insert(nti.complete_identifiable_name());
}

void hash_implementation::create_helper_methods(
    const cpp::formattables::class_info& ci) {
    const auto props(ci.properties());
    if (props.empty())
        return;

    std::unordered_set<std::string> types_done;
    for (const auto p : props)
        recursive_helper_method_creator(p.type(), types_done);
}

void hash_implementation::hasher_hash_method(
    const cpp::formattables::class_info& ci) {
    BOOST_LOG_SEV(lg, debug) << "Creating hash method for " << ci.name();

    const auto props(ci.properties());
    const auto parents(ci.parents());
    stream_ << indenter_ << "std::size_t " << ci.name() << "_hasher::"
            << "hash(const "
            << ci.name() << "&"
            << (props.empty() && parents.empty() ? ") " : " v) ");

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);

        stream_ << indenter_ << "std::size_t seed(0);" << std::endl;

        const auto parents(ci.parents());
        if (!parents.empty())
            utility_.blank_line();

        for (const auto p : parents) {
            stream_ << indenter_ << "combine(seed, dynamic_cast<const ";
            qname qname(stream_);
            qname.format(p);
            stream_ << "&>(v));" << std::endl;
        }

        if (!props.empty())
            utility_.blank_line();

        for (const auto p : props) {
            if (p.type().is_date()) {
                    stream_ << indenter_ << "combine(seed, v." << p.name()
                            << "().modjulian_day());" << std::endl;
            } else if (is_hashable(p.type())) {
                stream_ << indenter_ << "combine(seed, v." << p.name()
                        << "());" << std::endl;
            } else {
                stream_ << indenter_ << "combine(seed, "
                        << "hash_" << p.type().complete_identifiable_name()
                        << "(v." << p.name()
                        << "()));" << std::endl;
            }
        }

        if (props.size() > 1)
            utility_.blank_line();

        stream_ << indenter_ << "return seed;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::format_class(const cpp::formattables::file_info& f) {
    auto o(boost::dynamic_pointer_cast<
            cpp::formattables::class_info>(f.formattable()));
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_info;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_info));
    }

    const cpp::formattables::class_info& ci(*o);
    {
        using dogen::formatters::cpp::scoped_namespace_formatter;
        scoped_namespace_formatter nsh(stream_, std::list<std::string> { });

        utility_.blank_line();
        combine_function(ci);
        create_helper_methods(ci);
        utility_.blank_line();
    }
    utility_.blank_line(2);
    {
        using dogen::formatters::cpp::scoped_namespace_formatter;
        scoped_namespace_formatter nsh(stream_, ci.namespaces());
        utility_.blank_line();

        hasher_hash_method(ci);
        utility_.blank_line();
    }
    utility_.blank_line();
}

void hash_implementation::format_enumeration(
    const cpp::formattables::file_info&) {
    BOOST_LOG_SEV(lg, error) << enum_info_not_supported;
    BOOST_THROW_EXCEPTION(formatting_error(enum_info_not_supported));
}

void hash_implementation::format(const cpp::formattables::file_info& f) {
    licence licence(stream_);
    licence.format();

    includes includes(stream_);
    includes.format(f);

    using cpp::formattables::content_types;
    if (f.descriptor().content_type() == content_types::unversioned_key ||
        f.descriptor().content_type() == content_types::versioned_key ||
        f.descriptor().content_type() == content_types::value_object ||
        f.descriptor().content_type() == content_types::entity ||
        f.descriptor().content_type() == content_types::keyed_entity)
        format_class(f);
    else if (f.descriptor().content_type() == content_types::enumeration)
        format_enumeration(f);
}

} }
