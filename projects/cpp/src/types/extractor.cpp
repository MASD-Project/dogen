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
const std::string bool_type("bool");
const std::string double_type("double");
const std::string float_type("float");

const std::string concept_not_found("Concept not found in concept container: ");
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

void extractor::properties_for_concept(const sml::qname& qn,
    std::list<sml::property>& properties,
    std::unordered_set<sml::qname>& processed_qnames) const {

    if (processed_qnames.find(qn) != processed_qnames.end())
        return;

    processed_qnames.insert(qn);
    const auto i(concepts_.find(qn));
    if (i == concepts_.end()) {
        BOOST_LOG_SEV(lg, error) << concept_not_found << qn.type_name();
        BOOST_THROW_EXCEPTION(extraction_error(concept_not_found +
                qn.type_name()));
    }

    for (const auto& c : i->second.refines())
        properties_for_concept(c, properties, processed_qnames);

    const auto& props(i->second.properties());
    properties.insert(properties.end(), props.begin(), props.end());
}

relationships extractor::
extract_dependency_graph(const sml::pod& p) const {
    relationships r;

    if (p.parent_name())
        r.names().insert(*p.parent_name());

    if (p.is_visitable()) {
        auto qn(p.name());
        qn.type_name(qn.type_name() + "_visitor");
        r.visitor(qn);
    } else if (p.original_parent_name()) {
        auto opn(*p.original_parent_name());
        auto i(pods_.find(opn));
        if (i == pods_.end()) {
            BOOST_LOG_SEV(lg, error) << qname_could_not_be_found << opn;
            BOOST_THROW_EXCEPTION(extraction_error(qname_could_not_be_found +
                    boost::lexical_cast<std::string>(opn)));
        }

        if (i->second.is_visitable()) {
            opn.type_name(opn.type_name() + "_visitor");
            r.visitor(opn);
        }
    }

    r.is_parent(p.is_parent());
    r.is_child(p.parent_name());
    r.leaves().insert(p.leaves().begin(), p.leaves().end());

    std::list<sml::property> props;
    std::unordered_set<sml::qname> processed_qnames;
    for (const auto& qn : p.modeled_concepts())
        properties_for_concept(qn, props, processed_qnames);
    props.insert(props.end(), p.properties().begin(), p.properties().end());

    for (const auto prop : props) {
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
    BOOST_LOG_SEV(lg, debug) << "Extracting inheritance graph for "
                             << qn.type_name();

    relationships r;

    auto i(pods_.find(qn));
    if (i == pods_.end()) {
        BOOST_LOG_SEV(lg, error) << qname_could_not_be_found << qn;
        BOOST_THROW_EXCEPTION(extraction_error(qname_could_not_be_found +
                boost::lexical_cast<std::string>(qn)));
    }

    BOOST_LOG_SEV(lg, debug) << "adding type itself" << qn;
    r.names().insert(qn);

    const auto lambda([](const sml::qname& qn, const std::string& msg ) {
            BOOST_LOG_SEV(lg, error) << msg << qn;
            BOOST_THROW_EXCEPTION(extraction_error(msg +
                    boost::lexical_cast<std::string>(qn)));
        });

    if (i->second.leaves().empty())
        BOOST_LOG_SEV(lg, debug) << "type has no leaves.";

    for (const auto& l : i->second.leaves()) {
        i = pods_.find(l);
        if (i == pods_.end())
            lambda(l, qname_could_not_be_found);

        do {
           BOOST_LOG_SEV(lg, debug) << "adding " << i->second.name();
            r.names().insert(i->second.name());

            if (!i->second.parent_name())
                lambda(i->second.name(), type_does_not_have_a_parent);

            i = pods_.find(*i->second.parent_name());
        } while (i->second.name() != qn);
    }

    BOOST_LOG_SEV(lg, debug) << "Done extracting inheritance graph for "
                             << qn.type_name();

    return r;
}

} }
