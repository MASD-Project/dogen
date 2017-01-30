/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <set>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/enumeration_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.enumeration_expander"));

const std::string csharp_invalid("Invalid");
const std::string cpp_invalid("invalid");

const std::string duplicate_enumerator("Duplicate enumerator name: ");
const std::string unsupported_language("Invalid or unsupported language: ");
const std::string too_many_defaults(
    "Model has more than one default enumeration: ");
const std::string missing_default(
    "Model does not have a default enumeration type: ");

}

namespace dogen {
namespace yarn {

std::ostream&
operator<<(std::ostream& s,
    const enumeration_expander::enumeration_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::"
      << "enumeration_expander::enumeration_type_group\"" << ", "
      << "\"use_implementation_defined_underlying_element\": "
      << v.use_implementation_defined_underlying_element << ", "
      << "\"use_implementation_defined_enumerator_values\": "
      << v.use_implementation_defined_enumerator_values << ", "
      << "\"add_invalid_enumerator\": " << v.add_invalid_enumerator
      << " }";

    return s;
}

std::ostream&
operator<<(std::ostream& s,
    const enumeration_expander::enumerator_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::"
      << "enumeration_expander::enumerator_type_group\"" << ", "
      << "\"value\": " << v.value
      << " }";

    return s;
}

std::ostream&
operator<<(std::ostream& s, const enumeration_expander::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::enumeration_expander::"
      << "type_group\"" << ", "
      << "\"enumeration\": " << v.enumeration << ", "
      << "\"enumerator\": " << v.enumerator
      << " }";

    return s;
}

enumeration_expander::enumeration_type_group enumeration_expander::
make_enumeration_type_group(const annotations::type_repository& atrp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating enumeration type group.";

    enumeration_type_group r;
    const annotations::type_repository_selector s(atrp);

    using en = traits::enumeration;
    const auto uidue(en::use_implementation_defined_underlying_element());
    r.use_implementation_defined_underlying_element =
        s.select_type_by_name(uidue);

    const auto uidev(en::use_implementation_defined_enumerator_values());
    r.use_implementation_defined_enumerator_values =
        s.select_type_by_name(uidev);

    const auto aie(en::add_invalid_enumerator());
    r.add_invalid_enumerator = s.select_type_by_name(aie);

    BOOST_LOG_SEV(lg, debug) << "Created enumeration type group.";
    return r;
}

enumeration_expander::enumerator_type_group enumeration_expander::
make_enumerator_type_group(const annotations::type_repository& atrp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating enumerator type group.";

    enumerator_type_group r;
    const annotations::type_repository_selector s(atrp);
    r.value = s.select_type_by_name(traits::enumerator::value());

    BOOST_LOG_SEV(lg, debug) << "Created enumerator type group.";
    return r;
}

enumeration_expander::type_group enumeration_expander::
make_type_group(const annotations::type_repository& atrp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating type group.";

    type_group r;
    r.enumeration = make_enumeration_type_group(atrp);
    r.enumerator = make_enumerator_type_group(atrp);

    BOOST_LOG_SEV(lg, debug) << "Created type group. Result" << r;
    return r;
}

void enumeration_expander::populate_from_annotations(
    const enumeration_type_group& tg, enumeration& e) const {

    const auto& a(e.annotation());
    const annotations::entry_selector s(a);
    const auto uidue(tg.use_implementation_defined_underlying_element);
    e.use_implementation_defined_underlying_element(
        s.get_boolean_content_or_default(uidue));

    const auto uidev(tg.use_implementation_defined_enumerator_values);
    e.use_implementation_defined_enumerator_values(
        s.get_boolean_content_or_default(uidev));

    const auto aie(tg.add_invalid_enumerator);
    e.add_invalid_enumerator(s.get_boolean_content_or_default(aie));
}

void enumeration_expander::populate_from_annotations(
    const enumerator_type_group& tg, enumerator& e) const {
    const auto& a(e.annotation());
    const annotations::entry_selector s(a);
    if (s.has_entry(tg.value))
        e.value(s.get_text_content(tg.value));
}

name enumeration_expander::obtain_enumeration_default_underlying_element_name(
    const intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining default enumeration underlying "
                             << "element name for model: " << im.name().id();

    name r;
    bool found(false);
    for (const auto& pair : im.builtins()) {
        const auto b(pair.second);
        const auto id(b.name().id());
        if (b.is_default_enumeration_type()) {
            BOOST_LOG_SEV(lg, debug) << "Found default enumeration underlying "
                                     << " element name:" << id;

            if (found) {
                BOOST_LOG_SEV(lg, error) << too_many_defaults << id;
                BOOST_THROW_EXCEPTION(expansion_error(too_many_defaults + id));
            }
            found = true;
            r = b.name();
        }
    }

    if (!found) {
        const auto id(im.name().id());
        BOOST_LOG_SEV(lg, error) << missing_default << id;
        BOOST_THROW_EXCEPTION(expansion_error(missing_default + id));
    }

    BOOST_LOG_SEV(lg, debug) << "Obtained default enumeration underlying "
                             << "element name for model. ";
    return r;
}

std::string enumeration_expander::
obtain_invalid_enumerator_simple_name(const languages l) const {
    switch(l) {
    case languages::csharp: return csharp_invalid;
    case languages::cpp: return cpp_invalid;
    case languages::upsilon: return csharp_invalid;
    default: {
        const auto s(boost::lexical_cast<std::string>(l));
        BOOST_LOG_SEV(lg, error) << unsupported_language << s;
        BOOST_THROW_EXCEPTION(expansion_error(unsupported_language + s));
    } }
}

enumerator enumeration_expander::
make_invalid_enumerator(const name& n, const languages l) const {
    enumerator r;
    r.documentation("Represents an uninitialised enum");
    r.value("0");

    yarn::name_factory nf;
    const auto sn(obtain_invalid_enumerator_simple_name(l));
    r.name(nf.build_attribute_name(n, sn));

    return r;
}

void enumeration_expander::expand_default_underlying_element(
    const name& default_underlying_element_name, enumeration& e) {
    const auto ue(e.underlying_element());
    BOOST_LOG_SEV(lg, debug) << "Underlying type: '" << ue.id() << "'";

    if (!ue.simple().empty())
        return;

    BOOST_LOG_SEV(lg, debug) << "Defaulting enumeration to type: "
                             << default_underlying_element_name.id();
    e.underlying_element(default_underlying_element_name);
}

void enumeration_expander::
expand_enumerators(const enumerator_type_group& tg, const languages l,
    enumeration& e) const {
    std::vector<enumerator> enumerators;

    if (e.add_invalid_enumerator()) {
        enumerators.reserve(e.enumerators().size() + 1/*invalid*/);
        enumerators.push_back(make_invalid_enumerator(e.name(), l));
    } else
        enumerators.reserve(e.enumerators().size());

    /*
     * Update the value of each enumerator, and ensure the enumerator
     * names are unique.
     */
    unsigned int pos(e.add_invalid_enumerator() ? 1 : 0);
    yarn::name_factory nf;
    std::set<std::string> enumerator_names;
    for (const auto& en : e.enumerators()) {
        const auto sn(en.name().simple());
        const auto i(enumerator_names.find(sn));
        if (i != enumerator_names.end()) {
            BOOST_LOG_SEV(lg, error) << duplicate_enumerator << sn;
            BOOST_THROW_EXCEPTION(expansion_error(duplicate_enumerator + sn));
        }

        auto copy(en);
        populate_from_annotations(tg, copy);
        copy.value(boost::lexical_cast<std::string>(pos));

        /*
         * Expand name. At this point, we've only populated
         * the enumerator simple name.
         */
        copy.name(nf.build_attribute_name(e.name(), copy.name().simple()));
        enumerators.push_back(copy);
        ++pos;
    }
    e.enumerators(enumerators);
}

void enumeration_expander::
expand(const annotations::type_repository& atrp, intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Started expanding enumerations for model: "
                             << im.name().id();

    /*
     * If no enumerations exist, we can just exit. This means we can
     * still support models that have no dependencies, provided they
     * do not use enumerations. Otherwise, we'd fail when searching
     * for the default underlying element name.
     */
    if (im.enumerations().empty())
        return;

    const auto l(im.input_language());
    const auto tg(make_type_group(atrp));
    const auto duen(obtain_enumeration_default_underlying_element_name(im));

    for (auto& pair : im.enumerations()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Expanding: " << id;

        auto& e(pair.second);
        populate_from_annotations(tg.enumeration, e);
        expand_default_underlying_element(duen, e);
        expand_enumerators(tg.enumerator, l, e);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding enumerations for model.";
}

} }
