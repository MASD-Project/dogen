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
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include "dogen.utility/log/logger.hpp"
#include "dogen.annotations/types/entry_selector.hpp"
#include "dogen.annotations/types/type_repository_selector.hpp"
#include "dogen.quilt.csharp/types/traits.hpp"
#include "dogen.quilt.csharp/types/formattables/location_error.hpp"
#include "dogen.quilt.csharp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen.quilt.csharp/types/formattables/locator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.csharp.formattables.locator"));

const std::string empty;
const std::string extension("cs");
const std::string dot(".");

const std::string missing_archetype_configuration(
    "Could not find configuration for archetype: ");

}

namespace dogen {
namespace quilt {
namespace csharp {
namespace formattables {

locator::locator(const boost::filesystem::path& output_directory_path,
    const annotations::type_repository& atrp, const formatters::repository& frp,
    const annotations::annotation& root,
    const yarn::meta_model::name& model_name,
    const std::unordered_set<std::string>& module_ids,
    const bool enable_backend_directories)
    : model_name_(model_name),
      configuration_(make_configuration(atrp, frp, root)),
      module_ids_(module_ids),
      project_path_(make_project_path(output_directory_path, model_name,
              configuration_, enable_backend_directories)) {}

locator::type_group locator::make_type_group(
    const annotations::type_repository& atrp,
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

    const auto& kdn(traits::backend_directory_name());
    r.backend_directory_name = s.select_type_by_name(kdn);

    return r;
}

locator_configuration locator::make_configuration(
    const type_group& tg, const annotations::annotation& a) const {

    locator_configuration r;
    const annotations::entry_selector s(a);

    const auto& kdn(tg.backend_directory_name);
    r.backend_directory_name(s.get_text_content_or_default(kdn));

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

    return r;
}

locator_configuration locator::make_configuration(
    const annotations::type_repository& atrp, const formatters::repository& frp,
    const annotations::annotation& o) {

    const auto tg(make_type_group (atrp, frp));
    const auto r(make_configuration(tg, o));
    return r;
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

boost::filesystem::path locator::make_project_path(
    const boost::filesystem::path& output_directory_path,
    const yarn::meta_model::name& model_name, const locator_configuration& lc,
    const bool enable_backend_directories) const {

    boost::filesystem::path r;
    const auto& mmp(model_name.location().model_modules());
    r = output_directory_path;
    r /= boost::algorithm::join(mmp, dot);
    if (enable_backend_directories) {
        // FIXME: check directory name is not empty
        r /= lc.backend_directory_name();
    }

    return r;
}

boost::filesystem::path locator::make_facet_path(
    const std::string& archetype, const std::string& extension,
    const yarn::meta_model::name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Making facet path for: " << n.id();

    const auto& arch_cfg(configuration_for_archetype(archetype));

    boost::filesystem::path r;

    /*
     * If there is a facet directory, and it is configured to
     * contribute to the file name path, add it.
     */
    const auto& cfg(configuration_);
    if (!arch_cfg.facet_directory().empty() && !cfg.disable_facet_directories())
        r /= arch_cfg.facet_directory();

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

    if (!arch_cfg.archetype_postfix().empty())
        stream << arch_cfg.archetype_postfix();

    if (!arch_cfg.facet_postfix().empty())
        stream << arch_cfg.facet_postfix();

    if (!extension.empty())
        stream << dot << extension;

    r /= stream.str();

    BOOST_LOG_SEV(lg, debug) << "Done making the facet path. Result: " << r;
    return r;
}

const boost::filesystem::path locator::project_path() const {
    return project_path_;
}

boost::filesystem::path locator::make_relative_path(
    const boost::filesystem::path& full_path) const {

    const std::string fp(full_path.generic_string());
    std::string pp(project_path_.generic_string());
    pp += "/";
    return boost::replace_first_copy(fp, pp, empty);
}

boost::filesystem::path locator::make_full_path(
    const yarn::meta_model::name& n, const std::string& archetype) const {

    auto r(project_path_);
    const auto facet_path(make_facet_path(archetype, extension, n));
    r /= facet_path;
    return r;
}

boost::filesystem::path locator::make_full_path_for_project(
    const yarn::meta_model::name& n, const std::string& archetype) const {
    auto r(project_path_);
    const auto facet_path(make_facet_path(archetype, empty, n));
    r /= facet_path;
    return r;
}

boost::filesystem::path locator::make_full_path_for_solution(
    const yarn::meta_model::name& n, const std::string& archetype) const {
    auto r(project_path_);
    const auto facet_path(make_facet_path(archetype, empty, n));
    r /= facet_path;
    return r;
}

} } } }
