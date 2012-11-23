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
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_FILE_VIEW_MODEL_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_VIEW_MODELS_FILE_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/meta_types.hpp"
#include "dogen/sml/types/category_types.hpp"
#include "dogen/generator/backends/cpp/view_models/exception_view_model.hpp"
#include "dogen/generator/backends/cpp/view_models/enumeration_view_model.hpp"
#include "dogen/generator/backends/cpp/view_models/class_view_model.hpp"
#include "dogen/generator/backends/cpp/view_models/registrar_view_model.hpp"
#include "dogen/generator/backends/cpp/cpp_facet_types.hpp"
#include "dogen/generator/backends/cpp/cpp_file_types.hpp"
#include "dogen/generator/backends/cpp/cpp_aspect_types.hpp"
#include "dogen/generator/backends/cpp/cpp_aspect_types.hpp"

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace view_models {

class file_view_model {
public:
    file_view_model(const file_view_model&) = default;
    ~file_view_model() = default;
    file_view_model& operator=(const file_view_model&) = default;

public:
    file_view_model() :
        facet_type_(cpp_facet_types::invalid),
        file_type_(cpp_file_types::invalid),
        aspect_type_(cpp_aspect_types::invalid),
        category_type_(sml::category_types::invalid) { }

    file_view_model(file_view_model&& o) :
    facet_type_(std::move(o.facet_type_)),
    file_type_(std::move(o.file_type_)),
    aspect_type_(std::move(o.aspect_type_)),
    category_type_(std::move(o.category_type_)),
    meta_type_(std::move(o.meta_type_)),
    class_vm_(std::move(o.class_vm_)),
    enumeration_vm_(std::move(o.enumeration_vm_)),
    exception_vm_(std::move(o.exception_vm_)),
    registrar_vm_(std::move(o.registrar_vm_)),
    header_guard_(std::move(o.header_guard_)),
    system_includes_(std::move(o.system_includes_)),
    user_includes_(std::move(o.user_includes_)),
    file_path_(std::move(o.file_path_)) {}

public:
    void facet_type(cpp_facet_types value) { facet_type_ = value; }
    cpp_facet_types facet_type() const { return facet_type_; }

    void file_type(cpp_file_types value) { file_type_ = value; }
    cpp_file_types file_type() const { return file_type_; }

    void aspect_type(cpp_aspect_types value) { aspect_type_ = value; }
    cpp_aspect_types aspect_type() const { return aspect_type_; }

    void category_type(sml::category_types value) { category_type_ = value; }
    sml::category_types category_type() const { return category_type_; }

    void meta_type(sml::meta_types value) { meta_type_ = value; }
    sml::meta_types meta_type() const { return meta_type_; }

    void class_vm(boost::optional<class_view_model> value) {
        class_vm_ = value;
    }
    boost::optional<class_view_model> class_vm() const { return class_vm_; }

    void enumeration_vm(boost::optional<enumeration_view_model> value) {
        enumeration_vm_ = value;
    }
    boost::optional<enumeration_view_model> enumeration_vm() const {
        return enumeration_vm_;
    }

    void exception_vm(boost::optional<exception_view_model> value) {
        exception_vm_ = value;
    }
    boost::optional<exception_view_model> exception_vm() const {
        return exception_vm_;
    }

    void registrar_vm(boost::optional<registrar_view_model> value) {
        registrar_vm_ = value;
    }
    boost::optional<registrar_view_model> registrar_vm() const {
        return registrar_vm_;
    }

    void header_guard(std::string value) { header_guard_ = value; }
    std::string header_guard() const { return header_guard_; }

    void system_includes(std::list<std::string> value) {
        system_includes_ = value;
    }
    std::list<std::string> system_includes() const {
        return system_includes_;
    }

    void user_includes(std::list<std::string> value) {
        user_includes_ = value;
    }
    std::list<std::string> user_includes() const {
        return user_includes_;
    }

    void file_path(boost::filesystem::path value) { file_path_ = value; }
    boost::filesystem::path file_path() const { return file_path_; }

private:
    cpp_facet_types facet_type_;
    cpp_file_types file_type_;
    cpp_aspect_types aspect_type_;
    sml::category_types category_type_;
    sml::meta_types meta_type_;
    boost::optional<class_view_model> class_vm_;
    boost::optional<enumeration_view_model> enumeration_vm_;
    boost::optional<exception_view_model> exception_vm_;
    boost::optional<registrar_view_model> registrar_vm_;
    std::string header_guard_;
    std::list<std::string> system_includes_;
    std::list<std::string> user_includes_;
    boost::filesystem::path file_path_;
};

} } } } }

#endif
