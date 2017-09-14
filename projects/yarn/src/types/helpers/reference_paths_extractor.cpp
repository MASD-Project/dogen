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
#include <ostream>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/io/meta_model/languages_io.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/helpers/reference_paths_extractor.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.helpers.reference_paths_extractor"));

const std::string library_dir("library");

}

namespace dogen {
namespace yarn {
namespace helpers {

std::ostream&
operator<<(std::ostream& s, const reference_paths_extractor::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::"
      << "descriptor_factory::type_group\"" << ", "
      << "\"references\": " << v.reference
      << " }";

    return s;
}

reference_paths_extractor::type_group reference_paths_extractor::
make_type_group(const annotations::type_repository& atrp) {
    BOOST_LOG_SEV(lg, debug) << "Creating type group.";

    type_group r;
    const annotations::type_repository_selector s(atrp);
    r.reference = s.select_type_by_name(traits::reference());

    BOOST_LOG_SEV(lg, debug) << "Created type group. Result: " << r;
    return r;
}

std::list<std::string> reference_paths_extractor::
make_user_references(const type_group& tg, const annotations::annotation& a) {

    const annotations::entry_selector s(a);
    const auto& ref(tg.reference);
    if (s.has_entry(ref))
        return s.get_text_collection_content(ref);

    return std::list<std::string>{};
}

std::vector<boost::filesystem::path> reference_paths_extractor::to_library_dirs(
    const std::vector<boost::filesystem::path>& data_dirs) {

    std::vector<boost::filesystem::path> r;
    r.reserve(data_dirs.size());
    for (const auto& dir : data_dirs)
        r.push_back(dir / library_dir);
    return r;
}

std::list<boost::filesystem::path> reference_paths_extractor::
obtain_paths_to_system_models(const transforms::context& ctx) {
    const auto library_dirs(to_library_dirs(ctx.data_directories()));

    BOOST_LOG_SEV(lg, debug) << "Creating descriptors for library models.";
    std::list<boost::filesystem::path> r;
    for (const auto& dir : library_dirs) {
        BOOST_LOG_SEV(lg, trace) << "Directory: " << dir.generic_string();

        using namespace dogen::utility::filesystem;
        const auto files(find_files(dir));
        BOOST_LOG_SEV(lg, trace) << "Found " << files.size()
                                 << " paths to library models.";

        for (const auto& f : files) {
            BOOST_LOG_SEV(lg, trace) << "Library model: " << f.generic_string();
            r.push_back(f);
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Created descriptors for library models: " << r;
    return r;
}

std::list<boost::filesystem::path>
reference_paths_extractor::
obtain_paths_to_user_references(const transforms::context& ctx,
    const annotations::annotation& ra) {

    const auto target_dir(ctx.transform_options().target().parent_path());
    const auto tg(make_type_group(ctx.type_repository()));
    const auto refs(make_user_references(tg, ra));
    std::list<boost::filesystem::path> r;
    for (const auto& ref : refs) {
        const auto p(target_dir / ref);
        r.push_back(p);
    }
    return r;
}

std::list<boost::filesystem::path>
reference_paths_extractor::extract(const transforms::context& ctx,
    const meta_model::endomodel& target) {
    /*
     * Obtain the root annotation and read the requested user
     * references from it.
     */
    const auto& ra(target.root_module()->annotation());
    auto r(obtain_paths_to_user_references(ctx, ra));

    /*
     * Now obtain references to all system models, given the system
     * data directories.
     */
    r.splice(r.end(), obtain_paths_to_system_models(ctx));
    return r;
}

} } }
