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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_UTILITY_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_UTILITY_HPP

#include <iosfwd>
#include <string>
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class cpp_utility {
public:
    cpp_utility() = delete;
    cpp_utility(const cpp_utility&) = delete;
    ~cpp_utility() = default;
    cpp_utility(cpp_utility&&) = default;
    cpp_utility& operator=(const cpp_utility&) = delete;

public:
    cpp_utility(std::ostream& stream, cpp_indenter& indenter) :
        stream_(stream), indenter_(indenter) { }

public:
    void public_access_specifier();
    void private_access_specifier();

    void open_scope();
    void close_scope();
    void blank_line(unsigned int how_many = 1);
    std::string as_member_variable(std::string property_name) const;
    std::string quote(std::string original) const;
    std::string quote_escaped(std::string original) const;

private:
    std::ostream& stream_;
    cpp_indenter& indenter_;
};

} } } } }

#endif
