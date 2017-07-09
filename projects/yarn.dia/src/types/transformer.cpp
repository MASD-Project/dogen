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
#include <boost/make_shared.hpp>
#include <boost/variant/get.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
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

const std::string enumerator_with_type("Enumerators cannot have a type: ");
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
    yarn::helpers::name_factory f;
    return f.build_element_in_model(repository_.model().name(), n);
}

yarn::name transformer::
to_name(const std::string& n, const yarn::name& module_n) const {
    validate_dia_object_name(n);
    yarn::helpers::name_factory f;
    return f.build_element_in_module(module_n, n);
}

yarn::attribute transformer::to_attribute(const processed_attribute& a) const {
    validate_dia_object_name(a.name());

    yarn::attribute r;
    r.name().simple(a.name());
    r.unparsed_type(a.type());
    r.documentation(a.comment().documentation());
    return r;
}

yarn::enumerator
transformer::to_enumerator(const processed_attribute& a) const {
    validate_dia_object_name(a.name());

    if (!a.type().empty()) {
        BOOST_LOG_SEV(lg, error) << enumerator_with_type << a.type();
        BOOST_THROW_EXCEPTION(transformation_error(
                enumerator_with_type + a.type()));
    }

    yarn::enumerator r;
    r.name().simple(a.name());
    r.documentation(a.comment().documentation());
    return r;
}

void transformer::
update_element(const processed_object& po, yarn::element& e) const {
    e.origin_type(origin_types::not_yet_determined);

    const auto package_id(po.child_node_id());
    bool is_in_package(!package_id.empty());
    if (is_in_package) {
        /*
         * Create the element name taking into account the
         * packages the element is contained in.
         */
        const_repository_selector crs(repository_);
        const auto& module(crs.module_for_id(package_id));
        e.name(to_name(po.name(), module.name()));
    } else {
        /*
         * Type is a top-level type - e.g. belongs to the
         * synthetic module for the model; do not add this
         * dependency to the name.
         */
        e.name(to_name(po.name()));
    }

    e.documentation(po.comment().documentation());

    e.stereotypes().reserve(po.stereotypes().size());
    for (const auto us : po.stereotypes())
        e.stereotypes().push_back(us);
}

yarn::object transformer::to_object(const processed_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to object: "
                             << po.id();

    yarn::object r;
    update_element(po, r);

    for (const auto& p : po.attributes())
        r.local_attributes().push_back(to_attribute(p));

    /*
     * If we have any parents, setup generalisation properties.
     */
    const_repository_selector crs(repository_);
    const auto parent_names(crs.parent_names_for_id(po.id()));
    if (!parent_names.empty()) {
        for (const auto& pn : parent_names) {
            r.parents().push_back(pn);

            BOOST_LOG_SEV(lg, debug) << "Added parent. Child: " << r.name().id()
                                     << " parent: " << pn.id();
        }
    } else
        BOOST_LOG_SEV(lg, debug) << "Object has no parent: " << r.name().id();

    return r;
}

yarn::exception transformer::to_exception(const processed_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to exception: "
                             << po.id();

    yarn::exception e;
    update_element(po, e);
    return e;
}

yarn::enumeration
transformer::to_enumeration(const processed_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to enumeration: "
                             << po.id();

    yarn::enumeration r;
    update_element(po, r);

    for (const auto& attr : po.attributes())
        r.enumerators().push_back(to_enumerator(attr));

    return r;
}

yarn::primitive
transformer::to_primitive(const processed_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to primitive: "
                             << po.id();

    yarn::primitive r;
    update_element(po, r);
    return r;
}

yarn::module transformer::to_module(const processed_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to module: "
                             << po.id();

    yarn::module r;
    update_element(po, r);
    return r;
}

yarn::concept transformer::to_concept(const processed_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to concept: "
                             << po.id();

    yarn::concept r;
    update_element(po, r);

    for (const auto& attr : po.attributes())
        r.local_attributes().push_back(to_attribute(attr));

    const_repository_selector crs(repository_);
    const auto parent_names(crs.parent_names_for_id(po.id()));
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
