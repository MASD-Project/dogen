/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
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
