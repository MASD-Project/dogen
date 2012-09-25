/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SML_TEST_DATA_PROPERTY_SEQUENCE_HPP
#define DOGEN_SML_TEST_DATA_PROPERTY_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"
#include "dogen/sml/test_data/qualified_name_sequence.hpp"
#include "dogen/sml/domain/property.hpp"

namespace dogen {
namespace sml {
namespace test_data {

namespace detail {

/**
 * @brief Generates an open ended sequence of versions.
 *
 * @see sequence.
 */
class property_generator {
public:
    typedef dogen::sml::property value_type;

public:
    value_type next_term(const unsigned int position) {
        test_data::qualified_name_sequence seq;
        dogen::sml::property p;

        if (position == 0) {
            p.name("property_0");
            p.default_value("defval_0");
            p.type_name(seq());
        } else if (position == 1) {
            p.name("property_1");
            p.default_value("defval_1");
            seq();
            p.type_name(seq());
        } else {
            p.name("property_2");
            p.default_value("defval_2");
            seq();
            seq();
            p.type_name(seq());
        }
        return p;
    }

    unsigned int length() const { return(3); }
};

}

typedef utility::test_data::sequence<
    detail::property_generator> property_sequence;

} } }


#endif
