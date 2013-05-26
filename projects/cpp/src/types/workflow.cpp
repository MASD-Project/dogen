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
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/workflow_failure.hpp"
#include "dogen/cpp/types/formatters/factory.hpp"
#include "dogen/cpp/types/formatters/file_formatter.hpp"
#include "dogen/cpp/types/formatters/src_cmakelists.hpp"
#include "dogen/cpp/types/formatters/include_cmakelists.hpp"
#include "dogen/cpp/types/formatters/odb_options.hpp"
#include "dogen/cpp/types/sml_to_cpp_info.hpp"
#include "dogen/cpp/types/workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.workflow"));

const std::string includer_name("all");
const std::string cmakelists_file_name("CMakeLists.txt");
const std::string odb_options_file_name("options.odb");
const std::string domain_facet_must_be_enabled("Domain facet must be enabled");
const std::string integrated_io_incompatible_with_io_facet(
    "Integrated IO cannot be used with the IO facet");
}

namespace dogen {
namespace cpp {

workflow::
workflow(const sml::model& model, const config::cpp_settings& settings) :
    model_(model), settings_(settings), locator_(model.name(), settings_),
    includer_(model_, locator_, settings_),
    file_info_factory_(locator_, includer_),
    transformer_(model_),
    descriptor_factory_(settings_.enabled_facets()) {

    validate_settings();
}

void workflow::log_formating_view(const std::string& view_name) const {
    BOOST_LOG_SEV(lg, debug) << "Formatting file view: " << view_name;
}

void workflow::log_started() const {
    BOOST_LOG_SEV(lg, info) << "C++ backend started.";
}

void workflow::log_finished() const {
    BOOST_LOG_SEV(lg, info) << "C++ backend finished.";
}

void workflow::log_cmakelists_disabled() const {
    BOOST_LOG_SEV(lg, info) << "CMakeLists generation disabled.";
}

void workflow::log_file_views(unsigned int how_many) const {
    BOOST_LOG_SEV(lg, debug) << "File views returned by SML to C++ view model"
                             << " transformer: " << how_many;
}

void workflow::validate_settings() const {
    if (settings_.use_integrated_io()) {
        const auto f(settings_.enabled_facets());
        const bool has_io_facet(f.find(config::cpp_facet_types::io) != f.end());
        if (has_io_facet) {
            BOOST_LOG_SEV(lg, error)
                << integrated_io_incompatible_with_io_facet;
            BOOST_THROW_EXCEPTION(workflow_failure(
                    integrated_io_incompatible_with_io_facet));
        }
    }

    const auto f(settings_.enabled_facets());
    if (f.find(config::cpp_facet_types::types) == f.end()) {
        BOOST_LOG_SEV(lg, error) << domain_facet_must_be_enabled;
        BOOST_THROW_EXCEPTION(workflow_failure(domain_facet_must_be_enabled));
    }
}

workflow::result_type workflow::generate_cmakelists() const {
    cmakelists_info ci;
    ci.file_name(cmakelists_file_name);
    ci.file_path(locator_.absolute_path_to_src(ci.file_name()));
    ci.model_name(model_.name());

    if (!model_.external_package_path().empty())
        ci.product_name(model_.external_package_path().front());

    log_formating_view(ci.file_path().string());
    std::ostringstream stream;
    formatters::src_cmakelists src(stream);
    src.format(ci);

    workflow::result_type r;
    r.insert(std::make_pair(ci.file_path(), stream.str()));

    if (!settings_.split_project()) {
        const auto f(settings_.enabled_facets());
        const bool odb_enabled(f.find(config::cpp_facet_types::odb) != f.end());
        stream.str("");
        ci.file_path(locator_.absolute_path(ci.file_name()));
        log_formating_view(ci.file_path().string());
        formatters::include_cmakelists inc(stream, odb_enabled,
            settings_.odb_facet_folder());
        inc.format(ci);
        r.insert(std::make_pair(ci.file_path(), stream.str()));
    }

    return r;
}

workflow::result_entry_type workflow::generate_odb_options() const {
    BOOST_LOG_SEV(lg, info) << "Generating ODB options file.";

    odb_options_info ooi;
    ooi.file_name(odb_options_file_name);
    ooi.file_path(locator_.absolute_path_to_src(ooi.file_name()));
    ooi.model_name(model_.name());
    ooi.odb_folder(settings_.odb_facet_folder());

    if (!model_.external_package_path().empty())
        ooi.product_name(model_.external_package_path().front());

    log_formating_view(ooi.file_path().string());
    std::ostringstream stream;
    formatters::odb_options f(stream);
    f.format(ooi);

    return std::make_pair(ooi.file_path(), stream.str());
}

workflow::result_entry_type workflow::
generate_file_info(const file_info& fi) const {
    log_formating_view(fi.file_path().string());
    formatters::factory factory(settings_);
    formatters::file_formatter::shared_ptr ff;
    std::ostringstream s;
    ff = factory.create(s, fi.facet_type(), fi.file_type(), fi.aspect_type());
    ff->format(fi);
    return std::make_pair(fi.file_path(), s.str());
}

workflow::result_type workflow::old_generate_file_infos() const {
    includer im(model_, locator_, settings_);

    sml_to_cpp_info t(locator_, im, settings_, model_);
    std::vector<file_info> vfi(t.transform());
    log_file_views(vfi.size());

    workflow::result_type r;
    for (const auto& fi : vfi)
        r.insert(generate_file_info(fi));
    return r;
}

workflow::result_type workflow::generate_enums_activity() {
    workflow::result_type r;
    for (const auto& pair : model_.enumerations()) {
        const auto& e(pair.second);
        if (e.generation_type() == sml::generation_types::no_generation)
            continue;

        const auto ei(transformer_.transform(e));

        const auto ct(sml::category_types::user_defined);
        const auto cds(descriptor_factory_.create(e.name(), ct));
        for (const auto& fi : file_info_factory_.create(ei, cds)) {
            r.insert(generate_file_info(fi));

            const auto header(file_types::header);
            const auto main(aspect_types::main);
            if (fi.file_type() == header && fi.aspect_type() == main)
                includer_.register_header(fi.facet_type(), fi.relative_path());
        }
    }
    return r;
}

workflow::result_type workflow::generate_exceptions_activity() {
    workflow::result_type r;
    for (const auto& pair : model_.exceptions()) {
        const auto& e(pair.second);
        if (e.generation_type() == sml::generation_types::no_generation)
            continue;

        const auto ei(transformer_.transform(e));

        const auto ct(sml::category_types::user_defined);
        const auto cds(descriptor_factory_.create(e.name(), ct));
        for (const auto& fi : file_info_factory_.create(ei, cds)) {
            r.insert(generate_file_info(fi));

            const auto header(file_types::header);
            const auto main(aspect_types::main);
            if (fi.file_type() == header && fi.aspect_type() == main)
                includer_.register_header(fi.facet_type(), fi.relative_path());
        }
    }
    return r;
}

workflow::result_type workflow::generate_classes_activity() {
    workflow::result_type r;
    for (const auto& pair : model_.pods()) {
        const auto p(pair.second);

        if (p.generation_type() == sml::generation_types::no_generation)
            continue;

        const auto pi(transformer_.transform(p));
        const auto ct(p.category_type());
        const auto cds(descriptor_factory_.create(p.name(), ct));
        for (const auto& fi : file_info_factory_.create(pi, cds)) {
            r.insert(generate_file_info(fi));

            const auto header(file_types::header);
            const auto main(aspect_types::main);
            if (fi.file_type() == header && fi.aspect_type() == main)
                includer_.register_header(fi.facet_type(), fi.relative_path());
        }
    }
    return r;
}

workflow::result_type workflow::generate_namespaces_activity() {
    workflow::result_type r;

    if (!model_.documentation().empty()) {
        const auto ni(transformer_.transform_model_into_namespace());
        auto cds(descriptor_factory_.create(model_));

        for (const auto& fi : file_info_factory_.create(ni, cds)) {
            r.insert(generate_file_info(fi));

            // FIXME: do we need to register these headers?
            const auto header(file_types::header);
            const auto main(aspect_types::main);
            if (fi.file_type() == header && fi.aspect_type() == main)
                includer_.register_header(fi.facet_type(), fi.relative_path());
        }
    }

    for (const auto& pair : model_.packages()) {
        const auto& p(pair.second);

        if (p.documentation().empty())
            continue;

        const auto ni(transformer_.transform(p));
        auto cds(descriptor_factory_.create(p.name()));

        for (const auto& fi : file_info_factory_.create(ni, cds)) {
            r.insert(generate_file_info(fi));

            // FIXME: do we need to register these headers?
            const auto header(file_types::header);
            const auto main(aspect_types::main);
            if (fi.file_type() == header && fi.aspect_type() == main)
                includer_.register_header(fi.facet_type(), fi.relative_path());
        }
    }

    return r;
}

workflow::result_type workflow::generate_registrars_activity() {
    sml::qname qn;
    qn.model_name(model_.name());
    qn.external_package_path(model_.external_package_path());

    // FIXME: we should probably have a not SML type instead of lying
    qn.meta_type(sml::meta_types::pod);

    const auto ri(transformer_.transform_model_into_registrar());
    const auto cds(descriptor_factory_.create(qn));

    workflow::result_type r;
    for (const auto& fi : file_info_factory_.create_registrar(ri, cds)) {
        r.insert(generate_file_info(fi));

        const auto header(file_types::header);
        const auto main(aspect_types::main);
        if (fi.file_type() == header && fi.aspect_type() == main)
            includer_.register_header(fi.facet_type(), fi.relative_path());
    }
    return r;
}

workflow::result_type workflow::generate_includers_activity() {
    sml::qname qn;
    qn.type_name(includer_name);
    qn.external_package_path(model_.external_package_path());

    // FIXME: we should probably have a not SML type instead of lying
    qn.meta_type(sml::meta_types::pod);

    const auto cds(descriptor_factory_.create_includer(qn));

    workflow::result_type r;
    for (const auto& fi : file_info_factory_.create_includer(cds))
        r.insert(generate_file_info(fi));
    return r;
}

workflow::result_type workflow::generate_file_infos_activity() {
    const auto a(generate_enums_activity());
    const auto b(generate_exceptions_activity());
    const auto c(generate_classes_activity());
    const auto d(generate_namespaces_activity());
    const auto e(generate_registrars_activity());
    const auto f(generate_includers_activity());

    workflow::result_type r;
    r.insert(a.begin(), a.end());
    r.insert(b.begin(), b.end());
    r.insert(c.begin(), c.end());
    r.insert(d.begin(), d.end());
    r.insert(e.begin(), e.end());
    r.insert(f.begin(), e.end());
    return r;
}

workflow::result_type workflow::execute() {
    log_started();

    workflow::result_type r(old_generate_file_infos());
    // workflow::result_type r(generate_file_infos_activity());
    if (settings_.disable_cmakelists())
        log_cmakelists_disabled();
    else {
        const auto cm(generate_cmakelists());
        r.insert(cm.begin(), cm.end());
    }

    const auto f(settings_.enabled_facets());
    const bool odb_enabled(f.find(config::cpp_facet_types::odb) != f.end());
    if (odb_enabled)
        r.insert(generate_odb_options());
    else
        BOOST_LOG_SEV(lg, info) << "ODB options file generation disabled.";

    log_finished();
    return r;
}

std::vector<boost::filesystem::path> workflow::managed_directories() const {
    return locator_.managed_directories();
}

} }
