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
#include "dogen/sml/types/tags.hpp"

namespace dogen {
namespace sml {

const std::string tags::odb_pragma("ODB_PRAGMA");
const std::string tags::copyright_holder("COPYRIGHT");
const std::string tags::licence_name("LICENCE");
const std::string tags::modeline_group_name("MODELINE_GROUP");

const std::string tags::comment("COMMENT");
const std::string tags::identity_attribute("IDENTITY_ATTRIBUTE");
const std::string tags::generate_preamble("generate_preamble");
const std::string tags::original_parent_name("original_parent_name");
const std::string tags::is_original_parent_visitable(
    "is_original_parent_visitable");
const std::string tags::is_final("is_final");

const std::string tags::bool_true("true");
const std::string tags::bool_false("false");

const std::string tags::status_unsupported("unsupported");
const std::string tags::status_supported("supported");

const std::string tags::code_generation_marker::add_date_time(
    "code_generation_marker.add_date_time");
const std::string tags::code_generation_marker::add_warning(
    "code_generation_marker.add_warning");
const std::string tags::code_generation_marker::message(
    "code_generation_marker.message");

const std::string tags::cpp::split_project("cpp.split_project");
const std::string tags::cpp::source_directory("cpp.source_directory");
const std::string tags::cpp::include_directory("cpp.include_directory");
const std::string tags::cpp::header_file_extension("cpp.header_file_extension");
const std::string tags::cpp::implementation_file_extension(
    "cpp.implementation_file_extension");

const std::string tags::cpp::enable_facet_folders("cpp.enable_facet_folders");
const std::string tags::cpp::enable_unique_file_names(
    "cpp.enable_unique_file_names");
const std::string tags::cpp::forward_declaration_postfix(
    "cpp.forward_declaration_postfix");

/*
 * cpp::types
 */
const std::string tags::cpp::types::enabled("cpp.types.enabled");
const std::string tags::cpp::types::status("cpp.types.status");
const std::string tags::cpp::types::directory_name("cpp.types.directory_name");
const std::string tags::cpp::types::postfix("cpp.types.postfix");
const std::string tags::cpp::types::family("cpp.types.family");
const std::string tags::cpp::types::is_simple_type("cpp.types.is_simple_type");
const std::string tags::cpp::types::complete_name("cpp.types.complete_name");
const std::string tags::cpp::types::qualified_name("cpp.types.qualified_name");
const std::string tags::cpp::types::qualified_original_parent_name(
    "cpp.types.qualified_original_parent_name");

const std::string tags::cpp::types::generate_defaulted_functions(
    "cpp.types.generate_defaulted_functions");
const std::string tags::cpp::types::generate_explicit_default_constructor(
    "generate_explicit_default_constructor");
const std::string tags::cpp::types::generate_explicit_move_constructor(
    "cpp.types.generate_explicit_move_constructor");
const std::string tags::cpp::types::generate_explicit_destructor(
    "cpp.types.generate_explicit_destructor_constructor");
const std::string tags::cpp::types::generate_explicit_assignment_operator(
    "cpp.types.generate_explicit_assignment_operator");
const std::string tags::cpp::types::generate_complete_constructor(
    "cpp.types.generate_complete_constructor");
const std::string tags::cpp::types::generate_equality(
    "cpp.types.generate_equality");
const std::string tags::cpp::types::generate_swap("cpp.types.generate_swap");
const std::string tags::cpp::types::generate_friends(
    "cpp.types.generate_friends");
const std::string tags::cpp::types::generate_to_stream(
    "cpp.types.generate_to_stream");
const std::string tags::cpp::types::generate_accept(
    "cpp.types.generate_accept");

const std::string tags::cpp::types::header_file::generate(
    "cpp.types.header_file.generate");
const std::string tags::cpp::types::header_file::generate_header_guards(
    "cpp.types.header_file.generate_header_guards");
const std::string tags::cpp::types::header_file::overwrite(
    "cpp.types.header_file.overwrite");
const std::string tags::cpp::types::header_file::file_name(
    "cpp.types.header_file.file_name");
const std::string tags::cpp::types::header_file::is_system(
    "cpp.types.header_file.is_system");

const std::string tags::cpp::types::implementation_file::generate(
    "cpp.types.implementation_file.generate");
const std::string tags::cpp::types::implementation_file::overwrite(
    "cpp.types.implementation_file.overwrite");
const std::string tags::cpp::types::implementation_file::file_name(
    "cpp.types.implementation_file.file_name");
const std::string tags::cpp::types::implementation_file::is_system(
    "cpp.types.implementation_file.is_system");

const std::string tags::cpp::types::forward_declarations_file::generate(
    "cpp.types.forward_declarations_file.generate");
const std::string tags::cpp::types::forward_declarations_file::
generate_header_guards(
    "cpp.types.forward_declarations_file.generate_header_guards");
const std::string tags::cpp::types::forward_declarations_file::overwrite(
    "cpp.types.forward_declarations_file.overwrite");
const std::string tags::cpp::types::forward_declarations_file::file_name(
    "cpp.types.forward_declarations_file.file_name");
const std::string tags::cpp::types::forward_declarations_file::is_system(
    "cpp.types.forward_declarations_file.is_system");

const std::string tags::cpp::types::includers_file::generate(
    "cpp.types.includers_file.generate");
const std::string tags::cpp::types::includers_file::generate_header_guards(
    "cpp.types.includers_file.generate_header_guards");
const std::string tags::cpp::types::includers_file::overwrite(
    "cpp.types.includers_file.overwrite");
const std::string tags::cpp::types::includers_file::file_name(
    "cpp.types.includers_file.file_name");
const std::string tags::cpp::types::includers_file::is_system(
    "cpp.types.includers_file.is_system");

/*
 * cpp::hash::standard
 */
const std::string tags::cpp::hash::standard::enabled(
    "cpp.hash.standard.enabled");
const std::string tags::cpp::hash::standard::status("cpp.hash.standard.status");
const std::string tags::cpp::hash::standard::directory_name(
    "cpp.hash.standard.directory_name");
const std::string tags::cpp::hash::standard::postfix(
    "cpp.hash.standard.postfix");

const std::string tags::cpp::hash::standard::header_file::generate(
    "cpp.types.header_file.generate");
const std::string tags::cpp::hash::standard::header_file::
generate_header_guards("cpp.types.header_file.generate_header_guards");
const std::string tags::cpp::hash::standard::header_file::overwrite(
    "cpp.types.header_file.overwrite");
const std::string tags::cpp::hash::standard::header_file::file_name(
    "cpp.types.header_file.file_name");
const std::string tags::cpp::hash::standard::header_file::is_system(
    "cpp.types.header_file.is_system");

const std::string tags::cpp::hash::standard::implementation_file::generate(
    "cpp.hash.standard.implementation_file.generate");
const std::string tags::cpp::hash::standard::implementation_file::overwrite(
    "cpp.hash.standard.implementation_file.overwrite");
const std::string tags::cpp::hash::standard::implementation_file::file_name(
    "cpp.hash.standard.implementation_file.file_name");
const std::string tags::cpp::hash::standard::implementation_file::is_system(
    "cpp.hash.standard.implementation_file.is_system");

const std::string tags::cpp::hash::standard::forward_declarations_file::
generate("cpp.hash.standard.forward_declarations_file.generate");
const std::string tags::cpp::hash::standard::forward_declarations_file::
generate_header_guards(
    "cpp.hash.standard.forward_declarations_file.generate_header_guards");
const std::string tags::cpp::hash::standard::forward_declarations_file::
overwrite("cpp.hash.standard.forward_declarations_file.overwrite");
const std::string tags::cpp::hash::standard::forward_declarations_file::
file_name("cpp.hash.standard.forward_declarations_file.file_name");
const std::string tags::cpp::hash::standard::forward_declarations_file::
is_system("cpp.hash.standard.forward_declarations_file.is_system");

const std::string tags::cpp::hash::standard::includers_file::generate(
    "cpp.hash.standard.includers_file.generate");
const std::string tags::cpp::hash::standard::includers_file::
generate_header_guards(
    "cpp.hash.standard.includers_file.generate_header_guards");
const std::string tags::cpp::hash::standard::includers_file::overwrite(
    "cpp.hash.standard.includers_file.overwrite");
const std::string tags::cpp::hash::standard::includers_file::file_name(
    "cpp.hash.standard.includers_file.file_name");
const std::string tags::cpp::hash::standard::includers_file::is_system(
    "cpp.hash.standard.includers_file.is_system");

/*
 * cpp::serialization
 */
const std::string tags::cpp::serialization::boost::enabled(
    "cpp.serialization.boost.enabled");
const std::string tags::cpp::serialization::boost::status(
    "cpp.serialization.boost.status");
const std::string tags::cpp::serialization::boost::directory_name(
    "cpp.serialization.boost.directory_name");
const std::string tags::cpp::serialization::boost::postfix(
    "cpp.serialization.boost.postfix");

const std::string tags::cpp::serialization::boost::enable_xml_serialization(
    "cpp.serialization.boost.enable_xml_serialization");
const std::string tags::cpp::serialization::boost::header_file::generate(
    "cpp.serialization.boost.header_file.generate");
const std::string tags::cpp::serialization::boost::header_file::
generate_header_guards(
    "cpp.serialization.boost.header_file.generate_header_guards");
const std::string tags::cpp::serialization::boost::header_file::overwrite(
    "cpp.serialization.boost.header_file.overwrite");
const std::string tags::cpp::serialization::boost::header_file::file_name(
    "cpp.serialization.boost.header_file.file_name");
const std::string tags::cpp::serialization::boost::header_file::is_system(
    "cpp.serialization.boost.header_file.is_system");

const std::string tags::cpp::serialization::boost::implementation_file::
generate("cpp.serialization.boost.implementation_file.generate");
const std::string tags::cpp::serialization::boost::implementation_file::
overwrite("cpp.serialization.boost.implementation_file.overwrite");
const std::string tags::cpp::serialization::boost::implementation_file::
file_name("cpp.serialization.boost.implementation_file.file_name");
const std::string tags::cpp::serialization::boost::implementation_file::
is_system("cpp.serialization.boost.implementation_file.is_system");

const std::string tags::cpp::serialization::boost::forward_declarations_file::
generate("cpp.serialization.boost.forward_declarations_file.generate");
const std::string tags::cpp::serialization::boost::forward_declarations_file::
generate_header_guards(
    "cpp.serialization.boost.forward_declarations_file.generate_header_guards");
const std::string tags::cpp::serialization::boost::forward_declarations_file::
overwrite("cpp.serialization.boost.forward_declarations_file.overwrite");
const std::string tags::cpp::serialization::boost::forward_declarations_file::
file_name("cpp.serialization.boost.forward_declarations_file.file_name");
const std::string tags::cpp::serialization::boost::forward_declarations_file::
is_system("cpp.serialization.boost.forward_declarations_file.is_system");

const std::string tags::cpp::serialization::boost::includers_file::generate(
    "cpp.serialization.boost.includers_file.generate");
const std::string tags::cpp::serialization::boost::includers_file::
generate_header_guards(
    "cpp.serialization.boost.includers_file.generate_header_guards");
const std::string tags::cpp::serialization::boost::includers_file::overwrite(
    "cpp.serialization.boost.includers_file.overwrite");
const std::string tags::cpp::serialization::boost::includers_file::file_name(
    "cpp.serialization.boost.includers_file.file_name");
const std::string tags::cpp::serialization::boost::includers_file::is_system(
    "cpp.serialization.boost.includers_file.is_system");

/*
 * cpp::io
 */
const std::string tags::cpp::io::enabled("cpp.io.enabled");
const std::string tags::cpp::io::status("cpp.io.status");
const std::string tags::cpp::io::directory_name("cpp.io.directory_name");
const std::string tags::cpp::io::postfix("cpp.io.postfix");

const std::string tags::cpp::io::enable_integrated_io(
    "cpp.io.enable_integrated_io");

const std::string tags::cpp::io::header_file::generate(
    "cpp.io.header_file.generate");
const std::string tags::cpp::io::header_file::generate_header_guards(
    "cpp.io.header_file.generate_header_guards");
const std::string tags::cpp::io::header_file::overwrite(
    "cpp.io.header_file.overwrite");
const std::string tags::cpp::io::header_file::file_name(
    "cpp.io.header_file.file_name");
const std::string tags::cpp::io::header_file::is_system(
    "cpp.io.header_file.is_system");

const std::string tags::cpp::io::implementation_file::generate(
    "cpp.io.implementation_file.generate");
const std::string tags::cpp::io::implementation_file::overwrite(
    "cpp.io.implementation_file.overwrite");
const std::string tags::cpp::io::implementation_file::file_name(
    "cpp.io.implementation_file.file_name");
const std::string tags::cpp::io::implementation_file::is_system(
    "cpp.io.implementation_file.is_system");

const std::string tags::cpp::io::forward_declarations_file::generate(
    "cpp.io.forward_declarations_file.generate");
const std::string tags::cpp::io::forward_declarations_file::
generate_header_guards(
    "cpp.io.forward_declarations_file.generate_header_guards");
const std::string tags::cpp::io::forward_declarations_file::overwrite(
    "cpp.io.forward_declarations_file.overwrite");
const std::string tags::cpp::io::forward_declarations_file::file_name(
    "cpp.io.forward_declarations_file.file_name");
const std::string tags::cpp::io::forward_declarations_file::is_system(
    "cpp.io.forward_declarations_file.is_system");

const std::string tags::cpp::io::includers_file::generate(
    "cpp.io.includers_file.generate");
const std::string tags::cpp::io::includers_file::generate_header_guards(
    "cpp.io.includers_file.generate_header_guards");
const std::string tags::cpp::io::includers_file::overwrite(
    "cpp.io.includers_file.overwrite");
const std::string tags::cpp::io::includers_file::file_name(
    "cpp.io.includers_file.file_name");
const std::string tags::cpp::io::includers_file::is_system(
    "cpp.io.includers_file.is_system");

/*
 * cpp::test_data
 */
const std::string tags::cpp::test_data::enabled("cpp.test_data.enabled");
const std::string tags::cpp::test_data::status("cpp.test_data.status");
const std::string tags::cpp::test_data::directory_name(
    "cpp.test_data.directory_name");
const std::string tags::cpp::test_data::postfix("cpp.test_data.postfix");

const std::string tags::cpp::test_data::header_file::generate(
    "cpp.test_data.header_file.generate");
const std::string tags::cpp::test_data::header_file::generate_header_guards(
    "cpp.test_data.header_file.generate_header_guards");
const std::string tags::cpp::test_data::header_file::overwrite(
    "cpp.test_data.header_file.overwrite");
const std::string tags::cpp::test_data::header_file::file_name(
    "cpp.test_data.header_file.file_name");
const std::string tags::cpp::test_data::header_file::is_system(
    "cpp.test_data.header_file.is_system");

const std::string tags::cpp::test_data::implementation_file::generate(
    "cpp.test_data.implementation_file.generate");
const std::string tags::cpp::test_data::implementation_file::overwrite(
    "cpp.test_data.implementation_file.overwrite");
const std::string tags::cpp::test_data::implementation_file::file_name(
    "cpp.test_data.implementation_file.file_name");
const std::string tags::cpp::test_data::implementation_file::is_system(
    "cpp.test_data.implementation_file.is_system");

const std::string tags::cpp::test_data::forward_declarations_file::generate(
    "cpp.test_data.forward_declarations_file.generate");
const std::string tags::cpp::test_data::forward_declarations_file::
generate_header_guards(
    "cpp.test_data.forward_declarations_file.generate_header_guards");
const std::string tags::cpp::test_data::forward_declarations_file::overwrite(
    "cpp.test_data.forward_declarations_file.overwrite");
const std::string tags::cpp::test_data::forward_declarations_file::file_name(
    "cpp.test_data.forward_declarations_file.file_name");
const std::string tags::cpp::test_data::forward_declarations_file::is_system(
    "cpp.test_data.forward_declarations_file.is_system");

const std::string tags::cpp::test_data::includers_file::generate(
    "cpp.test_data.includers_file.generate");
const std::string tags::cpp::test_data::includers_file::generate_header_guards(
    "cpp.test_data.includers_file.generate_header_guards");
const std::string tags::cpp::test_data::includers_file::overwrite(
    "cpp.test_data.includers_file.overwrite");
const std::string tags::cpp::test_data::includers_file::file_name(
    "cpp.test_data.includers_file.file_name");
const std::string tags::cpp::test_data::includers_file::is_system(
    "cpp.test_data.includers_file.is_system");

/*
 * cpp::odb
 */
const std::string tags::cpp::odb::enabled("cpp.odb.enabled");
const std::string tags::cpp::odb::status("cpp.odb.status");
const std::string tags::cpp::odb::directory_name("cpp.odb.directory_name");
const std::string tags::cpp::odb::postfix("cpp.odb.postfix");

const std::string tags::cpp::odb::header_file::generate(
    "cpp.odb.header_file.generate");
const std::string tags::cpp::odb::header_file::generate_header_guards(
    "cpp.odb.header_file.generate_header_guards");
const std::string tags::cpp::odb::header_file::overwrite(
    "cpp.odb.header_file.overwrite");
const std::string tags::cpp::odb::header_file::file_name(
    "cpp.odb.header_file.file_name");
const std::string tags::cpp::odb::header_file::is_system(
    "cpp.odb.header_file.is_system");

const std::string tags::cpp::odb::includers_file::generate(
    "cpp.odb.includers_file.generate");
const std::string tags::cpp::odb::includers_file::generate_header_guards(
    "cpp.odb.includers_file.generate_header_guards");
const std::string tags::cpp::odb::includers_file::overwrite(
    "cpp.odb.includers_file.overwrite");
const std::string tags::cpp::odb::includers_file::file_name(
    "cpp.odb.includers_file.file_name");
const std::string tags::cpp::odb::includers_file::is_system(
    "cpp.odb.includers_file.is_system");

} }
