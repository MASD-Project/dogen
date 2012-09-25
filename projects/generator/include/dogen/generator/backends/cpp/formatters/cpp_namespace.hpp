/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_NAMESPACE_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_NAMESPACE_HPP

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

class cpp_namespace {
public:
    cpp_namespace() = delete;
    cpp_namespace(const cpp_namespace&) = default;
    ~cpp_namespace() = default;
    cpp_namespace(cpp_namespace&&) = default;
    cpp_namespace& operator=(const cpp_namespace&) = default;

public:
    explicit cpp_namespace(std::ostream& stream);

public:
    void format_start(std::string name);
    void format_end();

private:
    std::ostream& stream_;
};

} } } } }

#endif
