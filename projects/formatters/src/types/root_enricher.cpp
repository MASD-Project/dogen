/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <iostream>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/meta_data/workflow.hpp"
#include "dogen/sml/types/meta_data/workflow.hpp"
#include "dogen/formatters/types/root_enricher.hpp"

namespace {

std::string root_id("formatters.root_enricher");
std::list<std::string> empty_dependencies;

using namespace dogen::utility::log;
static logger lg(logger_factory(root_id));

}

namespace dogen {
namespace formatters {

std::string root_enricher::id() const { return root_id; }

std::list<std::string> root_enricher::dependencies() const {
    return empty_dependencies;
}

void root_enricher::
enrich(const sml::model& /*model*/,
    const sml::meta_data::enrichment_types /*enrichment_type*/,
    sml::concept& target) {
    BOOST_LOG_SEV(lg, debug) << "Enriching concept: " << target.name();
}

void root_enricher::
enrich(const sml::model& /*model*/,
    const sml::meta_data::enrichment_types /*enrichment_type*/,
    sml::module& target) {
    BOOST_LOG_SEV(lg, debug) << "Enriching module: " << target.name();
}

void root_enricher::
enrich(const sml::model& /*model*/,
    const sml::meta_data::enrichment_types /*enrichment_type*/,
    sml::type& target) {
    BOOST_LOG_SEV(lg, debug) << "Enriching type: " << target.name();
}

} }
