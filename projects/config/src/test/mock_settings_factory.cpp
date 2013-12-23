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
#include "dogen/config/test/mock_settings_factory.hpp"

namespace {

const std::string empty;
const std::string header_extension(".hpp");
const std::string source_extension(".cpp");
const std::string domain_facet_folder("types");
const std::string hash_facet_folder("hash");
const std::string io_facet_folder("io");
const std::string serialization_facet_folder("serialization");
const std::string test_data_facet_folder("test_data");
const std::string odb_facet_folder("odb");

}

namespace dogen {
namespace config {
namespace test {

std::set<cpp_facet_types>
mock_settings_factory::build_facets(const bool all) {
    if (all)
        return std::set<cpp_facet_types> {
            cpp_facet_types::types,
            cpp_facet_types::hash,
            cpp_facet_types::serialization,
            cpp_facet_types::io,
            cpp_facet_types::test_data,
            cpp_facet_types::odb
        };

    return std::set<cpp_facet_types> {
        cpp_facet_types::types,
        cpp_facet_types::hash,
    };
}

modeling_settings mock_settings_factory::
build_modeling_settings(boost::filesystem::path target,
    std::string module_path, bool verbose) {
    modeling_settings r;
    r.verbose(verbose);
    r.external_module_path(module_path);
    r.target(target);
    return r;
}

output_settings mock_settings_factory::build_output_settings(bool verbose) {
    output_settings r;
    r.verbose(verbose);
    r.output_to_stdout(false);
    r.output_to_file(true);
    r.delete_extra_files(true);
    r.force_write(false);
    return r;
}

troubleshooting_settings
mock_settings_factory::build_troubleshooting_settings(bool verbose) {
    troubleshooting_settings r;
    r.verbose(verbose);
    return r;
}

cpp_settings mock_settings_factory::build_cpp_settings() {
    return build_cpp_settings(empty, empty);
}

cpp_settings mock_settings_factory::build_cpp_settings(
    boost::filesystem::path src_dir,
    boost::filesystem::path include_dir,
    bool verbose) {

    cpp_settings r;
    r.verbose(verbose);
    r.split_project(true);
    r.source_directory(src_dir);
    r.include_directory(include_dir);

    std::set<cpp_facet_types> f = {
        cpp_facet_types::types,
        cpp_facet_types::hash,
        cpp_facet_types::serialization,
        cpp_facet_types::io,
        cpp_facet_types::test_data,
        cpp_facet_types::odb
    };
    r.enabled_facets(f);
    r.header_extension(header_extension);
    r.source_extension(source_extension);
    r.domain_facet_folder(domain_facet_folder);
    r.hash_facet_folder(hash_facet_folder);
    r.io_facet_folder(io_facet_folder);
    r.serialization_facet_folder(serialization_facet_folder);
    r.test_data_facet_folder(test_data_facet_folder);
    r.odb_facet_folder(odb_facet_folder);
    r.disable_eos_serialization(true);
    return r;
}

cpp_settings mock_settings_factory::build_cpp_settings(
    boost::filesystem::path project_dir,
    bool verbose) {

    cpp_settings r(build_cpp_settings(empty, empty, verbose));
    r.split_project(false);
    r.project_directory(project_dir);
    return r;
}

settings mock_settings_factory::build_settings(boost::filesystem::path target,
    boost::filesystem::path src_dir,
    boost::filesystem::path include_dir,
    std::string module_path,
    bool verbose) {
    settings r;
    r.modeling(build_modeling_settings(target, module_path, verbose));
    r.cpp(build_cpp_settings(src_dir, include_dir, verbose));
    r.troubleshooting(build_troubleshooting_settings(verbose));
    r.output(build_output_settings(verbose));
    return r;
}

settings mock_settings_factory::build_settings(boost::filesystem::path target,
    boost::filesystem::path project_dir,
    std::string module_path,
    bool verbose) {
    settings r;
    r.modeling(build_modeling_settings(target, module_path, verbose));
    r.cpp(build_cpp_settings(project_dir, verbose));
    r.troubleshooting(build_troubleshooting_settings(verbose));
    r.output(build_output_settings(verbose));
    return r;
}

} } }
