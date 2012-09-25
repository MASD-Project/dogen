/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_QUALIFIED_NAME_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_QUALIFIED_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include "dogen/generator/backends/cpp/view_models/class_view_model.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class cpp_qualified_name {
public:
    typedef view_models::class_view_model class_view_model;

public:
    cpp_qualified_name() = delete;
    cpp_qualified_name(const cpp_qualified_name&) = default;
    ~cpp_qualified_name() = default;
    cpp_qualified_name(cpp_qualified_name&&) = default;
    cpp_qualified_name& operator=(const cpp_qualified_name&) = default;

public:
    explicit cpp_qualified_name(std::ostream& stream);

public:
    void format(class_view_model vm);

private:
    std::ostream& stream_;
};

} } } } }

#endif
