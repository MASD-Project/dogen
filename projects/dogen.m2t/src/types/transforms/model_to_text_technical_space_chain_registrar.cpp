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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.m2t/types/transforms/registrar_error.hpp"
#include "dogen.m2t/types/transforms/model_to_text_technical_space_chain_registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "m2t.transforms.model_to_text_technical_space_chain_registrar"));

const std::string no_transforms("No model to text transforms provided.");
const std::string null_transform("Transform supplied is null.");
const std::string technical_space_taken(
    "Transform already registered for technical space: ");

}

namespace dogen::m2t::transforms {

void model_to_text_technical_space_chain_registrar::
register_transform(
    std::shared_ptr<model_to_text_technical_space_chain> t) {
    if (!t) {
        BOOST_LOG_SEV(lg, error) << null_transform;
        BOOST_THROW_EXCEPTION(registrar_error(null_transform));
    }

    const auto ts(t->technical_space());
    const auto pair(std::make_pair(ts, t));
    const auto inserted(transforms_by_technical_space_.insert(pair).second);
    if (!inserted) {
        std::ostringstream s;
        s << technical_space_taken << ts << " transform: " << t->id();
        const auto msg(s.str());
        BOOST_LOG_SEV(lg, error) << msg;
        BOOST_THROW_EXCEPTION(registrar_error(msg));
    }

    BOOST_LOG_SEV(lg, debug) << "Registered transform: " << t->id();
}

void model_to_text_technical_space_chain_registrar::validate() const {
    if (transforms_by_technical_space_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_transforms;
        BOOST_THROW_EXCEPTION(registrar_error(no_transforms));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

std::shared_ptr<model_to_text_technical_space_chain>
model_to_text_technical_space_chain_registrar::
transform_for_technical_space(
    const logical::entities::technical_space ts) const {
    const auto i(transforms_by_technical_space_.find(ts));
    if (i == transforms_by_technical_space_.end())
        return std::shared_ptr<model_to_text_technical_space_chain>();

    return i->second;
}

const std::unordered_map<
    logical::entities::technical_space,
    std::shared_ptr<model_to_text_technical_space_chain>>&
model_to_text_technical_space_chain_registrar::
transforms_by_technical_space() const {
    return transforms_by_technical_space_;
}

}
