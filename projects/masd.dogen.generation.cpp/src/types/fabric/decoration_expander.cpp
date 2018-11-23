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
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/object_template.hpp"
#include "masd.dogen.coding/types/meta_model/builtin.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"
#include "masd.dogen.coding/types/meta_model/exception.hpp"
#include "masd.dogen.coding/types/meta_model/visitor.hpp"
#include "masd.dogen.generation.cpp/types/fabric/registrar.hpp"
#include "masd.dogen.generation.cpp/types/fabric/cmakelists.hpp"
#include "masd.dogen.generation.cpp/types/fabric/master_header.hpp"
#include "masd.dogen.generation.cpp/types/fabric/element_visitor.hpp"
#include "masd.dogen.generation.cpp/types/fabric/msbuild_targets.hpp"
#include "masd.dogen.generation.cpp/types/fabric/common_odb_options.hpp"
#include "masd.dogen.generation.cpp/types/fabric/object_odb_options.hpp"
#include "masd.dogen.generation.cpp/types/fabric/forward_declarations.hpp"
#include "masd.dogen.generation.cpp/types/fabric/decoration_expander.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("generation.cpp.fabric.decoration_expander"));

const std::string cpp_modeline_name("cpp");
const std::string xml_modeline_name("xml");
const std::string cmake_modeline_name("cmake");
const std::string odb_modeline_name("odb");

}

namespace masd::dogen::generation::cpp::fabric {

class decoration_updater : public element_visitor {
public:
    decoration_updater(
        const dogen::extraction::decoration_properties_factory& dpf)
        : factory_(dpf) {}

private:
    void update(coding::meta_model::element& e,
        const std::string & modeline_name = cpp_modeline_name) {
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << e.name().id();
        e.decoration_properties(factory_.make(modeline_name));
    }

public:
    using element_visitor::visit;
    void visit(coding::meta_model::module& m) { update(m); }
    void visit(coding::meta_model::object_template& ot) { update(ot); }
    void visit(coding::meta_model::builtin& b) { update(b); }
    void visit(coding::meta_model::enumeration& e) { update(e); }
    void visit(coding::meta_model::primitive& p) { update(p); }
    void visit(coding::meta_model::object& o) { update(o); }
    void visit(coding::meta_model::exception& e) { update(e); }
    void visit(coding::meta_model::visitor& v) { update(v); }
    void visit(cmakelists& cm) { update(cm, cmake_modeline_name); }
    void visit(common_odb_options& coo) { update(coo, odb_modeline_name); }
    void visit(forward_declarations& fd) { update(fd); }
    void visit(master_header& mh) { update(mh); }
    void visit(object_odb_options& ooo) { update(ooo, odb_modeline_name); }
    void visit(msbuild_targets& mt) { update(mt, xml_modeline_name); }
    void visit(registrar& rg) { update(rg); }

private:
    const dogen::extraction::decoration_properties_factory& factory_;
};

void decoration_expander::
expand(const dogen::extraction::decoration_properties_factory& dpf,
    coding::meta_model::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Populating decoration properties.";

    decoration_updater du(dpf);
    for(auto& ptr : m.elements())
        ptr->accept(du);

    BOOST_LOG_SEV(lg, debug) << "Finished populating decoration properties.";
}

}
