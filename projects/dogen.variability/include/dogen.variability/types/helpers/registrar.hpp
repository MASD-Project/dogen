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
#ifndef DOGEN_VARIABILITY_TYPES_HELPERS_REGISTRAR_HPP
#define DOGEN_VARIABILITY_TYPES_HELPERS_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen.variability/types/meta_model/feature_template.hpp"
#include "dogen.variability/types/meta_model/feature_repository.hpp"
#include "dogen.variability/types/meta_model/feature_template_repository.hpp"

namespace dogen::variability::helpers {

/**
 * @brief Keeps track of all of the available feature templates in the
 * system.
 */
class registrar final {
public:
    /**
     * @brief Adds a number of templates into the registrar.
     */
    void register_templates(const std::list<meta_model::feature_template>& fts);

    /**
     * @brief Adds a number of features into the registrar.
     */
    void register_features(const std::list<meta_model::feature>& fts);

public:
    /**
     * @brief Returns all of the feature templates.
     */
    const meta_model::feature_template_repository&
    feature_template_repository();

    /**
     * @brief Returns all of the features.
     */
    const meta_model::feature_repository& feature_repository();

private:
    meta_model::feature_template_repository feature_template_repository_;
    meta_model::feature_repository feature_repository_;
};

}

#endif
