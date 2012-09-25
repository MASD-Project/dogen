/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_FILE_FORMATTER_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_FILE_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include "dogen/generator/backends/cpp/view_models/file_view_model.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class file_formatter {
public:
    file_formatter(const file_formatter&) = default;
    virtual ~file_formatter() noexcept = default;
    file_formatter(file_formatter&&) = default;
    file_formatter& operator=(const file_formatter&) = default;

protected:
    file_formatter() = default;

public:
    typedef std::shared_ptr<file_formatter> shared_ptr;

public:
    virtual void format(view_models::file_view_model vm) = 0;
};

} } } } }

#endif
