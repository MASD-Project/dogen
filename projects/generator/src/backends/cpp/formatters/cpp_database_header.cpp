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
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_database_header.hpp"

namespace {

const std::string detail_ns("detail");
const std::string name_suffix("_data_exchanger");
const std::string missing_class_view_model(
    "File view model must contain a class view model");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

database_header::
database_header(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) {
}

file_formatter::shared_ptr database_header::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new database_header(stream));
}

void database_header::
compiler_generated_constuctors(const class_view_model& vm) {
    utility_.public_access_specifier();

    const std::string class_name(vm.name() + name_suffix);
    stream_ << indenter_ << class_name << "() = default;" << std::endl;

    stream_ << indenter_ << class_name << "(const " << class_name
            << "&) = delete;" << std::endl
            << indenter_ << "~" << class_name << "() = default;" << std::endl
            << indenter_ << class_name << "(" << class_name << "&&) = delete;"
            << std::endl;

    if (vm.all_properties().empty()) {
        stream_ << indenter_ << vm.name() << "& operator=(const " << vm.name()
                << "&) = delete;" << std::endl;
    }

    utility_.blank_line();
}

void database_header::format_sql() {
    stream_ << indenter_ << "std::string format_sql("
            << "const std::string& format_str," << std::endl;

    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "const boost::optional<versioned_key> id "
                << "= boost::optional<versioned_key>());"
                << std::endl;
    }
    utility_.blank_line();
}

void database_header::load_internal(const class_view_model& vm) {
    stream_ << indenter_ << "std::vector<";

    cpp_qualified_name qualified_name(stream_);
    qualified_name.format(vm);

    stream_ << "> load_internal(" << std::endl;
    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "pqxx::connection& connection," << std::endl
                << indenter_ << "const boost::optional<versioned_key> id ="
                << "boost::optional<versioned_key>());" << std::endl;
    }
    utility_.blank_line();
}

void database_header::erase_internal() {
    stream_ << indenter_ << "void erase_internal(pqxx::connection& connection,"
            << std::endl;

    {
        cpp_positive_indenter_scope s(indenter_);

        stream_ << indenter_ << "const boost::optional<versioned_key> id "
                << "= boost::optional<versioned_key>());"
                << std::endl;
    }
    utility_.blank_line();
}

void database_header::load(const class_view_model& vm) {
    stream_ << indenter_ << "std::vector<";

    cpp_qualified_name qualified_name(stream_);
    qualified_name.format(vm);

    stream_ << "> load(" << std::endl;

    {
        cpp_positive_indenter_scope s(indenter_);
        stream_ << indenter_ << "pqxx::connection& connection," << std::endl
                << indenter_ << "const boost::optional<versioned_key> id ="
                << "boost::optional<versioned_key>());" << std::endl;
    }
    utility_.blank_line();
}

void database_header::save(const class_view_model& vm) {
    stream_ << indenter_ << "void save(" << std::endl;
    {
        cpp_positive_indenter_scope s(indenter_);

        stream_ << indenter_ << "pqxx::connection& connection," << std::endl
                << indenter_ << "std::vector<";

        cpp_qualified_name qualified_name(stream_);
        qualified_name.format(vm);

        stream_ << "> values);" << std::endl;
    }
    utility_.blank_line();
}

void database_header::erase() {
    stream_ << indenter_ << "void erase(pqxx::connection& connection);";
    utility_.blank_line();

    stream_ << indenter_ << "void erase(pqxx::connection& connection, "
            << "versioned_key id);";
    utility_.blank_line();
}

void database_header::format(const file_view_model& vm) {
    boost::optional<view_models::class_view_model> o(vm.class_vm());
    if (!o)
        throw generation_failure(missing_class_view_model);

    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(vm.header_guard());
    utility_.blank_line();

    cpp_includes includes(stream_);
    includes.format(vm);

    {
        const view_models::class_view_model& cvm(*o);
        std::list<std::string> namespaces(cvm.namespaces());
        namespace_helper ns_helper(stream_, namespaces);
        utility_.blank_line();

        const std::string class_name(cvm.name() + name_suffix);
        stream_ << indenter_ << "class " << class_name << " ";
        utility_.open_scope();
        {
            cpp_positive_indenter_scope s(indenter_);
            compiler_generated_constuctors(cvm);

            utility_.private_access_specifier();
            format_sql();
            load_internal(cvm);
            erase_internal();

            utility_.public_access_specifier();
            load(cvm);
            save(cvm);
            erase();
            stream_ << "};";
        }
        utility_.blank_line(2);
    }
    utility_.blank_line();
    guards.format_end();
}

} } } } }
