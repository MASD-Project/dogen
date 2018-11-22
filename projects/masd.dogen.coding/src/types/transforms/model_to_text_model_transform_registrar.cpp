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
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.coding/types/transforms/registrar_error.hpp"
#include "masd.dogen.coding/io/meta_model/languages_io.hpp"
#include "masd.dogen.coding/types/transforms/model_to_text_model_transform_registrar.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(
        "yarn.meta_model.model_to_text_model_transform_registrar"));

const std::string no_transforms("No model to text transforms provided.");
const std::string null_transform("Transform supplied is null");
const std::string language_taken("Transform already registered for language: ");

}

namespace masd::dogen::coding::transforms {

void model_to_text_model_transform_registrar::
register_transform(std::shared_ptr<model_to_text_model_transform_interface> t) {
    if (!t) {
        BOOST_LOG_SEV(lg, error) << null_transform;
        BOOST_THROW_EXCEPTION(registrar_error(null_transform));
    }

    const auto l(t->language());
    const auto pair(std::make_pair(l, t));
    const auto inserted(transforms_by_language_.insert(pair).second);
    if (!inserted) {
        std::ostringstream s;
        s << language_taken << l << " transform: " << t->id();
        const auto msg(s.str());
        BOOST_LOG_SEV(lg, error) << msg;
        BOOST_THROW_EXCEPTION(registrar_error(msg));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrered transform: " << t->id();
}

void model_to_text_model_transform_registrar::validate() const {
    if (transforms_by_language_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_transforms;
        BOOST_THROW_EXCEPTION(registrar_error(no_transforms));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

std::shared_ptr<model_to_text_model_transform_interface>
model_to_text_model_transform_registrar::
transform_for_language(const coding::meta_model::languages l) const {
    const auto i(transforms_by_language_.find(l));
    if (i == transforms_by_language_.end())
        return std::shared_ptr<model_to_text_model_transform_interface>();

    return i->second;
}

const std::unordered_map<coding::meta_model::languages, std::
                         shared_ptr<model_to_text_model_transform_interface>>&
model_to_text_model_transform_registrar::transforms_by_language() const {
    return transforms_by_language_;
}

}
