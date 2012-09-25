/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef KITANDA_DOGEN_BACKENDS_CPP_FORMATTERS_LICENCE_HPP
#define KITANDA_DOGEN_BACKENDS_CPP_FORMATTERS_LICENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class licence {
public:
    licence() = delete;
    licence(const licence&) = default;
    ~licence() = default;
    licence(licence&&) = default;
    licence& operator=(const licence&) = default;

public:
    explicit licence(std::ostream& stream);

public:
    void format();

private:
    std::ostream& stream_;
};

} } } } }

#endif
