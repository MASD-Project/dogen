/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SML_TEST_DATA_META_TYPES_SEQUENCE_HPP
#define DOGEN_SML_TEST_DATA_META_TYPES_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"
#include "dogen/sml/domain/meta_types.hpp"

namespace dogen {
namespace sml {
namespace test_data {

namespace detail {

/**
 * @brief Generates an open ended sequence of versions.
 *
 * @see sequence.
 */
class meta_types_generator {
public:
    typedef dogen::sml::meta_types value_type;

public:
    value_type next_term(const unsigned int position) {
        dogen::sml::meta_types name = dogen::sml::meta_types();

        if (position == 0)
            return meta_types::attribute;
        else if (position == 1)
            return meta_types::enumeration;
        else
            return meta_types::pod;

        return name;
    }

    unsigned int length() const { return(3); }
};

}

typedef utility::test_data::sequence<
    detail::meta_types_generator> meta_types_sequence;

} } }


#endif
