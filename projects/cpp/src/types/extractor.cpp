/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2013 Kitanda <info@kitanda.co.uk>
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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/cpp/types/extraction_error.hpp"
#include "dogen/cpp/types/extractor.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.extractor"));

const std::string empty;
const std::string primitive_model("primitive_model");
const std::string bool_type("bool");
const std::string double_type("double");
const std::string float_type("float");

const std::string qname_could_not_be_found(
    "Could not find QName in pod container: ");
const std::string type_does_not_have_a_parent(
    "Type in inheritance graph does not have a parent: ");


}

namespace dogen {
namespace cpp {

void extractor::
recurse_nested_qnames(const sml::nested_qname& nqn, relationships& rel,
    bool& is_pointer) const {

    const auto qn(nqn.type());
    if (is_pointer)
        rel.forward_decls().insert(qn);
    else
        rel.names().insert(qn);

    is_pointer = false;
    if (qn.meta_type() == sml::meta_types::pod) {
        const auto i(pods_.find(qn));
        if (i == pods_.end()) {
            BOOST_LOG_SEV(lg, error) << qname_could_not_be_found << qn;
            BOOST_THROW_EXCEPTION(extraction_error(qname_could_not_be_found +
                    boost::lexical_cast<std::string>(qn)));
        }

        const auto pt(i->second.pod_type());
        const auto is_ac(pt == sml::pod_types::associative_container);
        if (is_ac && nqn.children().size() >= 1)
            rel.keys().insert(nqn.children().front().type());
        is_pointer = pt == sml::pod_types::smart_pointer;
    }

    if (qn.type_name() == bool_type || qn.type_name() == double_type ||
        qn.type_name() == float_type)
        rel.requires_stream_manipulators(true);
    else if (qn.type_name() == std_.type(std_types::string))
        rel.has_std_string(true);
    else if (qn.type_name() == boost_.type(boost_types::variant))
        rel.has_variant(true);
    else if (qn.type_name() == std_.type(std_types::pair))
        rel.has_std_pair(true);

    for (const auto c : nqn.children())
        recurse_nested_qnames(c, rel, is_pointer);
}

relationships extractor::
extract_dependency_graph(const sml::pod& p) const {
    relationships r;

    if (p.parent_name())
        r.names().insert(*p.parent_name());

    r.is_parent(p.is_parent());
    r.is_child(p.parent_name());
    r.leaves().insert(p.leaves().begin(), p.leaves().end());

    for (const auto prop : p.properties()) {
        const auto nqn(prop.type_name());
        bool is_pointer(nqn.is_pointer());
        recurse_nested_qnames(nqn, r, is_pointer);
    }

    for (const auto& n : r.names()) {
        if (r.forward_decls().find(n) != r.forward_decls().end())
            r.forward_decls().erase(n);
    }

    return r;
}

relationships extractor::
extract_inheritance_graph(const sml::qname& qn) const {
    relationships r;

    auto i(pods_.find(qn));
    if (i == pods_.end()) {
        BOOST_LOG_SEV(lg, error) << qname_could_not_be_found << qn;
        BOOST_THROW_EXCEPTION(extraction_error(qname_could_not_be_found +
                boost::lexical_cast<std::string>(qn)));
    }

    const auto leaves(i->second.leaves());
    for (const auto& l : leaves) {
        i = pods_.find(l);
        if (i == pods_.end()) {
            BOOST_LOG_SEV(lg, error) << qname_could_not_be_found << l;
            BOOST_THROW_EXCEPTION(extraction_error(qname_could_not_be_found +
                    boost::lexical_cast<std::string>(l)));
        }

        do {
            r.names().insert(i->second.name());
            if (!i->second.parent_name()) {
                BOOST_LOG_SEV(lg, error) << type_does_not_have_a_parent
                                         << i->second.name();

                BOOST_THROW_EXCEPTION(
                    extraction_error(type_does_not_have_a_parent +
                        boost::lexical_cast<std::string>(i->second.name())));
            }
            i = pods_.find(*i->second.parent_name());
        } while (i->second.parent_name() != qn);
    }

    return r;
}

} }
