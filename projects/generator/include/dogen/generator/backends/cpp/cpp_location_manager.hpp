/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_LOCATION_MANAGER_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_LOCATION_MANAGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/generator/config/cpp_settings.hpp"
#include "dogen/generator/backends/cpp/cpp_location_request.hpp"
#include "dogen/generator/backends/cpp/cpp_facet_types.hpp"
#include "dogen/generator/backends/cpp/cpp_file_types.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

/**
 * @brief Manages the file names for all generated files and all the
 * pre-processor includes.
 */
class cpp_location_manager {
public:
    cpp_location_manager() = delete;
    cpp_location_manager(const cpp_location_manager&) = default;
    ~cpp_location_manager() = default;
    cpp_location_manager(cpp_location_manager&&) = default;
    cpp_location_manager& operator=(const cpp_location_manager&) = delete;

public:
    cpp_location_manager(std::string model_name, config::cpp_settings settings);

private:
    std::string facet_directory(cpp_facet_types facet) const;
    std::string facet_postfix(cpp_facet_types facet) const;
    boost::filesystem::path file_type_directory(cpp_file_types file_type) const;
    std::string extension(cpp_file_types file_type) const;

public:
    boost::filesystem::path relative_path(cpp_location_request request) const;
    boost::filesystem::path absolute_path(cpp_location_request request) const;
    boost::filesystem::path absolute_path(std::string name) const;

private:
    const std::string model_name_;
    config::cpp_settings settings_;
};

} } } }

#endif
