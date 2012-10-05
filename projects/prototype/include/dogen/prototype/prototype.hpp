/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_PROTOTYPE_PROTOTYPE_HPP
#define DOGEN_PROTOTYPE_PROTOTYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace kitanda {

/**
 * @brief The prototype model is a sandbox for introducing new code
 * generation features.
 *
 * Before attempting to implement a feature one should manually change
 * the prototype model and make sure the feature works as expected;
 * once that is done the feature should be introduced into dogen;
 * the output of the code generator can then be compared to the
 * current state of the prototype model.
 *
 */
namespace prototype {

} }

#endif
