/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/generator/test/mock_settings_factory.hpp"

namespace {

const std::string header_extension(".hpp");
const std::string source_extension(".cpp");
const std::string domain_facet_folder("domain");
const std::string hash_facet_folder("hash");
const std::string io_facet_folder("io");
const std::string serialization_facet_folder("serialization");
const std::string test_data_facet_folder("test_data");
const std::string database_facet_folder("database");

}

namespace dogen {
namespace generator {
namespace test {

config::modeling_settings mock_settings_factory::
build_modeling_settings(boost::filesystem::path target,
    std::string package_path, bool verbose) {
    config::modeling_settings r;
    r.verbose(verbose);
    r.external_package_path(package_path);
    r.target(target);
    return r;
}


config::output_settings
mock_settings_factory::build_output_settings(bool verbose) {
    config::output_settings r;
    r.verbose(verbose);
    r.output_to_stdout(false);
    r.output_to_file(true);
    r.delete_extra_files(true);
    r.force_write(false);
    return r;
}

config::troubleshooting_settings mock_settings_factory::
build_troubleshooting_settings(bool verbose) {
    config::troubleshooting_settings r;
    r.verbose(verbose);
    return r;
}

config::cpp_settings mock_settings_factory::build_cpp_settings(
    boost::filesystem::path src_dir,
    boost::filesystem::path include_dir,
    bool verbose) {

    config::cpp_settings r;
    r.verbose(verbose);
    r.split_project(true);
    r.source_directory(src_dir);
    r.include_directory(include_dir);

    using backends::cpp::cpp_facet_types;
    std::set<cpp_facet_types> f = {
        cpp_facet_types::domain,
        cpp_facet_types::hash,
        cpp_facet_types::serialization,
        cpp_facet_types::io,
        cpp_facet_types::test_data,
        cpp_facet_types::database
    };
    r.enabled_facets(f);
    r.header_extension(header_extension);
    r.source_extension(source_extension);
    r.domain_facet_folder(domain_facet_folder);
    r.hash_facet_folder(hash_facet_folder);
    r.io_facet_folder(io_facet_folder);
    r.serialization_facet_folder(serialization_facet_folder);
    r.test_data_facet_folder(test_data_facet_folder);
    r.database_facet_folder(database_facet_folder);
    return r;
}

config::settings
mock_settings_factory::build_settings(boost::filesystem::path target,
    boost::filesystem::path src_dir,
    boost::filesystem::path include_dir,
    std::string package_path,
    bool verbose) {
    config::settings r;
    r.modeling(build_modeling_settings(target, package_path, verbose));
    r.cpp(build_cpp_settings(src_dir, include_dir, verbose));
    r.troubleshooting(build_troubleshooting_settings(verbose));
    r.output(build_output_settings(verbose));
    return r;
}

} } }
