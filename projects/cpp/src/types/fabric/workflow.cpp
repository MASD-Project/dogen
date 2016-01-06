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
#include "dogen/cpp/types/fabric/workflow.hpp"

namespace dogen {
namespace cpp {
namespace fabric {

std::forward_list<boost::shared_ptr<yarn::element> >
workflow::model_elements_as_list_activity(const yarn::model& m) const {
    std::forward_list<boost::shared_ptr<yarn::element> > r;

    for (const auto& pair : m.elements()) {
        const auto e(pair.second);
        r.push_front(e);
    }
    return r;
}

std::forward_list<boost::shared_ptr<yarn::element> >
workflow::execute(const yarn::model& m) const {
    const auto r(model_elements_as_list_activity(m));
    return r;
}

} } }
