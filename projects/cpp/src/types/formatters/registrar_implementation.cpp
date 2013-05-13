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
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/namespace_helper.hpp"
#include "dogen/cpp/types/formatters/licence.hpp"
#include "dogen/cpp/types/formatters/includes.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formatters/registrar_implementation.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.formatters.registrar_implementation"));

const bool is_system(true);
const bool is_user(false);

const std::string boost_ns("boost::archive");

const std::string expected_registrar_info(
    "File view model must contain a registrar view model");

}

namespace dogen {
namespace cpp {
namespace formatters {

registrar_implementation::
registrar_implementation(std::ostream& stream,
    const bool disable_xml_serialization) :
    stream_(stream), utility_(stream_, indenter_),
    disable_xml_serialization_(disable_xml_serialization) { }

file_formatter::shared_ptr registrar_implementation::
create(std::ostream& stream, const bool disable_xml_serialization) {
    return file_formatter::shared_ptr(
        new registrar_implementation(stream, disable_xml_serialization));
}

void registrar_implementation::format(const file_info& fi) {
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

    // FIXME: massive hack for EOS workaround
    stream_ << "#ifdef __linux__" << std::endl
            << "#include \"eos/portable_iarchive.hpp\"" << std::endl
            << "#include \"eos/portable_oarchive.hpp\"" << std::endl
            << "#endif" << std::endl;
    utility_.blank_line();

    {
        const auto ei(*o);
        namespace_helper ns(stream_, ei.namespaces());

        const auto deps(ei.model_dependencies());
        const auto leaves(ei.leaves());
        const bool has_types(!deps.empty() || !leaves.empty());
        const std::string arg_name(has_types ? " ar" : "");
        utility_.blank_line();

        stream_ << indenter_ << "template<typename Archive>" << std::endl
                << indenter_ << "void register_types(Archive&" << arg_name
                << ") ";
        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            for (const auto d : deps) {
                stream_ << indenter_ << d << "::register_types(ar);"
                        << std::endl;
            }

            if (!deps.empty() && !leaves.empty())
                utility_.blank_line();

            for (const auto l : leaves) {
                stream_ << indenter_
                        << "ar.template register_type<" << l << ">();"
                        << std::endl;
            }
        }
        utility_.close_scope();
        utility_.blank_line();

        auto lambda([&](const std::string& archive) {
                stream_ << indenter_ << "template void register_types("
                        << boost_ns
                        << "::" << archive << "&" << arg_name << ");"
                        << std::endl;
            });

        lambda("polymorphic_oarchive");
        lambda("polymorphic_iarchive");
        utility_.blank_line();

        lambda("text_oarchive");
        lambda("text_iarchive");
        utility_.blank_line();

        lambda("binary_oarchive");
        lambda("binary_iarchive");
        utility_.blank_line();

        if (!disable_xml_serialization_) {
            lambda("xml_oarchive");
            lambda("xml_iarchive");
            utility_.blank_line();
        }

        stream_ << "#ifdef __linux__" << std::endl
                << indenter_ << "template void register_types("
                << "eos::portable_oarchive& ar);" << std::endl;
        stream_ << indenter_ << "template void register_types("
                << "eos::portable_iarchive& ar);" << std::endl
                << "#endif" << std::endl;
        utility_.blank_line();
    }
}

} } }
