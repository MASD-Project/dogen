/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
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
