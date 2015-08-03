/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/tack/types/json_hydrator.hpp"
#include "dogen/frontend/types/json_tack_frontend.hpp"

using namespace dogen::utility::log;

namespace {

const std::string id("frontend.json_tack_frontend");
const std::list<std::string> extensions({ ".json" });
auto lg(logger_factory(id));
const std::string empty;

}

namespace dogen {
namespace frontend {

std::string json_tack_frontend::id() const {
    return ::id;
}

std::list<std::string> json_tack_frontend::supported_extensions() const {
    return ::extensions;
}

tack::model json_tack_frontend::
generate(const dynamic::workflow& w, const input_descriptor& id,
    const frontend_settings& /*s*/) {
    tack::json_hydrator h(w);
    return h.hydrate(id.path());
}

} }
