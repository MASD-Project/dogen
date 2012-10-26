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
#ifndef DOGEN_SML_TEST_DATA_ENUMERATOR_SEQUENCE_HPP
#define DOGEN_SML_TEST_DATA_ENUMERATOR_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"
#include "dogen/sml/domain/enumerator.hpp"
#include "dogen/sml/test_data/property_sequence.hpp"
#include "dogen/sml/test_data/qualified_name_sequence.hpp"

namespace dogen {
namespace sml {
namespace test_data {

namespace detail {

/**
 * @brief Generates an open ended sequence of versions.
 *
 * @see sequence.
 */
class enumerator_generator {
public:
    typedef dogen::sml::enumerator result_type;

public:
    result_type next_term(const unsigned int position) {
        dogen::sml::enumerator result;

        if (position == 1) {
            result.name("my_enumerator_1");
            result.documentation("some docs 1");
            result.value("1");
        } else if (position == 2) {
            result.name("my_enumerator_2");
            result.documentation("some docs 2");
            result.value("2");
        } else {
            result.name("my_enumerator_3");
            result.documentation("some docs 3");
            result.value("3");
        }
        return result;
    }

    unsigned int length() const { return(3); }
};

}

typedef utility::test_data::sequence<
    detail::enumerator_generator> enumerator_sequence;

} } }


#endif
