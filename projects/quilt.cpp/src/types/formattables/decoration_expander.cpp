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
#include <typeindex>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.cpp/types/fabric/cmakelists.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_options.hpp"
#include "dogen/quilt.cpp/types/formattables/decoration_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.element_properties_repository_factory"));

const std::string cpp_modeline_name("cpp");
const std::string cmake_modeline_name("cmake");
const std::string odb_modeline_name("odb");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

void decoration_expander::
expand(const dogen::formatters::decoration_properties_factory& dpf,
    model& fm) const {

    const auto dc(dpf.make(cpp_modeline_name));
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        auto& formattable(pair.second);
        auto& eprops(formattable.element_properties());

        const auto& e(*formattable.master_segment());
        const auto ti(std::type_index(typeid(e)));

        /*
         * Not brilliant but at present we determine the type of
         * decoration to apply based on the element meta-type.
         */
        if (ti == std::type_index(typeid(fabric::cmakelists)))
            eprops.decoration_properties(dpf.make(cmake_modeline_name));
        else if (ti == std::type_index(typeid(fabric::odb_options)))
            eprops.decoration_properties(dpf.make(odb_modeline_name));
        else
            eprops.decoration_properties(dc);
    }
}

} } } }
