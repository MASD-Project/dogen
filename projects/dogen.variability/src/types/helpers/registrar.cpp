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
#include "dogen.variability/types/helpers/registrar.hpp"

namespace dogen::variability::helpers {

void registrar::
register_templates(const std::list<entities::feature_template>& fts) {
    for (const auto& ft : fts)
        feature_template_repository_.templates().push_back(ft);
}

void registrar::
register_features(const std::list<entities::feature>& fs) {
    for (const auto& f : fs)
        feature_repository_.features().push_back(f);
}

const entities::feature_template_repository&
registrar::feature_template_repository() {
    return feature_template_repository_;
}

const entities::feature_repository&
registrar::feature_repository() {
    return feature_repository_;
}

}
