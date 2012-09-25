/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SML_HASH_QUALIFIED_NAME_HASH_HPP
#define DOGEN_SML_HASH_QUALIFIED_NAME_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/utility/hash/combine.hpp"
#include "dogen/sml/hash/meta_types_hash.hpp"
#include "dogen/sml/domain/qualified_name.hpp"

namespace std {

template<>
class hash<dogen::sml::qualified_name> {
public:
    size_t operator()(dogen::sml::qualified_name value) const {
        std::size_t seed(0);

        dogen::utility::hash::combine(seed, value.model_name());
        dogen::utility::hash::combine(seed, value.type_name());
        dogen::utility::hash::combine(seed, value.meta_type());

        for (auto package_name : value.package_path())
            dogen::utility::hash::combine(seed, package_name);

        return seed;
    }
};

}

#endif
