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
#include <boost/throw_exception.hpp>
#include "dogen/cpp/types/inclusion_manager.hpp"
#include "dogen/cpp/types/generation_failure.hpp"
#include "dogen/cpp/types/formatters/factory.hpp"
#include "dogen/cpp/types/formatters/file_formatter.hpp"
#include "dogen/cpp/types/formatters/src_cmakelists.hpp"
#include "dogen/cpp/types/formatters/include_cmakelists.hpp"
#include "dogen/cpp/types/view_models/sml_to_cpp_view_model.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/generator.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("generator"));

const std::string cmakelists_file_name("CMakeLists.txt");
const std::string domain_facet_must_be_enabled("Domain facet must be enabled");
const std::string integrated_io_incompatible_with_io_facet(
    "Integrated IO cannot be used with the IO facet");
}

namespace dogen {
namespace cpp {

generator::
generator(const sml::model& model, const config::cpp_settings& settings) :
    model_(model), settings_(settings),
    location_manager_(model.name(), settings_) {

    if (settings_.use_integrated_io()) {
        const auto f(settings_.enabled_facets());
        const bool has_io_facet(f.find(config::cpp_facet_types::io) != f.end());
        if (has_io_facet) {
            BOOST_LOG_SEV(lg, error)
                << integrated_io_incompatible_with_io_facet;
            BOOST_THROW_EXCEPTION(generation_failure(
                integrated_io_incompatible_with_io_facet));
        }
    }

    const auto f(settings_.enabled_facets());
    if (f.find(config::cpp_facet_types::types) == f.end()) {
        BOOST_LOG_SEV(lg, error) << domain_facet_must_be_enabled;
        BOOST_THROW_EXCEPTION(generation_failure(domain_facet_must_be_enabled));
    }
}

void generator::log_formating_view(const std::string& view_name) const {
    BOOST_LOG_SEV(lg, debug) << "Formatting file view: " << view_name;
}

void generator::log_started() const {
    BOOST_LOG_SEV(lg, info) << "C++ backend started.";
}

void generator::log_finished() const {
    BOOST_LOG_SEV(lg, info) << "C++ backend finished.";
}

void generator::log_cmakelists_disabled() const {
    BOOST_LOG_SEV(lg, info) << "CMakeLists generation disabled.";
}

void generator::log_file_views(unsigned int how_many) const {
    BOOST_LOG_SEV(lg, debug) << "File views returned by SML to C++ view model"
                             << " transformer: " << how_many;
}

generator::value_type generator::generate_cmakelists() const {
    view_models::cmakelists_view_model vm;
    vm.file_name(cmakelists_file_name);
    vm.file_path(location_manager_.absolute_path_to_src(vm.file_name()));
    vm.model_name(model_.name());

    if (!model_.external_package_path().empty())
        vm.product_name(model_.external_package_path().front());

    log_formating_view(vm.file_path().string());
    std::ostringstream stream;
    formatters::src_cmakelists src(stream);
    src.format(vm);

    generator::value_type r;
    r.insert(std::make_pair(vm.file_path(), stream.str()));

    if (!settings_.split_project()) {
        stream.str("");
        vm.file_path(location_manager_.absolute_path(vm.file_name()));
        log_formating_view(vm.file_path().string());
        formatters::include_cmakelists inc(stream);
        inc.format(vm);
        r.insert(std::make_pair(vm.file_path(), stream.str()));
    }

    return r;
}

generator::value_entry_type generator::
generate_file_view_model(const view_models::file_view_model& vm) const {
    log_formating_view(vm.file_path().string());
    formatters::factory factory(settings_);
    formatters::file_formatter::shared_ptr ff;
    std::ostringstream s;
    ff = factory.create(s, vm.facet_type(), vm.file_type(), vm.aspect_type());
    ff->format(vm);
    return std::make_pair(vm.file_path(), s.str());
}

generator::value_type generator::generate_file_view_models() const {
    inclusion_manager im(model_, location_manager_, settings_);

    using view_models::sml_to_cpp_view_model;
    sml_to_cpp_view_model t(location_manager_, im, settings_, model_);
    std::vector<view_models::file_view_model> fvms(t.transform());
    log_file_views(fvms.size());

    generator::value_type r;
    for (auto fvm : fvms)
        r.insert(generate_file_view_model(fvm));
    return r;
}

generator::value_type generator::generate() {
    log_started();

    generator::value_type r(generate_file_view_models());
    if (settings_.disable_cmakelists())
        log_cmakelists_disabled();
    else {
        const auto cm(generate_cmakelists());
        r.insert(cm.begin(), cm.end());
    }

    log_finished();
    return r;
}

std::vector<boost::filesystem::path> generator::managed_directories() const {
    return location_manager_.managed_directories();
}

} }
