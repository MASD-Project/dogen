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
#include "dogen.utility/log/logger.hpp"
#include "dogen.modeling/types/meta_model/element.hpp"
#include "dogen.modeling/types/meta_model/object.hpp"
#include "dogen.modeling/types/meta_model/module.hpp"
#include "dogen.modeling/types/meta_model/object_template.hpp"
#include "dogen.modeling/types/meta_model/builtin.hpp"
#include "dogen.modeling/types/meta_model/enumeration.hpp"
#include "dogen.modeling/types/meta_model/primitive.hpp"
#include "dogen.modeling/types/meta_model/exception.hpp"
#include "dogen.modeling/types/meta_model/visitor.hpp"
#include "dogen.generation.csharp/types/fabric/assistant.hpp"
#include "dogen.generation.csharp/types/fabric/element_visitor.hpp"
#include "dogen.generation.csharp/types/fabric/decoration_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.csharp.fabric.decoration_expander"));

const std::string cs_modeline_name("cs");
const std::string xml_modeline_name("xml");

}

namespace dogen::generation::csharp::fabric {

class decoration_updater : public element_visitor {
public:
    decoration_updater(
        const dogen::formatting::decoration_properties_factory& dpf)
        : factory_(dpf) {}

private:
    void update(modeling::meta_model::element& e,
        const std::string & modeline_name = cs_modeline_name) {
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << e.name().id();
        e.decoration_properties(factory_.make(modeline_name));
    }

public:
    using element_visitor::visit;
    void visit(modeling::meta_model::element& e) { e.accept(*this); }
    void visit(modeling::meta_model::module& m) { update(m); }
    void visit(modeling::meta_model::object_template& ot) { update(ot); }
    void visit(modeling::meta_model::builtin& b) { update(b); }
    void visit(modeling::meta_model::enumeration& e) { update(e); }
    void visit(modeling::meta_model::primitive& p) { update(p); }
    void visit(modeling::meta_model::object& o) { update(o); }
    void visit(modeling::meta_model::exception& e) { update(e); }
    void visit(modeling::meta_model::visitor& v) { update(v); }
    void visit(assistant& a) { update(a); }

private:
    const dogen::formatting::decoration_properties_factory& factory_;
};

void decoration_expander::
expand(const dogen::formatting::decoration_properties_factory& dpf,
    modeling::meta_model::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Populating decoration properties.";

    decoration_updater du(dpf);
    for(auto& ptr : m.elements())
        ptr->accept(du);

    BOOST_LOG_SEV(lg, debug) << "Finished populating decoration properties.";
}

}
