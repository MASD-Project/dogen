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
#include "dogen/utility/io/jsonify_io.hpp"
#include "dogen/prototype/io/versioned_key_io.hpp"
#include "dogen/prototype/domain/currency.hpp"

namespace dogen {
namespace prototype {

currency::currency()
    : decimal_places_(0), numeric_code_(0/*invalid*/) { }

currency::currency(const std::string& name,
    const std::string& alpha_code,
    const unsigned int decimal_places,
    const unsigned int numeric_code,
    const dogen::prototype::versioned_key versioned_key) :
    name_(name),
    alpha_code_(alpha_code),
    decimal_places_(decimal_places),
    numeric_code_(numeric_code),
    versioned_key_(versioned_key) { }

void currency::to_stream(std::ostream& stream) const {
    using dogen::utility::streaming::jsonify;

    stream << " {"
           << "\"__type__\": " << "\"currency\"" << ","
           << " \"name\": \"" << name_ << "\","
           << " \"alpha_code\": \"" << alpha_code_ << "\","
           << " \"decimal_places\": " << decimal_places_ << ", "
           << " \"numeric_code\": " << numeric_code_ << ", "
           << " \"versioned_key\": " << versioned_key_
           << " }";
}

} }
