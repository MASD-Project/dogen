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
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/generation_failure.hpp"
#include "dogen/cpp/types/formatters/cpp_licence.hpp"
#include "dogen/cpp/types/formatters/cpp_header_guards.hpp"
#include "dogen/cpp/types/formatters/cpp_namespace.hpp"
#include "dogen/cpp/types/formatters/cpp_includes.hpp"
#include "dogen/cpp/types/formatters/cpp_namespace_helper.hpp"
#include "dogen/cpp/types/formatters/cpp_qualified_name.hpp"
#include "dogen/cpp/types/formatters/cpp_indenter.hpp"
#include "dogen/cpp/types/formatters/cpp_generator_implementation.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("generator_implementation"));

const std::string int_type("int");
const std::string bool_type("bool");
const std::string string_type("std::string");
const std::string invalid_sequence_container(
    "Sequence containers have exactly one type argument");
const std::string invalid_associative_container(
    "Associative containers have one or two type arguments");
const std::string invalid_smart_pointer(
    "Smart pointers have exactly one type argument");
const std::string invalid_pair(
    "Pairs  have exactly two type arguments");
const std::string missing_class_view_model(
    "Meta type is pod but class view model is empty");
const std::string missing_enumeration_view_model(
    "Meta type is enumeration but enumeration view model is empty");

}

