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
#include <ostream>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/io/meta_model/endomodel_io.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/io/meta_model/languages_io.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/enumerations_transform.hpp"

namespace {

const std::string id("yarn.transforms.enumerations_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

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
namespace transforms {

std::ostream&
operator<<(std::ostream& s,
    const enumerations_transform::enumeration_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::"
      << "enumerations_transform::enumeration_type_group\"" << ", "
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
    const enumerations_transform::enumerator_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::"
      << "enumerations_transform::enumerator_type_group\"" << ", "
      << "\"value\": " << v.value
      << " }";

    return s;
}

std::ostream&
operator<<(std::ostream& s, const enumerations_transform::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::enumerations_transform::"
      << "type_group\"" << ", "
      << "\"enumeration\": " << v.enumeration << ", "
      << "\"enumerator\": " << v.enumerator
      << " }";

    return s;
}

enumerations_transform::enumeration_type_group enumerations_transform::
make_enumeration_type_group(const annotations::type_repository& atrp) {
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

enumerations_transform::enumerator_type_group enumerations_transform::
make_enumerator_type_group(const annotations::type_repository& atrp) {
    BOOST_LOG_SEV(lg, debug) << "Creating enumerator type group.";

    enumerator_type_group r;
    const annotations::type_repository_selector s(atrp);
    r.value = s.select_type_by_name(traits::enumerator::value());

    BOOST_LOG_SEV(lg, debug) << "Created enumerator type group.";
    return r;
}

enumerations_transform::type_group enumerations_transform::
make_type_group(const annotations::type_repository& atrp) {
    BOOST_LOG_SEV(lg, debug) << "Creating type group.";

    type_group r;
    r.enumeration = make_enumeration_type_group(atrp);
    r.enumerator = make_enumerator_type_group(atrp);

    BOOST_LOG_SEV(lg, debug) << "Created type group. Result" << r;
    return r;
}

void enumerations_transform::populate_from_annotations(
    const enumeration_type_group& tg, meta_model::enumeration& e) {

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

void enumerations_transform::populate_from_annotations(
    const enumerator_type_group& tg, meta_model::enumerator& e) {
    const auto& a(e.annotation());
    const annotations::entry_selector s(a);
    if (s.has_entry(tg.value)) {
        e.value(s.get_text_content(tg.value));
        BOOST_LOG_SEV(lg, debug) << "Read enumerator value: "
                                 << e.value();
    }
}

meta_model::name
enumerations_transform::obtain_enumeration_default_underlying_element_name(
    const meta_model::endomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Obtaining default enumeration underlying "
                             << "element name for model: " << em.name().id();

    meta_model::name r;
    bool found(false);
    for (const auto& pair : em.builtins()) {
        const auto b(*pair.second);
        const auto id(b.name().id());
        if (b.is_default_enumeration_type()) {
            BOOST_LOG_SEV(lg, debug) << "Found default enumeration underlying "
                                     << " element name:" << id;

            if (found) {
                BOOST_LOG_SEV(lg, error) << too_many_defaults << id;
                BOOST_THROW_EXCEPTION(
                    transformation_error(too_many_defaults + id));
            }
            found = true;
            r = b.name();
        }
    }

    if (!found) {
        const auto id(em.name().id());
        BOOST_LOG_SEV(lg, error) << missing_default << id;
        BOOST_THROW_EXCEPTION(transformation_error(missing_default + id));
    }

    BOOST_LOG_SEV(lg, debug) << "Obtained default enumeration underlying "
                             << "element name for model. ";
    return r;
}

std::string enumerations_transform::
obtain_invalid_enumerator_simple_name(const meta_model::languages l) {
    switch(l) {
    case meta_model::languages::csharp: return csharp_invalid;
    case meta_model::languages::cpp: return cpp_invalid;
    case meta_model::languages::upsilon: return csharp_invalid;
    default: {
        const auto s(boost::lexical_cast<std::string>(l));
        BOOST_LOG_SEV(lg, error) << unsupported_language << s;
        BOOST_THROW_EXCEPTION(transformation_error(unsupported_language + s));
    } }
}

meta_model::enumerator enumerations_transform::make_invalid_enumerator(
    const meta_model::name& n, const meta_model::languages l) {
    meta_model::enumerator r;
    r.documentation("Represents an uninitialised enum");
    r.value("0");

    helpers::name_factory nf;
    const auto sn(obtain_invalid_enumerator_simple_name(l));
    r.name(nf.build_attribute_name(n, sn));

    return r;
}

void enumerations_transform::expand_default_underlying_element(
    const meta_model::name& default_underlying_element_name,
    meta_model::enumeration& e) {
    const auto ue(e.underlying_element());
    BOOST_LOG_SEV(lg, debug) << "Underlying type: '" << ue.id() << "'";

    if (!ue.simple().empty())
        return;

    BOOST_LOG_SEV(lg, debug) << "Defaulting enumeration to type: "
                             << default_underlying_element_name.id();
    e.underlying_element(default_underlying_element_name);
}

void enumerations_transform::expand_enumerators(const enumerator_type_group& tg,
    const meta_model::languages l, meta_model::enumeration& e) {
    std::vector<meta_model::enumerator> enumerators;

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
    helpers::name_factory nf;
    std::set<std::string> enumerator_names;
    for (const auto& en : e.enumerators()) {
        const auto sn(en.name().simple());
        const auto i(enumerator_names.find(sn));
        if (i != enumerator_names.end()) {
            BOOST_LOG_SEV(lg, error) << duplicate_enumerator << sn;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_enumerator + sn));
        }

        auto copy(en);

        /*
         * We try to read the value from the annotations. If its not
         * populated we set it ourselves. Note that it is validation's
         * job to ensure the user doesn't start mixing and matching,
         * populating the value for some enumerators but not others.
         */
        populate_from_annotations(tg, copy);
        if (copy.value().empty())
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

void enumerations_transform::transform(const context& ctx,
    meta_model::endomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Started enumerations transform. Model: "
                             << em.name().id();
    ctx.prober().start_transform(id, em.name().id(), em);

    /*
     * If no enumerations exist, we can just exit. This means we can
     * still support models that have no dependencies, provided they
     * do not use enumerations. Otherwise, we'd fail when searching
     * for the default underlying element name.
     */
    if (em.enumerations().empty()) {
        ctx.prober().end_transform();
        BOOST_LOG_SEV(lg, debug) << "Finished enumerations transform.";
        return;
    }

    const auto l(em.input_language());
    const auto tg(make_type_group(ctx.type_repository()));
    const auto duen(obtain_enumeration_default_underlying_element_name(em));

    for (auto& pair : em.enumerations()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Expanding: " << id;

        auto& e(*pair.second);
        populate_from_annotations(tg.enumeration, e);
        expand_default_underlying_element(duen, e);
        expand_enumerators(tg.enumerator, l, e);
    }

    ctx.prober().end_transform(em);
    BOOST_LOG_SEV(lg, debug) << "Finished enumerations transform.";
}

} } }
