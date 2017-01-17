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
#include "dogen/yarn/types/frontend_error.hpp"
#include "dogen/upsilon/types/hydrator.hpp"
#include "dogen/yarn.upsilon/types/workflow.hpp"
#include "dogen/yarn.upsilon/types/frontend.hpp"

namespace {

using namespace dogen::utility::log;
const std::string id("yarn.upsilon.frontend");
auto lg(logger_factory(id));
const std::string empty;

const std::string no_writing_support(
    "Writing not supported for yarn.upsilon frontend");

const std::string extension("Configuration.xml");

}

namespace dogen {
namespace yarn {
namespace upsilon {

frontend::~frontend() noexcept { }

std::string frontend::id() const {
    return ::id;
}

bool frontend::can_read(const boost::filesystem::path& p) const {
    const auto gs(p.generic_string());
    return boost::ends_with(gs, extension);
}

yarn::intermediate_model frontend::read(const yarn::descriptor& d) {
    BOOST_LOG_SEV(lg, debug) << "Reading Upsilon model.";
    dogen::upsilon::hydrator h;
    const auto m(h.hydrate(d.path()));
    BOOST_LOG_SEV(lg, debug) << "Read Upsilon model.";

    BOOST_LOG_SEV(lg, debug) << "Converting it into yarn.";
    workflow w;
    const auto r(w.execute(m));
    BOOST_LOG_SEV(lg, debug) << "Finished converting it into yarn.";

    return r;
}

bool frontend::can_write() const {
    return false;
}

void frontend::
write(const intermediate_model& /*im*/, const descriptor& /*d*/) {
    BOOST_LOG_SEV(lg, error) << no_writing_support;
    BOOST_THROW_EXCEPTION(frontend_error(no_writing_support));
}

} } }
