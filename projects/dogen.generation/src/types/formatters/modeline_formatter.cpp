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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.logical/io/meta_model/decoration/modeline_io.hpp"
#include "dogen.generation/types/formatters/formatting_error.hpp"
#include "dogen.generation/types/formatters/modeline_formatter.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("generation.modeline_formatter"));

const std::string vim_marker("vim: set");
const std::string vim_field_separator("=");

const std::string emacs_top_marker("-*-");
const std::string emacs_bottom_start_marker("Local variables:");
const std::string emacs_bottom_end_marker("End:");
const std::string emacs_field_separator(":");
const std::string emacs_kvp_separator(";");
const std::string space(" ");

const std::string unsupported_modeline("Modeline is not supported.");

}

namespace dogen::generation::formatters {

using logical::meta_model::decoration::editor;
using logical::meta_model::decoration::modeline_location;
using logical::meta_model::decoration::modeline;

bool modeline_formatter::
is_vim(const modeline& ml) const {
    return ml.editor() == editor::vim;
}

bool modeline_formatter::
is_emacs(const modeline& ml) const {
    return ml.editor() == editor::emacs;
}

bool modeline_formatter::
is_top_line(const modeline& ml) const {
    return ml.location() == modeline_location::top;
}

bool modeline_formatter::
is_bottom_line(const modeline& ml) const {
    return ml.location() == modeline_location::bottom;
}

void modeline_formatter::
vim_modeline(std::ostream& s, const modeline& ml) const {
    s << vim_marker << space;
    bool is_first(true);
    for (const auto& f : ml.fields()) {
        if (!is_first)
            s << space;

        s << f.name();
        if (!f.value().empty())
            s << vim_field_separator << f.value();

        is_first = false;
    }
}

void modeline_formatter::
emacs_top_modeline(std::ostream& s, const modeline& ml) const {
    s << emacs_top_marker << space;
    bool is_first(true);
    for (const auto& f : ml.fields()) {
        if (!is_first)
            s << emacs_kvp_separator << space;

        s << f.name() << emacs_field_separator << space << f.value();

        is_first = false;
    }
    s << space << emacs_top_marker;
}

void modeline_formatter::
emacs_bottom_modeline(std::ostream& s, const modeline& ml) const {
    s << emacs_bottom_start_marker << std::endl;
    for (const auto& f : ml.fields()) {
        s << f.name() << emacs_field_separator << space << f.value()
          << std::endl;
    }
    s << emacs_bottom_end_marker << std::endl;
}

void modeline_formatter::format(std::ostream& s, const modeline& ml) const {
    BOOST_LOG_SEV(lg, trace) << "Modeline: " << ml;

    if (is_emacs(ml)) {
        if (is_top_line(ml))
            return emacs_top_modeline(s, ml);
        else if (is_bottom_line(ml))
            return emacs_bottom_modeline(s, ml);
    } else if (is_vim(ml))
        return vim_modeline(s, ml);

    BOOST_LOG_SEV(lg, error) << unsupported_modeline << " contents: " << ml;
    BOOST_THROW_EXCEPTION(formatting_error(unsupported_modeline));
}

}
