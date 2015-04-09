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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/expansion/io/expansion_types_io.hpp"
#include "dogen/dynamic/expansion/types/expander_interface.hpp"
#include "dogen/dynamic/expansion/types/registrar_error.hpp"
#include "dogen/dynamic/expansion/types/expander_interface.hpp"
#include "dogen/dynamic/expansion/types/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.expansion..registrar"));

const std::string no_stand_alone_expanders(
    "No stand alone model expanders provided.");
const std::string no_merged_model_expanders(
    "No merged model expanders provided.");
const std::string unsupported_expander_type(
    "Expander type is not supported: ");
const std::string null_expander("Expander supplied is null");

}

namespace dogen {
namespace dynamic {
namespace expansion {

void registrar::validate() const {
    if (stand_alone_model_expanders_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_stand_alone_expanders;
        BOOST_THROW_EXCEPTION(registrar_error(no_stand_alone_expanders));
    }

    if (merged_model_expanders_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_merged_model_expanders;
        BOOST_THROW_EXCEPTION(registrar_error(no_merged_model_expanders));
    }

    BOOST_LOG_SEV(lg, debug) << "Found "
                             << std::distance(
                                 stand_alone_model_expanders_.begin(),
                                 stand_alone_model_expanders_.end())
                             << " registered stand alone model expander(s): ";

    BOOST_LOG_SEV(lg, debug) << "Listing all stand alone model expanders.";
    for (const auto& f : stand_alone_model_expanders_)
        BOOST_LOG_SEV(lg, debug) << "Key: '" << f->name() << "'";

    BOOST_LOG_SEV(lg, debug) << "Found "
                             << std::distance(
                                 merged_model_expanders_.begin(),
                                 merged_model_expanders_.end())
                             << " registered merged model expander(s): ";

    BOOST_LOG_SEV(lg, debug) << "Listing all merged model expanders.";
    for (const auto& f : merged_model_expanders_)
        BOOST_LOG_SEV(lg, debug) << "Key: '" << f->name() << "'";

    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

bool registrar::is_supported_expansion_type(const expansion_types et) const {
    return
        et == expansion_types::stand_alone_model_expansion ||
        et == expansion_types::merged_model_expansion;
}

void registrar::
register_expander(boost::shared_ptr<expander_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_expander));

    if (!is_supported_expansion_type(f->expansion_type()))
        BOOST_THROW_EXCEPTION(registrar_error(unsupported_expander_type));

    if (f->expansion_type() == expansion_types::stand_alone_model_expansion)
        stand_alone_model_expanders_.push_front(f);
    else if (f->expansion_type() == expansion_types::merged_model_expansion)
        merged_model_expanders_.push_front(f);
}

const std::forward_list<boost::shared_ptr<expander_interface> >&
registrar::stand_alone_model_expanders() const {
    return stand_alone_model_expanders_;
}

const std::forward_list<boost::shared_ptr<expander_interface> >&
registrar::merged_model_expanders() const {
    return merged_model_expanders_;
}

const std::forward_list<boost::shared_ptr<expander_interface> >&
registrar::expanders(const expansion_types et) const {
    if (!is_supported_expansion_type(et))
        BOOST_THROW_EXCEPTION(registrar_error(unsupported_expander_type));

    return et == expansion_types::stand_alone_model_expansion ?
        stand_alone_model_expanders_ : merged_model_expanders_;
}

} } }
