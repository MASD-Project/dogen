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
#ifndef DOGEN_CPP_FORMATTERS_TYPES_VISITOR_HPP
#define DOGEN_CPP_FORMATTERS_TYPES_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/cpp/types/visitor_info.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/file_formatter.hpp"

namespace dogen {
namespace cpp_formatters {

class visitor : public file_formatter {
public:
    visitor() = delete;
    visitor(const visitor&) = default;
    visitor(visitor&&) = default;
    visitor& operator=(const visitor&) = default;

public:
    explicit visitor(std::ostream& stream);
    virtual ~visitor() noexcept {}

public:
    static file_formatter::shared_ptr create(std::ostream& stream);

private:
    void format(const cpp::visitor_info& vi);

public:
    virtual void format(const cpp::file_info& fi) override;

private:
    std::ostream& stream_;
    indenter indenter_;
    utility utility_;
};

} }

#endif
