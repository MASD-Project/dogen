/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_INCLUDES_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_INCLUDES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <iosfwd>

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class cpp_includes {
public:
    cpp_includes() = delete;
    cpp_includes(const cpp_includes&) = default;
    ~cpp_includes() = default;
    cpp_includes(cpp_includes&&) = default;
    cpp_includes& operator=(const cpp_includes&) = default;

public:
    explicit cpp_includes(std::ostream& stream);

public:
    void format(std::list<std::string> value, bool is_system);

private:
    std::ostream& stream_;
};

} } } } }

#endif
