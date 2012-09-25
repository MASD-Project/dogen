/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_DATABASE_HEADER_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_DATABASE_HEADER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <boost/filesystem/path.hpp>
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_utility.hpp"
#include "dogen/generator/backends/cpp/view_models/file_view_model.hpp"
#include "dogen/generator/backends/cpp/formatters/file_formatter.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class database_header : public file_formatter {
public:
    typedef view_models::class_view_model class_view_model;
    typedef view_models::file_view_model file_view_model;

public:
    database_header() = delete;
    database_header(const database_header&) = default;
    database_header(database_header&&) = default;
    database_header& operator=(const database_header&) = default;

public:
    explicit database_header(std::ostream& stream);
    virtual ~database_header() noexcept {}

public:
    static file_formatter::shared_ptr create(std::ostream& stream);

private:
    void compiler_generated_constuctors(class_view_model vm);
    void format_sql();
    void load_internal(class_view_model vm);
    void erase_internal();
    void load(class_view_model vm);
    void save(class_view_model vm);
    void erase();

public:
    virtual void format(file_view_model vm) override;

private:
    std::ostream& stream_;
    const cpp_facet_types facet_type_;
    const cpp_file_types file_type_;
    cpp_indenter indenter_;
    cpp_utility utility_;
};

} } } } }

#endif
