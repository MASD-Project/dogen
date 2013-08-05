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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp_formatters/types/formatting_error.hpp"
#include "dogen/cpp_formatters/types/namespace_formatter.hpp"
#include "dogen/cpp_formatters/types/namespace_helper.hpp"
#include "dogen/cpp_formatters/types/licence.hpp"
#include "dogen/cpp_formatters/types/includes.hpp"
#include "dogen/cpp_formatters/types/registrar_header.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.registrar_header"));

const bool is_system(true);
const bool is_user(false);

const std::string expected_registrar_info(
    "File view model must contain a registrar view model");

}

namespace dogen {
namespace cpp_formatters {

registrar_header::
registrar_header(std::ostream& stream) :
    stream_(stream), utility_(stream_, indenter_) { }

file_formatter::shared_ptr registrar_header::
create(std::ostream& stream) {
    return file_formatter::shared_ptr(new registrar_header(stream));
}

void registrar_header::format(const cpp::file_info& fi) {
    const auto o(fi.registrar_info());
    if (!o) {
        BOOST_LOG_SEV(lg, error) << expected_registrar_info;
        BOOST_THROW_EXCEPTION(formatting_error(expected_registrar_info));
    }

    licence licence(stream_);
    licence.format();

    const bool blank_line(false);
    includes includes(stream_, blank_line);
    includes.format(fi);

    {
        const auto ri(*o);
        namespace_helper ns(stream_, ri.namespaces());
        utility_.blank_line();
        stream_ << indenter_ << "template<typename Archive>" << std::endl
                << indenter_ << "void register_types(Archive& ar);"
                << std::endl;
        utility_.blank_line();
    }
    utility_.blank_line();
}

} }
