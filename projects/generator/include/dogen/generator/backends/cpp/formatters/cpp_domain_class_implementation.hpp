/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_DOMAIN_CLASS_IMPLEMENTATION_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_DOMAIN_CLASS_IMPLEMENTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/generator/backends/cpp/formatters/cpp_class_implementation.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class cpp_domain_class_implementation : public cpp_class_implementation {
public:
    typedef view_models::class_view_model class_view_model;

public:
    cpp_domain_class_implementation() = delete;
    cpp_domain_class_implementation(
        const cpp_domain_class_implementation&) = default;
    cpp_domain_class_implementation(
        cpp_domain_class_implementation&&) = default;
    cpp_domain_class_implementation&
    operator=(const cpp_domain_class_implementation&) = default;

private:
    void hand_crafted_constructors(class_view_model vm);

public:
    cpp_domain_class_implementation(std::ostream& stream,
        bool disable_complete_constructor, bool disable_io);
    virtual ~cpp_domain_class_implementation() noexcept {}

public:
    virtual void format(class_view_model vm) override;

private:
    const bool disable_complete_constructor_;
    const bool disable_io_;
};

} } } } }

#endif
