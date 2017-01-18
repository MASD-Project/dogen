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
#include "dogen/yarn/io/model_io.hpp"
#include "dogen/yarn/types/intermediate_model_repository_factory.hpp"
#include "dogen/yarn/types/model_factory.hpp"
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

std::vector<intermediate_model> workflow::obtain_intermediate_models(
    const std::vector<boost::filesystem::path>& data_dirs,
    const annotations::annotation_groups_factory& agf,
    const annotations::type_repository& atrp,
    const options::knitting_options& ko) const {
    intermediate_model_repository_factory f;
    const auto rp(f.make(data_dirs, agf, atrp, ko, frontend_registrar()));
    std::vector<intermediate_model> r;

    if (rp.by_language().size() != 1) {
        BOOST_LOG_SEV(lg, error) << "Expected only one language. "
                                 << "Found: " << rp.by_language().size();
        BOOST_THROW_EXCEPTION(workflow_error("Expected only one language."));
    }

    const auto& pair(*rp.by_language().begin());
    const auto& list(pair.second);
    r.reserve(list.size());
    for (const auto& im : list)
        r.push_back(im);

    return r;
}

model workflow::obtain_final_model(const annotations::type_repository& atrp,
    const std::vector<intermediate_model>& ims) const {
    model_factory f;
    return f.make(atrp, injector_registrar(), ims);
}

model workflow::execute(const std::vector<boost::filesystem::path>& data_dirs,
    const annotations::annotation_groups_factory& agf,
    const annotations::type_repository& atrp,
    const options::knitting_options& ko) const {

    const auto im(obtain_intermediate_models(data_dirs, agf, atrp, ko));
    const auto r(obtain_final_model(atrp, im));

    BOOST_LOG_SEV(lg, debug) << "Final model: " << r;
    return r;
}

} }