namespace dogen {
namespace cpp {
namespace formatters {

generator_implementation::
generator_implementation(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) { }

file_formatter::shared_ptr
generator_implementation::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new generator_implementation(stream));
}

void generator_implementation::
sequence_container_helper(
    const nested_type_view_model& vm, unsigned int quantity) {
    const auto container_identifiable_type_name(
        vm.complete_identifiable_name());
    const auto container_type_name(vm.complete_name());

    const auto children(vm.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << invalid_sequence_container;
        BOOST_THROW_EXCEPTION(generation_failure(invalid_sequence_container));
    }

    const auto containee_vm(children.front());
    const auto containee_identifiable_type_name(
        containee_vm.complete_identifiable_name());

    stream_ << indenter_ << container_type_name << " create_"
            << container_identifiable_type_name
            << "(unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << container_type_name << " r;"
                << std::endl;
        stream_ << indenter_ << "for (unsigned int i(0); i < " << quantity
                << "; ++i) ";
        utility_.open_scope();
        {
            cpp_positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "r.push_back(create_"
                    << containee_identifiable_type_name
                    << "(position + i));" << std::endl;
        }
        utility_.close_scope();
        stream_ << indenter_ << "return r;" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void generator_implementation::
associative_container_helper(
    const nested_type_view_model& vm, unsigned int quantity) {

    const auto children(vm.children());
    if (children.size() != 1 && children.size() != 2) {
        BOOST_LOG_SEV(lg, error) << invalid_associative_container;
        BOOST_THROW_EXCEPTION(generation_failure(invalid_associative_container));
    }

    const auto container_identifiable_type_name(vm.complete_identifiable_name());
    const auto container_type_name(vm.complete_name());

    stream_ << indenter_ << container_type_name << " create_"
            << container_identifiable_type_name
            << "(unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << container_type_name << " r;"
                << std::endl;
        stream_ << indenter_ << "for (unsigned int i(0); i < " << quantity
                << "; ++i) ";
        utility_.open_scope();
        {
            cpp_positive_indenter_scope s(indenter_);
            if (children.size() == 1) {
                const auto containee_vm(children.front());
                const auto containee_identifiable_type_name(
                    containee_vm.complete_identifiable_name());

                stream_ << indenter_ << "r.insert(create_"
                        << containee_identifiable_type_name
                        << "(position + i));" << std::endl;
            } else {
                const auto key(children.front());
                const auto value(children.back());
                stream_ << indenter_ << "r.insert(std::make_pair("
                        << "create_" << key.complete_identifiable_name()
                        << "(position + i), "
                        << "create_" << value.complete_identifiable_name()
                        << "(position + i)));"
                        << std::endl;
            }
        }
        utility_.close_scope();
        stream_ << indenter_ << "return r;" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void generator_implementation::
smart_pointer_helper(const nested_type_view_model& vm) {
    const auto container_identifiable_type_name(
        vm.complete_identifiable_name());
    const auto container_type_name(vm.complete_name());

    const auto children(vm.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << invalid_smart_pointer;
        BOOST_THROW_EXCEPTION(generation_failure(invalid_smart_pointer));
    }

    const auto containee_vm(children.front());
    const auto containee_identifiable_type_name(
        containee_vm.complete_identifiable_name());

    stream_ << indenter_ << container_type_name
            << std::endl
            << indenter_ << "create_"
            << container_identifiable_type_name
            << "(unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << container_type_name << " r("
                << std::endl;
        {
            cpp_positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "create_"
                    << containee_identifiable_type_name
                    << "_ptr(position));" << std::endl;
        }
        stream_ << indenter_ << "return r;" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void generator_implementation::
optional_helper(const nested_type_view_model& vm) {
    const auto container_identifiable_type_name(
        vm.complete_identifiable_name());
    const auto container_type_name(vm.complete_name());

    const auto children(vm.children());
    if (children.size() != 1) {
        BOOST_LOG_SEV(lg, error) << invalid_smart_pointer;
        BOOST_THROW_EXCEPTION(generation_failure(invalid_smart_pointer));
    }

    stream_ << indenter_ << container_type_name
            << std::endl
            << indenter_ << "create_"
            << container_identifiable_type_name
            << "(unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << container_type_name << " r(";
        {
            cpp_positive_indenter_scope s(indenter_);
            const auto containee_vm(children.front());
            const auto containee_identifiable_type_name(
                containee_vm.complete_identifiable_name());

            stream_ << indenter_ << "create_"
                    << containee_identifiable_type_name
                    << "(position));" << std::endl;
        }
        stream_ << indenter_ << "return r;" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void generator_implementation::
pair_helper(const nested_type_view_model& vm) {
    const auto container_identifiable_type_name(
        vm.complete_identifiable_name());
    const auto container_type_name(vm.complete_name());

    const auto children(vm.children());
    if (children.size() != 2) {
        BOOST_LOG_SEV(lg, error) << invalid_pair;
        BOOST_THROW_EXCEPTION(generation_failure(invalid_pair));
    }

    stream_ << indenter_ << container_type_name
            << std::endl
            << indenter_ << "create_"
            << container_identifiable_type_name
            << "(unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << container_type_name << " r(" << std::endl;
        {
            cpp_positive_indenter_scope s(indenter_);
            const auto first(children.front());
            const auto first_identifiable_type_name(
                first.complete_identifiable_name());

            stream_ << indenter_ << "create_"
                    << first_identifiable_type_name
                    << "(position)," << std::endl;

            const auto second(children.back());
            const auto second_identifiable_type_name(
                second.complete_identifiable_name());

            stream_ << indenter_ << "create_"
                    << second_identifiable_type_name
                    << "(position));" << std::endl;
        }
        stream_ << indenter_ << "return r;" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void generator_implementation::
filesystem_path_helper(const nested_type_view_model& vm) {
    const auto type_name(vm.identifiable_name());
    const auto identifiable_type_name(vm.complete_identifiable_name());

    stream_ << indenter_ << vm.name() << std::endl
            << "create_" << identifiable_type_name
            << "(const unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::ostringstream s;" << std::endl
                << indenter_ << "s << " << utility_.quote("/a/path/number_")
                << " << position;" << std::endl;
        stream_ << indenter_ << "return " << vm.name() << "(s.str());"
                << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void generator_implementation::date_helper(const nested_type_view_model& vm) {
    const auto type_name(vm.identifiable_name());
    const auto identifiable_type_name(vm.complete_identifiable_name());

    stream_ << indenter_ << vm.name() << std::endl
            << "create_" << identifiable_type_name
            << "(const unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "unsigned int day(position % 28);" << std::endl
                << indenter_ << "boost::gregorian::date r(2002, 2, day);"
                << std::endl
                << indenter_ << "return r;" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void generator_implementation::ptime_helper(const nested_type_view_model& vm) {
    const auto type_name(vm.identifiable_name());
    const auto identifiable_type_name(vm.complete_identifiable_name());

    stream_ << indenter_ << vm.name() << std::endl
            << "create_" << identifiable_type_name
            << "(const unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "unsigned int day(position % 28);" << std::endl
                << indenter_ << "using boost::gregorian::date;" << std::endl
                << indenter_ << "using boost::posix_time::ptime;"
                << std::endl
                << indenter_ << "using boost::posix_time::time_duration;"
                << std::endl
                << indenter_ << "date d(2002, 2, day);"
                << indenter_
                << "ptime r(d, time_duration(1,2,3));" << std::endl
                << indenter_ << "return r;" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void generator_implementation::
time_duration_helper(const nested_type_view_model& vm) {
    const auto type_name(vm.identifiable_name());
    const auto identifiable_type_name(vm.complete_identifiable_name());

    stream_ << indenter_ << vm.name() << std::endl
            << "create_" << identifiable_type_name
            << "(const unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "unsigned int hour(position % 55);" << std::endl
                << indenter_ << "using boost::posix_time::time_duration;"
                << std::endl
                << indenter_ << "time_duration r(hour, 2, 3);" << std::endl
                << indenter_ << "return r;" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void generator_implementation::
variant_helper(const nested_type_view_model& vm) {
    const auto container_identifiable_type_name(
        vm.complete_identifiable_name());
    const auto container_type_name(vm.complete_name());

    const auto children(vm.children());
    if (children.empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_smart_pointer;
        BOOST_THROW_EXCEPTION(generation_failure(invalid_smart_pointer));
    }

    utility_.blank_line();
    stream_ << indenter_ << container_type_name
            << std::endl
            << indenter_ << "create_"
            << container_identifiable_type_name
            << "(unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << container_type_name << " r;" << std::endl;
        utility_.blank_line();

        unsigned int i(0);
        for (const auto& c : children) {
            if (i == 0) {
                stream_ << indenter_ << "if (position == 0 || ((position % "
                        << children.size() << ") == 0))" << std::endl;
            } else if (i == 1) {
                stream_ << indenter_
                        << "else if (position == 1 || ((position %"
                        << children.size() + 1 << ") == 0))" << std::endl;
            } else {
                stream_ << indenter_
                        << "else if ((position % " << i << ") == 0)"
                        << std::endl;
            }
            ++i;

            {
                cpp_positive_indenter_scope s(indenter_);
                stream_ << indenter_ << "r = create_"
                        << c.complete_identifiable_name()
                        << "(position);" << std::endl;
            }
        }
        utility_.blank_line();
        stream_ << indenter_ << "return r;" << std::endl;
    }
    utility_.close_scope();
    utility_.blank_line();
}

void generator_implementation::
domain_type_helper(const std::string& identifiable_type_name,
    const std::string& type_name, bool as_pointer) {
    stream_ << indenter_ << type_name << (as_pointer ? "*" : "")
            << std::endl
            << "create_" << identifiable_type_name
            << (as_pointer ? "_ptr" : "")
            << "(const unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        if (as_pointer) {
            stream_ << indenter_ << "return " << type_name
                    << "_generator::create_ptr(position);" << std::endl;
        } else {
            stream_ << indenter_ << "return " << type_name
                    << "_generator::create(position);" << std::endl;
        }
    }
    utility_.close_scope();
}

void generator_implementation::
composite_domain_type_helper(const std::string& identifiable_type_name,
    const std::string& type_name, bool as_pointer) {
    stream_ << indenter_ << type_name << (as_pointer ? "*" : "")
            << std::endl
            << "create_" << identifiable_type_name
            << (as_pointer ? "_ptr" : "")
            << "(const unsigned int) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        if (as_pointer) {
            stream_ << indenter_ << "return nullptr" << ";"
                    << std::endl;
        } else
            stream_ << indenter_ << "return " << type_name << "();"
                    << std::endl;
    }
    utility_.close_scope();
}

void generator_implementation::bool_helper() {
    stream_ << indenter_ << "bool create_bool(const unsigned int position) ";
    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "return (position % 2) == 0;" << std::endl;
    }
    utility_.close_scope();
}

void generator_implementation::string_helper() {
    stream_ << indenter_ << "std::string create_std_string"
            << "(const unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "std::ostringstream s;" << std::endl
                << indenter_ << "s << " << utility_.quote("a_string_")
                << " << position;" << std::endl;
        stream_ << indenter_ << "return s.str();" << std::endl;
    }
    utility_.close_scope();
}

void generator_implementation::
char_like_helper(const std::string& identifiable_type_name,
    const std::string& type_name) {
    stream_ << indenter_ << type_name << " create_" << identifiable_type_name
            << "(const unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_
                << "return static_cast<" << type_name
                << ">(((position % 95) + 32) == 34) ? 35 :"
                << " ((position % 95) + 32);"
                << std::endl;
    }
    utility_.close_scope();
}

void generator_implementation::
int_like_helper(const std::string& identifiable_type_name,
    const std::string& type_name) {
    stream_ << indenter_ << type_name << " create_" << identifiable_type_name
            << "(const unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        if (type_name == int_type)
            stream_ << indenter_ << "return position;";
        else
            stream_ << indenter_ << "return static_cast<" << type_name
                    << ">(position);";

        stream_ << std::endl;
    }
    utility_.close_scope();
}

void generator_implementation::
recursive_helper_method_creator(const std::string& owner_name,
    const nested_type_view_model& vm,
    std::unordered_set<std::string>& types_done, bool as_pointer) {
    const unsigned int quantity(10);

    std::string type_name(vm.complete_identifiable_name());
    if (as_pointer)
        type_name += "_ptr";

    if (types_done.find(type_name) != types_done.end())
        return;

    const auto children(vm.children());
    for (const auto c : children)
        recursive_helper_method_creator(owner_name, c, types_done,
            vm.is_smart_pointer());

    if (vm.is_primitive()) {
        if (vm.is_char_like()) {
            char_like_helper(vm.identifiable_name(), vm.name());
            utility_.blank_line();
        } else if (vm.is_int_like()) {
            int_like_helper(vm.identifiable_name(), vm.name());
            utility_.blank_line();
        } else if (vm.name() == bool_type) {
            bool_helper();
            utility_.blank_line();
        }
    } else if (vm.is_sequence_container())
        sequence_container_helper(vm, quantity);
    else if (vm.is_associative_container())
        associative_container_helper(vm, quantity);
    else if (vm.is_smart_pointer())
        smart_pointer_helper(vm);
    else if (vm.is_optional_like())
        optional_helper(vm);
    else if (vm.is_pair())
        pair_helper(vm);
    else if (vm.is_variant_like())
        variant_helper(vm);
    else if (vm.is_filesystem_path())
        filesystem_path_helper(vm);
    else if (vm.is_date())
        date_helper(vm);
    else if (vm.is_ptime())
        ptime_helper(vm);
    else if (vm.is_time_duration())
        time_duration_helper(vm);
    else {
        if (vm.name() == string_type) {
            string_helper();
            utility_.blank_line();
        } else {
            if (boost::algorithm::ends_with(vm.name(), "::" + owner_name)) {
                composite_domain_type_helper(vm.identifiable_name(), vm.name(),
                    as_pointer);
            } else {
                domain_type_helper(vm.identifiable_name(), vm.name(),
                    as_pointer);
            }
            utility_.blank_line();
        }
    }
    types_done.insert(type_name);
}

void generator_implementation::
create_helper_methods(const class_view_model& vm) {
    const auto props(vm.properties());
    if (props.empty())
        return;

    namespace_helper ns_helper(stream_, std::list<std::string> { });
    std::unordered_set<std::string> types_done;

    utility_.blank_line();
    const bool as_ptr(false);
    const auto owner(vm.name());
    for (const auto p : props)
        recursive_helper_method_creator(owner, p.type(), types_done, as_ptr);
}

void generator_implementation::populate_method(const class_view_model& vm) {
    const auto props(vm.properties());
    const std::string name(vm.name() + "_generator");

    stream_ << indenter_ << "void " << name << "::" << std::endl;
    if (!props.empty()) {
        stream_ << "populate(const unsigned int position, result_type& v) " ;
    } else {
        stream_ << "populate(const unsigned int /*position*/, "
                << "result_type& /*v*/) " ;
    }
    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        unsigned int j(0);
        for (const auto p : props) {
            stream_ << indenter_ << "v." << p.name() << "("
                    << "create_" << p.type().complete_identifiable_name()
                    << "(position + " << j << "));" << std::endl;
            ++j;
        }
    }
    utility_.close_scope();
}

void generator_implementation::create_method(const class_view_model& vm) {
    if (vm.is_parent())
        return;

    const bool has_properties(!vm.properties().empty());
    const auto parents(vm.parents());
    const bool has_parents(!parents.empty());
    const bool has_properties_or_parents(has_properties || has_parents);

    const std::string name(vm.name() + "_generator");
    stream_ << indenter_ << name << "::result_type" << std::endl
            << name << "::create(const unsigned int"
            << (has_properties_or_parents ? " position" : "/*position*/")
            << ") ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << vm.name() << " r;" << std::endl;

        for (const auto p : parents) {
            stream_ << indenter_;
            cpp_qualified_name qualified_name(stream_);
            qualified_name.format(p);
            stream_ << "_generator::populate(position, r);"
                    << std::endl;
        }

        if (has_properties) {
            stream_ << indenter_ << name << "::populate(position, r);"
                    << std::endl;
        }
        stream_ << indenter_ << "return r;" << std::endl;
    }
    utility_.close_scope();
}

void generator_implementation::create_method_ptr(const class_view_model& vm) {
    auto leaves(vm.leaves());
    const std::string name(vm.name() + "_generator");
    stream_ << indenter_ << name << "::result_type*" << std::endl
            << name << "::create_ptr(const unsigned int position) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);

        if (leaves.empty()) {
            stream_ << indenter_ << vm.name() << "* p = new " << vm.name()
                    << "();" << std::endl
                    << indenter_ << name << "::populate(position, *p);"
                    << std::endl
                    << indenter_ << "return p;" << std::endl;
        } else {
            const auto front(leaves.front());
            leaves.pop_front();
            unsigned int i(0);
            unsigned int total(leaves.size());
            for (const auto l : leaves) {
                stream_ << indenter_ << "if ((position % " << total << ") == "
                        << i++ << ")"
                        << std::endl;
                {
                    cpp_positive_indenter_scope s(indenter_);
                    stream_ << indenter_ << "return " << l
                            << "_generator::create_ptr(position);"
                            << std::endl;
                }
            }
            stream_ << indenter_ << "return " << front
                    << "_generator::create_ptr(position);"
                    << std::endl;
        }
    }
    utility_.close_scope();
}

void generator_implementation::function_operator(const class_view_model& vm) {
    if (vm.is_parent())
        return;

    const std::string name(vm.name() + "_generator");
    stream_ << indenter_ << name << "::result_type" << std::endl
            << name << "::operator()() ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "return create("
                << utility_.as_member_variable("position") << "++);"
                << std::endl;
    }
    utility_.close_scope();
}

void generator_implementation::default_constructor(const class_view_model& vm) {
    if (vm.is_parent())
        return;

    const std::string name(vm.name() + "_generator");
    stream_ << indenter_ << name << "::" << name << "() : position_(0) { }";
    utility_.blank_line();
}

void generator_implementation::format_class(const file_view_model& vm) {
    boost::optional<view_models::class_view_model> o(vm.class_vm());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_class_view_model;
        BOOST_THROW_EXCEPTION(generation_failure(missing_class_view_model));
    }

