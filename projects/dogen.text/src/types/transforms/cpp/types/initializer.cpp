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
#include "dogen.text.cpp/types/transforms/types/main_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/builtin_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/primitive_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/primitive_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/class_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/class_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/enum_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/exception_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/namespace_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/visitor_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/class_forward_declarations_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/visitor_forward_declarations_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/primitive_forward_declarations_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/feature_template_bundle_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/feature_template_bundle_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/feature_bundle_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/feature_bundle_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/variability_initializer_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/variability_initializer_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/archetype_class_header_transform_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/archetype_class_header_factory_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/archetype_class_implementation_transform_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/archetype_class_implementation_factory_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/facet_class_header_transform_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/facet_class_implementation_transform_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/facet_class_header_factory_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/facet_class_implementation_factory_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/backend_class_header_transform_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/backend_class_implementation_transform_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/backend_class_header_factory_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/backend_class_implementation_factory_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/part_class_header_transform_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/part_class_implementation_transform_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/part_class_header_factory_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/part_class_implementation_factory_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/helper_class_header_transform_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/helper_class_implementation_transform_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/helper_class_header_factory_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/helper_class_implementation_factory_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/archetype_kind_class_header_factory_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/archetype_kind_class_implementation_factory_transform.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text/types/transforms/cpp/types/smart_pointer_helper_transform.hpp"
#include "dogen.text/types/transforms/cpp/types/initializer.hpp"

namespace dogen::text::transforms::cpp::types {

void initializer::
initialize(text_transform_registrar& ttrg, helper_registrar& hrg) {
    using namespace text::cpp::transforms::types;
    register_text_transform<builtin_header_transform>(ttrg);
    register_text_transform<primitive_header_transform>(ttrg);
    register_text_transform<primitive_implementation_transform>(ttrg);
    register_text_transform<class_header_transform>(ttrg);
    register_text_transform<class_implementation_transform>(ttrg);
    register_text_transform<enum_header_transform>(ttrg);
    register_text_transform<exception_header_transform>(ttrg);
    register_text_transform<namespace_header_transform>(ttrg);
    register_text_transform<visitor_header_transform>(ttrg);
    register_text_transform<class_forward_declarations_transform>(ttrg);
    register_text_transform<visitor_forward_declarations_transform>(ttrg);
    register_text_transform<primitive_forward_declarations_transform>(ttrg);
    register_text_transform<feature_template_bundle_header_transform>(ttrg);
    register_text_transform<feature_template_bundle_implementation_transform>(ttrg);
    register_text_transform<feature_bundle_header_transform>(ttrg);
    register_text_transform<feature_bundle_implementation_transform>(ttrg);
    register_text_transform<variability_initializer_header_transform>(ttrg);
    register_text_transform<variability_initializer_implementation_transform>(ttrg);
    register_text_transform<main_transform>(ttrg);
    register_text_transform<archetype_class_header_transform_transform>(ttrg);
    register_text_transform<archetype_class_header_factory_transform>(ttrg);
    register_text_transform<archetype_class_implementation_transform_transform>(ttrg);
    register_text_transform<archetype_class_implementation_factory_transform>(ttrg);
    register_text_transform<facet_class_header_transform_transform>(ttrg);
    register_text_transform<facet_class_implementation_transform_transform>(ttrg);
    register_text_transform<facet_class_header_factory_transform>(ttrg);
    register_text_transform<facet_class_implementation_factory_transform>(ttrg);
    register_text_transform<backend_class_header_transform_transform>(ttrg);
    register_text_transform<backend_class_implementation_transform_transform>(ttrg);
    register_text_transform<backend_class_header_factory_transform>(ttrg);
    register_text_transform<backend_class_implementation_factory_transform>(ttrg);
    register_text_transform<part_class_header_transform_transform>(ttrg);
    register_text_transform<part_class_implementation_transform_transform>(ttrg);
    register_text_transform<part_class_header_factory_transform>(ttrg);
    register_text_transform<part_class_implementation_factory_transform>(ttrg);
    register_text_transform<helper_class_header_transform_transform>(ttrg);
    register_text_transform<helper_class_implementation_transform_transform>(ttrg);
    register_text_transform<helper_class_header_factory_transform>(ttrg);
    register_text_transform<helper_class_implementation_factory_transform>(ttrg);
    register_text_transform<archetype_kind_class_header_factory_transform>(ttrg);
    register_text_transform<archetype_kind_class_implementation_factory_transform>(ttrg);

    register_helper<smart_pointer_helper_transform>(hrg);
}

}
