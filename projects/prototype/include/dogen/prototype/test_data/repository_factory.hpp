/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_PROTOTYPE_TEST_DATA_REPOSITORY_FACTORY_HPP
#define DOGEN_PROTOTYPE_TEST_DATA_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/prototype/domain/repository.hpp"

namespace dogen {
namespace prototype {

/**
 * @brief Produces a repository object and all of its associated
 * dependencies.
 */
class repository_factory {
public:
    typedef repository product;

public:
    static product create_majors();
    static product create_all();
    static product create_unrealistic(const unsigned int how_many);
};

} }

#endif
