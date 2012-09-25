/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/generator/backends/cpp/formatters/cpp_domain_class_declaration.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

cpp_domain_class_declaration::
cpp_domain_class_declaration(std::ostream& stream,
    bool disable_complete_constructor, bool disable_io)
    : cpp_class_declaration(stream),
      disable_complete_constructor_(disable_complete_constructor),
      disable_io_(disable_io) {}

void cpp_domain_class_declaration::
hand_crafted_constructors(class_view_model vm) {
    default_constructor(vm);
    if (!disable_complete_constructor_)
        complete_constructor(vm);
}

void cpp_domain_class_declaration::format(class_view_model vm) {
    open_class(vm);
    {
        cpp_positive_indenter_scope s(indenter_);
        compiler_generated_constuctors(vm);
        hand_crafted_constructors(vm);
        friends(vm);
        if (!disable_io_)
            to_stream();
        getters_and_setters(vm);
        equality(vm);
        swap_and_assignment(vm);
        member_variables(vm);
    }
    close_class();
}

} } } } }
