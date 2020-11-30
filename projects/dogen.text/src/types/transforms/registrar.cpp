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
#include "dogen.text/io/transforms/repository_io.hpp"
#include "dogen.text/types/transforms/registrar_error.hpp"
#include "dogen.text/types/transforms/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.transforms.registrar"));

const std::string null_helper_transform("Helper transform supplied is null");
const std::string null_transform("Transform supplied is null.");
const std::string duplicate_archetype("Duplicate formatter name: ");
const std::string empty_family("Family cannot be empty.");
const std::string no_helpers_by_family("No helpers by family provided.");

}

namespace dogen::text::transforms {

void registrar::validate(std::shared_ptr<helper_transform> ht) const {
    /*
     * Must be pointing to a valid object.
     */
    if (!ht) {
        BOOST_LOG_SEV(lg, error) << null_helper_transform;
        BOOST_THROW_EXCEPTION(registrar_error(null_helper_transform));
    }

    /*
     * Helper family must be populated
     */
    if(ht->family().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_family;
        BOOST_THROW_EXCEPTION(registrar_error(empty_family));
    }
}

void registrar::validate() const {
    /*
     * We must have at least one registered transform. This is a quick
     * way of troubleshooting validation errors.
     */
    if (repository_.helpers_by_family().empty()) {
        BOOST_LOG_SEV(lg, error) << no_helpers_by_family;
        BOOST_THROW_EXCEPTION(registrar_error(no_helpers_by_family));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is valid. Repository: "
                             << repository_;
}

void registrar::register_helper_transform(std::shared_ptr<helper_transform> ht) {
    validate(ht);
    auto& hbf(repository_.helpers_by_family()[ht->family()]);
    for (const auto& of : ht->owning_formatters()) {
        identification::entities::physical_meta_id pid(of);
        hbf[pid].push_back(ht);
    }

    BOOST_LOG_SEV(lg, debug) << "Registrered helper transform: "
                             << ht->helper_name();

}

const repository& registrar::helper_repository() const {
    return repository_;
}

}
