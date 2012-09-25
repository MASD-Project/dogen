/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_NAMEPSACE_HELPER_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_NAMEPSACE_HELPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <list>
#include "dogen/generator/backends/cpp/formatters/cpp_namespace.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class namespace_helper {
public:
    namespace_helper() = delete;
    namespace_helper(const namespace_helper&) = default;
    namespace_helper(namespace_helper&&) = default;
    namespace_helper& operator=(const namespace_helper&) = default;

public:
    namespace_helper(std::ostream& stream,
        const std::list<std::string>& namespaces);

    ~namespace_helper();

private:
    std::ostream& stream_;
    cpp_namespace namespace_formatter_;
    std::list<std::string> namespaces_;
};

} } } } }

#endif
