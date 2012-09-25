/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_DOMAIN_IMPLEMENTATION_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_DOMAIN_IMPLEMENTATION_HPP

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

class domain_implementation : public file_formatter {
public:
    domain_implementation() = delete;
    domain_implementation(const domain_implementation&) = default;
    domain_implementation(domain_implementation&&) = default;
    domain_implementation& operator=(const domain_implementation&) = default;

public:
    domain_implementation(std::ostream& stream,
        bool disable_complete_constructor,
        bool use_integrated_io, bool disable_io);

    virtual ~domain_implementation() noexcept {}

private:
    void inserter_operator(view_models::class_view_model vm);
    void class_implementation(cpp_aspect_types aspect_type,
        view_models::class_view_model vm);

public:
    static file_formatter::shared_ptr create(std::ostream& stream,
        bool disable_complete_constructor, bool use_integrated_io,
        bool disable_io);

public:
    virtual void format(view_models::file_view_model vm) override;

private:
    std::ostream& stream_;
    const cpp_facet_types facet_type_;
    const cpp_file_types file_type_;
    cpp_indenter indenter_;
    cpp_utility utility_;
    const bool disable_complete_constructor_;
    const bool use_integrated_io_;
    const bool disable_io_;
};

} } } } }

#endif
