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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn.json/types/hydrator.hpp"
#include "dogen/yarn.json/types/frontend.hpp"

using namespace dogen::utility::log;

namespace {

const std::string id("yarn.json.frontend");
auto lg(logger_factory(id));
const std::string empty;

}

namespace dogen {
namespace yarn {
namespace json {

frontend::~frontend() noexcept { }

std::string frontend::id() const {
    return ::id;
}

std::list<std::string> frontend::supported_extensions() const {
    static const std::list<std::string> extensions({ ".json" });
    return extensions;
}

yarn::intermediate_model frontend::execute(const yarn::descriptor& d) {
    yarn::json::hydrator h;
    return h.hydrate(d.path(), d.is_target());
}

} } }
