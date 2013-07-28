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
#include <boost/pointer_cast.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/types/value_object_types.hpp"
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
    "Could not find QName in object container: ");
const std::string type_does_not_have_a_parent(
    "Type in inheritance graph does not have a parent: ");

}

namespace dogen {
namespace cpp {

void extractor::recurse_nested_qnames(const sml::nested_qname& nqn,
    relationships& rel, bool& is_pointer) const {

    const auto qn(nqn.type());
    if (is_pointer)
        rel.forward_decls().insert(qn);
    else
        rel.names().insert(qn);

    bool found(false);
    const auto i(model_.primitives().find(qn));
    if (i != model_.primitives().end()) {
        found = true;
        is_pointer = false;
    }

    if (!found) {
        const auto j(model_.enumerations().find(qn));
        if (j != model_.enumerations().end()) {
            is_pointer = false;
            found = true;
        }
    }

    if (!found) {
        const auto k(model_.objects().find(qn));
        if (k == model_.objects().end()) {
            BOOST_LOG_SEV(lg, error) << qname_could_not_be_found << qn;
            BOOST_THROW_EXCEPTION(extraction_error(qname_could_not_be_found +
                    boost::lexical_cast<std::string>(qn)));
        }

        using sml::value_object;
        const auto vo(boost::dynamic_pointer_cast<value_object>(k->second));

        if (vo) {
            const auto ac(sml::value_object_types::associative_container);
            if (vo->type() == ac && nqn.children().size() >= 1)
                rel.keys().insert(nqn.children().front().type());

            const auto sp(sml::value_object_types::smart_pointer);
            is_pointer = vo->type() == sp;
        }
    }

    const auto sn(qn.simple_name());
    if (sn == bool_type || sn == double_type || sn == float_type)
        rel.requires_stream_manipulators(true);
    else if (sn == std_.type(std_types::string))
        rel.has_std_string(true);
    else if (sn == boost_.type(boost_types::variant))
        rel.has_variant(true);
    else if (sn == std_.type(std_types::pair))
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
    const auto i(model_.concepts().find(qn));
    if (i == model_.concepts().end()) {
        const auto sn(qn.simple_name());
        BOOST_LOG_SEV(lg, error) << concept_not_found << sn;
        BOOST_THROW_EXCEPTION(extraction_error(concept_not_found + sn));
    }

    for (const auto& c : i->second.refines())
        properties_for_concept(c, properties, processed_qnames);

    const auto& props(i->second.properties());
    properties.insert(properties.end(), props.begin(), props.end());
}

relationships
extractor::extract_dependency_graph(const sml::abstract_object& ao) const {
    BOOST_LOG_SEV(lg, debug) << "Extracting dependency graph for " << ao.name();

    relationships r;

    if (ao.parent_name())
        r.names().insert(*ao.parent_name());

    r.is_parent(ao.is_parent());
    r.is_child(ao.parent_name());
    r.leaves().insert(ao.leaves().begin(), ao.leaves().end());

    std::list<sml::property> props;
    std::unordered_set<sml::qname> processed_qnames;
    for (const auto& qn : ao.modeled_concepts())
        properties_for_concept(qn, props, processed_qnames);
    props.insert(props.end(), ao.properties().begin(), ao.properties().end());

    for (const auto& prop : props) {
        const auto nqn(prop.type());
        bool is_pointer(nqn.is_pointer());
        recurse_nested_qnames(nqn, r, is_pointer);
    }

    for (const auto& op : ao.operations()) {
        if (!op.type())
            continue;

        const auto nqn(*op.type());
        bool is_pointer(nqn.is_pointer());
        recurse_nested_qnames(nqn, r, is_pointer);

        // FIXME: do parameters too
    }

    for (const auto& n : r.names()) {
        if (r.forward_decls().find(n) != r.forward_decls().end())
            r.forward_decls().erase(n);
    }

    BOOST_LOG_SEV(lg, debug) << "Extracted dependency graph for " << ao.name();
    return r;
}

relationships extractor::extract_inheritance_graph(const sml::qname& qn) const {
    BOOST_LOG_SEV(lg, debug) << "Extracting inheritance graph for "
                             << qn.simple_name();

    relationships r;

    auto i(model_.objects().find(qn));
    if (i == model_.objects().end()) {
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

    const auto& ao(*i->second);
    if (ao.leaves().empty())
        BOOST_LOG_SEV(lg, debug) << "type has no leaves.";

    for (const auto& l : ao.leaves()) {
        i = model_.objects().find(l);
        if (i == model_.objects().end())
            lambda(l, qname_could_not_be_found);

        do {
            const auto& lao(*i->second);
            BOOST_LOG_SEV(lg, debug) << "adding " << lao.name();
            r.names().insert(lao.name());

            if (!lao.parent_name())
                lambda(lao.name(), type_does_not_have_a_parent);

            i = model_.objects().find(*lao.parent_name());
            if (i == model_.objects().end())
                lambda(*lao.parent_name(), qname_could_not_be_found);
        } while (i->second->name() != qn);
    }

    BOOST_LOG_SEV(lg, debug) << "Done extracting inheritance graph for "
                             << qn.simple_name();

    return r;
}

} }
