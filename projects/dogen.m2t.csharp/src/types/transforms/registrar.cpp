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
#include "dogen.physical/io/entities/location_io.hpp"
#include "dogen.m2t.csharp/io/transforms/repository_io.hpp"
#include "dogen.m2t.csharp/types/transforms/registrar_error.hpp"
#include "dogen.m2t.csharp/types/transforms/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("m2t.csharp.formatters.registrar"));

const std::string no_file_formatters("File formatters repository is empty.");
const std::string no_file_formatters_by_meta_name(
    "No file formatters by meta name provided.");

const std::string null_formatter_helper("Formatter helper supplied is null");
const std::string null_formatter("Formatter supplied is null.");
const std::string empty_archetype("Formatter name is empty.");
const std::string empty_facet_name("Facet name is empty.");
const std::string empty_model_name("Model name is empty.");
const std::string duplicate_archetype("Duplicate formatter name: ");
const std::string empty_family("Family cannot be empty.");

}

namespace dogen::m2t::csharp::transforms {

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

    if (frp.stock_artefact_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_file_formatters;
        BOOST_THROW_EXCEPTION(registrar_error(no_file_formatters));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state. Repository: "
                             << frp;
    BOOST_LOG_SEV(lg, debug) << "Archetype locations: " << archetype_locations_;
}

void registrar::
register_formatter(std::shared_ptr<model_to_text_transform> f) {
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

    formatter_repository_.stock_artefact_formatters_.push_front(f);

    /*
     * Add the formatter to the archetype location stores. Note that
     * we need not worry about canonical archetypes since this backend
     * does not have them.
     */
    archetype_locations_.push_front(al);
    const auto mn(f->meta_name().qualified().dot());
    auto& alg(archetype_locations_by_meta_name_[mn]);
    alg.locations().push_back(al);
    auto& albf(archetype_locations_by_family_[f->family()]);
    albf.push_back(al);

    /*
     * Add the formatter to the index by meta-name.
     */
    auto& safmt(formatter_repository_.stock_artefact_formatters_by_meta_name());
    safmt[mn].push_front(f);

    /*
     * Add formatter to the index by archetype name. Inserting the
     * formatter into this repository has the helpful side-effect of
     * ensuring the formatter id is unique in formatter space.
     */
    const auto arch(al.archetype());
    auto& fffn(formatter_repository_.stock_artefact_formatters_by_archetype());
    const auto pair(std::make_pair(arch, f));
    const auto inserted(fffn.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_archetype << arch;
        BOOST_THROW_EXCEPTION(registrar_error(duplicate_archetype + arch));
    }

    BOOST_LOG_SEV(lg, debug) << "Registrered formatter: " << f->id()
                             << " against meta name: " << mn;
}

void registrar::register_formatter_helper(
    std::shared_ptr<helper_transform> fh) {

    // note: not logging by design
    if (!fh) {
        BOOST_LOG_SEV(lg, error) << null_formatter_helper;
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter_helper));
    }

    if(fh->family().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_family;
        BOOST_THROW_EXCEPTION(registrar_error(empty_family));
    }

    auto& f(formatter_repository_.helper_formatters_[fh->family()]);
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

}
