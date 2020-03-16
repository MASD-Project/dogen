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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.logical/types/meta_model/elements_traversal.hpp"
#include "dogen.logical/io/helpers/decomposition_result_io.hpp"
#include "dogen.logical/types/helpers/decomposer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("assets.helpers.decomposer"));

}

namespace dogen::logical::helpers {

void decomposer::add_name(const std::string& owner, const meta_model::name& n) {
    result_.names().push_back(std::make_pair(owner, n));
}

void decomposer::
add_meta_name(const std::string& owner, const meta_model::name& n) {
    result_.meta_names().push_back(std::make_pair(owner, n));
}

void decomposer::
add_name_tree(const std::string& owner, const meta_model::name_tree& nt) {
    result_.name_trees().push_back(std::make_pair(owner, nt));
}

void decomposer::
add_names(const std::string& owner, const std::list<meta_model::name>& names) {
    for (const auto& n : names)
        add_name(owner, n);
}

void decomposer::decompose_attributes(const std::string& owner,
    const std::list<meta_model::attribute>& attrs) {
    for (const auto& attr : attrs) {
        add_name(owner, attr.name());
        add_name_tree(owner, attr.parsed_type());
    }
}

void decomposer::decompose_element(const meta_model::element& e) {
    add_name(e.name().qualified().dot(), e.name());
    add_meta_name(e.name().qualified().dot(), e.meta_name());
}

void decomposer::operator()(const meta_model::element& e) {
    decompose_element(e);
}

void decomposer::operator()(const meta_model::structural::module& m) {
    /*
     * The global module represents the unnamed global
     * namespace. There can only be one of these and it is generated
     * internally by Dogen so there is nothing to validate.
     */
    if (m.is_global_module())
        return;

    decompose_element(m);
}

void decomposer::operator()(const meta_model::structural::object_template& ot) {
    decompose_element(ot);
    decompose_attributes(ot.name().qualified().dot(), ot.local_attributes());
}

void decomposer::operator()(const meta_model::structural::builtin& b) {
    decompose_element(b);
}

void decomposer::operator()(const meta_model::structural::enumeration& e) {
    decompose_element(e);
    for (const auto& en : e.enumerators())
        add_name(e.name().qualified().dot(), en.name());
}

void decomposer::operator()(const meta_model::structural::primitive& p) {
    decompose_element(p);
}

void decomposer::operator()(const meta_model::structural::object& o) {
    decompose_element(o);
    decompose_attributes(o.name().qualified().dot(), o.local_attributes());
}

void decomposer::operator()(const meta_model::structural::exception& e) {
    decompose_element(e);
}

void decomposer::operator()(const meta_model::structural::visitor& v) {
    decompose_element(v);
}

const decomposition_result& decomposer::result() const {
    return result_;
}

decomposition_result
decomposer::decompose(const meta_model::model& em) {
    BOOST_LOG_SEV(lg, debug) << "Decomposing model: "
                             << em.name().qualified().dot();

    decomposer dc;
    meta_model::elements_traversal(em, dc);

    BOOST_LOG_SEV(lg, debug) << "Finished decomposing model. Result: "
                             << dc.result();;
    return dc.result();
}

}
