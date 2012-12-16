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
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_database_implementation.hpp"
#include "dogen/utility/log/logger.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("database_implementation"));

const std::string empty;
const std::string underscore("_");
const std::string dot(".");
const std::string statement_name("statement");
const std::string work_name("work");
const std::string load_name("load");
const std::string load_id_name("load_id");
const std::string save_name("save");
const std::string erase_name("erase");
const std::string erase_id_name("erase_id");
const std::string name_suffix("_data_exchanger");
const std::string missing_class_view_model(
    "Meta type is pod but class view model is empty");
const std::string missing_enumeration_view_model(
    "Meta type is enumeration but enumeration view model is empty");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

database_implementation::
database_implementation(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) { }

file_formatter::shared_ptr
database_implementation::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new database_implementation(stream));
}

std::string database_implementation::
make_identifier(std::string type, std::string name, std::string operation) {
    std::ostringstream stream;
    if (!type.empty())
        stream << type << underscore;

    stream << name << underscore << operation;
    return stream.str();
}

std::string database_implementation::
make_sql(std::string name, std::string schema_name, std::string operation,
    unsigned int number_of_parameters) {
    std::ostringstream stream;
    stream << (operation == save_name ? "select " : "select * from ");

    if (!schema_name.empty())
        stream << schema_name << dot;

    stream << make_identifier(empty, name, operation);

    stream << "(";
    for (unsigned int i = 0; i < number_of_parameters; ++i) {
        if (i != 0)
            stream << ", ";
        stream << "$" << i;
    }

    stream << ");";
    return utility_.quote(stream.str());
}

void database_implementation::anonymous_namespace(const class_view_model& vm) {
    namespace_helper ns_helper(stream_, std::list<std::string> { });
    utility_.blank_line();

    stream_ << indenter_ << "enum fields ";
    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        bool is_first(true);
        unsigned int i(0);
        for (auto p : vm.all_properties()) {
            if (!is_first)
                stream_ << "," << std::endl;
            stream_ << indenter_ << p.name() << "_field = " << i;
            is_first = false;
            ++i;
        }
        stream_ << std::endl;
    }
    stream_ << "};" << std::endl;
    utility_.blank_line();

    const std::string string_type("const std::string ");
    auto lambda([&](std::string type, std::string operation) {
            const std::string dbn(vm.database_name());
            stream_ << indenter_ << string_type << operation
                    << (type == work_name ? "_work" : "")
                    << "_name("
                    << utility_.quote(make_identifier(type, dbn, operation))
                    << ");" << std::endl;
        });

    auto pi([&](std::string operation) {
            const std::string dbn(vm.database_name());
            const std::string sn(vm.schema_name());
            const unsigned int p(vm.all_properties().size());
            stream_ << indenter_ << string_type << operation << "_sql("
                    << make_sql(dbn, sn, operation, p)
                    << ");" << std::endl;
        });

    lambda(statement_name, load_name);
    lambda(statement_name, load_id_name);
    lambda(work_name, load_name);
    pi(load_name);
    utility_.blank_line();

    lambda(statement_name, erase_name);
    lambda(statement_name, erase_id_name);
    lambda(work_name, erase_name);
    pi(erase_name);
    utility_.blank_line();

    lambda(statement_name, save_name);
    lambda(work_name, save_name);
    pi(save_name);

    utility_.blank_line(); // namespace end
}

void database_implementation::format_sql(const class_view_model& vm) {
    const std::string class_name(vm.name() + name_suffix);

    stream_ << indenter_ << "std::string " << class_name << "::"
            << std::endl
            << indenter_ << "format_sql(const std::string& format_str, "
            << "const boost::optional<versioned_key> id) ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "return (boost::format(format_str) % (id ? "
                << utility_.quote("$1") << " : "
                << utility_.quote("null") << ")).str();"
                << std::endl;
    }
    utility_.close_scope();
}

void database_implementation::load_internal(const class_view_model&) {

}

void database_implementation::erase_internal(const class_view_model&) {

}

void database_implementation::load(const class_view_model&) {

}

void database_implementation::save(const class_view_model&) {

}

void database_implementation::erase(const class_view_model&) {

}

void database_implementation::format(const file_view_model& vm) {
    licence licence(stream_);
    licence.format();

    cpp_includes includes(stream_);
    includes.format(vm);

    if (vm.meta_type() == sml::meta_types::enumeration) {
        const auto o(vm.enumeration_vm());
        if (!o) {
            BOOST_LOG_SEV(lg, error) << missing_enumeration_view_model;
            BOOST_THROW_EXCEPTION(generation_failure(missing_enumeration_view_model));
        }
        const auto evm(*o);
        stream_ << "void dummy_function_" << evm.name()
                << "() { }" << std::endl;
    } else if (vm.meta_type() == sml::meta_types::pod) {
        boost::optional<view_models::class_view_model> o(vm.class_vm());
        if (!o) {
            BOOST_LOG_SEV(lg, error) << missing_class_view_model;
            BOOST_THROW_EXCEPTION(generation_failure(missing_class_view_model));
        }
        const view_models::class_view_model& cvm(*o);
        anonymous_namespace(cvm);
        utility_.blank_line(2);

        {
            namespace_helper ns_helper(stream_, cvm.namespaces());
            utility_.blank_line();

            format_sql(cvm);
            utility_.blank_line();

            utility_.blank_line(2);
        }
    }
    utility_.blank_line();
}

} } } } }
