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
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/formatters/types/repository_factory.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/workflow.hpp"
#include "dogen/quilt.cpp/types/formattables/workflow.hpp"
#include "dogen/quilt.cpp/types/kernel.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(dogen::quilt::cpp::traits::kernel()));

const std::string empty;
const std::string dot(".");

}

namespace dogen {
namespace quilt {
namespace cpp {

kernel::~kernel() noexcept { }

formattables::model kernel::create_formattables_model(
    const annotations::type_repository& atrp,
    const annotations::annotation& ra,
    const dogen::formatters::decoration_properties_factory& dpf,
    const formatters::repository& frp, const formattables::locator& l,
    const yarn::model& m) const {
    formattables::workflow fw;
    return fw.execute(atrp, ra, dpf, l, frp, m);
}

formattables::locator kernel::make_locator(const options::knitting_options& ko,
    const annotations::type_repository& atrp, const annotations::annotation& ra,
    const formatters::repository& frp, const bool enable_kernel_directories,
    const yarn::model& m) const {

    const auto& mn(m.name());
    const auto odp(ko.output_directory_path());
    const auto chodp(ko.cpp_headers_output_directory_path());
    const auto ekd(enable_kernel_directories);
    const auto ids(m.module_ids());
    const formattables::locator r(odp, chodp, atrp, frp, ra, mn, ids, ekd);
    return r;
}

std::string kernel::id() const {
    return archetype_location().kernel();
}

std::list<dogen::formatters::artefact>
kernel::format(const annotations::type_repository& atrp,
    const annotations::annotation_groups_factory& agf,
    const dogen::formatters::repository& drp,
    const formattables::model& fm) const {
    formatters::workflow wf(atrp, agf, drp);
    return wf.execute(fm);
}

std::list<boost::filesystem::path> kernel::
managed_directories(const formattables::locator& l) const {
    std::list<boost::filesystem::path> r;
    r.push_back(l.project_path());
    if (l.project_path() != l.headers_project_path())
      r.push_back(l.headers_project_path());

    return r;
}

annotations::archetype_location kernel::archetype_location() const {
    static annotations::archetype_location r(traits::family(), traits::kernel(),
        empty/*facet*/, empty/*archetype*/);
    return r;
}

std::forward_list<annotations::archetype_location>
kernel::archetype_locations() const {
    return formatters::workflow::registrar().archetype_locations();
}

yarn::languages kernel::language() const {
    return yarn::languages::cpp;
}

kernel_output kernel::generate(const options::knitting_options& ko,
    const annotations::type_repository& atrp,
    const annotations::annotation_groups_factory& agf,
    const dogen::formatters::repository& drp,
    const dogen::formatters::decoration_properties_factory& dpf,
    const bool enable_kernel_directories,
    const yarn::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started kernel.";

    const auto ra(m.root_module().annotation());
    const auto& frp(formatters::workflow::registrar().formatter_repository());
    const auto l(make_locator(ko, atrp, ra, frp, enable_kernel_directories, m));
    const auto fm(create_formattables_model(atrp, ra, dpf, frp, l, m));

    kernel_output r;
    r.artefacts(format(atrp, agf, drp, fm));
    r.managed_directories(managed_directories(l));

    BOOST_LOG_SEV(lg, debug) << "Finished kernel.";
    return r;
}

} } }
