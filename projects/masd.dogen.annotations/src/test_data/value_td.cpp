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
#include "masd.dogen.annotations/test_data/text_td.hpp"
#include "masd.dogen.annotations/test_data/value_td.hpp"
#include "masd.dogen.annotations/test_data/number_td.hpp"
#include "masd.dogen.annotations/test_data/boolean_td.hpp"
#include "masd.dogen.annotations/test_data/key_value_pair_td.hpp"
#include "masd.dogen.annotations/test_data/text_collection_td.hpp"

namespace masd::dogen::annotations {

void value_generator::
populate(const unsigned int /*position*/, result_type& /*v*/) {
}

value_generator::result_type*
value_generator::create_ptr(const unsigned int position) {
    if ((position % 4) == 0)
        return masd::dogen::annotations::key_value_pair_generator::create_ptr(position);
    if ((position % 4) == 1)
        return masd::dogen::annotations::number_generator::create_ptr(position);
    if ((position % 4) == 2)
        return masd::dogen::annotations::text_generator::create_ptr(position);
    if ((position % 4) == 3)
        return masd::dogen::annotations::text_collection_generator::create_ptr(position);
    return masd::dogen::annotations::boolean_generator::create_ptr(position);
}

}
