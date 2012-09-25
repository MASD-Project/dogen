/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
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
