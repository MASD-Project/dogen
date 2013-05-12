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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_CPP_TYPES_FORMATTERS_IO_HEADER_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_IO_HEADER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/types/formatters/indenter.hpp"
#include "dogen/cpp/types/formatters/utility.hpp"
#include "dogen/cpp/types/file_view_model.hpp"
#include "dogen/cpp/types/formatters/file_formatter.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class io_header : public file_formatter {
public:
    io_header() = delete;
    io_header(const io_header&) = default;
    io_header(io_header&&) = default;
    io_header& operator=(const io_header&) = default;

public:
    explicit io_header(std::ostream& stream);
    virtual ~io_header() noexcept {}

public:
    static file_formatter::shared_ptr create(std::ostream& stream);

private:
    void format_class(const file_view_model& vm);
    void format_enumeration(const file_view_model& vm);

public:
    virtual void format(const file_view_model& vm) override;

private:
    std::ostream& stream_;
    indenter indenter_;
    utility utility_;
};

} } }

#endif
