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
#include "dogen/generator/backends/cpp/boost_model_helper.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"

namespace {

const bool is_system(true);
const bool is_user(false);

const std::string include("#include ");
const std::string open_system("<");
const std::string close_system(">");
const std::string open_user("\"");
const std::string close_user("\"");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

cpp_includes::cpp_includes(std::ostream& stream, const bool blank_line)
    : stream_(stream), utility_(stream_, indenter_), blank_line_(blank_line) { }

void cpp_includes::format(std::list<std::string> v, bool is_system) {
    v.sort();

    // FIXME: hacks for headers that must be last
    boost_model_helper boost_;
    const auto gd(boost_.include(boost_types::serialization_gregorian_date));
    const auto i(std::find(v.begin(), v.end(), gd));
    if (i != v.end())
        v.splice(v.end(), v, i);

    for (auto i : v) {
        stream_ << include << (is_system ? open_system : open_user)
                << i
                << (is_system ? close_system : close_user)
                << std::endl;
    }
}

void cpp_includes::format(const file_view_model& vm) {
    const auto sys(vm.system_includes());
    const auto usr(vm.user_includes());

    if (sys.empty() && usr.empty())
        return;

    format(vm.system_includes(), is_system);
    format(vm.user_includes(), is_user);

    if (blank_line_)
        utility_.blank_line();
}

} } } } }
