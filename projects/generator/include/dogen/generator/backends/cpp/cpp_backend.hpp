/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_BACKEND_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_BACKEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <utility>
#include <string>
#include <sstream>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/domain/model.hpp"
#include "dogen/generator/config/cpp_settings.hpp"
#include "dogen/generator/backends/cpp/cpp_location_manager.hpp"
#include "dogen/generator/backends/cpp/view_models/cmakelists_view_model.hpp"
#include "dogen/generator/backends/cpp/view_models/file_view_model.hpp"
#include "dogen/generator/backends/backend.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

class cpp_backend : public backend {
public:
    cpp_backend() = delete;
    cpp_backend(const cpp_backend&) = default;
    cpp_backend(cpp_backend&&) = default;
    cpp_backend& operator=(const cpp_backend&) = default;

public:
    cpp_backend(sml::model model, config::cpp_settings settings);
    virtual ~cpp_backend() noexcept {}

public:
    static backend::ptr
    create(sml::model model, config::cpp_settings settings);

private:
    void log_formating_view(std::string view_name) const;
    void log_started() const;
    void log_finished() const;
    void log_cmakelists_disabled() const;
    void log_file_views(unsigned int how_many) const;

private:
    backend::value_entry_type
    generate_file_view_model(view_models::file_view_model vm) const;
    backend::value_type generate_file_view_models() const;
    backend::value_entry_type generate_cmakelists() const;

public:
    backend::value_type generate() override;
    std::vector<boost::filesystem::path> managed_directories() const override;

private:
    const sml::model model_;
    config::cpp_settings settings_;
    const cpp_location_manager location_manager_;
};

} } } }

#endif
