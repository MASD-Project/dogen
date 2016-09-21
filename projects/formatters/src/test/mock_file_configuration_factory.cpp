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
#include <sstream>
#include "dogen/formatters/test/mock_file_configuration_factory.hpp"

namespace  {

const std::string marker("this is a marker");
const std::string empty_marker;
const std::string header_guard("A_PATH_HPP");
const std::string empty_header_guard;

}

namespace dogen {
namespace formatters {
namespace test {

modeline mock_file_configuration_factory::
make_modeline(const modeline_locations l) const {
    modeline r;
    r.editor(editors::emacs);
    r.location(l);

    modeline_field mf;
    mf.name("a_field");
    mf.value("a_value");

    r.fields(std::list<modeline_field>{ mf });
    return r;
}

licence mock_file_configuration_factory::
make_licence(const bool is_empty, const bool is_multiline) const {
    licence r;
    if (is_empty)
        return r;

    r.copyright_notices().push_back("a_holder");
    if (is_multiline)
        r.copyright_notices().push_back("another_holder");

    if (is_multiline) {
        std::ostringstream s;
        s << "first line of licence text" << std::endl
          << "second line of licence text" << std::endl;
        r.text(s.str());
    } else
        r.text("licence text");

    return r;
}

std::list<std::string> mock_file_configuration_factory::make_includes(
    const bool is_empty) const {
    std::list<std::string> r;
    if (is_empty)
        return r;

    // FIXME: bug in generic_string so not testing win32 paths atm
    r.push_back("<win32/system_inc_1>");
    r.push_back("<unix/system_inc_2>");
    r.push_back("\"user_inc_1\"");
    r.push_back("\"user_inc_2\"");
    return r;
}

std::string mock_file_configuration_factory::
make_marker(const bool is_empty) const {
    return is_empty ? empty_marker : marker;
}

std::string mock_file_configuration_factory::
make_header_guard(const bool is_empty) const {
    return is_empty ? empty_header_guard : header_guard;
}

decoration mock_file_configuration_factory::
make_decoration(const modeline_locations ml, const bool use_multiline_licence,
    const bool use_empty_licence, const bool use_empty_marker) const {
    const auto inc(make_includes());
    const auto m(make_modeline(ml));
    const auto l(make_licence(use_empty_licence, use_multiline_licence));
    const decoration r(m, l, make_marker(use_empty_marker));
    return r;
}

decoration mock_file_configuration_factory::make_empty_decoration() const {
    const modeline m;
    licence l;
    const decoration r(m, l, make_marker(true/*use_empty_marker*/));
    return r;
}

file_configuration mock_file_configuration_factory::make_file_configuration() const {
    file_configuration r;
    r.decoration(make_decoration());
    return r;
}

} } }
