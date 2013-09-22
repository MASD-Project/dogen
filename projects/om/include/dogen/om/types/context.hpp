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
#ifndef DOGEN_OM_TYPES_CONTEXT_HPP
#define DOGEN_OM_TYPES_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ostream>
#include "dogen/cpp_formatters/types/indenter.hpp"
#include "dogen/cpp_formatters/types/utility.hpp"
#include "dogen/sml/types/indexer_interface.hpp"

namespace dogen {
namespace om {

class context {
public:
    context() = delete;
    context(const context&) = delete;
    context(context&&) = delete;
    context& operator=(const context&) = delete;
    ~context() noexcept = default;

public:
    context(std::ostream& s, const sml::indexer_interface& i,
        cpp_formatters::indenter& ind, cpp_formatters::utility& u);

public:
    std::ostream& stream();
    const sml::indexer_interface& indexer();
    cpp_formatters::indenter& indenter();
    cpp_formatters::utility& utility();

private:
    std::ostream& stream_;
    const sml::indexer_interface& indexer_;
    cpp_formatters::indenter& indenter_;
    cpp_formatters::utility& utility_;
};

} }

#endif
