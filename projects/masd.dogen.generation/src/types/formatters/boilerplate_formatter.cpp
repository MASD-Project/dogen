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

#include <ostream>
#include "masd.dogen.generation/types/formatters/dependencies_formatter.hpp"
#include "masd.dogen.generation/types/formatters/header_guard_formatter.hpp"
#include "masd.dogen.generation/types/formatters/boilerplate_formatter.hpp"
#include "masd.dogen.generation/types/formatters/boilerplate_formatter.hpp"

namespace masd::dogen::generation::formatters {

boilerplate_formatter::
boilerplate_formatter(std::ostream& s, const boilerplate_properties& bp)
    : stream_(s), boilerplate_properties_(bp),
      supports_header_guards_(
          bp.technical_space() == coding::meta_model::technical_space::cpp) {}

void boilerplate_formatter::format_preamble() const {
    const auto& bp(boilerplate_properties_);
    if (!bp.generate_preamble())
        return;

    stream_ << bp.preamble();
}

void boilerplate_formatter::format_postamble() const {
    const auto& bp(boilerplate_properties_);
    if (!bp.generate_preamble())
        return;

    stream_ << bp.postamble();
}

void boilerplate_formatter::format_guards_begin() const {
    const auto& bp(boilerplate_properties_);
    if (!supports_header_guards_ || !bp.generate_header_guards())
        return;

    const auto& hg(bp.header_guard());
    header_guard_formatter f(stream_, hg);
    f.format_begin();

    if (!hg.empty())
        stream_ << std::endl;
}

void boilerplate_formatter::format_guards_end() const {
    const auto& bp(boilerplate_properties_);
    if (!supports_header_guards_ || !bp.generate_header_guards())
        return;

    const auto& hg(bp.header_guard());
    header_guard_formatter f(stream_, hg);
    f.format_end();
}

void boilerplate_formatter::format_dependencies() const {
    const auto& bp(boilerplate_properties_);
    dependencies_formatter f;
    f.format(stream_, bp.technical_space(), bp.dependencies());
}

void boilerplate_formatter::format_begin() const {
    format_preamble();
    format_guards_begin();
    format_dependencies();
}

void boilerplate_formatter::format_end() const {
    format_postamble();
    format_guards_end();
}

}
