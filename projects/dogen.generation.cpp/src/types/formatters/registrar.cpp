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
#include "dogen.physical/io/entities/location_io.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/io/formatters/repository_io.hpp"
#include "dogen.generation.cpp/types/formatters/registrar_error.hpp"
#include "dogen.generation.cpp/types/formatters/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.cpp.formatters.registrar"));

const std::string no_file_formatters("File formatters repository is empty.");
const std::string no_file_formatters_by_meta_name(
    "No file formatters by meta name provided.");
const std::string no_forward_declarations_formatters(
    "No forward declarations formatters provided.");
const std::string null_formatter("Formatter supplied is null.");
const std::string facets_missing_canonical_archetype(
    "One or more facets have been declared without a canonical archetype");
const std::string more_than_one_canonical_archetype(
    "Found more than one canonical formatter for a facet: ");
const std::string empty_archetype("Archetype is empty.");
const std::string empty_facet_name("Facet name is empty.");
const std::string empty_model_name("Model name is empty.");
const std::string duplicate_archetype("Duplicate formatter id: ");
const std::string empty_family("Family cannot be empty.");
const std::string null_helper_formatter("Formatter helper supplied is null");

}

namespace dogen::generation::cpp::formatters {

void registrar::
validate(std::shared_ptr<artefact_formatter_interface> f) const {
    if (!f) {
        BOOST_LOG_SEV(lg, error) << null_formatter;
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));
    }

    const auto& al(f->archetype_location());
    if (al.archetype().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_archetype;
        BOOST_THROW_EXCEPTION(registrar_error(empty_archetype));
    }

    if (al.facet().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_facet_name;
        BOOST_THROW_EXCEPTION(registrar_error(empty_facet_name));
    }

    if (al.backend().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_model_name;
        BOOST_THROW_EXCEPTION(registrar_error(empty_model_name));
    }
}

void registrar::validate(std::shared_ptr<helper_formatter_interface> hf) const {
    if (!hf) {
        BOOST_LOG_SEV(lg, error) << null_helper_formatter;
        BOOST_THROW_EXCEPTION(registrar_error(null_helper_formatter));
    }

    if(hf->family().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_family;
        BOOST_THROW_EXCEPTION(registrar_error(empty_family));
    }
}

