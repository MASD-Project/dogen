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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/annotations/io/archetype_location_io.hpp"
#include "dogen/quilt.csharp/io/formatters/repository_io.hpp"
#include "dogen/quilt.csharp/types/formatters/registrar_error.hpp"
#include "dogen/quilt.csharp/types/formatters/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.csharp.formatters.registrar"));

const std::string no_file_formatters("File formatters repository is empty.");
const std::string no_file_formatters_by_type_index(
    "No file formatters by type index provided.");

const std::string null_formatter("Formatter supplied is null.");
const std::string empty_formatter_name("Formatter name is empty.");
const std::string empty_facet_name("Facet name is empty.");
const std::string empty_model_name("Model name is empty.");
const std::string duplicate_formatter_name("Duplicate formatter name: ");
const std::string empty_family("Family cannot be empty.");

}

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {

void registrar::validate() const {
    /*
     * We must have at least one registered formatter. This is a quick
     * way of troubleshooting validation errors.
     */
    const auto& frp(formatter_repository_);
    if (frp.stock_artefact_formatters_by_type_index().empty()) {
        BOOST_LOG_SEV(lg, error) << no_file_formatters_by_type_index;
        BOOST_THROW_EXCEPTION(
            registrar_error(no_file_formatters_by_type_index));
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
register_formatter(std::shared_ptr<artefact_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    const auto& al(f->archetype_location());
    if (al.archetype().empty())
        BOOST_THROW_EXCEPTION(registrar_error(empty_formatter_name));

    if (al.facet().empty())
        BOOST_THROW_EXCEPTION(registrar_error(empty_facet_name));

    if (al.kernel().empty())
        BOOST_THROW_EXCEPTION(registrar_error(empty_model_name));

    archetype_locations_.push_front(al);
    formatter_repository_.stock_artefact_formatters_.push_front(f);

    /*
     * Add the formatter to the index by element type index.
     */
    auto& ffti(formatter_repository_.stock_artefact_formatters_by_type_index());
    auto& ti(ffti[f->element_type_index()]);
    ti.push_front(f);

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
        BOOST_LOG_SEV(lg, error) << duplicate_formatter_name << arch;
        BOOST_THROW_EXCEPTION(registrar_error(duplicate_formatter_name + arch));
    }
}

const repository& registrar::formatter_repository() const {
    return formatter_repository_;
}

const std::forward_list<annotations::archetype_location>&
registrar::archetype_locations() const {
    return archetype_locations_;
}

} } } }
