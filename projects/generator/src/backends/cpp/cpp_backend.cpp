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
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/backends/cpp/formatters/factory.hpp"
#include "dogen/generator/backends/cpp/formatters/file_formatter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_cmakelists.hpp"
#include "dogen/generator/backends/cpp/view_models/sml_to_cpp_view_model.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/backends/cpp/cpp_backend.hpp"

using namespace dogen::utility::log;

namespace {

static logger lg(logger_factory("cpp_backend"));

const std::string unsupported_aspect_type("Unsupported aspect type");
const std::string domain_facet_must_be_enabled("Domain facet must be enabled");
const std::string integrated_io_incompatible_with_io_facet(
    "Integrated IO cannot be used with the IO facet");
}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

cpp_backend::
cpp_backend(const sml::model& model, const config::cpp_settings& settings) :
    model_(model), settings_(settings),
    location_manager_(model.name(), settings_) {

    if (settings_.use_integrated_io()) {
        const auto f(settings_.enabled_facets());
        const bool has_io_facet(f.find(cpp_facet_types::io) != f.end());
        if (has_io_facet) {
            throw generation_failure(
                integrated_io_incompatible_with_io_facet);
        }
    }

    const auto f(settings_.enabled_facets());
    if (f.find(cpp_facet_types::domain) == f.end()) {
        throw generation_failure(domain_facet_must_be_enabled);
    }
}

backend::ptr cpp_backend::
create(const sml::model& model, const config::cpp_settings& settings) {
    return backend::ptr(new cpp_backend(model, settings));
}

void cpp_backend::log_formating_view(const std::string& view_name) const {

    BOOST_LOG_SEV(lg, debug) << "Formatting file view: " << view_name;
}

void cpp_backend::log_started() const {
    BOOST_LOG_SEV(lg, info) << "C++ backend started.";
}

void cpp_backend::log_finished() const {
    BOOST_LOG_SEV(lg, info) << "C++ backend finished.";
}

void cpp_backend::log_cmakelists_disabled() const {
    BOOST_LOG_SEV(lg, info) << "CMakeLists.txt generation disabled.";
}

void cpp_backend::log_file_views(unsigned int how_many) const {
    BOOST_LOG_SEV(lg, debug) << "File views returned by SML to C++ view model"
                             << " transformer: " << how_many;
}

backend::value_entry_type cpp_backend::generate_cmakelists() const {
    view_models::cmakelists_view_model vm;
    vm.file_path(location_manager_.absolute_path(vm.file_name()));
    vm.model_name(model_.name());

    log_formating_view(vm.file_path().string());
    std::ostringstream stream;
    formatters::cpp_cmakelists formatter(stream);
    formatter.format(vm);
    return std::make_pair(vm.file_path(), stream.str());
}

backend::value_entry_type cpp_backend::
generate_file_view_model(const view_models::file_view_model& vm) const {
    log_formating_view(vm.file_path().string());
    std::ostringstream stream;
    const auto f(settings_.enabled_facets());
    const bool disable_io(f.find(cpp_facet_types::io) == f.end());
    formatters::factory factory(settings_, disable_io);
    formatters::file_formatter::shared_ptr ff;

    switch (vm.aspect_type()) {
    case cpp_aspect_types::versioned_key:
    case cpp_aspect_types::unversioned_key:
    case cpp_aspect_types::main:
        ff = factory.create(stream, vm.facet_type(), vm.file_type());
        break;
    case cpp_aspect_types::includers:
        ff = factory.create(stream, vm.facet_type());
        break;
    default:
        using dogen::utility::exception::invalid_enum_value;
        throw invalid_enum_value(unsupported_aspect_type);
    }

    ff->format(vm);
    return std::make_pair(vm.file_path(), stream.str());
}

backend::value_type cpp_backend::generate_file_view_models() const {
    const auto f(settings_.enabled_facets());
    const bool dfi(settings_.disable_facet_includers());
    const bool dk(settings_.disable_versioning());

    using view_models::sml_to_cpp_view_model;
    const bool iio(settings_.use_integrated_io());
    const bool disable_io(f.find(cpp_facet_types::io) == f.end());
    sml_to_cpp_view_model t(location_manager_, f, model_, dfi, dk, iio,
        disable_io);
    std::vector<view_models::file_view_model> fvms(t.transform());
    log_file_views(fvms.size());

    backend::value_type r;
    for (auto fvm : fvms)
        r.insert(generate_file_view_model(fvm));
    return r;
}

backend::value_type cpp_backend::generate() {
    log_started();

    backend::value_type r(generate_file_view_models());
    if (settings_.disable_cmakelists())
        log_cmakelists_disabled();
    else
        r.insert(generate_cmakelists());

    log_finished();
    return r;
}

std::vector<boost::filesystem::path> cpp_backend::managed_directories() const {
    return location_manager_.managed_directories();
}

} } } }
