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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/qname.hpp"
#include "dogen/cpp/types/formatters/licence.hpp"
#include "dogen/cpp/types/formatters/header_guards.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/includes.hpp"
#include "dogen/cpp/types/formatters/namespace_helper.hpp"
#include "dogen/cpp/types/formatters/qname.hpp"
#include "dogen/cpp/types/formatters/indenter.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formatters/hash_implementation.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.hash_implementation"));

const std::string std_ns("std");

const std::string invalid_sequence_container(
    "Sequence containers have exactly one type argument: ");
const std::string invalid_associative_container(
    "Associative containers have one or two type arguments");
const std::string invalid_smart_pointer(
    "Smart pointers have exactly one type argument");
const std::string missing_class_view_model(
    "Meta type is pod but class view model is empty");
const std::string enumeration_view_model_not_supported(
    "Enumerations do not have an implementation");

}

namespace dogen {
namespace cpp {
namespace formatters {

hash_implementation::hash_implementation(std::ostream& stream) :
    stream_(stream), utility_(stream_, indenter_) { }

file_formatter::shared_ptr hash_implementation::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new hash_implementation(stream));
}

bool hash_implementation::is_hashable(const nested_type_view_model& vm) {
    return
        !vm.is_sequence_container() &&
        !vm.is_associative_container() &&
        !vm.is_smart_pointer() &&
        !vm.is_pair() &&
        !vm.is_optional_like() &&
        !vm.is_variant_like() &&
        !vm.is_ptime() &&
        !vm.is_time_duration();
}

void hash_implementation::combine_function(const class_view_model& vm) {
    if (vm.properties().empty() && vm.parents().empty())
        return;

    stream_ << indenter_ << "template <typename HashableType>" << std::endl
            << indenter_ << "inline void combine(std::size_t& seed, "
            << "const HashableType& value)" << std::endl;

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::hash<HashableType> hasher;" << std::endl
                << indenter_ << "seed ^= hasher(value) + 0x9e3779b9 + "
                << "(seed << 6) + (seed >> 2);" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::pair_helper(const nested_type_view_model& vm) {
    const auto children(vm.children());
    if (children.size() != 2) {
        BOOST_LOG_SEV(lg, error) << "Children container has unexpected size: "
                                 << children.size() << " in nested type: "
                                 << vm.name();

        BOOST_THROW_EXCEPTION(formatting_error(invalid_sequence_container
                + vm.name()));
    }

    const std::string container_identifiable_type_name(
        vm.complete_identifiable_name());
    const std::string container_type_name(vm.complete_name());

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

void hash_implementation::optional_helper(const nested_type_view_model& vm) {
    const auto children(vm.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Children container has unexpected size: "
                                 << children.size() << " in nested type: "
                                 << vm.name();

        BOOST_THROW_EXCEPTION(formatting_error(invalid_sequence_container
                + vm.name()));
    }

    const std::string container_identifiable_type_name(
        vm.complete_identifiable_name());
    const std::string container_type_name(vm.complete_name());

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

void hash_implementation::variant_helper(const nested_type_view_model& vm) {
    const auto children(vm.children());
    if (children.empty()) {
        BOOST_LOG_SEV(lg, error) << "Children container has unexpected size: "
                                 << children.size() << " in nested type: "
                                 << vm.name();

        BOOST_THROW_EXCEPTION(formatting_error(invalid_sequence_container
                + vm.name()));
    }

    const std::string container_identifiable_type_name(
        vm.complete_identifiable_name());
    const std::string container_type_name(vm.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "struct "
            << vm.complete_identifiable_name()
            << "_visitor : public boost::static_visitor<> ";

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);
        stream_ << indenter_ << vm.complete_identifiable_name()
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
        stream_ << indenter_ << vm.complete_identifiable_name()
                << "_visitor vis;" << std::endl
                << indenter_ << "boost::apply_visitor(vis, v);" << std::endl
                << indenter_ << "return vis.hash;" << std::endl;
    }
    utility_.close_scope();
}

void hash_implementation::
sequence_container_helper(const nested_type_view_model& vm) {
    const auto children(vm.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Children container has unexpected size: "
                                 << children.size() << " in nested type: "
                                 << vm.name();

        BOOST_THROW_EXCEPTION(formatting_error(invalid_sequence_container
                + vm.name()));
    }

    const std::string container_identifiable_type_name(
        vm.complete_identifiable_name());
    const std::string container_type_name(vm.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_"
            << container_identifiable_type_name
            << "(const " << container_type_name << "& v)";

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
associative_container_helper(const nested_type_view_model& vm) {
    const auto children(vm.children());
    if (children.size() != 1 && children.size() != 2) {
        BOOST_LOG_SEV(lg, error) << invalid_associative_container;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_associative_container));
    }

    if (children.size() == 1) {
        sequence_container_helper(vm);

        return;
    }

    const std::string container_identifiable_type_name(
        vm.complete_identifiable_name());
    const std::string container_type_name(vm.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_"
            << container_identifiable_type_name
            << "(const " << container_type_name << "& v)";

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
smart_pointer_helper(const nested_type_view_model& vm) {
    const auto children(vm.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << invalid_smart_pointer;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_smart_pointer));
    }

    const std::string container_identifiable_type_name(
        vm.complete_identifiable_name());
    const std::string container_type_name(vm.complete_name());

    utility_.blank_line();
    stream_ << indenter_ << "inline std::size_t hash_"
            << container_identifiable_type_name
            << "(const " << container_type_name << "& v)";

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

void hash_implementation::ptime_helper(const nested_type_view_model& vm) {
    const std::string identifiable_type_name(
        vm.complete_identifiable_name());
    const std::string type_name(vm.complete_name());

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
time_duration_helper(const nested_type_view_model& vm) {
    const std::string identifiable_type_name(
        vm.complete_identifiable_name());
    const std::string type_name(vm.complete_name());

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

void hash_implementation::
recursive_helper_method_creator(const nested_type_view_model& vm,
    std::unordered_set<std::string>& types_done) {
    BOOST_LOG_SEV(lg, debug) << "Creating helper methods for " << vm.name();

    if (types_done.find(vm.complete_identifiable_name()) != types_done.end())
        return;

    const auto children(vm.children());
    for (const auto c : children)
        recursive_helper_method_creator(c, types_done);

    if (vm.is_sequence_container())
        sequence_container_helper(vm);
    else if (vm.is_associative_container())
        associative_container_helper(vm);
    else if (vm.is_smart_pointer())
        smart_pointer_helper(vm);
    else if (vm.is_pair())
        pair_helper(vm);
    else if (vm.is_optional_like())
        optional_helper(vm);
    else if (vm.is_variant_like())
        variant_helper(vm);
    else if (vm.is_ptime())
        ptime_helper(vm);
    else if (vm.is_time_duration())
        time_duration_helper(vm);

    types_done.insert(vm.complete_identifiable_name());
}

void hash_implementation::create_helper_methods(const class_view_model& vm) {
    const auto props(vm.properties());
    if (props.empty())
        return;

    std::unordered_set<std::string> types_done;
    for (const auto p : props)
        recursive_helper_method_creator(p.type(), types_done);
}

void hash_implementation::hasher_hash_method(const class_view_model& vm) {
    BOOST_LOG_SEV(lg, debug) << "Creating hash method for " << vm.name();

    const auto props(vm.properties());
    const auto parents(vm.parents());
    stream_ << indenter_ << "std::size_t " << vm.name() << "_hasher::"
            << "hash(const "
            << vm.name() << "&"
            << (props.empty() && parents.empty() ? ") " : "v) ");

    utility_.open_scope();
    {
        positive_indenter_scope s(indenter_);

        stream_ << indenter_ << "std::size_t seed(0);" << std::endl;

        const auto parents(vm.parents());
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
            if (p.type().is_filesystem_path()) {
                stream_ << indenter_ << "combine(seed, v." << p.name()
                        << "().generic_string());" << std::endl;
            } else if (p.type().is_date()) {
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

void hash_implementation::format_class(const file_view_model& vm) {
    boost::optional<view_models::class_view_model> o(vm.class_vm());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_view_model;
        BOOST_THROW_EXCEPTION(formatting_error(missing_class_view_model));
    }

    const class_view_model& cvm(*o);
    {
        namespace_helper nsh(stream_, std::list<std::string> { });
        utility_.blank_line();
        combine_function(cvm);
        create_helper_methods(cvm);
        utility_.blank_line();
    }
    utility_.blank_line(2);
    {
        namespace_helper ns_helper(stream_, cvm.namespaces());
        utility_.blank_line();

        hasher_hash_method(cvm);
        utility_.blank_line();
    }
    utility_.blank_line();
}

void hash_implementation::format_enumeration(const file_view_model&) {
    BOOST_LOG_SEV(lg, error) << enumeration_view_model_not_supported;
    BOOST_THROW_EXCEPTION(formatting_error(enumeration_view_model_not_supported));
}

void hash_implementation::format(const file_view_model& vm) {
    licence licence(stream_);
    licence.format();

    includes includes(stream_);
    includes.format(vm);

    if (vm.meta_type() == sml::meta_types::enumeration)
        format_enumeration(vm);
    else if (vm.meta_type() == sml::meta_types::pod)
        format_class(vm);
}

} } }
