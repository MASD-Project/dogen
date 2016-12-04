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
#include "dogen/quilt.csharp/types/workflow.hpp"

namespace {

const std::string name("quilt.csharp.workflow");

using namespace dogen::utility::log;
static logger lg(logger_factory(name));

const std::string dot(".");

}

namespace dogen {
namespace quilt {
namespace csharp {

std::string workflow::name() const {
    return ::name;
}

std::forward_list<boost::filesystem::path> workflow::
managed_directories(const options::knitting_options& ko,
    const yarn::name& model_name) const {
    const auto& mm(model_name.location().model_modules());
    const auto mn(boost::algorithm::join(mm, dot));
    std::forward_list<boost::filesystem::path> r;
    r.push_front(ko.output_directory_path() / mn);
    return r;
}

std::forward_list<annotations::archetype_location>
workflow::archetype_location() const {
    std::forward_list<annotations::archetype_location> r;
    return r;
}

std::forward_list<dogen::formatters::artefact> workflow::generate(
    const options::knitting_options& /*ko*/,
    const annotations::type_repository& /*atrp*/,
    const annotations::annotation_groups_factory& /*agf*/,
    const yarn::model& /*m*/) const {
    std::forward_list<dogen::formatters::artefact> r;
    return r;
}

} } }
