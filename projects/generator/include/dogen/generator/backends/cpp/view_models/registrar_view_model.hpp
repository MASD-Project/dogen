/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_REGISTRAR_VIEW_MODEL_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_REGISTRAR_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace view_models {

class registrar_view_model {
public:
    registrar_view_model() = default;
    registrar_view_model(const registrar_view_model&) = default;
    ~registrar_view_model() = default;
    registrar_view_model(registrar_view_model&&) = default;
    registrar_view_model& operator=(const registrar_view_model&) = default;

public:
    registrar_view_model(const std::list<std::string>& namespaces,
        const std::list<std::string>& leaves) :
        namespaces_(namespaces), leaves_(leaves) { }

public:
    std::list<std::string> namespaces() const { return(namespaces_); }
    void namespaces(const std::list<std::string>& v) { namespaces_ = v; }

    std::list<std::string> leaves() const { return(leaves_); }
    void leaves(const std::list<std::string>& v) { leaves_ = v; }

    std::list<std::string> model_dependencies() const {
        return(model_dependencies_);
    }
    void model_dependencies(const std::list<std::string>& v) {
        model_dependencies_ = v;
    }

private:
    std::list<std::string> namespaces_;
    std::list<std::string> leaves_;
    std::list<std::string> model_dependencies_;
};

} } } } }

#endif
