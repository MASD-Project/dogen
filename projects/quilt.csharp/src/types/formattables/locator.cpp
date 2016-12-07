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
#include <boost/algorithm/string/join.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/quilt.csharp/types/formattables/locator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.csharp.formattables.locator"));

const std::string empty;
const std::string extension("cs");
const std::string underscore("_");
const std::string double_quote("\"");
const std::string dot(".");
const std::string separator("_");

const std::string missing_archetype_configuration(
    "Could not find configuration for archetype: ");

}

namespace dogen {
namespace quilt {
namespace csharp {
namespace formattables {

locator::locator(const boost::filesystem::path& output_directory_path,
    const annotations::type_repository& atrp, const formatters::repository& frp,
    const annotations::annotation& root, const yarn::name& model_name,
    const std::unordered_set<std::string>& module_ids,
    const bool enable_kernel_directories)
    : model_name_(model_name),
      configuration_(make_configuration(atrp, frp, root)),
      module_ids_(module_ids),
      project_path_(make_project_path(output_directory_path, model_name,
              configuration_, enable_kernel_directories)) {}

locator::type_group locator::make_type_group(
    const annotations::type_repository& atrp,
    const formatters::repository& /*frp*/) const {

    type_group r;
    const annotations::type_repository_selector s(atrp);

    const auto& kdn(traits::kernel_directory_name());
    r.kernel_directory_name = s.select_type_by_name(kdn);

    return r;
}

locator_configuration locator::make_configuration(
    const type_group& tg, const annotations::annotation& o) const {

    locator_configuration r;
    const annotations::entry_selector s(o);

    const auto& kdn(tg.kernel_directory_name);
    r.kernel_directory_name(s.get_text_content_or_default(kdn));

    return r;
}

locator_configuration locator::make_configuration(
    const annotations::type_repository& atrp, const formatters::repository& frp,
    const annotations::annotation& o) {

    const auto tg(make_type_group (atrp, frp));
    const auto r(make_configuration(tg, o));
    return r;
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
        // FIXME: check directory name is not empty
        r /= lc.kernel_directory_name();
    }

    return r;
}

boost::filesystem::path locator::make_facet_path(
    const std::string& /*archetype*/, const std::string& extension,
    const yarn::name& n) const {
    BOOST_LOG_SEV(lg, debug) << "Making facet path for: " << n.id();

    const std::string facet_directory;
    // const auto& arch_cfg(configuration_for_archetype(archetype));

    boost::filesystem::path r;

    /*
     * If there is a facet directory, and it is configured to
     * contribute to the file name path, add it.
     */
    const auto& cfg(configuration_);
    if (!facet_directory.empty() && !cfg.disable_facet_directories())
        r /= facet_directory;

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

    stream << dot << extension;
    r /= stream.str();

    BOOST_LOG_SEV(lg, debug) << "Done making the facet path. Result: " << r;
    return r;
}

boost::filesystem::path locator::make_full_path(
    const yarn::name& n, const std::string& archetype) const {

    auto r(project_path_);
    const auto facet_path(make_facet_path(archetype, extension, n));
    r /= facet_path;
    return r;
}

} } } }
