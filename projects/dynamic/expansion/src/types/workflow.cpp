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
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
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

/**
 * @brief Performs all expansions.
 */
class composite_expander {
public:
    composite_expander(
        const expansion_context& ec,
        const std::forward_list<boost::shared_ptr<const expander_interface> >&
        expanders)
        : expansion_context_(ec), expanders_(expanders) { }

private:
    template<typename IdentifiableAndExensible>
    void expand(IdentifiableAndExensible& ie) {
        for (const auto expander : expanders_) {
            using sml::string_converter;
            BOOST_LOG_SEV(lg, debug) << "Performing expansion: '"
                                     << expander->name()
                                     << "' to '"
                                     << string_converter::convert(ie.name());

            auto& o(ie.extensions());
            BOOST_LOG_SEV(lg, debug) << "Before expansion: " << o;
            expander->expand(expansion_context_, ie.extensions());
            BOOST_LOG_SEV(lg, debug) << "After expansion: " << o;
        }
    }

public:
    void operator()(dogen::sml::object& o) {
        expand(o);
        // FIXME: expand every property and operation
    }
    void operator()(dogen::sml::enumeration& e) { expand(e); }
    void operator()(dogen::sml::primitive& p) { expand(p); }
    void operator()(dogen::sml::module& m) { expand(m); }
    void operator()(dogen::sml::concept& c) { expand(c); }

private:
    const expansion_context& expansion_context_;
    const std::forward_list<boost::shared_ptr<const expander_interface> >&
    expanders_;
};

std::shared_ptr<expansion::registrar> workflow::registrar_;

expansion::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<expansion::registrar>();

    return *registrar_;
}

sml::module workflow::obtain_root_module(const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining model's module.";

    sml::module r;
    bool found(false);
    for (const auto pair : m.modules()) {
        const auto mod(pair.second);
        if (mod.generation_type() != sml::generation_types::full_generation ||
            mod.type() != sml::module_types::model)
            continue;

        if (found) {
            const auto n(sml::string_converter::convert(mod.name()));
            BOOST_LOG_SEV(lg, error) << multiple_model_modules << n;
            BOOST_THROW_EXCEPTION(workflow_error(multiple_model_modules + n));
        }
        r = pair.second;
        found = true;
    }

    if (!found) {
        const auto n(sml::string_converter::convert(r.name()));
        BOOST_LOG_SEV(lg, error) << model_module_not_found << n;
        BOOST_THROW_EXCEPTION(workflow_error(model_module_not_found + n));
    }

    BOOST_LOG_SEV(lg, debug) << "Obtained model's module.";
    return r;
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
    const std::list<schema::field_definition>& fds,
    const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Expanding model: "
                             << sml::string_converter::convert(m.name());

    validate();

    const auto rm(obtain_root_module(m));
    expansion_context ec;
    ec.field_definitions(fds);
    ec.model(m);

    sml::model r(m);
    composite_expander ce(ec, registrar().expanders());
    all_model_items_traversal(r, ce);

    BOOST_LOG_SEV(lg, debug) << "Finished expanding model.";

    return r;
}

} } }
