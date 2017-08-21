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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_EXOENDO_TRANSFORM_CHAIN_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_EXOENDO_TRANSFORM_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen/yarn/types/meta_model/intermediate_model.hpp"
#include "dogen/yarn/types/transforms/context_fwd.hpp"
#include "dogen/yarn/types/transforms/exomodel_transform_registrar.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

/**
 * @brief Given the location of a supported exogenous model, it
 * obtains it and transforms it into an intermediate model.
 */
class exoendo_transform_chain final {
private:
    /*
     * @brief Given a path to an exogenous model, returns the
     * appropriate exogenous transform for it.
     */
    static exomodel_transform_interface&
    transform_for_model(const boost::filesystem::path& p);

public:
    /**
     * @brief Registrar that keeps track of the available exogenous
     * transforms.
     */
    static exomodel_transform_registrar& registrar();

public:
    /**
     * @brief Apply the transformation to the exogenous model at path
     * @e p.
     *
     * @pre @e p must point to a valid file, and contain a supported
     * exogenous model.
     */
    static meta_model::intermediate_model
    transform(const context& ctx, const boost::filesystem::path& p);

private:
    static std::shared_ptr<exomodel_transform_registrar> registrar_;
};

/*
 * Helper method to register exogenous transforms.
 */
template<typename ExogenousTransforms>
inline void register_exomodel_transform() {
    auto& rg(exoendo_transform_chain::registrar());
    auto t(std::make_shared<ExogenousTransforms>());
    rg.register_exomodel_transform(t);
}

} } }

#endif
