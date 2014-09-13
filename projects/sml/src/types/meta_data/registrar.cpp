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
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/meta_data/registrar_error.hpp"
#include "dogen/sml/types/meta_data/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("sml.meta_data.registrar"));

const std::string null_root_enricher("Root enricher is null");
const std::string null_ordinary_enricher("Ordinary enricher is null");

}

namespace dogen {
namespace sml {
namespace meta_data {

void registrar::register_root_enricher(std::shared_ptr<enricher_interface> e) {
    BOOST_LOG_SEV(lg, debug) << "Registering root enricher: " << e->id();
    root_enricher_ = e;
}

void registrar::
register_ordinary_enricher(std::shared_ptr<enricher_interface> e) {
    BOOST_LOG_SEV(lg, debug) << "Registering ordinary enricher: " << e->id();
    ordinary_enrichers_.push_back(e);
}


void registrar::validate_state() const {
    BOOST_LOG_SEV(lg, debug) << "Validating state of registrar.";

    if (root_enricher_)
        BOOST_LOG_SEV(lg, debug) << "Foundry root enricher: "
                                 << root_enricher_->id();
    else {
        BOOST_LOG_SEV(lg, error) << null_root_enricher;
        BOOST_THROW_EXCEPTION(registrar_error(null_root_enricher));
    }

    for (const auto oe : ordinary_enrichers_) {
        if (oe)
            BOOST_LOG_SEV(lg, debug) << "Foundry ordinary enricher: "
                                     << oe->id();
        else {
            BOOST_LOG_SEV(lg, error) << null_ordinary_enricher;
            BOOST_THROW_EXCEPTION(registrar_error(null_ordinary_enricher));
        }
    }
    BOOST_LOG_SEV(lg, debug) << "State of registrar is valid.";
}

std::shared_ptr<enricher_interface> registrar::root_enricher() {
    return root_enricher_;
}


std::list<std::shared_ptr<enricher_interface>> registrar::ordinary_enrichers() {
    return ordinary_enrichers_;
}

} } }
