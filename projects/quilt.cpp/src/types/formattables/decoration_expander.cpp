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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.cpp/types/fabric/cmakelists.hpp"
#include "dogen/quilt.cpp/types/fabric/msbuild_targets.hpp"
#include "dogen/quilt.cpp/types/fabric/common_odb_options.hpp"
#include "dogen/quilt.cpp/types/fabric/object_odb_options.hpp"
#include "dogen/quilt.cpp/types/formattables/decoration_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.decoration_expander"));

const std::string cpp_modeline_name("cpp");
const std::string xml_modeline_name("xml");
const std::string cmake_modeline_name("cmake");
const std::string odb_modeline_name("odb");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

dogen::formatters::decoration_properties
decoration_expander::make_decoration_properties(
    const dogen::formatters::decoration_properties_factory& dpf,
    const yarn::element& e) const {
    /*
     * Not brilliant but at present we determine the type of
     * decoration to apply based on the element meta-type.
     */
    const auto ti(std::type_index(typeid(e)));
    if (ti == std::type_index(typeid(fabric::msbuild_targets)))
        return dpf.make(xml_modeline_name);
    if (ti == std::type_index(typeid(fabric::cmakelists)))
        return dpf.make(cmake_modeline_name);
    else if (ti == std::type_index(typeid(fabric::common_odb_options)))
        return dpf.make(odb_modeline_name);
    else if (ti == std::type_index(typeid(fabric::object_odb_options)))
        return dpf.make(odb_modeline_name);

    return dpf.make(cpp_modeline_name);
}

void decoration_expander::
expand(const dogen::formatters::decoration_properties_factory& dpf,
    model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Generating decoration properties.";

    for (auto& pair : fm.formattables()) {
        auto& formattable(pair.second);
        auto& eprops(formattable.element_properties());
        auto& map(eprops.decoration_properties());
        for (const auto ptr : formattable.all_segments()) {
            const auto& e(*ptr);
            const auto key(typeid(e).name());
            const auto dc(make_decoration_properties(dpf, e));

            /*
             * Note that we don't mind duplicate keys - they map to
             * the same decoration properties.
             */
            map.insert(std::make_pair(key, dc));
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished generating decoration properties.";
}

} } } }
