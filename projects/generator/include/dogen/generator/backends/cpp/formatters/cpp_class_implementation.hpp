/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_CLASS_IMPLEMENTATION_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_CLASS_IMPLEMENTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include "dogen/generator/backends/cpp/view_models/class_view_model.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_utility.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class cpp_class_implementation {
public:
    typedef view_models::class_view_model class_view_model;

public:
    cpp_class_implementation() = default;
    cpp_class_implementation(const cpp_class_implementation&) = default;
    ~cpp_class_implementation() = default;
    cpp_class_implementation(cpp_class_implementation&&) = default;
    cpp_class_implementation&
    operator=(const cpp_class_implementation&) = default;

public:
    explicit cpp_class_implementation(std::ostream& stream);

protected:
    void default_constructor(class_view_model vm);
    void complete_constructor(class_view_model vm);
    void to_stream(class_view_model vm);
    void swap(class_view_model vm);
    void assignment_operator(class_view_model vm);

public:
    virtual void format(class_view_model vm) = 0;

protected:
    std::ostream& stream_;
    cpp_indenter indenter_;
    cpp_utility utility_;
};

} } } } }

#endif
