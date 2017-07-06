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
#include "dogen/yarn/types/transformer.hpp"
#include "dogen/yarn/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.workflow"));

}

namespace dogen {
namespace yarn {

std::shared_ptr<frontend_registrar> workflow::frontend_registrar_;
std::shared_ptr<external_expander_registrar>
workflow::external_expander_registrar_;

workflow::workflow() {
    validate();
}

yarn::frontend_registrar& workflow::frontend_registrar() {
    if (!frontend_registrar_)
        frontend_registrar_ = std::make_shared<yarn::frontend_registrar>();

    return *frontend_registrar_;
}

yarn::external_expander_registrar& workflow::external_expander_registrar() {
    if (!external_expander_registrar_)
        external_expander_registrar_ =
            std::make_shared<yarn::external_expander_registrar>();

    return *external_expander_registrar_;
}

void workflow::validate() const {
    BOOST_LOG_SEV(lg, debug) << "Validating registrars.";
    frontend_registrar().validate();
    external_expander_registrar().validate();
    BOOST_LOG_SEV(lg, debug) << "Finished validating registrars. ";
}

intermediate_model_repository workflow::create_intermediate_model_repository(
    const std::vector<boost::filesystem::path>& dirs,
    const annotations::annotation_groups_factory& agf,
    const annotations::type_repository& atrp,
    const options::knitting_options& ko) const {
    intermediate_model_repository_factory f;
    const auto r(f.make(dirs, agf, atrp, ko, frontend_registrar()));
    return r;
}

intermediate_model workflow::peform_second_stage_expansion(
    const std::vector<boost::filesystem::path>& dirs,
    const annotations::type_repository& atrp,
    const std::list<intermediate_model>& ims) const {
    second_stage_expander ex;
    return ex.make(dirs, atrp, external_expander_registrar(), ims);
}

model workflow::transform_to_model(const intermediate_model& im) const {
    transformer t;
    return t.transform(im);
}

std::list<model>
workflow::execute(const transforms::context& ctx) const {
    BOOST_LOG_SEV(lg, debug) << "Starting workflow.";

    std::list<model> r;
    const std::vector<boost::filesystem::path>& dirs(ctx.data_directories());
    const annotations::annotation_groups_factory& agf(ctx.groups_factory());
    const annotations::type_repository& atrp(ctx.type_repository());
    const options::knitting_options& ko(ctx.options());

    const auto imrp(create_intermediate_model_repository(dirs, agf, atrp, ko));
    for(const auto& pair : imrp.by_language()) {
        const auto& ims(pair.second);
        const auto im(peform_second_stage_expansion(dirs, atrp, ims));
        r.push_back(transform_to_model(im));
    }

    BOOST_LOG_SEV(lg, debug) << "Finished workflow. Models: " << r;
    return r;
}

} }
