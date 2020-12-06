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
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/forward_list_io.hpp"
#include "dogen.identification/io/entities/physical_meta_id_io.hpp"
#include "dogen.identification/io/entities/physical_meta_name_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_validator.hpp"
#include "dogen.text.csharp/io/transforms/repository_io.hpp"
#include "dogen.text.csharp/types/transforms/registrar_error.hpp"
#include "dogen.text.csharp/types/transforms/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.csharp.transforms.registrar"));

const std::string no_transforms("Transform repository is empty.");
const std::string no_transforms_by_meta_name(
    "No transforms by meta name provided.");

const std::string null_transform("Transform supplied is null.");
const std::string duplicate_archetype("Duplicate formatter name: ");
const std::string empty_family("Family cannot be empty.");

}

namespace dogen::text::csharp::transforms {

void registrar::validate() const {
    /*
     * We must have at least one registered formatter. This is a quick
     * way of troubleshooting validation errors.
     */
    const auto& frp(transform_repository_);
    if (frp.stock_artefact_formatters_by_meta_name().empty()) {
        BOOST_LOG_SEV(lg, error) << no_transforms_by_meta_name;
        BOOST_THROW_EXCEPTION(registrar_error(no_transforms_by_meta_name));
    }

    if (frp.stock_artefact_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_transforms;
        BOOST_THROW_EXCEPTION(registrar_error(no_transforms));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state. Repository: "
                             << frp;
}

void registrar::register_transform(std::shared_ptr<
    text::transforms::model_to_text_transform> t) {
    /*
     * Must be pointing to a valid object.
     */
    if (!t) {
        BOOST_LOG_SEV(lg, error) << null_transform;
        BOOST_THROW_EXCEPTION(registrar_error(null_transform));
    }

    /*
     * Validate the physical name.
     */
    const auto pmn(t->archetype().meta_name());
    using identification::helpers::physical_meta_name_validator;
    physical_meta_name_validator::validate_archetype_name(pmn);

    /*
     * Insert it into the main collection of stock transforms.
     */
    transform_repository_.stock_artefact_formatters_.push_front(t);

    /*
     * Add the transform to the index by meta-name.
     */
    const auto lmn(t->archetype().logical_meta_element_id());
    auto& safmt(transform_repository_.stock_artefact_formatters_by_meta_name());
    safmt[lmn].push_front(t);

    /*
     * Add transform to the index by archetype name. Inserting the
     * transform into this repository has the helpful side-effect of
     * ensuring the id is unique in physical space.
     */
    const auto pid(pmn.id());
    auto& safba(transform_repository_.stock_artefact_formatters_by_archetype());
    const auto pair(std::make_pair(pid, t));
    const auto inserted(safba.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_archetype << pid;
        BOOST_THROW_EXCEPTION(
            registrar_error(duplicate_archetype + pid.value()));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrered transform: "
                             << t->archetype().meta_name().id().value()
                             << " against meta name: " << pmn;
}

const repository& registrar::formatter_repository() const {
    return transform_repository_;
}

}
