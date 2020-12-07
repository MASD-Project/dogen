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
#include "dogen.text.csharp/types/transforms/io/primitive_transform.hpp"
#include "dogen.text.csharp/types/transforms/io/class_transform.hpp"
#include "dogen.text.csharp/types/transforms/io/enum_transform.hpp"
#include "dogen.text.csharp/types/transforms/io/assistant_transform.hpp"
#include "dogen.text/types/transforms/csharp/io/enumerable_helper_transform.hpp"
#include "dogen.text/types/transforms/csharp/io/initializer.hpp"

namespace dogen::text::transforms::csharp::io {

void initializer::initialize(text_transform_registrar& ttrg,
    helper_registrar& hrg) {
    using namespace text::csharp::transforms::io;
    register_text_transform<class_transform>(ttrg);
    register_text_transform<primitive_transform>(ttrg);
    register_text_transform<enum_transform>(ttrg);
    register_text_transform<assistant_transform>(ttrg);

    register_helper<enumerable_helper_transform>(hrg);
}

}
