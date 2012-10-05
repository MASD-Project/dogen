/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_PROTOTYPE_IO_REPOSITORY_IO_HPP
#define DOGEN_PROTOTYPE_IO_REPOSITORY_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ostream>
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/prototype/io/currency_io.hpp"
#include "dogen/prototype/io/unversioned_key_io.hpp"
#include "dogen/prototype/domain/repository.hpp"

namespace dogen {
namespace prototype {

inline std::ostream&
operator<<(std::ostream& stream, const repository& insertee) {
    stream << "\"repository\": { \"currencies\": "
           << insertee.currencies()
           << " }";
    return(stream);
}

} }

#endif
