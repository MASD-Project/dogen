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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include "dogen/utility/test_data/generate_container.hpp"
#include "dogen/prototype/test_data/currency_td.hpp"
#include "dogen/prototype/test_data/repository_factory.hpp"

namespace dogen {
namespace prototype {

using dogen::prototype::currency;
using dogen::utility::test_data::generate_vector;
using dogen::prototype::majors_currency_sequence;
using dogen::prototype::complete_currency_sequence;
typedef std::vector<currency> currencies_type;

repository_factory::product repository_factory::create_majors() {
    currencies_type currencies(generate_vector<majors_currency_sequence>());
    product repository;
    repository.update_currencies(currencies);
    return(repository);
}

repository_factory::product repository_factory::create_all() {
    currencies_type currencies(generate_vector<complete_currency_sequence>());
    product repository;
    repository.update_currencies(currencies);
    return(repository);
}

repository_factory::product
repository_factory::create_unrealistic(const unsigned int how_many) {
    currencies_type currencies(
        generate_vector<unrealistic_currency_sequence>(how_many));
    product repository;
    repository.update_currencies(currencies);
    return(repository);
}

} }
