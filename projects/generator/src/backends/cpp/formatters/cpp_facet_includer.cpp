/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_facet_includer.hpp"

namespace {

const bool is_system(true);
const bool is_user(false);

const std::string unexpected_class_view_model(
    "File view model should not contain a class view model");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

facet_includer::
facet_includer(std::ostream& stream, cpp_facet_types facet_type) :
    stream_(stream), facet_type_(facet_type),
    file_type_(cpp_file_types::header),
    utility_(stream_, indenter_) { }

file_formatter::shared_ptr facet_includer::
create(std::ostream& stream,cpp_facet_types facet_type) {
    return file_formatter::shared_ptr(new facet_includer(stream, facet_type));
}

void facet_includer::format(view_models::file_view_model vm) {
    if (vm.class_vm())
        throw generation_failure(unexpected_class_view_model);

    licence licence(stream_);
    licence.format();

    cpp_includes includes(stream_);
    includes.format(vm.system_dependencies(), is_system);
    includes.format(vm.user_dependencies(), is_user);
}

} } } } }
