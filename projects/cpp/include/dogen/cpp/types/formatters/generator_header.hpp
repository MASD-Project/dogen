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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_GENERATOR_HEADER_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_GENERATOR_HEADER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/types/enumeration_info.hpp"
#include "dogen/cpp/types/file_info.hpp"
#include "dogen/cpp/types/formatters/indenter.hpp"
#include "dogen/cpp/types/formatters/utility.hpp"
#include "dogen/cpp/types/formatters/file_formatter.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class generator_header : public file_formatter {
public:
    generator_header() = delete;
    generator_header(const generator_header&) = default;
    generator_header(generator_header&&) = default;
    generator_header& operator=(const generator_header&) = default;

public:
    explicit generator_header(std::ostream& stream);
    virtual ~generator_header() noexcept {}

public:
    static file_formatter::shared_ptr create(std::ostream& stream);

private:
    void generator_class(const class_info& vm);
    void generator_class(const enumeration_info& vm);

private:
    void format_class(const file_info& vm);
    void format_enumeration(const file_info& vm);

public:
    virtual void format(const file_info& vm) override;

private:
    std::ostream& stream_;
    indenter indenter_;
    utility utility_;
};

} } }

#endif
