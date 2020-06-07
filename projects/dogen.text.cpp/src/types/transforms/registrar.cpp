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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/set_io.hpp"
#include "dogen.utility/types/io/forward_list_io.hpp"
#include "dogen.physical/io/entities/meta_name_io.hpp"
#include "dogen.physical/types/helpers/meta_name_validator.hpp"
#include "dogen.physical/types/helpers/qualified_meta_name_builder.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/io/transforms/repository_io.hpp"
#include "dogen.text.cpp/types/transforms/registrar_error.hpp"
#include "dogen.text.cpp/types/transforms/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.cpp.transforms.registrar"));

const std::string no_transforms("Transform repository is empty.");
const std::string no_transforms_by_meta_name(
    "No transforms by meta name provided.");
const std::string null_transform("Transform supplied is null.");
const std::string facets_missing_canonical_archetype(
    "One or more facets have been declared without a canonical archetype");
const std::string more_than_one_canonical_archetype(
    "Found more than one canonical transform for a facet: ");
const std::string duplicate_archetype("Duplicate transform id: ");
const std::string empty_family("Family cannot be empty.");
const std::string null_helper_transform("Helper transform supplied is null");

}

namespace dogen::text::cpp::transforms {

void registrar::validate(std::shared_ptr<model_to_text_transform> t) const {
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
    physical::helpers::meta_name_validator::validate_archetype_name(mn);
}

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
    const auto& trp(transform_repository_);
    if (trp.stock_artefact_formatters_by_meta_name().empty()) {
        BOOST_LOG_SEV(lg, error) << no_transforms_by_meta_name;
        BOOST_THROW_EXCEPTION(registrar_error(no_transforms_by_meta_name));
    }

    if (trp.stock_artefact_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_transforms;
        BOOST_THROW_EXCEPTION(registrar_error(no_transforms));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is valid. Repository: " << trp;
}

void registrar::register_transform(std::shared_ptr<model_to_text_transform> f) {
    /*
     * First we ensure the transform is vaguely valid and insert it
     * into the main collection of stock transforms.
     */
    validate(f);
    auto& trp(transform_repository_);
    trp.stock_artefact_formatters_.push_front(f);

    /*
     * Add the transform to the index of transforms by meta-name.
     */
    const auto mn(f->archetype().logical_meta_element_id());
    auto& safbmt(trp.stock_artefact_formatters_by_meta_name());
    safbmt[mn].push_front(f);

    /*
     * Add transform to the index of transforms by archetype
     * name. Inserting the transform into this repository has the
     * helpful side-effect of ensuring the id is unique in physical
     * space.
     */
    const auto pmn(f->archetype().meta_name());
    const auto qn(pmn.qualified());
    auto& safba(trp.stock_artefact_formatters_by_archetype());
    const auto pair(std::make_pair(qn, f));
    const auto inserted(safba.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_archetype << qn;
        BOOST_THROW_EXCEPTION(registrar_error(duplicate_archetype + qn));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrered transform: '"
                             << f->archetype().meta_name().qualified()
                             << "' against meta name: '" << mn << "'";
}

void registrar::register_helper_transform(std::shared_ptr<helper_transform> ht) {
    validate(ht);
    auto& trp(transform_repository_);
    auto& f(trp.helper_formatters_[ht->family()]);
    for (const auto& of : ht->owning_formatters())
        f[of].push_back(ht);

    BOOST_LOG_SEV(lg, debug) << "Registrered helper transform: "
                             << ht->helper_name();
}

const repository& registrar::formatter_repository() const {
    return transform_repository_;
}

const std::unordered_map<
    std::string, std::unordered_map<
                     std::string,
                     std::list<
                         std::shared_ptr<helper_transform>>>>&
registrar::helper_formatters() const {
    return transform_repository_.helper_formatters();
}

}
