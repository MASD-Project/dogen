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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/module_types.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/dynamic/schema/io/scope_types_io.hpp"
#include "dogen/dynamic/schema/io/object_io.hpp"
#include "dogen/dynamic/expansion/types/expansion_context.hpp"
#include "dogen/dynamic/expansion/types/workflow_error.hpp"
#include "dogen/dynamic/expansion/types/expander_interface.hpp"
#include "dogen/dynamic/expansion/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.expansion.workflow"));

const std::string model_module_not_found(
    "No generatable model modules found.");
const std::string multiple_model_modules(
    "More than one model module is generatable: ");

}

namespace dogen {
namespace dynamic {
namespace expansion {

class dispatcher {
public:
    dispatcher(const expander_interface& e) : expander_(e) { }

private:
    template<typename IdentifiableAndExensible>
    void expand(schema::scope_types st, IdentifiableAndExensible& ie) {
        using sml::string_converter;
        BOOST_LOG_SEV(lg, debug) << "Performing expansion: '"
                                 << expander_.name() << "' to '"
                                 << string_converter::convert(ie.name())
                                 << " at scope: " << st;

        BOOST_LOG_SEV(lg, debug) << "Before expansion: " << ie.extensions();
        expander_.expand(ie.name(), st, ie.extensions());
        BOOST_LOG_SEV(lg, debug) << "After expansion: " << ie.extensions();
    }

public:
    void operator()(dogen::sml::object& o) {
        expand(schema::scope_types::entity, o);
        // FIXME: expand every property and operation
    }

    void operator()(dogen::sml::enumeration& e) {
        expand(schema::scope_types::entity, e);
    }

    void operator()(dogen::sml::primitive& p) {
        expand(schema::scope_types::entity, p);
    }

    void operator()(dogen::sml::module& m) {
        const auto st(m.type() == sml::module_types::root_model ?
            schema::scope_types::root_module :
            schema::scope_types::any_module);
        expand(st, m);
    }

    void operator()(dogen::sml::concept& c) {
        expand(schema::scope_types::entity, c);
    }

private:
    const expander_interface& expander_;
};

std::shared_ptr<expansion::registrar> workflow::registrar_;

expansion::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<expansion::registrar>();

    return *registrar_;
}

void workflow::validate() const {
    BOOST_LOG_SEV(lg, debug) << "Validating workflow.";

    registrar().validate();
    const auto& expanders(registrar().expanders());
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << std::distance(expanders.begin(),
                                 expanders.end())
                             << " registered expander(s): ";

    BOOST_LOG_SEV(lg, debug) << "Listing all expanders.";
    for (const auto& f : expanders)
        BOOST_LOG_SEV(lg, debug) << "Key: '" << f->name() << "'";

    BOOST_LOG_SEV(lg, debug) << "Finished validating workflow.";
}

sml::model workflow::execute(
    const config::cpp_options& options,
    const std::list<schema::field_definition>& fds,
    const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Expanding model: "
                             << sml::string_converter::convert(m.name());

    validate();

    expansion_context ec(m, fds, options);
    for (auto expander : registrar().expanders()) {
        expander->setup(ec);
        dispatcher d(*expander);
        all_model_items_traversal(ec.model(), d);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding model.";

    return ec.model();
}

} } }
