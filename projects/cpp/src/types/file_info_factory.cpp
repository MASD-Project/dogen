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
const std::string includer_name("all");
const std::string invalid_enabled_facets("Invalid enabled facets request: ");
const std::string unsupported_meta_type("Meta type not supported: ");

}

namespace dogen {
namespace cpp {

file_info_factory::
file_info_factory(const std::set<config::cpp_facet_types>& enabled_facets,
    const transformer& t, const locator& l, includer& i)
    : descriptor_factory_(enabled_facets), transformer_(t), locator_(l),
      includer_(i) { }

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

location_request file_info_factory::
location_request_factory(const content_descriptor& cd) const {
    location_request r;
    r.facet_type(cd.facet_type());
    r.file_type(cd.file_type());
    r.aspect_type(cd.aspect_type());
    r.model_name(cd.name().model_name());
    r.package_path(cd.name().package_path());
    r.file_name(cd.name().type_name());
    r.external_package_path(cd.name().external_package_path());
    return r;
}

file_info file_info_factory::create(const content_descriptor& cd) {
    file_info r;
    r.facet_type(cd.facet_type());
    r.file_type(cd.file_type());
    r.aspect_type(cd.aspect_type());
    r.category_type(cd.category_type());
    r.meta_type(cd.name().meta_type());

    const auto rq(location_request_factory(cd));
    r.file_path(locator_.absolute_path(rq));

    if (cd.file_type() == file_types::header) {
        const auto rp(locator_.relative_logical_path(rq));
        r.header_guard(to_header_guard_name(rp));
        if (cd.aspect_type() == aspect_types::main)
            includer_.register_header(cd.facet_type(), rp);
    }

    return r;
}

std::list<file_info> file_info_factory::create(const sml::enumeration& e) {
    if (e.generation_type() == sml::generation_types::no_generation)
        return std::list<file_info>{ };

    std::list<file_info> r;
    const auto ei(transformer_.transform(e));
    const auto ct(sml::category_types::user_defined);
    for (const auto cd : descriptor_factory_.create(e.name(), ct)) {
        file_info fi(create(cd));
        fi.enumeration_info(ei);

        const auto in(includer_.includes_for_enumeration(e,
                cd.facet_type(), cd.file_type(), cd.aspect_type()));
        fi.system_includes(in.system);
        fi.user_includes(in.user);

        r.push_back(fi);
    }
    return r;
}

std::list<file_info> file_info_factory::create(const sml::exception& e) {
    if (e.generation_type() == sml::generation_types::no_generation)
        return std::list<file_info>{ };

    std::list<file_info> r;
    const auto ei(transformer_.transform(e));
    const auto ct(sml::category_types::user_defined);
    for (const auto cd : descriptor_factory_.create(e.name(), ct)) {
        file_info fi(create(cd));
        fi.exception_info(ei);

        const auto in(includer_.includes_for_exception(e,
                cd.facet_type(), cd.file_type(), cd.aspect_type()));
        fi.system_includes(in.system);
        fi.user_includes(in.user);

        r.push_back(fi);
    }
    return r;
}

std::list<file_info> file_info_factory::create(const sml::package& p) {
    if (p.documentation().empty())
        return std::list<file_info>{ };

    std::list<file_info> r;
    const auto pi(transformer_.transform(p));
    for (const auto cd : descriptor_factory_.create(p.name())) {
        file_info fi(create(cd));
        fi.namespace_info(pi);
        r.push_back(fi);
    }
    return r;
}

std::list<file_info> file_info_factory::create(const sml::model& m) {
    if (m.documentation().empty())
        return std::list<file_info>{ };

    std::list<file_info> r;
    const auto pi(transformer_.transform(m));
    for (const auto cd : descriptor_factory_.create(m)) {
        file_info fi(create(cd));
        fi.namespace_info(pi);
        r.push_back(fi);
    }
    return r;
}

std::list<file_info> file_info_factory::create(const sml::pod& p,
    const optional_class_info pci, const optional_class_info opci) {

    if (p.generation_type() == sml::generation_types::no_generation)
        return std::list<file_info>{ };

    std::list<file_info> r;
    const auto ci(transformer_.transform(p, pci, opci));
    const auto ct(p.category_type());
    const auto pt(p.pod_type());
    for (const auto cd : descriptor_factory_.create(p.name(), ct, pt)) {
        file_info fi(create(cd));
        fi.class_info(ci);

        const auto in(includer_.includes_for_pod(p,
                cd.facet_type(), cd.file_type(), cd.aspect_type()));
        fi.system_includes(in.system);
        fi.user_includes(in.user);

        r.push_back(fi);
    }
    return r;
}

std::list<file_info> file_info_factory::create_includer(
    const std::list<std::string>& external_package_path,
    const config::cpp_facet_types ft) {

    sml::qname qn;
    qn.type_name(includer_name);
    qn.external_package_path(external_package_path);
    qn.meta_type(sml::meta_types::pod);

    std::list<file_info> r;
    for (const auto cd : descriptor_factory_.create_includer(qn, ft)) {
        file_info fi(create(cd));
        fi.aspect_type(aspect_types::includers);

        const auto includes(includer_.includes_for_includer_files(ft));
        fi.system_includes(includes.system);
        fi.user_includes(includes.user);
        r.push_back(fi);
    }
    return r;
}

} }
