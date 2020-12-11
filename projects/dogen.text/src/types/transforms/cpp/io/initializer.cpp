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
#include "dogen.text/types/transforms/cpp/io/builtin_header_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/primitive_header_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/primitive_implementation_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/class_header_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/class_implementation_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/enum_header_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/enum_implementation_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/smart_pointer_helper_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/associative_container_helper_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/optional_helper_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/pair_helper_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/ptree_helper_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/sequence_container_helper_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/smart_pointer_helper_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/string_helper_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/variant_helper_transform.hpp"
#include "dogen.text/types/transforms/cpp/io/initializer.hpp"

namespace dogen::text::transforms::cpp::io {

void initializer::initialize(text_transform_registrar& ttrg,
    helper_registrar& hrg) {
    register_text_transform<builtin_header_transform>(ttrg);
    register_text_transform<primitive_header_transform>(ttrg);
    register_text_transform<primitive_implementation_transform>(ttrg);
    register_text_transform<class_header_transform>(ttrg);
    register_text_transform<class_implementation_transform>(ttrg);
    register_text_transform<enum_header_transform>(ttrg);
    register_text_transform<enum_implementation_transform>(ttrg);

    register_helper<smart_pointer_helper_transform>(hrg);
    register_helper<associative_container_helper_transform>(hrg);
    register_helper<optional_helper_transform>(hrg);
    register_helper<pair_helper_transform>(hrg);
    register_helper<ptree_helper_transform>(hrg);
    register_helper<sequence_container_helper_transform>(hrg);
    register_helper<string_helper_transform>(hrg);
    register_helper<variant_helper_transform>(hrg);
}

}
