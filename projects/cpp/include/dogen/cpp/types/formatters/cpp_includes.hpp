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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_CPP_TYPES_FORMATTERS_CPP_INCLUDES_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_CPP_INCLUDES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <iosfwd>
#include "dogen/cpp/types/formatters/cpp_indenter.hpp"
#include "dogen/cpp/types/formatters/cpp_utility.hpp"
#include "dogen/cpp/types/view_models/file_view_model.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class cpp_includes {
public:
    typedef view_models::file_view_model file_view_model;

public:
    cpp_includes() = delete;
    cpp_includes(const cpp_includes&) = default;
    ~cpp_includes() = default;
    cpp_includes(cpp_includes&&) = default;
    cpp_includes& operator=(const cpp_includes&) = default;

public:
    explicit cpp_includes(std::ostream& stream, const bool blank_line = true);

private:
    void format(std::list<std::string> v, bool is_system);

public:
    void format(const file_view_model& vm);

private:
    std::ostream& stream_;
    cpp_indenter indenter_;
    cpp_utility utility_;
    const bool blank_line_;
};

} } }

#endif
