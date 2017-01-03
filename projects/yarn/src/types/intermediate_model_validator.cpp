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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/yarn/types/intermediate_model_validator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.intermediate_model_validator"));

}

namespace dogen {
namespace yarn {

namespace {

class name_accumulator final {
public:
    void operator()(const yarn::concept& /*c*/) {}
    void operator()(const yarn::primitive& /*p*/) {}
    void operator()(const dogen::yarn::visitor& /*v*/) { }
    void operator()(const yarn::enumeration& /*e*/) { }
    void operator()(const yarn::object& /*o*/) { }
    void operator()(const yarn::exception& /*e*/) { }
    void operator()(const yarn::module& /*m*/) { }

public:
    const std::list<name>& result() const;

private:
    std::list<name> result_;
};

}

void intermediate_model_validator::
sanity_check_all_names(const intermediate_model& im) const {
    name_accumulator na;
    yarn::elements_traversal(im, na);
}

void intermediate_model_validator::
validate(const intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Started validation. Model: " << im.name().id();

    BOOST_LOG_SEV(lg, debug) << "Finished validation.";
}

} }
