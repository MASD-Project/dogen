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
#include <sstream>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/generator/backends/cpp/cpp_location_manager.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("location_manager"));

const std::string empty;
const std::string domain_postfix;
const std::string io_postfix("_io");
const std::string hash_postfix("_hash");
const std::string serialization_postfix("_ser");
const std::string test_data_postfix("_td");
const std::string forward_decls_postfix("_fwd");

const std::string src_dir("src");
const std::string include_dir("include");

const std::string invalid_facet_types("Invalid value for cpp_facet_types");
const std::string invalid_file_types("Invalid value for cpp_file_types");
const std::string invalid_aspect_types("Invalid value for cpp_aspect_types");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

using utility::exception::invalid_enum_value;

cpp_location_manager::cpp_location_manager(const std::string& model_name,
    const config::cpp_settings& settings) :
    model_name_(model_name), settings_(settings) {

    if (settings_.split_project()) {
        source_directory_ = settings_.source_directory();
        include_directory_ = settings_.include_directory();
    } else {
        source_directory_ = settings_.project_directory() / model_name_;
        source_directory_ /= src_dir;

        include_directory_ = settings_.project_directory() / model_name_;
        include_directory_ /= include_dir;
    }

    BOOST_LOG_SEV(lg, debug)
        << "Initial configuration:"
        << " settings: " << settings_
        << " include_directory: " << include_directory_
        << " source_directory_: " << source_directory_
        << " model name: " << model_name;
}

std::string cpp_location_manager::facet_directory(cpp_facet_types facet) const {
    if (settings_.disable_facet_folders())
        return empty;

    switch(facet) {
    case cpp_facet_types::io: return settings_.io_facet_folder(); break;
    case cpp_facet_types::domain: return settings_.domain_facet_folder(); break;
    case cpp_facet_types::hash: return settings_.hash_facet_folder(); break;
    case cpp_facet_types::serialization:
        return settings_.serialization_facet_folder();
        break;
    case cpp_facet_types::test_data:
        return settings_.test_data_facet_folder();
        break;
    default:
        throw invalid_enum_value(invalid_facet_types);
    }
}

std::string cpp_location_manager::facet_postfix(cpp_facet_types facet) const {
    if (settings_.disable_unique_file_names())
        return empty;

    switch(facet) {
    case cpp_facet_types::io: return io_postfix; break;
    case cpp_facet_types::domain: return domain_postfix; break;
    case cpp_facet_types::hash: return hash_postfix; break;
    case cpp_facet_types::serialization: return serialization_postfix; break;
    case cpp_facet_types::test_data: return test_data_postfix; break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_facet_types;
        throw invalid_enum_value(invalid_facet_types);
    }
}

std::string
cpp_location_manager::aspect_postfix(cpp_aspect_types aspect) const {
    if (settings_.disable_unique_file_names())
        return empty;

    switch(aspect) {
    case cpp_aspect_types::main: return empty; break;
    case cpp_aspect_types::includers: return empty; break;
    case cpp_aspect_types::forward_decls: return forward_decls_postfix; break;
    case cpp_aspect_types::registrar: return empty; break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_aspect_types;
        throw invalid_enum_value(invalid_aspect_types);
    }
}

boost::filesystem::path
cpp_location_manager::file_type_directory(cpp_file_types file_type) const {
    switch(file_type) {
    case cpp_file_types::header: return include_directory_; break;
    case cpp_file_types::implementation: return source_directory_; break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_file_types;
        throw invalid_enum_value(invalid_file_types);
    }
}

std::string cpp_location_manager::extension(cpp_file_types file_type) const {
    switch(file_type) {
    case cpp_file_types::header: return settings_.header_extension(); break;
    case cpp_file_types::implementation:
        return settings_.source_extension(); break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_file_types;
        throw invalid_enum_value(invalid_file_types);
    }
}

boost::filesystem::path cpp_location_manager::relative_logical_path(
    const cpp_location_request& request) const {
    boost::filesystem::path r;

    if (settings_.split_project()) {
        for(auto n : request.external_package_path())
            r /= n;
        return r / relative_physical_path(request);
    }

    return relative_physical_path(request);
}

boost::filesystem::path cpp_location_manager::relative_physical_path(
    const cpp_location_request& request) const {
    boost::filesystem::path r;

    if (settings_.split_project())
        r /= request.model_name();
    else if (request.file_type() == cpp_file_types::header) {
        for(auto n : request.external_package_path())
            r /= n;
        r /= request.model_name();
    }

    r /= facet_directory(request.facet_type());
    for(auto n : request.package_path())
        r /= n;

    std::ostringstream stream;
    stream << request.file_name()
           << aspect_postfix(request.aspect_type())
           << facet_postfix(request.facet_type())
           << extension(request.file_type());
    r /= stream.str();

    return r;
}

boost::filesystem::path
cpp_location_manager::absolute_path(const cpp_location_request& request) const {

    auto r(file_type_directory(request.file_type()));
    r /= relative_physical_path(request);
    return r;
}

boost::filesystem::path
cpp_location_manager::absolute_path_to_src(const std::string& name) const {
    if (settings_.split_project())
        return source_directory_ / model_name_ / name;
    return source_directory_ / name;
}

boost::filesystem::path
cpp_location_manager::absolute_path_to_include(const std::string& name) const {
    if (settings_.split_project())
        return include_directory_ / model_name_ / name;
    return include_directory_ / name;
}

std::vector<boost::filesystem::path>
cpp_location_manager::managed_directories() const {
    std::vector<boost::filesystem::path> r;

    if (settings_.split_project()) {
        r.reserve(2);
        r.push_back(source_directory_ / model_name_);
        r.push_back(include_directory_ / model_name_);
    } else {
        r.push_back(settings_.project_directory() / model_name_);
    }

    return r;
}

} } } }
