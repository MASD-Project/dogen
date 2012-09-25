/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SML_HASH_META_TYPE_HASH_HPP
#define DOGEN_SML_HASH_META_TYPE_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/sml/domain/meta_types.hpp"

namespace std {

template<>
class hash<dogen::sml::meta_types> {
public:
    size_t operator()(dogen::sml::meta_types value) const {
        return std::hash<unsigned int>()(static_cast<unsigned int>(value));
    }
};

}

#endif
