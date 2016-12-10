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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/types/pretty_printer.hpp"
#include "dogen/yarn/types/string_processor.hpp"
#include "dogen/yarn/types/identifiable_and_qualified_builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.resolver"));

const std::string qn_missing("Could not find qualified name for language: ");

}

namespace dogen {
namespace yarn {

identifiable_and_qualified_builder::
identifiable_and_qualified_builder() : csharp_pp_(separators::dots),
                                       cpp_pp_(separators::double_colons) {}

std::string identifiable_and_qualified_builder::obtain_qualified(
    const std::map<languages, std::string>& map, const languages& l) const {
    const auto i(map.find(l));
    if (i == map.end()) {
        BOOST_LOG_SEV(lg, error) << qn_missing << l;
        BOOST_THROW_EXCEPTION(building_error(qn_missing));
    }
    return i->second;
}

void identifiable_and_qualified_builder::add(const name& n) {
    // csharp_pp_.add(obtain_qualified(n.qualified(), languages::csharp));
    cpp_pp_.add(obtain_qualified(n.qualified(), languages::cpp));
}

void identifiable_and_qualified_builder::add(const name_tree& nt) {
    // csharp_pp_.add_child(obtain_qualified(nt.qualified(), languages::csharp));
    cpp_pp_.add_child(obtain_qualified(nt.qualified(), languages::cpp));
}

std::pair<std::string, std::map<languages, std::string> >
identifiable_and_qualified_builder::build() {
    const auto cpp_qn(cpp_pp_.print());
    const auto qualified(std::map<languages, std::string> {
            /*{ languages::csharp, csharp_pp_.print() },*/
            { languages::cpp, cpp_qn }
        });

    csharp_pp_.clear();
    cpp_pp_.clear();

    string_processor sp;
    const auto ident(sp.to_identifiable(cpp_qn));

    const auto r(std::make_pair(ident, qualified));
    return r;
}

std::pair<std::string, std::map<languages, std::string> >
identifiable_and_qualified_builder::
build(const name& n, const bool model_name_mode) {
    csharp_pp_.add(n, model_name_mode);
    cpp_pp_.add(n, model_name_mode);
    return build();
}

} }
