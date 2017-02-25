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
#include <memory>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/io/model_io.hpp"
#include "dogen/yarn/types/intermediate_model_repository_factory.hpp"
#include "dogen/yarn/types/second_stage_expander.hpp"
#include "dogen/yarn/types/descriptor_factory.hpp"
#include "dogen/yarn/types/workflow_error.hpp"
#include "dogen/yarn/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.workflow"));

}

namespace dogen {
namespace yarn {

std::shared_ptr<frontend_registrar> workflow::frontend_registrar_;
std::shared_ptr<injector_registrar> workflow::injector_registrar_;

workflow::workflow() {
    validate();
}

yarn::frontend_registrar& workflow::frontend_registrar() {
    if (!frontend_registrar_)
        frontend_registrar_ = std::make_shared<yarn::frontend_registrar>();

    return *frontend_registrar_;
}

yarn::injector_registrar& workflow::injector_registrar() {
    if (!injector_registrar_)
        injector_registrar_ = std::make_shared<yarn::injector_registrar>();

    return *injector_registrar_;
}

void workflow::validate() const {
    BOOST_LOG_SEV(lg, debug) << "Validating registrars.";
    frontend_registrar().validate();
    injector_registrar().validate();
    BOOST_LOG_SEV(lg, debug) << "Finished validating registrars. ";
}

intermediate_model_repository workflow::obtain_intermediate_model_repository(
    const std::vector<boost::filesystem::path>& dirs,
    const annotations::annotation_groups_factory& agf,
    const annotations::type_repository& atrp,
    const options::knitting_options& ko) const {
    intermediate_model_repository_factory f;
    const auto r(f.make(dirs, agf, atrp, ko, frontend_registrar()));
    return r;
}

model workflow::obtain_model(const annotations::type_repository& atrp,
    const std::list<intermediate_model>& ims) const {
    second_stage_expander ex;
    return ex.make(atrp, injector_registrar(), ims);
}

std::list<model>
workflow::execute(const std::vector<boost::filesystem::path>& dirs,
    const annotations::annotation_groups_factory& agf,
    const annotations::type_repository& atrp,
    const options::knitting_options& ko) const {
    BOOST_LOG_SEV(lg, debug) << "Starting workflow.";
    std::list<model> r;
    const auto imrp(obtain_intermediate_model_repository(dirs, agf, atrp, ko));
    for(const auto& pair : imrp.by_language()) {
        const auto& ims(pair.second);
        r.push_back(obtain_model(atrp, ims));
    }

    BOOST_LOG_SEV(lg, debug) << "Finished workflow. Models: " << r;
    return r;
}

} }
