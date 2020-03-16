/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_PRETTY_PRINTER_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_PRETTY_PRINTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <sstream>
#include <string_view>
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.logical/types/helpers/separators.hpp"

namespace dogen::logical::helpers {

class pretty_printer {
public:
    pretty_printer();
    explicit pretty_printer(const separators s);

private:
    std::list<std::string> to_list(const entities::name& n,
        const bool model_name_mode) const;

private:
    void print_scoped(std::string_view separator,
        const std::list<std::string>& l);
    void print_enclosed(const std::list<std::string>& l);

public:
    void add(const entities::name& n, const bool model_name_mode = false);
    void add(const std::string& c);
    void add_child(const std::string& c);

public:
    std::string print();
    void clear();

private:
    bool has_children_;
    bool last_child_had_children_;
    std::ostringstream stream_;
    const separators separator_;
};

}

#endif
