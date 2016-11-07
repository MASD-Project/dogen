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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/io/descriptor_io.hpp"
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/types/descriptor_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.descriptor_factory"));

const std::string library_dir("library");
const std::string comma(",");
const std::string at_least_one_argument(
    "Expected at least one argument for reference");
const std::string at_most_two_arguments(
    "Expected only at most two arguments for reference");

}

namespace dogen {
namespace yarn {

std::ostream&
operator<<(std::ostream& s, const descriptor_factory::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "descriptor_factory::type_group\"" << ", "
      << "\"references\": " << v.reference
      << " }";

    return s;
}

descriptor_factory::type_group descriptor_factory::
make_type_group(const annotations::type_repository& atrp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating type group.";

    type_group r;
    const annotations::type_repository_selector s(atrp);
    r.reference = s.select_type_by_name(traits::reference());
    return r;
}

std::list<std::string> descriptor_factory::make_references(const type_group& tg,
    const annotations::annotation& a) const {

    const annotations::entry_selector s(a);
    const auto& ref(tg.reference);
    if (s.has_entry(ref))
        return s.get_text_collection_content(ref);

    return std::list<std::string>{};
}

std::vector<boost::filesystem::path> descriptor_factory::to_library_dirs(
    const std::vector<boost::filesystem::path>& data_dirs) const {

    std::vector<boost::filesystem::path> r;
    r.reserve(data_dirs.size());
    for (const auto& dir : data_dirs)
        r.push_back(dir / library_dir);
    return r;
}

std::list<descriptor> descriptor_factory::
make(const std::vector<boost::filesystem::path>& dirs) const {

    BOOST_LOG_SEV(lg, debug) << "Creating descriptors for library models.";
    std::list<descriptor> r;
    for (const auto& dir : dirs) {
        BOOST_LOG_SEV(lg, trace) << "Directory: " << dir.generic_string();

        using namespace dogen::utility::filesystem;
        const auto files(find_files(dir));
        BOOST_LOG_SEV(lg, trace) << "Found " << files.size()
                                 << " paths to library models.";

        for (const auto& f: files) {
            BOOST_LOG_SEV(lg, trace) << "Library model: " << f.generic_string();

            descriptor d;
            d.path(f);
            d.is_target(false);
            d.extension(f.extension().string());
            r.push_back(d);
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Created descriptors for library models: " << r;
    return r;
}

std::list<descriptor>
descriptor_factory::make(const std::list<options::input>& refs) const {
    BOOST_LOG_SEV(lg, debug) << "Creating descriptors for reference models.";
    BOOST_LOG_SEV(lg, debug) << "Found " << refs.size() << " reference models.";

    std::list<descriptor> r;
    for (const auto ref: refs) {
        BOOST_LOG_SEV(lg, trace) << "Reference model: "
                                 << ref.path().generic_string();

        descriptor d;
        d.path(ref.path());
        d.external_modules(ref.external_modules());
        d.is_target(false);
        d.extension(ref.path().extension().string());
        r.push_back(d);
    }
    BOOST_LOG_SEV(lg, debug) << "Created descriptors for reference models: "
                             << r;
    return r;
}

std::list<descriptor>
descriptor_factory::make(const annotations::type_repository& atrp,
    const boost::filesystem::path& references_dir,
    const annotations::annotation& a) const {
    const auto tg(make_type_group(atrp));
    const auto refs(make_references(tg, a));
    std::list<descriptor> r;
    for (const auto& s : refs) {
        std::vector<std::string> tokens;
        boost::split(tokens, s, boost::is_any_of(comma));

        if (tokens.empty()) {
            BOOST_LOG_SEV(lg, error) << at_least_one_argument;
            BOOST_THROW_EXCEPTION(building_error(at_least_one_argument));
        }

        if (tokens.size() > 2) {
            BOOST_LOG_SEV(lg, error) << at_most_two_arguments;
            BOOST_THROW_EXCEPTION(building_error(at_most_two_arguments));
        }

        auto p(references_dir);
        p /= tokens[0];

        descriptor d;
        d.path(p);

        if (tokens.size() > 1)
            d.external_modules(tokens[1]);

        d.extension(p.extension().string());
        r.push_back(d);
    }
    return r;
}

descriptor descriptor_factory::make(const options::input& tg) const {
    BOOST_LOG_SEV(lg, debug) << "Creating descriptor for target model.";

    descriptor r;
    r.path(tg.path());
    r.is_target(true);
    r.external_modules(tg.external_modules());
    r.extension(tg.path().extension().string());

    BOOST_LOG_SEV(lg, trace) << "Added target model: " << r.path();
    BOOST_LOG_SEV(lg, debug) << "Created descriptor for target model: " << r;
    return r;
}

std::list<descriptor> descriptor_factory::
make(const std::vector<boost::filesystem::path>& data_dirs,
    const boost::filesystem::path& references_dir,
    const options::input_options& io,
    const annotations::type_repository& atrp,
    const annotations::annotation& a) const {

    const auto library_dirs(to_library_dirs(data_dirs));
    auto r(make(library_dirs));
    r.splice(r.end(), make(io.references()));
    r.splice(r.end(), make(atrp, references_dir, a));

    return r;
}

} }
