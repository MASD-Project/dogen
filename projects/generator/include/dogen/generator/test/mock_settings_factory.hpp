/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_TEST_MOCK_SETTINGS_FACTORY_HPP
#define DOGEN_GENERATOR_TEST_MOCK_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/generator/config/settings.hpp"

namespace dogen {
namespace generator {
namespace test {

class mock_settings_factory {
public:
    mock_settings_factory() = delete;
    mock_settings_factory(const mock_settings_factory&) = delete;
    ~mock_settings_factory() = delete;
    mock_settings_factory(mock_settings_factory&&) = delete;
    mock_settings_factory& operator=(const mock_settings_factory&) = delete;

public:
    static config::output_settings build_output_settings(bool verbose = true);

    static config::troubleshooting_settings
    build_troubleshooting_settings(bool verbose = true);

    static config::cpp_settings build_cpp_settings(
        boost::filesystem::path src_dir,
        boost::filesystem::path include_dir,
        bool verbose = true);

    static config::modeling_settings build_modeling_settings(
        boost::filesystem::path target,
        std::string package_path,
        bool verbose = true);

    static config::settings build_settings(boost::filesystem::path target,
        boost::filesystem::path src_dir,
        boost::filesystem::path include_dir,
        std::string package_path,
        bool verbose = true);
};

} } }

#endif
