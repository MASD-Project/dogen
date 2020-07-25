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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.text/io/formatters/boilerplate_properties_io.hpp"
#include "dogen.text/types/formatters/dependencies_formatter.hpp"
#include "dogen.text/types/formatters/header_guard_formatter.hpp"
#include "dogen.text/types/formatters/boilerplate_formatter.hpp"
#include "dogen.text/types/formatters/boilerplate_formatter.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("text.formatters.boilerplate_formatter"));

}

namespace dogen::text::formatters {

using identification::entities::technical_space;

boilerplate_formatter::
boilerplate_formatter(std::ostream& s, const boilerplate_properties& bp)
    : stream_(s), boilerplate_properties_(bp),
      supports_header_guards_(
          bp.technical_space() == technical_space::cpp) {

    BOOST_LOG_SEV(lg, trace) << "Boilerplate properties: " << bp;
}

void boilerplate_formatter::format_preamble() const {
    BOOST_LOG_SEV(lg, trace) << "Formatting preamble.";

    const auto &bp(boilerplate_properties_);
    if (!bp.generate_preamble()) {
        BOOST_LOG_SEV(lg, trace) << "Preamble is disabled.";
        return;
    }

    stream_ << bp.preamble();
}

void boilerplate_formatter::format_postamble() const {
    BOOST_LOG_SEV(lg, trace) << "Formatting postamble.";

    const auto &bp(boilerplate_properties_);
    if (!bp.generate_preamble()) {
        BOOST_LOG_SEV(lg, trace) << "Postamble is disabled.";
        return;
    }

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
    BOOST_LOG_SEV(lg, trace) << "Beginning boilerplate.";

    format_preamble();
    format_guards_begin();
    format_dependencies();
}

void boilerplate_formatter::format_end() const {
    BOOST_LOG_SEV(lg, trace) << "Ending boilerplate.";

    format_postamble();
    format_guards_end();
    stream_.flush();
}

}