void registrar::validate() const {
    /*
     * We must have at least one registered formatter. This is a quick
     * way of troubleshooting validation errors.
     */
    const auto& frp(formatter_repository_);
    if (frp.stock_artefact_formatters_by_meta_name().empty()) {
        BOOST_LOG_SEV(lg, error) << no_file_formatters_by_meta_name;
        BOOST_THROW_EXCEPTION(registrar_error(no_file_formatters_by_meta_name));
    }

    /*
     * Validate the registered canonical formatters.
     */
    const auto cs(inclusion_support_types::canonical_support);
    for (const auto& pair : frp.stock_artefact_formatters_by_meta_name()) {
        const auto mn(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing type: " << mn;

        const auto& formatters(pair.second);
        std::set<std::string> facets_found;
        std::set<std::string> all_facets;
        for (const auto& ptr : formatters) {
            const auto& formatter(*ptr);
            const auto& al(formatter.archetype_location());
            const auto fct(al.facet());
            all_facets.insert(fct);
            if (formatter.inclusion_support_type() != cs)
                continue;

            /*
             * We can only have one canonical formatter per type per facet.
             */
            const auto i(facets_found.find(fct));
            if (i != facets_found.end()) {
                const auto arch(al.archetype());
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
         * We must have one canonical formatter per type per facet.
         * FIXME: this check is broken at the moment because this is
         * only applicable to yarn types, not fabric types. It is also
         * not applicable to forward declarations. We need some
         * additional information from yarn to be able to figure out
         * which types must have a canonical archetype.
         */
        std::set<std::string> result;
        std::set_difference(all_facets.begin(), all_facets.end(),
            facets_found.begin(), facets_found.end(),
            std::inserter(result, result.end()));
        if (!result.empty()) {
            BOOST_LOG_SEV(lg, warn) << facets_missing_canonical_archetype
                                    << " : " << result;

            // FIXME: broken at present.
            // BOOST_THROW_EXCEPTION(
            //     registrar_error(facets_missing_canonical_archetype));
        }
    }

    if (frp.stock_artefact_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_file_formatters;
        BOOST_THROW_EXCEPTION(
            registrar_error(no_file_formatters));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state. Repository: "
                             << frp;
    BOOST_LOG_SEV(lg, debug) << "Archetype locations: " << archetype_locations_;
}

void registrar::
register_formatter(std::shared_ptr<artefact_formatter_interface> f) {
    /*
     * First we ensure the formatter is vaguely valid and insert it
     * into the main collection of stock formatters.
     */
    validate(f);
    auto& frp(formatter_repository_);
    frp.stock_artefact_formatters_.push_front(f);

    /*
     * Add the formatter to the archetype location stores.
     */
    const auto& al(f->archetype_location());
    archetype_locations_.push_front(al);

    /*
     * Handle the meta-type collection of archetype locations.
     */
    const auto mn(f->meta_name().qualified().dot());
    auto& alg(archetype_locations_by_meta_name_[mn]);
    alg.locations().push_back(al);
    auto& albf(archetype_locations_by_family_[f->family()]);
    albf.push_back(al);

    /*
     * If the archetype location points to a canonical archetype,
     * update the canonical archetype mapping.
     */
    auto& cal(alg.canonical_locations());
    const auto cs(inclusion_support_types::canonical_support);
    if (f->inclusion_support_type() == cs) {
        const auto arch(al.archetype());
        const auto fct(al.facet());
        const auto carch(formatters::traits::canonical_archetype(fct));
        const auto inserted(cal.insert(std::make_pair(arch, carch)).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_archetype << arch;
            BOOST_THROW_EXCEPTION(registrar_error(duplicate_archetype + arch));
        }
        BOOST_LOG_SEV(lg, debug) << "Mapped " << carch << " to " << arch;
    }

    /*
     * Add the formatter to the index of formatters by meta-name.
     */
    auto& safbmt(frp.stock_artefact_formatters_by_meta_name());
    safbmt[mn].push_front(f);

    /*
     * Add formatter to the index of formatters by archetype
     * name. Inserting the formatter into this repository has the
     * helpful side-effect of ensuring the formatter id is unique in
     * formatter space.
     */
    const auto arch(al.archetype());
    auto& fffn(frp.stock_artefact_formatters_by_archetype());
    const auto pair(std::make_pair(arch, f));
    const auto inserted(fffn.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_archetype << arch;
        BOOST_THROW_EXCEPTION(registrar_error(duplicate_archetype + arch));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrered formatter: " << f->id()
                             << " against meta name: " << mn;
}

void registrar::
register_helper_formatter(std::shared_ptr<helper_formatter_interface> fh) {
    validate(fh);
    auto& frp(formatter_repository_);
    auto& f(frp.helper_formatters_[fh->family()]);
    for (const auto& of : fh->owning_formatters())
        f[of].push_back(fh);

    BOOST_LOG_SEV(lg, debug) << "Registrered formatter helper: "
                             << fh->helper_name();
}

const repository& registrar::formatter_repository() const {
    return formatter_repository_;
}

const std::forward_list<physical::entities::location>&
registrar::archetype_locations() const {
    return archetype_locations_;
}

const std::unordered_map<std::string,
                   physical::entities::locations_group>&
registrar::archetype_locations_by_meta_name() const {
    return archetype_locations_by_meta_name_;
}

const std::unordered_map<std::string,
                         std::list<physical::entities::location>>&
registrar::archetype_locations_by_family() const {
    return archetype_locations_by_family_;
}

const physical::entities::location_repository_parts&
registrar::archetype_location_repository_parts() const {
    return archetype_location_repository_parts_;
}

const std::unordered_map<
    std::string, std::unordered_map<
                     std::string,
                     std::list<
                         std::shared_ptr<helper_formatter_interface>>>>&
registrar::helper_formatters() const {
    return formatter_repository_.helper_formatters();
}

}
