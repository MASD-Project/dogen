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
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
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
    const auto ut(e.underlying_type());
    BOOST_LOG_SEV(lg, debug) << "Underlying type: '" << ut.id() << "'";

    if (!ut.simple().empty())
        return;

    BOOST_LOG_SEV(lg, debug) << "Defaulting enumeration to type: "
                             << default_underlying_element_name.id();
    e.underlying_type(default_underlying_element_name);
}

void enumeration_expander::
expand_enumerators(const languages l, enumeration& e) const {
    std::vector<enumerator> enumerators;
    enumerators.reserve(e.enumerators().size() + 1/*invalid*/);
    enumerators.push_back(make_invalid_enumerator(e.name(), l));

    /*
     * Update the value of each enumerator, and ensure the
     * enumerator names are unique. Note that position zero is
     * already taken by "invalid".
     */
    unsigned int pos(1);
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

void enumeration_expander::expand(intermediate_model& im) {
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
    const auto duen(obtain_enumeration_default_underlying_element_name(im));

    for (auto& pair : im.enumerations()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Expanding: " << id;

        auto& e(pair.second);
        expand_default_underlying_element(duen, e);
        expand_enumerators(l, e);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding enumerations for model.";
}

} }
