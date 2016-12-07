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
#include "dogen/quilt.cpp/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.workflow"));

const std::string empty;
const std::string dot(".");

}

namespace dogen {
namespace quilt {
namespace cpp {

workflow::~workflow() noexcept { }

formattables::model workflow::create_formattables_model(
    const options::knitting_options& ko,
    const annotations::type_repository& atrp,
    const annotations::annotation& ra,
    const dogen::formatters::decoration_properties_factory& dpf,
    const formatters::repository& frp, const bool enable_kernel_directories,
    const yarn::model& m) const {
    formattables::workflow fw;
    return fw.execute(ko, atrp, ra, dpf, frp, enable_kernel_directories, m);
}

std::forward_list<boost::filesystem::path>
workflow::managed_directories(const options::knitting_options& ko,
    const yarn::name& model_name) const {
    const auto& mm(model_name.location().model_modules());
    const auto mn(boost::algorithm::join(mm, dot));
    std::forward_list<boost::filesystem::path> r;
    r.push_front(ko.output_directory_path() / mn);
    return r;
}

std::forward_list<dogen::formatters::artefact>
workflow::format(const annotations::type_repository& atrp,
    const annotations::annotation_groups_factory& agf,
    const dogen::formatters::repository& drp,
    const formattables::model& fm) const {
    formatters::workflow wf(atrp, agf, drp);
    return wf.execute(fm);
}

annotations::archetype_location workflow::archetype_location() const {
    static annotations::archetype_location r(traits::family(), traits::kernel(),
        empty/*facet*/, empty/*archetype*/);
    return r;
}

std::forward_list<annotations::archetype_location>
workflow::archetype_locations() const {
    return formatters::workflow::registrar().archetype_locations();
}

std::forward_list<dogen::formatters::artefact>
workflow::generate(const options::knitting_options& ko,
    const annotations::type_repository& atrp,
    const annotations::annotation_groups_factory& agf,
    const dogen::formatters::repository& drp,
    const dogen::formatters::decoration_properties_factory& dpf,
    const bool enable_kernel_directories,
    const yarn::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started backend.";

    const auto ra(m.root_module().annotation());
    const auto& frp(formatters::workflow::registrar().formatter_repository());
    const bool ekd(enable_kernel_directories);
    const auto fm(create_formattables_model(ko, atrp, ra, dpf, frp, ekd, m));
    const auto r(format(atrp, agf, drp, fm));

    BOOST_LOG_SEV(lg, debug) << "Finished backend.";
    return r;
}

} } }
