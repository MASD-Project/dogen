/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_SEQUENCE_IMPLEMENTATION_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_SEQUENCE_IMPLEMENTATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <boost/filesystem/path.hpp>
#include "dogen/generator/backends/cpp/view_models/file_view_model.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_utility.hpp"
#include "dogen/generator/backends/cpp/formatters/file_formatter.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class sequence_implementation : public file_formatter {
public:
    sequence_implementation() = delete;
    sequence_implementation(const sequence_implementation&) = default;
    sequence_implementation(sequence_implementation&&) = default;
    sequence_implementation&
    operator=(const sequence_implementation&) = default;

public:
    explicit sequence_implementation(std::ostream& stream);
    virtual ~sequence_implementation() noexcept {}

public:
    static file_formatter::shared_ptr create(std::ostream& stream);

private:
    void length_method(view_models::class_view_model vm);
    void next_term_method(view_models::class_view_model vm);

public:
    virtual void format(view_models::file_view_model vm) override;

private:
    std::ostream& stream_;
    const cpp_facet_types facet_type_;
    const cpp_file_types file_type_;
    cpp_indenter indenter_;
    cpp_utility utility_;
    const unsigned int generator_length_;
};

} } } } }

#endif
