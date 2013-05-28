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
#include "dogen/sml/io/meta_types_io.hpp"
#include "dogen/sml/io/pod_types_io.hpp"
#include "dogen/cpp/types/building_error.hpp"
#include "dogen/cpp/types/file_info_factory.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.file_info_factory"));

const std::string empty;
const std::string dot(".");
const std::string separator("_");
const std::string visitor_postfix("_visitor");

}

namespace dogen {
namespace cpp {

file_info_factory::file_info_factory(const locator& l) : locator_(l) { }

std::string file_info_factory::
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

file_info file_info_factory::create(const content_descriptor& cd) const {
    file_info r;
    r.facet_type(cd.facet_type());
    r.file_type(cd.file_type());
    r.aspect_type(cd.aspect_type());
    r.category_type(cd.category_type());
    r.meta_type(cd.name().meta_type());
    r.file_path(locator_.absolute_path(cd));

    const auto rp(locator_.relative_logical_path(cd));
    r.relative_path(rp);
    if (cd.file_type() == file_types::header)
        r.header_guard(to_header_guard_name(rp));

    return r;
}

file_info file_info_factory::create(const enum_info& ei,
    const content_descriptor& cd, const inclusion_lists& il) const {
    file_info r(create(cd));
    r.enum_info(ei);
    r.system_includes(il.system());
    r.user_includes(il.user());
    return r;
}

file_info file_info_factory::create(const exception_info& ei,
    const content_descriptor& cd, const inclusion_lists& il) const {
    file_info r(create(cd));
    r.exception_info(ei);
    r.system_includes(il.system());
    r.user_includes(il.user());
    return r;
}

file_info file_info_factory::
create(const namespace_info& ni, const content_descriptor& cd) const {
    file_info r(create(cd));
    r.namespace_info(ni);
    return r;
}

file_info file_info_factory::create(const class_info& ci,
    const content_descriptor& cd, const inclusion_lists& il) const {
    file_info r(create(cd));
    r.class_info(ci);
    r.system_includes(il.system());
    r.user_includes(il.user());
    return r;
}

file_info file_info_factory::create_includer(const content_descriptor& cd,
    const inclusion_lists& il) const {
    file_info r(create(cd));
    r.aspect_type(aspect_types::includers);
    r.system_includes(il.system());
    r.user_includes(il.user());
    return r;
}

file_info file_info_factory::create_registrar(const registrar_info& ri,
    const content_descriptor& cd, const inclusion_lists& il) const {
    file_info r(create(cd));
    r.registrar_info(ri);
    r.system_includes(il.system());
    r.user_includes(il.user());
    return r;
}

file_info file_info_factory::
create_visitor(const visitor_info& vi, const content_descriptor& cd,
    const inclusion_lists& il) const {
    file_info r(create(cd));
    r.visitor_info(vi);
    r.system_includes(il.system());
    r.user_includes(il.user());
    return r;
}

} }
