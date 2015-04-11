/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/stitch/test_data/block_td.hpp"
#include "dogen/stitch/test_data/text_block_td.hpp"
#include "dogen/stitch/test_data/scriptlet_block_td.hpp"
#include "dogen/stitch/test_data/mixed_content_block_td.hpp"



namespace dogen {
namespace stitch {


void block_generator::
populate(const unsigned int /*position*/, result_type& /*v*/) {
}

block_generator::result_type*
block_generator::create_ptr(const unsigned int position) {
    if ((position % 2) == 0)
        return dogen::stitch::scriptlet_block_generator::create_ptr(position);
    if ((position % 2) == 1)
        return dogen::stitch::text_block_generator::create_ptr(position);
    return dogen::stitch::mixed_content_block_generator::create_ptr(position);
}


} }
