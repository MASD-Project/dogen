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
#include <string>
#include <list>
#include <ostream>
#include "dogen/generator/generation_failure.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_licence.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_includes.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_qualified_name.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_indenter.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_serialization_implementation.hpp"

namespace {

const std::string boost_ns("boost");
const std::string serialization_ns("serialization");

const std::string missing_class_view_model(
    "File view model must contain a class view model");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

serialization_implementation::
serialization_implementation(std::ostream& stream) :
    stream_(stream),
    utility_(stream_, indenter_) { }

file_formatter::shared_ptr
serialization_implementation::create(std::ostream& stream) {
    return file_formatter::shared_ptr(new serialization_implementation(stream));
}

void serialization_implementation::format(const file_view_model& vm) {
    boost::optional<view_models::class_view_model> o(vm.class_vm());
    if (!o)
        throw generation_failure(missing_class_view_model);

    licence licence(stream_);
    licence.format();

    cpp_includes includes(stream_);
    includes.format(vm);
    utility_.blank_line();

    const view_models::class_view_model& cvm(*o);
    if (cvm.is_parent() || !cvm.parents().empty()) {
        cpp_qualified_name qualified_name(stream_);

        stream_ << indenter_ << "BOOST_CLASS_IS_WRAPPER(";
        qualified_name.format(cvm);
        stream_ << ")" << std::endl;

        stream_ << indenter_ << "BOOST_CLASS_TRACKING(";
        qualified_name.format(cvm);
        stream_ << ", boost::serialization::track_selectively)"
                << std::endl;

        // stream_ << indenter_ << "BOOST_CLASS_IMPLEMENTATION(";
        // qualified_name.format(cvm);
        // stream_ << ", boost::serialization::object_class_info)"
        //         << std::endl;
    }
}

} } } } }
