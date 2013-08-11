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
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/io/content_types_io.hpp"
#include "dogen/cpp/types/building_error.hpp"
#include "dogen/sml_to_cpp/types/source_file_factory.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.source_file_factory"));

const std::string empty;
const std::string dot(".");
const std::string separator("_");
const std::string visitor_postfix("_visitor");

}

namespace dogen {
namespace sml_to_cpp {

source_file_factory::source_file_factory(const locator& l) : locator_(l) { }

std::string source_file_factory::
to_header_guard_name(const boost::filesystem::path& rp) const {
    bool is_first(true);
    std::ostringstream stream;
    for (auto p : rp) {
        std::string s(p.string());
        boost::replace_all(s, dot, separator);
        boost::to_upper(s);
        stream << (is_first ? empty : separator) << s;
        is_first = false;
    }
    return stream.str();
}

cpp::source_file source_file_factory::
create(const cpp::content_descriptor& cd) const {
    cpp::source_file r;
    r.descriptor(cd);
    r.file_path(locator_.absolute_path(cd));

    const auto rp(locator_.relative_logical_path(cd));
    r.relative_path(rp);
    if (cd.file_type() == cpp::file_types::header)
        r.header_guard(to_header_guard_name(rp));

    return r;
}

cpp::source_file source_file_factory::create(const cpp::enum_info& ei,
    const cpp::content_descriptor& cd, const inclusion_lists& il) const {
    cpp::source_file r(create(cd));
    r.enum_info(ei);
    r.system_includes(il.system());
    r.user_includes(il.user());
    return r;
}

cpp::source_file source_file_factory::create(const cpp::exception_info& ei,
    const cpp::content_descriptor& cd, const inclusion_lists& il) const {
    cpp::source_file r(create(cd));
    r.exception_info(ei);
    r.system_includes(il.system());
    r.user_includes(il.user());
    return r;
}

cpp::source_file source_file_factory::
create(const cpp::namespace_info& ni, const cpp::content_descriptor& cd) const {
    cpp::source_file r(create(cd));
    r.namespace_info(ni);
    return r;
}

cpp::source_file source_file_factory::create(const cpp::class_info& ci,
    const cpp::content_descriptor& cd, const inclusion_lists& il) const {
    cpp::source_file r(create(cd));
    r.class_info(ci);
    r.system_includes(il.system());
    r.user_includes(il.user());
    return r;
}

cpp::source_file source_file_factory::
create_includer(const cpp::content_descriptor& cd,
    const inclusion_lists& il) const {
    cpp::source_file r(create(cd));
    r.descriptor().content_type(cpp::content_types::includer);
    r.system_includes(il.system());
    r.user_includes(il.user());
    return r;
}

cpp::source_file source_file_factory::
create_registrar(const cpp::registrar_info& ri,
    const cpp::content_descriptor& cd, const inclusion_lists& il) const {
    cpp::source_file r(create(cd));
    r.registrar_info(ri);
    r.system_includes(il.system());
    r.user_includes(il.user());
    return r;
}

cpp::source_file source_file_factory::
create_visitor(const cpp::visitor_info& vi, const cpp::content_descriptor& cd,
    const inclusion_lists& il) const {
    cpp::source_file r(create(cd));
    r.visitor_info(vi);
    r.system_includes(il.system());
    r.user_includes(il.user());
    return r;
}

} }
