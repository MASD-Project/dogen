/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_CPP_LOCATION_REQUEST_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_CPP_LOCATION_REQUEST_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/generator/backends/cpp/cpp_facet_types.hpp"
#include "dogen/generator/backends/cpp/cpp_file_types.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

class cpp_location_request {
public:
    cpp_location_request(const cpp_location_request&) = default;
    ~cpp_location_request() = default;
    cpp_location_request(cpp_location_request&&) = default;
    cpp_location_request& operator=(const cpp_location_request&) = default;

    cpp_location_request() :
        facet_type_(cpp_facet_types::invalid),
        file_type_(cpp_file_types::invalid) { }

public:
    void facet_type(cpp_facet_types value) { facet_type_ = value; }
    cpp_facet_types facet_type() const { return facet_type_; }

    void file_type(cpp_file_types value) { file_type_ = value; }
    cpp_file_types file_type() const { return file_type_; }

    void model_name(std::string value) { model_name_ = value; }
    std::string model_name() const { return model_name_; }

    void external_package_path(std::list<std::string> value) {
        external_package_path_ = value;
    }
    std::list<std::string> external_package_path() const {
        return external_package_path_;
    }

    void package_path(std::list<std::string> value) { package_path_ = value; }
    std::list<std::string> package_path() const { return package_path_; }

    void file_name(std::string value) { file_name_ = value; }
    std::string file_name() const { return file_name_; }


private:
    cpp_facet_types facet_type_;
    cpp_file_types file_type_;
    std::string model_name_;
    std::list<std::string> external_package_path_;
    std::list<std::string> package_path_;
    std::string file_name_;
};

} } } }

#endif
