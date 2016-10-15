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
#include <boost/make_shared.hpp>
#include <boost/variant/get.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/dia/types/composite.hpp"
#include "dogen/yarn.dia/types/transformation_error.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/io/processed_object_io.hpp"
#include "dogen/yarn.dia/io/repository_io.hpp"
#include "dogen/yarn.dia/types/validator.hpp"
#include "dogen/yarn.dia/types/repository_selector.hpp"
#include "dogen/yarn.dia/types/transformer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.transformer"));

const std::string duplicate_enumerator("Duplicate enumerator name: ");
const std::string empty_dia_object_name("Dia object name is empty");
const std::string multiple_inheritance(
    "Child has more than one parent, but multiple inheritance not supported:");

}

namespace dogen {
namespace yarn {
namespace dia {

transformer::transformer(const repository& rp) : repository_(rp) {
    BOOST_LOG_SEV(lg, debug) << "Initial repository: " << repository_;
}

void transformer::validate_dia_object_name(const std::string& n) const {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }
}

yarn::name transformer::to_name(const std::string& n) const {
    validate_dia_object_name(n);
    yarn::name_factory f;
    return f.build_element_in_model(repository_.model().name(), n);
}

yarn::name transformer::
to_name(const std::string& n, const yarn::name& module_n) const {
    validate_dia_object_name(n);
    yarn::name_factory f;
    return f.build_element_in_module(module_n, n);
}

yarn::attribute transformer::to_attribute(const yarn::name& owning_element,
    const processed_attribute& a) const {
    validate_dia_object_name(a.name());

    yarn::name_factory f;
    const auto n(f.build_attribute_name(owning_element, a.name()));

    yarn::attribute r;
    r.name(n);
    r.unparsed_type(a.type());
    r.documentation(a.comment().documentation());
    return r;
}

yarn::enumerator transformer::to_enumerator(const processed_attribute& a,
    const unsigned int position) const {
    validate_dia_object_name(a.name());

    yarn::enumerator r;
    r.name(a.name());
    r.value(boost::lexical_cast<std::string>(position));
    r.documentation(a.comment().documentation());
    return r;
}

void transformer::
update_element(const profiled_object& po, yarn::element& e) const {
    e.origin_type(origin_types::not_yet_determined);

    const auto package_id(po.object().child_node_id());
    bool is_in_package(!package_id.empty());
    if (is_in_package) {
        /*
         * Create the element name taking into account the
         * packages the element is contained in.
         */
        const_repository_selector crs(repository_);
        const auto& module(crs.module_for_id(package_id));
        e.name(to_name(po.object().name(), module.name()));
    } else {
        /*
         * Type is a top-level type - e.g. belongs to the
         * synthetic module for the model; do not add this
         * dependency to the name.
         */
        e.name(to_name(po.object().name()));
    }

    e.documentation(po.object().comment().documentation());
}

yarn::object transformer::to_object(const profiled_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to object: "
                             << po.object().id();

    yarn::object r;
    update_element(po, r);

    r.stereotypes().reserve(po.profile().unknown_stereotypes().size());
    for (const auto us : po.profile().unknown_stereotypes())
        r.stereotypes().push_back(us);

    for (const auto& p : po.object().attributes())
        r.local_attributes().push_back(to_attribute(r.name(), p));

    /*
     * If we have any parents, setup generalisation properties.
     */
    const_repository_selector crs(repository_);
    const auto parent_names(crs.parent_names_for_id(po.object().id()));
    if (!parent_names.empty()) {
        /*
         * Ensure we have at most one parent as we do not support
         * multiple inheritance for objects.
         */
        if (parent_names.size() > 1) {
            BOOST_LOG_SEV(lg, error) << multiple_inheritance
                                     << po.object().id();
            BOOST_THROW_EXCEPTION(transformation_error(multiple_inheritance +
                    po.object().id()));
        }

        const auto parent_name(parent_names.front());
        r.parent(parent_name);
        BOOST_LOG_SEV(lg, debug) << "Set parent. Child: " << r.name().id()
                                 << " parent: " << parent_name.id();
    } else
        BOOST_LOG_SEV(lg, debug) << "Object has no parent: " << r.name().id();

    return r;
}

yarn::exception transformer::to_exception(const profiled_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to exception: "
                             << po.object().id();

    yarn::exception e;
    update_element(po, e);
    return e;
}

yarn::enumeration transformer::to_enumeration(const profiled_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to enumeration: "
                             << po.object().id();

    yarn::enumeration r;
    update_element(po, r);

    /*
     * Setup the invalid enumeration.
     */
    dogen::yarn::enumerator invalid;
    invalid.name("invalid");
    invalid.documentation("Represents an uninitialised enum");
    invalid.value("0");
    r.enumerators().push_back(invalid);

    std::set<std::string> enumerator_names;
    enumerator_names.insert(invalid.name());

    /*
     * Convert each attribute into an enumerator, ensuring the
     * enumerator names is unique within this enumeration. For each
     * enumerator we compute a position. Note that the zeroth position
     * is already taken by invalid, so we skip it.
     */
    unsigned int pos(0);
    for (const auto& attr : po.object().attributes()) {
        auto enumerator(to_enumerator(attr, ++pos));
        const auto i(enumerator_names.find(enumerator.name()));
        if (i != enumerator_names.end()) {
            BOOST_LOG_SEV(lg, error) << duplicate_enumerator
                                     << enumerator.name();
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_enumerator + enumerator.name()));
        }
        enumerator_names.insert(enumerator.name());
        r.enumerators().push_back(enumerator);
    }
    return r;
}

yarn::module transformer::to_module(const profiled_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to module: "
                             << po.object().id();

    yarn::module r;
    update_element(po, r);
    return r;
}

yarn::concept transformer::to_concept(const profiled_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to concept: "
                             << po.object().id();

    yarn::concept r;
    update_element(po, r);

    for (const auto& attr : po.object().attributes())
        r.local_attributes().push_back(to_attribute(r.name(), attr));

    const_repository_selector crs(repository_);
    const auto parent_names(crs.parent_names_for_id(po.object().id()));
    r.is_child(!parent_names.empty());

    if (parent_names.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Object has no parent: " << r.name().id();
        return r;
    }

    for (const auto parent_name : parent_names)
        r.refines().push_back(parent_name);
    return r;
}

} } }
