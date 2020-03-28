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
#include "dogen.utility/types/io/forward_list_io.hpp"
#include "dogen.physical/io/entities/name_io.hpp"
#include "dogen.physical/types/helpers/name_validator.hpp"
#include "dogen.m2t.csharp/io/transforms/repository_io.hpp"
#include "dogen.m2t.csharp/types/transforms/registrar_error.hpp"
#include "dogen.m2t.csharp/types/transforms/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("m2t.csharp.formatters.registrar"));

const std::string no_transforms("Transform repository is empty.");
const std::string no_transforms_by_meta_name(
    "No transforms by meta name provided.");

const std::string null_transform_helper("Helper transform supplied is null");
const std::string null_transform("Transform supplied is null.");
const std::string duplicate_archetype("Duplicate formatter name: ");
const std::string empty_family("Family cannot be empty.");

}

namespace dogen::m2t::csharp::transforms {

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

    BOOST_LOG_SEV(lg, debug) << "Archetype locations: " << physical_names_;
}

void registrar::register_transform(std::shared_ptr<model_to_text_transform> t) {
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
    const auto& n(t->physical_name());
    physical::helpers::name_validator::validate_archetype_name(n);

    /*
     * Insert it into the main collection of stock transforms.
     */
    transform_repository_.stock_artefact_formatters_.push_front(t);

    /*
     * Add the transform to the archetype location stores. Note that
     * we need not worry about canonical archetypes since this backend
     * does not have them.
     */
    physical_names_.push_front(n);
    const auto mn(t->meta_name().qualified().dot());
    auto& alg(physical_names_by_meta_name_[mn]);
    alg.names().push_back(n);

    /*
     * Add the transform to the index by meta-name.
     */
    auto& safmt(transform_repository_.stock_artefact_formatters_by_meta_name());
    safmt[mn].push_front(t);

    /*
     * Add transform to the index by archetype name. Inserting the
     * transform into this repository has the helpful side-effect of
     * ensuring the id is unique in physical space.
     */
    const auto& l(n.location());
    const auto arch(l.archetype());
    auto& fffn(transform_repository_.stock_artefact_formatters_by_archetype());
    const auto pair(std::make_pair(arch, t));
    const auto inserted(fffn.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_archetype << arch;
        BOOST_THROW_EXCEPTION(registrar_error(duplicate_archetype + arch));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrered transform: " << t->id()
                             << " against meta name: " << mn;
}

void registrar::
register_helper_transform(std::shared_ptr<helper_transform> ht) {
    if (!ht) {
        BOOST_LOG_SEV(lg, error) << null_transform_helper;
        BOOST_THROW_EXCEPTION(registrar_error(null_transform_helper));
    }

    if(ht->family().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_family;
        BOOST_THROW_EXCEPTION(registrar_error(empty_family));
    }

    auto& f(transform_repository_.helper_formatters_[ht->family()]);
    for (const auto& of : ht->owning_formatters())
        f[of].push_back(ht);

    BOOST_LOG_SEV(lg, debug) << "Registrered formatter helper: "
                             << ht->helper_name();
}

const repository& registrar::formatter_repository() const {
    return transform_repository_;
}

const std::forward_list<physical::entities::name>&
registrar::physical_names() const {
    return physical_names_;
}

const std::unordered_map<std::string, physical::entities::name_group>&
registrar::physical_names_by_meta_name() const {
    return physical_names_by_meta_name_;
}

const std::unordered_map<std::string, std::list<physical::entities::name>>&
registrar::physical_names_by_family() const {
    return physical_names_by_family_;
}

const physical::entities::name_repository_parts&
registrar::physical_name_repository_parts() const {
    return physical_name_repository_parts_;
}

}
