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
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/quilt.cpp/types/fabric/registrar.hpp"
#include "dogen/quilt.cpp/types/fabric/cmakelists.hpp"
#include "dogen/quilt.cpp/types/fabric/master_header.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/fabric/msbuild_targets.hpp"
#include "dogen/quilt.cpp/types/fabric/common_odb_options.hpp"
#include "dogen/quilt.cpp/types/fabric/object_odb_options.hpp"
#include "dogen/quilt.cpp/types/fabric/forward_declarations.hpp"
#include "dogen/quilt.cpp/types/fabric/decoration_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.fabric.decoration_expander"));

const std::string cpp_modeline_name("cpp");
const std::string xml_modeline_name("xml");
const std::string cmake_modeline_name("cmake");
const std::string odb_modeline_name("odb");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

class decoration_updater : public element_visitor {
public:
    decoration_updater(
        const dogen::formatters::decoration_properties_factory& dpf)
        : factory_(dpf) {}

private:
    void update(yarn::element& e,
        const std::string & modeline_name = cpp_modeline_name) {
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << e.name().id();
        auto& ep(e.element_properties());
        ep.decoration_properties(factory_.make(modeline_name));
    }

public:
    bool include_injected_elements() { return true; }
    void operator()(yarn::element& e) { e.accept(*this); }
    void operator()(yarn::module& m) { update(m); }
    void operator()(yarn::concept& c) { update(c); }
    void operator()(yarn::builtin& b) { update(b); }
    void operator()(yarn::enumeration& e) { update(e); }
    void operator()(yarn::primitive& p) { update(p); }
    void operator()(yarn::object& o) { update(o); }
    void operator()(yarn::exception& e) { update(e); }
    void operator()(yarn::visitor& v) { update(v); }

public:
    using element_visitor::visit;
    void visit(cmakelists& cm) { update(cm, cmake_modeline_name); }
    void visit(common_odb_options& coo) { update(coo, odb_modeline_name); }
    void visit(forward_declarations& fd) { update(fd); }
    void visit(master_header& mh) { update(mh); }
    void visit(object_odb_options& ooo) { update(ooo, odb_modeline_name); }
    void visit(registrar& rg) { update(rg); }

private:
    const dogen::formatters::decoration_properties_factory& factory_;
};

void decoration_expander::
expand(const dogen::formatters::decoration_properties_factory& dpf,
    yarn::intermediate_model& im) const {

    BOOST_LOG_SEV(lg, debug) << "Populating decoration properties.";

    decoration_updater du(dpf);
    yarn::elements_traversal(im, du);


    /*
     * Type dispatching is not brilliant but at present we
     * determine the type of decoration to apply based on the
     * element meta-type.
     */
/*    std::string modeline_name(cpp_modeline_name);
    const auto ti(std::type_index(typeid(e)));
    if (ti == std::type_index(typeid(fabric::msbuild_targets)))
        modeline_name = xml_modeline_name;
    if (ti == std::type_index(typeid(fabric::cmakelists)))
        modeline_name = cmake_modeline_name;
    else if (ti == std::type_index(typeid(fabric::common_odb_options)))
        modeline_name = odb_modeline_name;
    else if (ti == std::type_index(typeid(fabric::object_odb_options)))
        modeline_name = odb_modeline_name;
*/


    BOOST_LOG_SEV(lg, debug) << "Finished populating decoration properties.";
}

} } } }