    const class_view_model& cvm(*o);
    create_helper_methods(cvm);
    utility_.blank_line(2);

    {
        std::list<std::string> ns(cvm.namespaces());
        namespace_helper ns_helper(stream_, ns);

        utility_.blank_line();
        default_constructor(cvm);
        utility_.blank_line();
        populate_method(cvm);
        utility_.blank_line();
        create_method(cvm);
        create_method_ptr(cvm);
        utility_.blank_line();
        function_operator(cvm);
        utility_.blank_line();
    }
    utility_.blank_line();
}

void generator_implementation::format_enumeration(const file_view_model& vm) {
    const auto o(vm.enumeration_vm());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << missing_enumeration_view_model;
        BOOST_THROW_EXCEPTION(generation_failure(missing_enumeration_view_model));
    }

    const auto evm(*o);
    {
        std::list<std::string> ns(evm.namespaces());
        namespace_helper ns_helper(stream_, ns);

        utility_.blank_line();
        const std::string name(evm.name() + "_generator");
        stream_ << indenter_ << name << "::" << name << "() : position_(0) { }";
        utility_.blank_line();

        stream_ << indenter_ << "void " << name << "::" << std::endl
                << "populate(const unsigned int position, result_type& v) " ;

        utility_.open_scope();
        {
            cpp_positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "v = static_cast<" << evm.name() << ">"
                    << "(position % " << evm.enumerators().size() << ");"
                    << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();

        stream_ << indenter_ << name << "::result_type" << std::endl
                << name << "::create(const unsigned int  position) ";
        utility_.open_scope();
        {
            {
                cpp_positive_indenter_scope s(indenter_);
                stream_ << indenter_ << "result_type r;" << std::endl;
                stream_ << indenter_ << name << "::populate(position, r);"
                        << std::endl;
                stream_<< indenter_ << "return r;" << std::endl;
            }
        }
        utility_.close_scope();
        utility_.blank_line();

        stream_ << indenter_ << name << "::result_type" << std::endl
                << name << "::operator()() ";

        utility_.open_scope();
        {
            cpp_positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "return create("
                    << utility_.as_member_variable("position") << "++);"
                    << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
    }
}

void generator_implementation::format(const file_view_model& vm) {
    licence licence(stream_);
    licence.format();

    cpp_includes includes(stream_);
    includes.format(vm);

    if (vm.meta_type() == sml::meta_types::enumeration)
        format_enumeration(vm);
    else if (vm.meta_type() == sml::meta_types::pod)
        format_class(vm);
}

} } }
