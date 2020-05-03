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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.text/types/transforms/registrar_error.hpp"
#include "dogen.text/types/transforms/text_to_text_transform.hpp"
#include "dogen.text/types/transforms/text_to_text_transform_registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("text.transforms.text_to_text_transform_registrar"));

const std::string no_transforms("No text to text transforms provided.");
const std::string null_transform("Transform supplied is null.");
const std::string duplicate_id("Transform already registered with ID: ");

}

namespace dogen::text::transforms {

void text_to_text_transform_registrar::
register_transform(std::shared_ptr<text_to_text_transform> t) {
    if (!t) {
        BOOST_LOG_SEV(lg, error) << null_transform;
        BOOST_THROW_EXCEPTION(registrar_error(null_transform));
    }

    const auto id(t->id());
    const auto pair(std::make_pair(id, t));
    const auto inserted(transforms_by_id_.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_id << id;
        BOOST_THROW_EXCEPTION(registrar_error(duplicate_id + id));
    }

    BOOST_LOG_SEV(lg, debug) << "Registered transform: " << id;
}

void text_to_text_transform_registrar::validate() const {
    if (transforms_by_id_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_transforms;
        BOOST_THROW_EXCEPTION(registrar_error(no_transforms));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

std::shared_ptr<text_to_text_transform>text_to_text_transform_registrar::
transforms_for_id(const std::string& id) const {
    const auto i(transforms_by_id_.find(id));
    if (i == transforms_by_id_.end())
        return std::shared_ptr<text_to_text_transform>();

    return i->second;
}

}
