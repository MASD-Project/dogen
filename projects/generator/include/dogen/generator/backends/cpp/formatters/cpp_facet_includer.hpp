/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_FACET_INCLUDER_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_FACET_INCLUDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
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

class facet_includer : public file_formatter {
public:
    facet_includer() = delete;
    facet_includer(const facet_includer&) = default;
    facet_includer(facet_includer&&) = default;
    facet_includer& operator=(const facet_includer&) = default;

public:
    facet_includer(std::ostream& stream, cpp_facet_types facet_type);
    virtual ~facet_includer() noexcept {}

public:
    static file_formatter::shared_ptr create(std::ostream& stream,
        cpp_facet_types facet_type);

public:
    virtual void format(view_models::file_view_model vm) override;

private:
    std::ostream& stream_;
    const cpp_facet_types facet_type_;
    const cpp_file_types file_type_;
    cpp_indenter indenter_;
    cpp_utility utility_;
};

} } } } }

#endif
