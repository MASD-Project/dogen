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
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formattables/location_error.hpp"
#include "dogen/quilt.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formattables/locator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.locator"));

const std::string empty;
const std::string underscore("_");
const std::string double_quote("\"");
const std::string dot(".");
const std::string separator("_");

const std::string missing_facet_configuration(
    "Could not find configuration for facet: ");
const std::string missing_archetype_configuration(
    "Could not find configuration for archetype: ");
const std::string missing_kernel_directory(
    "Enable kernel directory is on but kernel directory is empty.");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

locator::locator(
    const boost::filesystem::path& output_directory_path,
    const boost::filesystem::path& cpp_headers_output_directory_path,
    const annotations::type_repository& atrp, const formatters::repository& frp,
    const annotations::annotation& root, const yarn::name& model_name,
    const std::unordered_set<std::string>& module_ids,
    const bool enable_kernel_directories)
    : model_name_(model_name),
      configuration_(make_configuration(atrp, frp, root)),
      module_ids_(module_ids),
      project_path_(make_project_path(output_directory_path, model_name,
              configuration_, enable_kernel_directories)),
      headers_project_path_(
          cpp_headers_output_directory_path.empty() ?
          project_path_ :
          make_project_path(cpp_headers_output_directory_path, model_name,
              configuration_, enable_kernel_directories)) {}

locator::type_group
locator::make_type_group(const annotations::type_repository& atrp,
    const formatters::repository& frp) const {

    type_group r;
    const annotations::type_repository_selector s(atrp);

    std::unordered_set<std::string> processed_facets;
    for (const auto ptr : frp.stock_artefact_formatters()) {
        const auto& fmt(*ptr);
        const auto& al(fmt.archetype_location());

        const auto arch(al.archetype());
        const auto fct(al.facet());
        const auto pf(traits::postfix());

        formatter_type_group fmt_tg;
        const auto pfix(traits::postfix());
        fmt_tg.archetype_postfix = s.select_type_by_name(arch, pfix);

        auto dir(s.try_type_field_by_name(fct, traits::directory()));
        if (dir)
            fmt_tg.facet_directory = *dir;

        auto postfix(s.try_type_field_by_name(fct, traits::postfix()));
        if (postfix)
            fmt_tg.facet_postfix = *postfix;

        r.formatters_type_group[arch] = fmt_tg;

        const bool done(processed_facets.find(fct) != processed_facets.end());
        if (fmt_tg.facet_directory && !done) {
            processed_facets.insert(fct);
            facet_type_group fct_tg;
            fct_tg.directory = *fmt_tg.facet_directory;
            fct_tg.postfix = *fmt_tg.facet_postfix;
            r.facets_type_group[fct] = fct_tg;
        }
    }

    const auto& idn(traits::cpp::include_directory_name());
    r.include_directory_name = s.select_type_by_name(idn);

    const auto& sdn(traits::cpp::source_directory_name());
    r.source_directory_name = s.select_type_by_name(sdn);

    const auto& hde(traits::cpp::header_file_extension());
    r.header_file_extension = s.select_type_by_name(hde);

    const auto& ife(traits::cpp::implementation_file_extension());
    r.implementation_file_extension = s.select_type_by_name(ife);

    const auto& dt(traits::cpp::disable_facet_directories());
    r.disable_facet_directories = s.select_type_by_name(dt);

    const auto& kdn(traits::cpp::kernel_directory_name());
    r.kernel_directory_name = s.select_type_by_name(kdn);

    return r;
}

locator_configuration locator::make_configuration(
    const type_group& tg, const annotations::annotation& o) const {

    locator_configuration r;
    const annotations::entry_selector s(o);

    for (const auto& pair : tg.facets_type_group) {
        const auto fct(pair.first);
        const auto& fct_tg(pair.second);

        locator_facet_configuration fct_cfg;
        fct_cfg.directory(s.get_text_content_or_default(fct_tg.directory));
        fct_cfg.postfix(s.get_text_content_or_default(fct_tg.postfix));
        r.facet_configurations()[fct] = fct_cfg;
    }

    for (const auto& pair : tg.formatters_type_group) {
        const auto arch(pair.first);
        const auto fmt_tg(pair.second);
        locator_archetype_configuration arch_cfg;

        if (fmt_tg.facet_directory) {
            const auto t(*fmt_tg.facet_directory);
            arch_cfg.facet_directory(s.get_text_content_or_default(t));
        }

        if (fmt_tg.facet_postfix) {
            const auto t(*fmt_tg.facet_postfix);
            arch_cfg.facet_postfix(s.get_text_content_or_default(t));
        }

        const auto pfix(fmt_tg.archetype_postfix);
        arch_cfg.archetype_postfix(s.get_text_content_or_default(pfix));

        r.archetype_configurations()[arch] = arch_cfg;
    }

    const auto& hfe(tg.header_file_extension);
    r.header_file_extension(s.get_text_content_or_default(hfe));

    const auto& ife(tg.implementation_file_extension);
    r.implementation_file_extension(s.get_text_content_or_default(ife));

    const auto& idn(tg.include_directory_name);
    r.include_directory_name(s.get_text_content_or_default(idn));

    const auto& sdn(tg.source_directory_name);
    r.source_directory_name(s.get_text_content_or_default(sdn));

    const auto& dt(tg.disable_facet_directories);
    r.disable_facet_directories(s.get_boolean_content_or_default(dt));

    const auto& kdn(tg.kernel_directory_name);
    r.kernel_directory_name(s.get_text_content_or_default(kdn));

    return r;
}

