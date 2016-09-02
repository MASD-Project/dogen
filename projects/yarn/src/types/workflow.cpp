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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/model_io.hpp"
#include "dogen/yarn/types/merger.hpp"
#include "dogen/yarn/types/pre_merge_workflow.hpp"
#include "dogen/yarn/types/post_merge_workflow.hpp"
#include "dogen/yarn/types/transformer.hpp"
#include "dogen/yarn/types/descriptor_factory.hpp"
#include "dogen/yarn/types/pre_merge_workflow.hpp"
#include "dogen/yarn/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.workflow"));

}

namespace dogen {
namespace yarn {

std::shared_ptr<frontend_registrar> workflow::registrar_;

workflow::workflow() {
    validate();
}

frontend_registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<frontend_registrar>();

    return *registrar_;
}

void workflow::validate() const {
    BOOST_LOG_SEV(lg, debug) << "Validating registrar.";
    registrar().validate();
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << registrar().frontends_by_extension().size()
                             << " registered frontends. Details: ";

    for (const auto& pair : registrar().frontends_by_extension()) {
        BOOST_LOG_SEV(lg, debug) << "extension: '" << pair.first << "' "
                                 << "id: '" << pair.second->id() << "'";
    }
    BOOST_LOG_SEV(lg, debug) << "Finished validating registrar. ";
}


std::list<intermediate_model> workflow::
obtain_intermediate_models(const dynamic::repository& drp,
    const std::list<boost::filesystem::path>& dirs,
    const config::input_options& io) const {
    pre_merge_workflow w;
    return w.execute(drp, dirs, io, registrar());
}

intermediate_model workflow::
merge_intermediate_models(const std::list<intermediate_model>& im) const {
    merger mg;
    for (const auto& m : im)
        mg.add(m);

    const auto r(mg.merge());

    BOOST_LOG_SEV(lg, debug) << "Totals: objects: " << r.objects().size()
                             << " modules: " << r.modules().size()
                             << " concepts: " << r.concepts().size()
                             << " enumerations: " << r.enumerations().size()
                             << " primitives: " << r.primitives().size();
    return r;
}

void workflow::post_process_merged_intermediate_model(
    intermediate_model& im) const {
    post_merge_workflow w;
    return w.execute(im);
}

model workflow::transform_intermediate_model(
    const intermediate_model& m) const {
    transformer t;
    return t.transform(m);
}

model workflow::execute(const dynamic::repository& drp,
    const std::list<boost::filesystem::path>& dirs,
    const config::input_options& io) const {

    const auto im(obtain_intermediate_models(drp, dirs, io));
    auto mim(merge_intermediate_models(im));
    post_process_merged_intermediate_model(mim);
    const auto r(transform_intermediate_model(mim));

    BOOST_LOG_SEV(lg, debug) << "Final model: " << r;
    return r;
}

} }
