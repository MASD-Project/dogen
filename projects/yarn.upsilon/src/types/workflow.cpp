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
#include <list>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/origin_types.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/upsilon/types/type_visitor.hpp"
#include "dogen/yarn.upsilon/types/transformer.hpp"
#include "dogen/yarn.upsilon/types/workflow_error.hpp"
#include "dogen/yarn.upsilon/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.upsilon.workflow"));

const std::string incorrect_number_of_outputs(
    "Upsilon moodel does not have expected number of outputs (1): ");

const std::string duplicate_qualified_name("Duplicate qualified name: ");



}

namespace dogen {
namespace yarn {
namespace upsilon {

class model_populator : public dogen::upsilon::type_visitor {
public:
    model_populator(yarn::intermediate_model& im);

public:
    using dogen::upsilon::type_visitor::visit;
    void visit(const dogen::upsilon::collection& c);
    void visit(const dogen::upsilon::compound& c);
    void visit(const dogen::upsilon::enumeration& e);
    void visit(const dogen::upsilon::primitive& p);

private:
    yarn::intermediate_model& model_;
    transformer transformer_;
};


model_populator::
model_populator(yarn::intermediate_model& im) : model_(im) {}

void model_populator::visit(const dogen::upsilon::collection& c) {
    const auto ot(model_.origin_type());
    const auto& mn(model_.name());
    const auto o(transformer_.to_object(ot, mn, c));
    const auto id(o.name().id());
    const auto pair(std::make_pair(id, o));
    const auto inserted(model_.objects().insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << id;
        BOOST_THROW_EXCEPTION(workflow_error(duplicate_qualified_name + id));
    }
}

void model_populator::visit(const dogen::upsilon::compound& c) {
    const auto ot(model_.origin_type());
    const auto& mn(model_.name());
    const auto o(transformer_.to_object(ot, mn, c));
    const auto id(o.name().id());
    const auto pair(std::make_pair(id, o));
    const auto inserted(model_.objects().insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << id;
        BOOST_THROW_EXCEPTION(workflow_error(duplicate_qualified_name + id));
    }
}

void model_populator::visit(const dogen::upsilon::enumeration& e) {
    const auto ot(model_.origin_type());
    const auto& mn(model_.name());
    const auto o(transformer_.to_enumeration(ot, mn, e));
    const auto id(o.name().id());
    const auto pair(std::make_pair(id, o));
    const auto inserted(model_.enumerations().insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << id;
        BOOST_THROW_EXCEPTION(workflow_error(duplicate_qualified_name + id));
    }
}

void model_populator::visit(const dogen::upsilon::primitive& p) {
    const auto ot(model_.origin_type());
    const auto& mn(model_.name());
    const auto o(transformer_.to_primitive(ot, mn, p));
    const auto id(o.name().id());
    const auto pair(std::make_pair(id, o));
    const auto inserted(model_.primitives().insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << id;
        BOOST_THROW_EXCEPTION(workflow_error(duplicate_qualified_name + id));
    }
}

yarn::intermediate_model
workflow::create_model(const dogen::upsilon::model& um) const {
    if (um.config().outputs().size() != 1) {
        const auto gs(um.config().file_name().generic_string());
        BOOST_LOG_SEV(lg, error) << incorrect_number_of_outputs << gs;
        BOOST_THROW_EXCEPTION(workflow_error(incorrect_number_of_outputs + gs));
    }

    yarn::intermediate_model r;
    r.language(yarn::languages::upsilon);

    const auto& output(um.config().outputs()[0]);

    yarn::name_factory nf;
    const auto n(nf.build_model_name(output.schema_name()));
    r.name(n);
    r.origin_type(origin_types::target);

    yarn::module root_module;
    root_module.name(n);
    root_module.origin_type(origin_types::target);

    r.modules()[n.id()] = root_module;

    return r;
}

void workflow::populate_model(const dogen::upsilon::model& um,
    yarn::intermediate_model& im) const {
    model_populator mp(im);

    // FIXME: merging all models into one at present
    // FIXME: not respecting schema names either.
    for (const auto& pair : um.schemas()) {
        const auto& schema(pair.second);
        BOOST_LOG_SEV(lg, debug) << "Populating from Schema: "
                                 << schema.file_name().generic_string();

        const auto& types(schema.types());
        for (const auto& ptr : types) {
            const auto& t(*ptr);
            t.accept(mp);
        }

        BOOST_LOG_SEV(lg, debug) << "Finished populating from Schema.";
    }
}

yarn::intermediate_model
workflow::execute(const dogen::upsilon::model& um) const {
    BOOST_LOG_SEV(lg, debug) << "Executing workflow on upsilon model. Config: "
                             << um.config().file_name().generic_string();

    auto r(create_model(um));
    populate_model(um, r);

    BOOST_LOG_SEV(lg, debug) << "Finished executing workflow on upsilon model.";
    return r;
}

} } }
