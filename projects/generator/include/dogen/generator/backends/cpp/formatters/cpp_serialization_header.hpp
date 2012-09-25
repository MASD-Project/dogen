/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_SERIALIZATION_HEADER_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_SERIALIZATION_HEADER_HPP

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

class serialization_header : public file_formatter {
public:
    serialization_header() = delete;
    serialization_header(const serialization_header&) = default;
    serialization_header(serialization_header&&) = default;
    serialization_header& operator=(const serialization_header&) = default;

public:
    serialization_header(std::ostream& stream, bool disable_xml_serialization);
    virtual ~serialization_header() noexcept {}

public:
    static file_formatter::shared_ptr create(std::ostream& stream,
        bool disable_xml_serialization);

private:
    void serializer_class(view_models::class_view_model vm);
    void serialize_method(view_models::class_view_model vm);

public:
    virtual void format(view_models::file_view_model vm) override;

private:
    std::ostream& stream_;
    const cpp_facet_types facet_type_;
    const cpp_file_types file_type_;
    cpp_indenter indenter_;
    cpp_utility utility_;
    const bool disable_xml_serialization_;
};

} } } } }

#endif
