/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/io/formattables/locator_configuration_io.hpp"
#include "dogen.generation.cpp/types/formattables/location_error.hpp"
#include "dogen.generation.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen.generation.cpp/types/formattables/locator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.cpp.formattables.locator"));

const std::string empty;
const std::string underscore("_");
const std::string double_quote("\"");
const std::string dot(".");
const std::string separator("_");

const std::string missing_facet_configuration(
    "Could not find configuration for facet: ");
const std::string missing_archetype_configuration(
    "Could not find configuration for archetype: ");
const std::string missing_backend_directory(
    "Enable backend directory is on but backend directory is empty.");

}

namespace dogen::generation::cpp::formattables {

locator::locator(
    const boost::filesystem::path& output_directory_path,
    const boost::filesystem::path& cpp_headers_output_directory_path,
    const variability::meta_model::feature_model& fm,
    const formatters::repository& frp,
    const variability::meta_model::configuration& rcfg,
    const assets::meta_model::name& model_name,
    const std::unordered_set<std::string>& module_ids,
    const bool enable_backend_directories)
    : model_name_(model_name),
      configuration_(make_configuration(fm, frp, rcfg)),
      module_ids_(module_ids),
      project_path_(make_project_path(output_directory_path, model_name,
              configuration_, enable_backend_directories)),
      headers_project_path_(compute_headers_path(output_directory_path,
              project_path_, cpp_headers_output_directory_path)),
      templates_project_path_(compute_templates_path(project_path_)),
      split_mode_(!cpp_headers_output_directory_path.empty()) {

    BOOST_LOG_SEV(lg, debug) << "Configuration: " << configuration_;
}

locator::feature_group
locator::make_feature_group(const variability::meta_model::feature_model& fm,
    const formatters::repository& frp) const {

    feature_group r;
    const variability::helpers::feature_selector s(fm);

    std::unordered_set<std::string> processed_facets;
    for (const auto ptr : frp.stock_artefact_formatters()) {
        const auto& fmt(*ptr);
        const auto& al(fmt.archetype_location());

        const auto arch(al.archetype());
        const auto fct(al.facet());
        const auto pf(traits::postfix());

        formatter_feature_group fmt_fg;
        const auto pfix(traits::postfix());
        fmt_fg.archetype_postfix = s.get_by_name(arch, pfix);

        auto dir(s.try_get_by_name(fct, traits::directory()));
        if (dir)
            fmt_fg.facet_directory = *dir;

        auto postfix(s.try_get_by_name(fct, traits::postfix()));
        if (postfix)
            fmt_fg.facet_postfix = *postfix;

        r.formatters_feature_group[arch] = fmt_fg;

        const bool done(processed_facets.find(fct) != processed_facets.end());
        if (fmt_fg.facet_directory && !done) {
            processed_facets.insert(fct);
            facet_feature_group fct_fg;
            fct_fg.directory = *fmt_fg.facet_directory;
            fct_fg.postfix = *fmt_fg.facet_postfix;
            r.facets_feature_group[fct] = fct_fg;
        }
    }

    const auto& idn(traits::cpp::include_directory_name());
    r.include_directory_name = s.get_by_name(idn);

    const auto& sdn(traits::cpp::source_directory_name());
    r.source_directory_name = s.get_by_name(sdn);

    const auto& tdn(traits::cpp::tests_directory_name());
    r.tests_directory_name = s.get_by_name(tdn);

    const auto& tpl_dn(traits::cpp::templates_directory_name());
    r.templates_directory_name = s.get_by_name(tpl_dn);

    const auto& tpl_fe(traits::cpp::templates_file_extension());
    r.templates_file_extension = s.get_by_name(tpl_fe);

    const auto& hde(traits::cpp::header_file_extension());
    r.header_file_extension = s.get_by_name(hde);

    const auto& ife(traits::cpp::implementation_file_extension());
    r.implementation_file_extension = s.get_by_name(ife);

    const auto& dt(traits::cpp::disable_facet_directories());
    r.disable_facet_directories = s.get_by_name(dt);

    const auto& kdn(traits::cpp::backend_directory_name());
    r.backend_directory_name = s.get_by_name(kdn);

    return r;
}

locator_configuration locator::make_configuration(const feature_group& fg,
    const variability::meta_model::configuration& cfg) const {

    locator_configuration r;
    const variability::helpers::configuration_selector s(cfg);

    for (const auto& pair : fg.facets_feature_group) {
        const auto fct(pair.first);
        const auto& fct_tg(pair.second);

        locator_facet_configuration fct_cfg;
        fct_cfg.directory(s.get_text_content_or_default(fct_tg.directory));
        fct_cfg.postfix(s.get_text_content_or_default(fct_tg.postfix));
        r.facet_configurations()[fct] = fct_cfg;
    }

    for (const auto& pair : fg.formatters_feature_group) {
        const auto arch(pair.first);
        const auto fmt_fg(pair.second);
        locator_archetype_configuration arch_cfg;

        if (fmt_fg.facet_directory) {
            const auto t(*fmt_fg.facet_directory);
            arch_cfg.facet_directory(s.get_text_content_or_default(t));
        }

        if (fmt_fg.facet_postfix) {
            const auto t(*fmt_fg.facet_postfix);
            arch_cfg.facet_postfix(s.get_text_content_or_default(t));
        }

        const auto pfix(fmt_fg.archetype_postfix);
        arch_cfg.archetype_postfix(s.get_text_content_or_default(pfix));

        r.archetype_configurations()[arch] = arch_cfg;
    }

    const auto& hfe(fg.header_file_extension);
    r.header_file_extension(s.get_text_content_or_default(hfe));

    const auto& ife(fg.implementation_file_extension);
    r.implementation_file_extension(s.get_text_content_or_default(ife));

    const auto& tpl_fe(fg.templates_file_extension);
    r.templates_file_extension(s.get_text_content_or_default(tpl_fe));

    const auto& idn(fg.include_directory_name);
    r.include_directory_name(s.get_text_content_or_default(idn));

    const auto& sdn(fg.source_directory_name);
    r.source_directory_name(s.get_text_content_or_default(sdn));

    const auto& tdn(fg.tests_directory_name);
    r.tests_directory_name(s.get_text_content_or_default(tdn));

    const auto& tpl_dn(fg.templates_directory_name);
    r.templates_directory_name(s.get_text_content_or_default(tpl_dn));

    const auto& dt(fg.disable_facet_directories);
    r.disable_facet_directories(s.get_boolean_content_or_default(dt));

    const auto& kdn(fg.backend_directory_name);
    r.backend_directory_name(s.get_text_content_or_default(kdn));

    return r;
}

boost::filesystem::path locator::compute_headers_path(
    const boost::filesystem::path& output_directory_path,
    const boost::filesystem::path& project_path,
    const boost::filesystem::path& cpp_headers_output_directory_path) const {

    /*
     * If the user did not supply a path for C++ headers, we simply
     * place them inside the project.
     */
    if (cpp_headers_output_directory_path.empty())
        return project_path;

    /*
     * If a path was supplied, it is relative to the output
     * directory. We need to compute the canonical path resulting from
     * that.
     */
    using boost::filesystem::canonical;
    return canonical(cpp_headers_output_directory_path, output_directory_path);
}

boost::filesystem::path locator::compute_templates_path(
    const boost::filesystem::path& project_path) const {
    const auto r(project_path / configuration_.templates_directory_name());
    BOOST_LOG_SEV(lg, debug) << "templates path: " << r.generic_string();
    return r;
}

locator_configuration locator::make_configuration(
    const variability::meta_model::feature_model& fm,
    const formatters::repository& frp,
    const variability::meta_model::configuration& cfg) {

    const auto fg(make_feature_group (fm, frp));
    const auto r(make_configuration(fg, cfg));
    return r;
}

const locator_facet_configuration& locator::
configuration_for_facet(const std::string& facet) const {
    const auto& fct_cfg(configuration_.facet_configurations());
    const auto i(fct_cfg.find(facet));
    if (i == fct_cfg.end()) {
        BOOST_LOG_SEV(lg, error) << missing_facet_configuration;
        BOOST_THROW_EXCEPTION(location_error(missing_facet_configuration));
    }

    return i->second;
}

const locator_archetype_configuration& locator::
configuration_for_archetype(const std::string& archetype) const {
    const auto& arch_cfg(configuration_.archetype_configurations());
    const auto i(arch_cfg.find(archetype));
    if (i == arch_cfg.end()) {
        BOOST_LOG_SEV(lg, error) << missing_archetype_configuration;
        BOOST_THROW_EXCEPTION(location_error(missing_archetype_configuration));
    }

    return i->second;
}

std::string locator::header_file_extension() const {
    return configuration_.header_file_extension();
}

std::string locator::implementation_file_extension() const {
    return configuration_.implementation_file_extension();
}

std::string locator::postfix_for_facet(const std::string& facet) const {
    const auto cfg(configuration_for_facet(facet));
    return cfg.postfix();
}

boost::filesystem::path locator::make_project_path(
    const boost::filesystem::path& output_directory_path,
    const assets::meta_model::name& model_name, const locator_configuration& lc,
    const bool enable_backend_directories) const {

    boost::filesystem::path r(output_directory_path);
    const auto& mmp(model_name.location().model_modules());
    r /= boost::algorithm::join(mmp, dot);
    if (enable_backend_directories) {
        if (lc.backend_directory_name().empty()) {
            BOOST_LOG_SEV(lg, error) << missing_backend_directory;
            BOOST_THROW_EXCEPTION(location_error(missing_backend_directory));
        }

        r /= lc.backend_directory_name();
    }

    return r;
}

boost::filesystem::path locator::make_facet_path(
    const std::string& archetype, const std::string& extension,
    const assets::meta_model::name& n) const {
    BOOST_LOG_SEV(lg, trace) << "Making facet path for: "
                             << n.qualified().dot();

    boost::filesystem::path r;

    /*
     * If there is a facet directory, and it is configured to
     * contribute to the file name path, add it.
     */
    const auto& cfg(configuration_);
    const auto& arch_cfg(configuration_for_archetype(archetype));
    if (!arch_cfg.facet_directory().empty() && !cfg.disable_facet_directories())
        r /= arch_cfg.facet_directory();

    /*
     * Add the module path of all the modules that contain this name.
     */
    for (const auto& m : n.location().internal_modules())
        r /= m;

    /*
     * Modules other than the model module contribute their simple
     * names to the directories.
     */
    if (n != model_name_) {
        const auto i(module_ids_.find(n.qualified().dot()));
        if (i != module_ids_.end())
            r /= n.simple();
    }

    /*
     * Handle the file name.
     */
    std::ostringstream stream;
    stream << n.simple();

    if (!arch_cfg.archetype_postfix().empty())
        stream << underscore << arch_cfg.archetype_postfix();

    if (!arch_cfg.facet_postfix().empty())
        stream << underscore << arch_cfg.facet_postfix();

    if (!extension.empty())
        stream << dot << extension;
    r /= stream.str();

    BOOST_LOG_SEV(lg, trace) << "Done making the facet path. Result: "
                             << r.generic_string();
    return r;
}

boost::filesystem::path locator::make_facet_path_temp(
    const std::string& archetype, const std::string& file_name,
    const assets::meta_model::name& n) const {
    BOOST_LOG_SEV(lg, trace) << "Making facet path for: "
                             << n.qualified().dot();

    /*
     * If there is a facet directory, and it is configured to
     * contribute to the file name path, add it.
     */
    boost::filesystem::path r;
    const auto& cfg(configuration_);
    const auto& arch_cfg(configuration_for_archetype(archetype));
    if (!arch_cfg.facet_directory().empty() && !cfg.disable_facet_directories())
        r /= arch_cfg.facet_directory();

    /*
     * Add the module path of all the modules that contain this name.
     */
    for (const auto& m : n.location().internal_modules())
        r /= m;

    /*
     * Modules other than the model module contribute their simple
     * names to the directories.
     */
    if (n != model_name_) {
        const auto i(module_ids_.find(n.qualified().dot()));
        if (i != module_ids_.end())
            r /= n.simple();
    }

    /*
     * Handle the file name.
     */
    std::ostringstream stream;
    stream << file_name;
    r /= stream.str();

    BOOST_LOG_SEV(lg, trace) << "Done making the facet path. Result: "
                             << r.generic_string();
    return r;
}

boost::filesystem::path locator::make_inclusion_path_prefix(
    const assets::meta_model::name& n) const {
    /*
     * Header files require both the external module path and the
     * model module path in the file name path.
     */
    boost::filesystem::path r;
    for (const auto& m : n.location().external_modules())
        r /= m;

    const auto& mmp(n.location().model_modules());
    r /= boost::algorithm::join(mmp, dot);
    return r;
}

boost::filesystem::path locator::make_inclusion_path(
    const std::string& archetype, const std::string& extension,
    const assets::meta_model::name& n) const {

    boost::filesystem::path r(make_inclusion_path_prefix(n));
    r /= make_facet_path(archetype, extension, n);
    return r;
}

boost::filesystem::path locator::project_path() const {
    return project_path_;
}

boost::filesystem::path locator::headers_project_path() const {
    return headers_project_path_;
}

boost::filesystem::path locator::templates_project_path() const {
    return templates_project_path_;
}

boost::filesystem::path locator::headers_model_path() const {
    auto r(headers_project_path_);
    r /= make_inclusion_path_prefix(model_name_);
    return r;
}

std::string locator::include_directory_name() const {
    return configuration_.include_directory_name();
}

std::string locator::source_directory_name() const {
    return configuration_.source_directory_name();
}

std::string locator::tests_directory_name() const {
    return configuration_.tests_directory_name();
}

std::string locator::templates_directory_name() const {
    return configuration_.templates_directory_name();
}

boost::filesystem::path locator::
make_relative_include_path(bool for_include_statement) const {
    boost::filesystem::path r;
    const auto& cfg(configuration_);

    /*
     * If the path is being made for an include statement, we must not
     * include the top-level include directory.
     */
    if (!for_include_statement)
        r /= cfg.include_directory_name();

    r /= make_inclusion_path_prefix(model_name_);
    return r;
}

boost::filesystem::path locator::make_relative_include_path_for_facet(
    const std::string& facet, bool for_include_statement) const {
    auto r(make_relative_include_path(for_include_statement));

    const auto& cfg(configuration_);
    const auto& fct_cfg(configuration_for_facet(facet));
    if (!fct_cfg.directory().empty() && !cfg.disable_facet_directories())
        r /= fct_cfg.directory();

    return r;
}

boost::filesystem::path locator::make_inclusion_path_for_cpp_header(
    const assets::meta_model::name& n, const std::string& archetype) const {
    const auto extension(configuration_.header_file_extension());
    return make_inclusion_path(archetype, extension, n);
}

boost::filesystem::path locator::make_full_path_to_include_directory() const {
    auto r(headers_project_path_);
    const auto& cfg(configuration_);

    /*
     * If we are in split mode, we do not want to add a top-level
     * include directory; the user is expected to have already set up
     * its own directory structure.
     */
    if (!split_mode_)
        r /= cfg.include_directory_name();

    return r;
}

boost::filesystem::path
locator::make_full_path_to_implementation_directory() const {
    auto r(project_path_);
    const auto& cfg(configuration_);
    r /= cfg.source_directory_name();
    return r;
}

boost::filesystem::path locator::make_full_path_to_include_facet_directory(
    const std::string& facet) const {

    auto r(make_full_path_to_include_directory());
    r /= make_relative_include_path_for_facet(facet, true/**/);
    return r;
}

boost::filesystem::path locator::make_full_path_for_cpp_header(
    const assets::meta_model::name& n, const std::string& archetype) const {
    auto r(make_full_path_to_include_directory());
    r /= make_inclusion_path_for_cpp_header(n, archetype);
    return r;
}

boost::filesystem::path locator::make_relative_implementation_path_for_facet(
    const std::string& facet) const {

    const auto& cfg(configuration_);
    boost::filesystem::path r(cfg.source_directory_name());

    const auto& fct_cfg(configuration_for_facet(facet));
    if (!fct_cfg.directory().empty() && !cfg.disable_facet_directories())
        r /= fct_cfg.directory();

    return r;
}

boost::filesystem::path locator::make_full_path_for_templates(
    const assets::meta_model::name& n, const std::string& archetype) const {
    auto r(project_path_);

    const auto& cfg(configuration_);
    const auto extension(cfg.templates_file_extension());
    const auto facet_path(make_facet_path(archetype, extension, n));
    r /= facet_path;

    return r;
}

boost::filesystem::path locator::make_full_path_for_tests_cpp_implementation(
    const assets::meta_model::name& n, const std::string& archetype) const {
    auto r(project_path_);

    const auto& cfg(configuration_);
    const auto extension(cfg.implementation_file_extension());
    const auto facet_path(make_facet_path(archetype, extension, n));
    r /= facet_path;

    return r;
}

boost::filesystem::path locator::make_full_path_for_tests_cpp_main(
    const assets::meta_model::name& n, const std::string& archetype) const {

    auto r(project_path_);

    const auto& cfg(configuration_);
    const auto extension(cfg.implementation_file_extension());

    // FIXME: hack
    const auto facet_path(make_facet_path_temp(archetype,
            "main." + extension, n));
    r /= facet_path;

    return r;
}

boost::filesystem::path locator::make_full_path_for_cpp_implementation(
    const assets::meta_model::name& n, const std::string& archetype) const {

    auto r(make_full_path_to_implementation_directory());

    const auto& cfg(configuration_);
    const auto extension(cfg.implementation_file_extension());
    const auto facet_path(make_facet_path(archetype, extension, n));
    r /= facet_path;

    return r;
}

boost::filesystem::path locator::make_full_path_for_include_cmakelists(
    const assets::meta_model::name& n, const std::string& /*archetype*/) const {
    /*
     * Note that we are placing the "include" CMake file with the
     * project directory rather than the project headers directory.
     */
    auto r(project_path_);
    r /= n.simple() + ".txt"; // FIXME: hack for extension
    return r;
}

boost::filesystem::path locator::make_full_path_for_source_cmakelists(
    const assets::meta_model::name& n, const std::string& /*archetype*/) const {
    auto r(make_full_path_to_implementation_directory());
    r /= n.simple() + ".txt"; // FIXME: hack for extension
    return r;
}

boost::filesystem::path locator::make_full_path_for_tests_cmakelists(
    const assets::meta_model::name& n, const std::string& archetype) const {
    auto r(project_path_);
    const auto facet_path(make_facet_path_temp(archetype, "CMakeLists.txt", n)); // FIXME: hack
    r /= facet_path;
    return r;
}

boost::filesystem::path locator::
make_full_path_for_msbuild_targets(const assets::meta_model::name& /*n*/,
    const std::string& /*archetype*/) const {
    auto r(make_full_path_to_implementation_directory());
    r /= "msbuild.targets"; // FIXME: hack
    return r;
}

boost::filesystem::path locator::make_relative_path_for_odb_options(
    const assets::meta_model::name& n, const std::string& archetype,
    const bool include_source_directory) const {

    boost::filesystem::path r;
    if (include_source_directory)
        r /= configuration_.source_directory_name();

    /*
     * If there is a facet directory, and it is configured to
     * contribute to the file name path, add it.
     */
    const auto& cfg(configuration_);
    const auto& arch_cfg(configuration_for_archetype(archetype));
    if (!arch_cfg.facet_directory().empty() && !cfg.disable_facet_directories())
        r /= arch_cfg.facet_directory();

    /*
     * Add the module path of all the modules that contain this name.
     */
    for (const auto& m : n.location().internal_modules())
        r /= m;

    std::ostringstream stream;
    stream << n.simple();

    if (!arch_cfg.archetype_postfix().empty())
        stream << underscore << arch_cfg.archetype_postfix();

    if (!arch_cfg.facet_postfix().empty())
        stream << underscore << "options";

    const auto extension("odb");
    stream << dot << extension;
    r /= stream.str();

    return r;
}

boost::filesystem::path locator::make_full_path_for_odb_options(
    const assets::meta_model::name& n, const std::string& archetype) const {
    auto r(project_path_);
    r /= make_relative_path_for_odb_options(n, archetype);
    return r;
}

boost::filesystem::path locator::make_full_path_for_project(
    const assets::meta_model::name& n, const std::string& archetype) const {
    auto r(project_path_);
    const auto facet_path(make_facet_path(archetype, empty, n));
    r /= facet_path;
    return r;
}

boost::filesystem::path locator::make_full_path_for_solution(
    const assets::meta_model::name& n, const std::string& archetype) const {
    auto r(project_path_);
    const auto facet_path(make_facet_path(archetype, empty, n));
    r /= facet_path;
    return r;
}

std::unordered_map<std::string, std::string>
locator::facet_directories() const {
    std::unordered_map<std::string, std::string> r;

    for (const auto& pair : configuration_.facet_configurations()) {
        const auto fct(pair.first);
        const auto fct_cfg(pair.second);
        r[fct] = fct_cfg.directory();
    }

    return r;
}

}
