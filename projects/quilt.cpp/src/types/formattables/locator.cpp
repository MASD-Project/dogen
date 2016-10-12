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
#include "dogen/annotations/types/field_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formattables/building_error.hpp"
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formattables/locator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.locator"));

const std::string empty;
const std::string underscore("_");
const std::string double_quote("\"");
const std::string dot(".");
const std::string separator("_");

const std::string missing_formatter_configuration(
    "Could not find configuration for formatter: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

locator::locator(const boost::filesystem::path& project_directory_path,
    const annotations::type_repository& atrp, const formatters::container& fc,
    const annotations::annotation& root, const yarn::name& model_name,
    const std::unordered_set<std::string>& module_ids)
    : model_name_(model_name),
      configuration_(make_configuration(atrp, fc, root)),
      module_ids_(module_ids),
      project_path_(make_project_path(project_directory_path, model_name)) {}

locator::type_group locator::make_type_group(
    const annotations::type_repository& atrp,
    const formatters::container& fc) const {

    type_group r;
    const annotations::type_repository_selector s(atrp);

    std::unordered_set<std::string> processed_facets;
    for (const auto ptr : fc.file_formatters()) {
        const auto& fmt(*ptr);
        const auto& oh(fmt.ownership_hierarchy());

        const auto fmtn(oh.formatter_name());
        const auto fctn(oh.facet_name());
        const auto pf(traits::postfix());
        formatter_type_group fmt_tg;
        const auto pfix(traits::postfix());
        fmt_tg.formatter_postfix = s.select_type_by_name(fmtn, pfix);

        auto dir(s.try_type_field_by_name(fctn, traits::directory()));
        if (dir)
            fmt_tg.facet_directory = *dir;

        auto postfix(s.try_type_field_by_name(fctn, traits::postfix()));
        if (postfix)
            fmt_tg.facet_postfix = *postfix;

        r.formatters_type_group[fmtn] = fmt_tg;

        const bool done(processed_facets.find(fctn) != processed_facets.end());
        if (fmt_tg.facet_directory && !done) {
            processed_facets.insert(fctn);
            facet_type_group fct_tg;
            fct_tg.directory = *fmt_tg.facet_directory;
            fct_tg.postfix = *fmt_tg.facet_postfix;
            r.facets_type_group[fctn] = fct_tg;
        }

        const auto& idn(traits::cpp::include_directory_name());
        r.include_directory_name = s.select_type_by_name(idn);

        const auto& sdn(traits::cpp::source_directory_name());
        r.source_directory_name = s.select_type_by_name(sdn);

        const auto& hde(traits::cpp::header_file_extension());
        r.header_file_extension = s.select_type_by_name(hde);

        const auto& ife(traits::cpp::implementation_file_extension());
        r.implementation_file_extension = s.select_type_by_name(ife);

        const auto& dfd(traits::cpp::disable_facet_directories());
        r.disable_facet_directories = s.select_type_by_name(dfd);
    }

    return r;
}

locator_configuration locator::make_configuration(
    const type_group& tg, const annotations::annotation& o) const {

    locator_configuration r;
    const annotations::field_selector fs(o);

    for (const auto& pair : tg.facets_type_group) {
        const auto fctn(pair.first);
        const auto& fct_tg(pair.second);
        locator_facet_configuration fct_cfg;
        fct_cfg.directory(fs.get_text_content_or_default(fct_tg.directory));
        fct_cfg.postfix(fs.get_text_content_or_default(fct_tg.postfix));
        r.facet_configurations()[fctn] = fct_cfg;
    }

    for (const auto& pair : tg.formatters_type_group) {
        const auto fmtn(pair.first);
        const auto fmt_tg(pair.second);
        locator_formatter_configuration fmt_cfg;

        if (fmt_tg.facet_directory) {
            const auto fd(*fmt_tg.facet_directory);
            fmt_cfg.facet_directory(fs.get_text_content_or_default(fd));
        }

        if (fmt_tg.facet_postfix) {
            const auto fd(*fmt_tg.facet_postfix);
            fmt_cfg.facet_postfix(fs.get_text_content_or_default(fd));
        }

        const auto pfix(fmt_tg.formatter_postfix);
        fmt_cfg.formatter_postfix(fs.get_text_content_or_default(pfix));

        r.formatter_configurations()[fmtn] = fmt_cfg;
    }

    const auto& hfe(tg.header_file_extension);
    r.header_file_extension(fs.get_text_content_or_default(hfe));

    const auto& ife(tg.implementation_file_extension);
    r.implementation_file_extension(fs.get_text_content_or_default(ife));

    const auto& idn(tg.include_directory_name);
    r.include_directory_name(fs.get_text_content_or_default(idn));

    const auto& sdn(tg.source_directory_name);
    r.source_directory_name(fs.get_text_content_or_default(sdn));

    const auto& dfd(tg.disable_facet_directories);
    r.disable_facet_directories(fs.get_boolean_content_or_default(dfd));

    return r;
}

locator_configuration locator::make_configuration(
    const annotations::type_repository& atrp, const formatters::container& fc,
    const annotations::annotation& o) {

    const auto tg(make_type_group (atrp, fc));
    const auto r(make_configuration(tg, o));
    return r;
}

const locator_formatter_configuration& locator::
configuration_for_formatter(const std::string& formatter_name) const {
    const auto& fmt_cfg(configuration_.formatter_configurations());
    const auto i(fmt_cfg.find(formatter_name));
    if (i == fmt_cfg.end()) {
        BOOST_LOG_SEV(lg, error) << missing_formatter_configuration;
        BOOST_THROW_EXCEPTION(building_error(missing_formatter_configuration));
    }

    return i->second;
}

boost::filesystem::path locator::make_project_path(
    const boost::filesystem::path& project_directory_path,
    const yarn::name& model_name) const {

    boost::filesystem::path r;
    const auto& mmp(model_name.location().model_modules());
    r = project_directory_path;
    r /= boost::algorithm::join(mmp, dot);
    return r;
}

boost::filesystem::path locator::make_facet_path(
    const std::string& formatter_name, const std::string& extension,
    const yarn::name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Making facet path for: " << n.id();

    const auto& fmt_cfg(configuration_for_formatter(formatter_name));

    boost::filesystem::path r;

    /*
     * If there is a facet directory, and it is configured to
     * contribute to the file name path, add it.
     */
    const auto& cfg(configuration_);
    if (!fmt_cfg.facet_directory().empty() && !cfg.disable_facet_directories())
        r /= fmt_cfg.facet_directory();

    /*
     * Add the module path of the modules internal to this model.
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

    if (!fmt_cfg.formatter_postfix().empty())
        stream << underscore << fmt_cfg.formatter_postfix();

    if (!fmt_cfg.facet_postfix().empty())
        stream << underscore << fmt_cfg.facet_postfix();

    stream << dot << extension;
    r /= stream.str();

    BOOST_LOG_SEV(lg, debug) << "Done making the facet path. Result: " << r;
    return r;
}

boost::filesystem::path locator::make_inclusion_path(
    const std::string& formatter_name, const std::string& extension,
    const yarn::name& n) const {

    boost::filesystem::path r;

    /*
     * Header files require both the external module path and the
     * model module path in the file name path.
     */
    for (const auto& m : n.location().external_modules())
        r /= m;

    const auto& mmp(n.location().model_modules());
    r /= boost::algorithm::join(mmp, dot);
    r /= make_facet_path(formatter_name, extension, n);
    return r;
}

boost::filesystem::path locator::make_inclusion_path_for_cpp_header(
    const yarn::name& n, const std::string& formatter_name) const {
    const auto extension(configuration_.header_file_extension());
    return make_inclusion_path(formatter_name, extension, n);
}

boost::filesystem::path locator::make_full_path_for_cpp_header(
    const yarn::name& n, const std::string& formatter_name) const {

    auto r(project_path_);
    r /= configuration_.include_directory_name();

    const auto extension(configuration_.header_file_extension());
    r /= make_inclusion_path_for_cpp_header(n, formatter_name);

    return r;
}

boost::filesystem::path locator::make_full_path_for_cpp_implementation(
    const yarn::name& n, const std::string& formatter_name) const {

    auto r(project_path_);
    r /= configuration_.source_directory_name();

    const auto extension(configuration_.implementation_file_extension());
    const auto facet_path(make_facet_path(formatter_name, extension, n));
    r /= facet_path;

    return r;
}

boost::filesystem::path locator::make_full_path_for_include_cmakelists(
    const yarn::name& n, const std::string& /*formatter_name*/) const {
    auto r(project_path_);
    r /= n.simple() + ".txt"; // FIXME: hack for extension
    return r;
}

boost::filesystem::path locator::make_full_path_for_source_cmakelists(
    const yarn::name& n, const std::string& /*formatter_name*/) const {
    auto r(project_path_);
    r /= configuration_.source_directory_name();
    r /= n.simple() + ".txt"; // FIXME: hack for extension
    return r;
}

boost::filesystem::path locator::make_full_path_for_odb_options(
    const yarn::name& /*n*/, const std::string& /*formatter_name*/) const {
    auto r(project_path_);
    r /= configuration_.source_directory_name();
    r /= "options.odb"; // FIXME: hack for filename
    return r;
}

std::unordered_map<std::string, std::string>
locator::facet_directories() const {
    std::unordered_map<std::string, std::string> r;

    for (const auto& pair : configuration_.facet_configurations()) {
        const auto fctn(pair.first);
        const auto fct_cfg(pair.second);
        r[fctn] = fct_cfg.directory();
    }

    return r;
}

} } } }
