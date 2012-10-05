/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
