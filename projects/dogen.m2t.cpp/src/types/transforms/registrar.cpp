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
#include "dogen.physical/types/helpers/name_validator.hpp"
#include "dogen.physical/types/helpers/qualified_name_builder.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/io/transforms/repository_io.hpp"
#include "dogen.m2t.cpp/types/transforms/registrar_error.hpp"
#include "dogen.m2t.cpp/types/transforms/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("m2t.cpp.transforms.registrar"));

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

namespace dogen::m2t::cpp::transforms {

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
    const auto& mn(t->physical_name());
    physical::helpers::name_validator::validate_archetype_name(mn);
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

    /*
     * Validate the registered canonical transforms.
     */
    const auto cs(inclusion_support_types::canonical_support);
    for (const auto& pair : trp.stock_artefact_formatters_by_meta_name()) {
        const auto mn(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing type: " << mn;

        const auto& transforms(pair.second);
        std::set<std::string> facets_found;
        std::set<std::string> all_facets;
        using qnb = physical::helpers::qualified_name_builder;
        for (const auto& ptr : transforms) {
            const auto& transform(*ptr);
            const auto pn(transform.physical_name());
            const auto fct(qnb::build_facet(pn));
            all_facets.insert(fct);
            if (transform.inclusion_support_type() != cs)
                continue;

            /*
             * We can only have one canonical transform per type per
             * facet.
             */
            const auto i(facets_found.find(fct));
            if (i != facets_found.end()) {
                const auto arch(pn.qualified());
                BOOST_LOG_SEV(lg, error) << more_than_one_canonical_archetype
                                         << fct << " archetype: " << arch
                                         << " meta name: " << mn;
                BOOST_THROW_EXCEPTION(registrar_error(
                        more_than_one_canonical_archetype + fct));
            }
            facets_found.insert(fct);
        }

        BOOST_LOG_SEV(lg, debug) << "All Facets: " << all_facets;
        BOOST_LOG_SEV(lg, debug) << "Facets found: " << facets_found;

        /*
         * We should have one canonical transform per type per
         * facet. However, there are certain facet such as build and
         * visual studio where we don't actually require canonical
         * archetypes so we just warn.
         */
        std::set<std::string> result;
        std::set_difference(all_facets.begin(), all_facets.end(),
            facets_found.begin(), facets_found.end(),
            std::inserter(result, result.end()));
        if (!result.empty()) {
            BOOST_LOG_SEV(lg, warn) << facets_missing_canonical_archetype
                                     << " : " << result;
        }
    }

    if (trp.stock_artefact_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_transforms;
        BOOST_THROW_EXCEPTION(registrar_error(no_transforms));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is valid. Repository: " << trp;
    BOOST_LOG_SEV(lg, debug) << "Physical names: " << physical_names_;
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
     * Add the transform to the physical names stores.
     */
    const auto& pmn(f->physical_name());
    physical_names_.push_front(pmn);

    /*
     * Handle the meta-type collection of physical names.
     */
    const auto mn(f->meta_name().qualified().dot());
    auto& g(physical_names_by_meta_name_[mn]);
    g.meta_names().push_back(pmn);

    /*
     * If the archetype location points to a canonical archetype,
     * update the canonical archetype mapping.
     */
    auto& cal(g.canonical_locations());
    const auto qn(pmn.qualified());
    using qnb = physical::helpers::qualified_name_builder;
    const auto cs(inclusion_support_types::canonical_support);
    if (f->inclusion_support_type() == cs) {
        const auto fct(qnb::build_facet(pmn));
        const auto carch(transforms::traits::canonical_archetype(fct));
        const auto inserted(cal.insert(std::make_pair(qn, carch)).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_archetype << qn;
            BOOST_THROW_EXCEPTION(registrar_error(duplicate_archetype + qn));
        }
        BOOST_LOG_SEV(lg, debug) << "Mapped " << carch << " to " << qn;
    }

    /*
     * Add the transform to the index of transforms by meta-name.
     */
    auto& safbmt(trp.stock_artefact_formatters_by_meta_name());
    safbmt[mn].push_front(f);

    /*
     * Add transform to the index of transforms by archetype
     * name. Inserting the transform into this repository has the
     * helpful side-effect of ensuring the id is unique in physical
     * space.
     */
    auto& safba(trp.stock_artefact_formatters_by_archetype());
    const auto pair(std::make_pair(qn, f));
    const auto inserted(safba.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_archetype << qn;
        BOOST_THROW_EXCEPTION(registrar_error(duplicate_archetype + qn));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrered transform: '" << f->id()
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

const std::forward_list<physical::entities::meta_name>&
registrar::physical_names() const {
    return physical_names_;
}

const std::unordered_map<std::string, physical::entities::meta_name_group>&
registrar::physical_names_by_meta_name() const {
    return physical_names_by_meta_name_;
}

const std::unordered_map<std::string, std::list<physical::entities::meta_name>>&
registrar::physical_names_by_family() const {
    return physical_names_by_family_;
}

const physical::entities::name_repository_parts&
registrar::physical_name_repository_parts() const {
    return physical_name_repository_parts_;
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
