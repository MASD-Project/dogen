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
#ifndef DOGEN_CPP_FORMATTERS_TYPES_TYPES_MAIN_HEADER_FILE_FORMATTER_HPP
#define DOGEN_CPP_FORMATTERS_TYPES_TYPES_MAIN_HEADER_FILE_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp/types/exception_info.hpp"
#include "dogen/cpp/types/source_file.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"
#include "dogen/cpp_formatters/types/file_formatter.hpp"
#include "dogen/cpp/types/entity_visitor.hpp"

namespace dogen {
namespace cpp_formatters {

class types_main_header_file_formatter : public file_formatter,
                                         private cpp::entity_visitor {
public:
    types_main_header_file_formatter() = delete;
    types_main_header_file_formatter(
        const types_main_header_file_formatter&) = default;
    types_main_header_file_formatter(
        types_main_header_file_formatter&&) = default;
    types_main_header_file_formatter& operator=(
        const types_main_header_file_formatter&) = default;

public:
    types_main_header_file_formatter(std::ostream& stream,
        const bool disable_complete_constructor,
        const bool use_integrated_io, const bool disable_io,
        const bool serialization_enabled);

    virtual ~types_main_header_file_formatter() noexcept {}

public:
    static file_formatter::shared_ptr create(std::ostream& stream,
        const bool disable_complete_constructor, const bool use_integrated_io,
        const bool disable_io, const bool disable_serialization);

private:
    void inserter_operator(const cpp::class_info& ci);
    void equality_operator(const cpp::class_info& ci);
    void swap_method(const cpp::class_info& ci);

private:
    using cpp::entity_visitor::visit;
    virtual void visit(dogen::cpp::class_info& ci) override;
    virtual void visit(dogen::cpp::enum_info& ei) override;
    virtual void visit(dogen::cpp::exception_info& ei) override;

public:
    virtual void format(const cpp::source_file& f) override;

private:
    std::ostream& stream_;
    indenter indenter_;
    utility utility_;
    const bool disable_complete_constructor_;
    const bool use_integrated_io_;
    const bool disable_io_;
    const bool disable_serialization_;
};

} }

#endif
