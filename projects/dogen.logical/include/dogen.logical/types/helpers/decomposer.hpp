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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_DECOMPOSER_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_DECOMPOSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/object_template.hpp"
#include "dogen.logical/types/helpers/decomposition_result.hpp"

namespace dogen::logical::helpers {

/**
 * @brief Collect the names of all elements and attributes, for
 * subsequent validation.
 *
 * Note that we do not add the model name itself; this is because we
 * will validate the model's module, which is generated from the model
 * name.
 */
class decomposer final {
private:
    void add_name(const std::string& owner, const entities::name& n);
    void add_meta_name(const std::string& owner, const entities::name& n);
    void add_name_tree(const std::string& owner,
        const entities::name_tree& nt);
    void add_names(const std::string& owner,
        const std::list<entities::name>& names);
    void decompose_attributes(const std::string& owner,
        const std::list<entities::attribute>& attrs);
    void decompose_element(const entities::element& e);

public:
    /*
     * These methods are morally private, but are required to be
     * public due to the traversal.
     */
    void operator()(const entities::element& e);
    void operator()(const entities::structural::module& m);
    void operator()(const entities::structural::object_template& ot);
    void operator()(const entities::structural::builtin& b);
    void operator()(const entities::structural::enumeration& e);
    void operator()(const entities::structural::primitive& p);
    void operator()(const entities::structural::object& o);
    void operator()(const entities::structural::exception& e);
    void operator()(const entities::structural::visitor& v);

private:
    const decomposition_result& result() const;

public:
    static decomposition_result
    decompose(const entities::model& em);

private:
    decomposition_result result_;
};

}

#endif
