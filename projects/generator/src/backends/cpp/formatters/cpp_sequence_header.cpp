/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_header_guards.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_namespace_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_sequence_header.hpp"

namespace {

const bool is_system(false);
const bool is_user(false);
const std::string generator_include("dogen/utility/test_data/generator.hpp");
const std::string sequence_include("dogen/utility/test_data/sequence.hpp");
const std::string detail_ns("detail");

const std::string missing_class_view_model(
    "File view model must contain a class view model");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

sequence_header::
sequence_header(std::ostream& stream) :
    stream_(stream),
    facet_type_(cpp_facet_types::test_data),
    file_type_(cpp_file_types::header),
    utility_(stream_, indenter_) {
}

file_formatter::shared_ptr sequence_header::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new sequence_header(stream));
}

void sequence_header::generator_class(view_models::class_view_model vm) {
    const std::string class_name(vm.name() + "_generator");

    stream_ << indenter_ << "class " << class_name << " ";
    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        utility_.public_access_specifier();

        stream_ << indenter_ << "typedef ";
        cpp_qualified_name qualified_name(stream_);
        qualified_name.format(vm);
        stream_ << " value_type;" << std::endl;
        utility_.blank_line();

        utility_.public_access_specifier();
        stream_ << indenter_
                << "value_type next_term(const unsigned int position);"
                << std::endl;

        stream_ << indenter_ << "unsigned int length() const;" << std::endl;
    }
    stream_ << "};";
}

void sequence_header::sequence_typedefs(view_models::class_view_model vm) {
    stream_ << indenter_ << "typedef dogen::utility::test_data::sequence<"
            << std::endl;

    cpp_positive_indenter_scope s(indenter_);
    stream_ << indenter_ << "detail::" << vm.name() << "_generator> " << vm.name()
            << "_sequence;" << std::endl;
}

void sequence_header::format(view_models::file_view_model vm) {
    boost::optional<view_models::class_view_model> o(vm.class_vm());
    if (!o)
        throw generation_failure(missing_class_view_model);

    licence licence(stream_);
    licence.format();

    header_guards guards(stream_);
    guards.format_start(vm.header_guard());
    utility_.blank_line();

    std::list<std::string> user_dependencies(vm.user_dependencies());
    user_dependencies.push_back(generator_include);
    user_dependencies.push_back(sequence_include);

    cpp_includes includes(stream_);
    includes.format(vm.system_dependencies(), is_system);
    includes.format(user_dependencies, is_user);
    utility_.blank_line();

    {
        const view_models::class_view_model& cvm(*o);
        std::list<std::string> namespaces(cvm.namespaces());
        namespace_helper ns_helper(stream_, namespaces);
        utility_.blank_line();

        {
            typedef std::list<std::string> list;
            namespace_helper ns_helper(stream_, list { detail_ns});
            utility_.blank_line();
            generator_class(cvm);
            utility_.blank_line(2);
        }
        utility_.blank_line(2);
        sequence_typedefs(cvm);
        utility_.blank_line();
    }
    utility_.blank_line(2);
    guards.format_end();
}

} } } } }
