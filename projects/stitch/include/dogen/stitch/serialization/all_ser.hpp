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
#include "dogen/stitch/serialization/block_ser.hpp"
#include "dogen/stitch/serialization/segment_ser.hpp"
#include "dogen/stitch/serialization/text_line_ser.hpp"
#include "dogen/stitch/serialization/formatter_ser.hpp"
#include "dogen/stitch/serialization/registrar_ser.hpp"
#include "dogen/stitch/serialization/text_block_ser.hpp"
#include "dogen/stitch/serialization/segment_types_ser.hpp"
#include "dogen/stitch/serialization/text_template_ser.hpp"
#include "dogen/stitch/serialization/scriptlet_line_ser.hpp"
#include "dogen/stitch/serialization/scriptlet_block_ser.hpp"
#include "dogen/stitch/serialization/mixed_content_line_ser.hpp"
#include "dogen/stitch/serialization/mixed_content_block_ser.hpp"
