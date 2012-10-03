/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <sstream>
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/generator/backends/cpp/cpp_location_manager.hpp"

namespace {

const std::string empty;
const std::string domain_postfix;
const std::string io_postfix("_io");
const std::string hash_postfix("_hash");
const std::string serialization_postfix("_ser");
const std::string test_data_postfix("_sequence");
const std::string database_postfix("_db");

const std::string hpp_extension(".hpp");
const std::string cpp_extension(".cpp");

const std::string invalid_facet_types_enum("Invalid value for cpp_facet_types");
const std::string invalid_file_types_enum("Invalid value for cpp_file_types");
}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

cpp_location_manager::cpp_location_manager(std::string model_name,
    config::cpp_settings settings) :
    model_name_(model_name), settings_(settings) { }

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
    case cpp_facet_types::database:
        return settings_.database_facet_folder();
        break;
    default:
        using utility::exception::invalid_enum_value;
        throw invalid_enum_value(invalid_facet_types_enum);
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
    case cpp_facet_types::database: return database_postfix; break;
    default:
        using utility::exception::invalid_enum_value;
        throw invalid_enum_value(invalid_facet_types_enum);
    }
}

boost::filesystem::path
cpp_location_manager::file_type_directory(cpp_file_types file_type) const {
    switch(file_type) {
    case cpp_file_types::header: return settings_.include_directory(); break;
    case cpp_file_types::implementation:
        return settings_.source_directory(); break;
    default:
        using utility::exception::invalid_enum_value;
        throw invalid_enum_value(invalid_file_types_enum);
    }
}

std::string cpp_location_manager::extension(cpp_file_types file_type) const {
    switch(file_type) {
    case cpp_file_types::header: return settings_.header_extension(); break;
    case cpp_file_types::implementation:
        return settings_.source_extension(); break;
    default:
        using utility::exception::invalid_enum_value;
        throw invalid_enum_value(invalid_file_types_enum);
    }
}

boost::filesystem::path
cpp_location_manager::relative_path(cpp_location_request request) const {

    boost::filesystem::path r;
    for(auto n : request.external_package_path())
        r /= n;

    r /= request.model_name();
    r /= facet_directory(request.facet_type());

    for(auto n : request.package_path())
        r /= n;

    std::ostringstream stream;
    stream << request.file_name() << facet_postfix(request.facet_type())
           << extension(request.file_type());
    r /= stream.str();

    return r;
}

boost::filesystem::path
cpp_location_manager::absolute_path(cpp_location_request request) const {

    auto r(file_type_directory(request.file_type()));
    r /= relative_path(request);
    return r;
}

boost::filesystem::path
cpp_location_manager::absolute_path(std::string name) const {
    return settings_.source_directory() / model_name_ / name;
}

std::vector<boost::filesystem::path>
cpp_location_manager::managed_directories() const {
    std::vector<boost::filesystem::path> r;

    r.reserve(2);
    r.push_back(settings_.source_directory() /= model_name_);
    r.push_back(settings_.include_directory() /= model_name_);

    return r;
}

} } } }
