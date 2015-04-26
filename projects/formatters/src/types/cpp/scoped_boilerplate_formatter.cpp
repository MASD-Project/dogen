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
#include <ostream>
#include "dogen/formatters/types/cpp/scoped_boilerplate_formatter.hpp"

namespace dogen {
namespace formatters {
namespace cpp {

scoped_boilerplate_formatter::
scoped_boilerplate_formatter(std::ostream& s,
    const boost::optional<general_settings> gs,
    const std::list<std::string> inclusion_dependencies,
    const std::string header_guard)
    : stream_(s), general_settings_(gs),
      inclusion_dependencies_(inclusion_dependencies),
      header_guard_(header_guard) {

    if (!general_settings_)
        return;

    const auto& a(general_settings_->annotation());
    formatter_.format_begin(stream_, a, inclusion_dependencies, header_guard);
}

scoped_boilerplate_formatter::~scoped_boilerplate_formatter() {
    if (!general_settings_)
        return;

    const auto& a(general_settings_->annotation());
    formatter_.format_end(stream_, a, header_guard_);
}

} } }
