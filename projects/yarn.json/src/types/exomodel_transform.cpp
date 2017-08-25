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
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn.json/types/hydrator.hpp"
#include "dogen/yarn.json/types/dehydrator.hpp"
#include "dogen/yarn.json/types/exomodel_transform.hpp"

namespace {

using namespace dogen::utility::log;
const std::string id("yarn.json.exomodel_transform");
auto lg(logger_factory(id));

const std::string extension(".json");

}

namespace dogen {
namespace yarn {
namespace json {

exomodel_transform::~exomodel_transform() noexcept {}

std::string exomodel_transform::id() const {
    return ::id;
}

yarn::transforms::exomodel_transform_types
exomodel_transform::transform_types() const {
    return yarn::transforms::exomodel_transform_types::bidirectional;
}

std::list<std::string> exomodel_transform::supported_extensions() const {
    static const auto extensions = std::list<std::string> { extension };
    return extensions;
}

meta_model::exomodel
exomodel_transform::transform(const boost::filesystem::path& p) {
    hydrator h;
    return h.hydrate(p);
}

void exomodel_transform::transform(const meta_model::exomodel& em,
    const boost::filesystem::path& p) {
     return dehydrator::dehydrate(em, p);
}

} } }
