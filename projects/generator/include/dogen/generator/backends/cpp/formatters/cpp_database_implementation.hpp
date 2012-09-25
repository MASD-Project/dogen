/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_DATABASE_IMPLEMENTATION_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_DATABASE_IMPLEMENTATION_HPP

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

class database_implementation : public file_formatter {
public:
    typedef view_models::class_view_model class_view_model;
    typedef view_models::file_view_model file_view_model;

public:
    database_implementation() = delete;
    database_implementation(const database_implementation&) = default;
    database_implementation(database_implementation&&) = default;
    database_implementation& operator=(const database_implementation&) = default;

public:
    explicit database_implementation(std::ostream& stream);
    virtual ~database_implementation() noexcept {}

public:
    static file_formatter::shared_ptr create(std::ostream& stream);

private:
    std::string
    make_sql(std::string name, std::string schema_name, std::string operation,
        unsigned int number_of_parameters);
    std::string
    make_identifier(std::string type, std::string name, std::string operation);
    void anonymous_namespace(class_view_model vm);
    void format_sql(class_view_model vm);
    void load_internal(class_view_model vm);
    void erase_internal(class_view_model vm);
    void load(class_view_model vm);
    void save(class_view_model vm);
    void erase(class_view_model vm);

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