locator_configuration locator::make_configuration(
    const annotations::type_repository& atrp, const formatters::repository& frp,
    const annotations::annotation& a) {

    const auto tg(make_type_group (atrp, frp));
    const auto r(make_configuration(tg, a));
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
    const yarn::name& model_name, const locator_configuration& lc,
    const bool enable_kernel_directories) const {

    boost::filesystem::path r;
    const auto& mmp(model_name.location().model_modules());
    r = output_directory_path;
    r /= boost::algorithm::join(mmp, dot);
    if (enable_kernel_directories) {
        if (lc.kernel_directory_name().empty()) {
            BOOST_LOG_SEV(lg, error) << missing_kernel_directory;
            BOOST_THROW_EXCEPTION(location_error(missing_kernel_directory));
        }

        r /= lc.kernel_directory_name();
    }

    return r;
}

boost::filesystem::path locator::make_facet_path(
    const std::string& archetype, const std::string& extension,
    const yarn::name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Making facet path for: " << n.id();

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
        const auto i(module_ids_.find(n.id()));
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

    stream << dot << extension;
    r /= stream.str();

    BOOST_LOG_SEV(lg, debug) << "Done making the facet path. Result: "
                             << r.generic_string();
    return r;
}

boost::filesystem::path locator::make_inclusion_path_prefix(
    const yarn::name& n) const {
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
    const yarn::name& n) const {

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

std::string locator::include_directory_name() const {
    return configuration_.include_directory_name();
}

std::string locator::source_directory_name() const {
    return configuration_.source_directory_name();
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
    const yarn::name& n, const std::string& archetype) const {
    const auto extension(configuration_.header_file_extension());
    return make_inclusion_path(archetype, extension, n);
}

boost::filesystem::path locator::make_full_path_to_include_directory() const {
    auto r(headers_project_path_);
    const auto& cfg(configuration_);
    r /= cfg.include_directory_name();
    return r;
}

boost::filesystem::path locator::make_full_path_for_cpp_header(
    const yarn::name& n, const std::string& archetype) const {
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

boost::filesystem::path locator::make_full_path_for_cpp_implementation(
    const yarn::name& n, const std::string& archetype) const {

    auto r(project_path_);
    const auto& cfg(configuration_);
    r /= cfg.source_directory_name();

    const auto extension(cfg.implementation_file_extension());
    const auto facet_path(make_facet_path(archetype, extension, n));
    r /= facet_path;

    return r;
}

boost::filesystem::path locator::make_full_path_for_include_cmakelists(
    const yarn::name& n, const std::string& /*archetype*/) const {
    /*
     * Note that we are placing the "include" CMake file with the
     * project directory rather than the project headers directory.
     */
    auto r(project_path_);
    r /= n.simple() + ".txt"; // FIXME: hack for extension
    return r;
}

boost::filesystem::path locator::make_full_path_for_source_cmakelists(
    const yarn::name& n, const std::string& /*archetype*/) const {
    auto r(project_path_);
    r /= configuration_.source_directory_name();
    r /= n.simple() + ".txt"; // FIXME: hack for extension
    return r;
}

boost::filesystem::path locator::make_relative_path_for_odb_options(
    const yarn::name& /*n*/, const std::string& /*archetype*/) const {

    boost::filesystem::path r(configuration_.source_directory_name());
    r /= "options.odb"; // FIXME: hack for filename
    return r;
}

boost::filesystem::path locator::make_full_path_for_odb_options(
    const yarn::name& n, const std::string& archetype) const {
    auto r(project_path_);
    r /= make_relative_path_for_odb_options(n, archetype);
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

} } } }
