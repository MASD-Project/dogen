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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/config/io/cpp_settings_io.hpp"
#include "dogen/sml_to_cpp/types/locator.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml_to_cpp.locator"));

const std::string empty;
const std::string domain_postfix;
const std::string io_postfix("_io");
const std::string hash_postfix("_hash");
const std::string serialization_postfix("_ser");
const std::string test_data_postfix("_td");
const std::string odb_postfix("_pragmas");
const std::string forward_decls_postfix("_fwd");
const std::string visitor_postfix("_visitor");

const std::string src_dir("src");
const std::string include_dir("include");

const std::string absolute_path_with_split(
    "Absolute path cannot be used with split projects");
const std::string invalid_facet_types("Invalid value for cpp_facet_types");
const std::string invalid_file_types("Invalid value for file_types");
const std::string invalid_aspect_types("Invalid value for aspect_types");

}

namespace dogen {
namespace sml_to_cpp {

using utility::exception::invalid_enum_value;

locator::locator(locator&& rhs)
  : model_name_(std::move(rhs.model_name_)),
    settings_(std::move(rhs.settings_)),
    source_directory_(std::move(rhs.source_directory_)),
    include_directory_(std::move(rhs.include_directory_)) { }

locator::locator(const std::string& model_name,
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

std::string locator::facet_directory(const config::cpp_facet_types ft) const {
    if (settings_.disable_facet_folders())
        return empty;

    using config::cpp_facet_types;
    switch(ft) {
    case cpp_facet_types::io: return settings_.io_facet_folder(); break;
    case cpp_facet_types::types: return settings_.domain_facet_folder(); break;
    case cpp_facet_types::hash: return settings_.hash_facet_folder(); break;
    case cpp_facet_types::serialization:
        return settings_.serialization_facet_folder();
        break;
    case cpp_facet_types::test_data:
        return settings_.test_data_facet_folder();
        break;
    case cpp_facet_types::odb: return settings_.odb_facet_folder(); break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_facet_types;
        BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_facet_types));
    }
}

std::string locator::
facet_postfix(const config::cpp_facet_types ft) const {
    if (settings_.disable_unique_file_names())
        return empty;

    using config::cpp_facet_types;
    switch(ft) {
    case cpp_facet_types::io: return io_postfix; break;
    case cpp_facet_types::types: return domain_postfix; break;
    case cpp_facet_types::hash: return hash_postfix; break;
    case cpp_facet_types::serialization: return serialization_postfix; break;
    case cpp_facet_types::test_data: return test_data_postfix; break;
    case cpp_facet_types::odb: return odb_postfix; break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_facet_types;
        BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_facet_types));
    }
}

std::string
locator::aspect_postfix(const cpp::formattables::aspect_types at) const {
    if (settings_.disable_unique_file_names())
        return empty;

    using cpp::formattables::aspect_types;
    switch(at) {
    case aspect_types::forward_decls: return forward_decls_postfix; break;
    case aspect_types::main:
        return empty; break;

    default:
        BOOST_LOG_SEV(lg, error) << invalid_aspect_types;
        BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_aspect_types));
    }
}

boost::filesystem::path
locator::file_type_directory(const cpp::formattables::file_types flt) const {
    using cpp::formattables::file_types;
    switch(flt) {
    case file_types::header: return include_directory_; break;
    case file_types::implementation: return source_directory_; break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_file_types;
        BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_file_types));
    }
}

std::string locator::extension(const cpp::formattables::file_types flt) const {
    using cpp::formattables::file_types;
    switch(flt) {
    case file_types::header: return settings_.header_extension(); break;
    case file_types::implementation:
        return settings_.source_extension(); break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_file_types;
        BOOST_THROW_EXCEPTION(invalid_enum_value(invalid_file_types));
    }
}

boost::filesystem::path locator::relative_logical_path(
    const cpp::formattables::content_descriptor& cd) const {
    boost::filesystem::path r;

    if (settings_.split_project()) {
        for(auto n : cd.name().external_module_path())
            r /= n;
        return r / relative_physical_path(cd);
    }

    return relative_physical_path(cd);
}

boost::filesystem::path locator::relative_physical_path(
    const cpp::formattables::content_descriptor& cd) const {
    boost::filesystem::path r;
    using cpp::formattables::file_types;
    if (settings_.split_project())
        r /= cd.name().model_name();
    else if (cd.file_type() == file_types::header) {
        for(auto n : cd.name().external_module_path())
            r /= n;
        r /= cd.name().model_name();
    }

    r /= facet_directory(cd.facet_type());
    for(auto n : cd.name().module_path())
        r /= n;

    std::ostringstream stream;
    stream << cd.name().simple_name()
           << aspect_postfix(cd.aspect_type())
           << facet_postfix(cd.facet_type())
           << extension(cd.file_type());
    r /= stream.str();

    return r;
}

boost::filesystem::path
locator::absolute_path(const cpp::formattables::content_descriptor& cd) const {

    auto r(file_type_directory(cd.file_type()));
    r /= relative_physical_path(cd);
    return r;
}

boost::filesystem::path
locator::absolute_path_to_src(const std::string& name) const {
    if (settings_.split_project())
        return source_directory_ / model_name_ / name;
    return source_directory_ / name;
}

boost::filesystem::path
locator::absolute_path_to_include(const std::string& name) const {
    if (settings_.split_project())
        return include_directory_ / model_name_ / name;
    return include_directory_ / name;
}

boost::filesystem::path
locator::absolute_path(const std::string& name) const {
    if (settings_.split_project()) {
        BOOST_LOG_SEV(lg, error) << absolute_path_with_split;
        BOOST_THROW_EXCEPTION(
            utility::exception::exception(absolute_path_with_split));
    }
    return settings_.project_directory() / model_name_ / name;
}

std::forward_list<boost::filesystem::path>
locator::managed_directories() const {
    std::forward_list<boost::filesystem::path> r;

    if (settings_.split_project()) {
        r.push_front(source_directory_ / model_name_);
        r.push_front(include_directory_ / model_name_);
    } else {
        r.push_front(settings_.project_directory() / model_name_);
    }

    return r;
}

} }
