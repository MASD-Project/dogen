/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <iostream>
#include "dogen/generator/backends/cpp/formatters/cpp_key_class_implementation.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

cpp_key_class_implementation::
cpp_key_class_implementation(std::ostream& stream,
    bool is_versioned, bool disable_complete_constructor, bool disable_io) :
    cpp_class_implementation(stream),
    is_versioned_(is_versioned),
    disable_complete_constructor_(disable_complete_constructor),
    disable_io_(disable_io) { }

void cpp_key_class_implementation::
hand_crafted_constructors(class_view_model vm) {
    default_constructor(vm);
    if (!disable_complete_constructor_)
        complete_constructor(vm);
}

void cpp_key_class_implementation::to_unversioned_key(class_view_model vm) {
    if (!is_versioned_)
        return;

    stream_ << indenter_ << "unversioned_key " << vm.name()
            << "::to_unversioned() const ";

    utility_.open_scope();
    {
        cpp_positive_indenter_scope s(indenter_);
        if (!disable_complete_constructor_) {
            stream_ << indenter_ << "return unversioned_key(id());"
                    << std::endl;
        } else {
            stream_ << indenter_ << "unversioned_key uk;" << std::endl;
            stream_ << indenter_ << "uk.id(id());" << std::endl;
            stream_ << indenter_ << "return uk;" << std::endl;
        }
    }
    utility_.close_scope();
    utility_.blank_line();
}

void cpp_key_class_implementation::format(class_view_model vm) {
    hand_crafted_constructors(vm);
    if (!disable_io_)
        to_stream(vm);
    to_unversioned_key(vm);
    swap(vm);
    assignment_operator(vm);
}

} } } } }
