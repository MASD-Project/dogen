/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_HEADER_GUARDS_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_HEADER_GUARDS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class header_guards {
public:
    header_guards() = delete;
    header_guards(const header_guards&) = default;
    ~header_guards() = default;
    header_guards(header_guards&&) = default;
    header_guards& operator=(const header_guards&) = default;

public:
    explicit header_guards(std::ostream& stream);

public:
    void format_start(std::string guard_name);
    void format_end();

private:
    std::ostream& stream_;
};

} } } } }

#endif
