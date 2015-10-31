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
#ifndef DOGEN_YARN_TYPES_FRONTEND_WORKFLOW_HPP
#define DOGEN_YARN_TYPES_FRONTEND_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <boost/optional.hpp>
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/yarn/types/frontend_registrar.hpp"
#include "dogen/yarn/types/frontend_interface.hpp"
#include "dogen/yarn/types/input_descriptor.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Manages the entire frontend workflow.
 */
class frontend_workflow {
public:
    explicit frontend_workflow(const dynamic::repository& rp);

public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static frontend_registrar& registrar();

private:
    /**
     * @brief Given an input descriptor, obtains the associated
     * intermediate model.
     */
    intermediate_model obtain_model(const input_descriptor& d) const;

public:
    /**
     * @brief Process all of the inputs into intermediate models,
     * using the appropriate frontends.
     *
     * @pre All supplied descriptors must be supported by the
     * registered frontends.
     */
    std::list<intermediate_model> execute(
        const std::list<input_descriptor>& descriptors);

private:
    static std::shared_ptr<frontend_registrar> registrar_;
    const dynamic::workflow dynamic_workflow_;
};

/*
 * Helper method to register the frontend.
 */
template<typename Frontend>
inline void register_frontend() {
    auto s(std::make_shared<Frontend>());
    auto& rg(frontend_workflow::registrar());
    for (const auto& e : s->supported_extensions())
        rg.register_frontend_against_extension(e, s);
}

} }

#endif
