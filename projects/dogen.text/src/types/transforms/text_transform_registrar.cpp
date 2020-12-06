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
#include <set>
#include <iterator>
#include <algorithm>
#include <boost/throw_exception.hpp>
#include "dogen.text/types/transforms/text_transform_repository.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/set_io.hpp"
#include "dogen.utility/types/io/forward_list_io.hpp"
#include "dogen.identification/io/entities/logical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_name_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_validator.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_builder.hpp"
#include "dogen.text/io/transforms/text_transform_repository_io.hpp"
#include "dogen.text/types/transforms/registrar_error.hpp"
#include "dogen.text/types/transforms/text_transform_registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.transforms.text_transform_registrar"));

const std::string no_transforms_by_meta_name(
    "No transforms by meta name provided.");
const std::string null_transform("Transform supplied is null.");

}

namespace dogen::text::transforms {

void text_transform_registrar::
validate(std::shared_ptr<model_to_text_transform> t) const {
    /*
     * Must be pointing to a valid object.
     */
    if (!t) {
        BOOST_LOG_SEV(lg, error) << null_transform;
        BOOST_THROW_EXCEPTION(registrar_error(null_transform));
    }

    /*
     * Validate the physical meta-name.
     */
    const auto mn(t->archetype().meta_name());
    using identification::helpers::physical_meta_name_validator;
    physical_meta_name_validator::validate_archetype_name(mn);
}

void text_transform_registrar::validate() const {
    /*
     * We must have at least one registered transform. This is a quick
     * way of troubleshooting validation errors.
     */
    if (repository_.model_to_text_transforms_by_meta_name().empty()) {
        BOOST_LOG_SEV(lg, error) << no_transforms_by_meta_name;
        BOOST_THROW_EXCEPTION(registrar_error(no_transforms_by_meta_name));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is valid. Repository: "
                             << repository_;
}

void text_transform_registrar::
register_transform(std::shared_ptr<model_to_text_transform> f) {
    /*
     * First we ensure the transform is vaguely valid and insert it
     * into the main collection of stock transforms.
     */
    validate(f);

    /*
     * Add the transform to the index of transforms by meta-name.
     */
    const auto mn(f->archetype().logical_meta_element_id());
    auto& m2ts(repository_.model_to_text_transforms_by_meta_name());
    m2ts[mn].push_front(f);

    BOOST_LOG_SEV(lg, debug) << "Registrered transform: '"
                             << f->archetype().meta_name().id().value()
                             << "' against meta name: '" << mn << "'";
}

const text_transform_repository& text_transform_registrar::repository() const {
    return repository_;
}

}
