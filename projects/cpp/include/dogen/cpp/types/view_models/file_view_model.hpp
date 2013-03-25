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
#ifndef DOGEN_CPP_TYPES_VIEW_MODELS_FILE_VIEW_MODEL_HPP
#define DOGEN_CPP_TYPES_VIEW_MODELS_FILE_VIEW_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>
#include <list>
#include <string>
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/cpp/serialization/view_models/file_view_model_fwd_ser.hpp"
#include "dogen/cpp/types/cpp_aspect_types.hpp"
#include "dogen/cpp/types/file_types.hpp"
#include "dogen/cpp/types/view_models/class_view_model.hpp"
#include "dogen/cpp/types/view_models/enumeration_view_model.hpp"
#include "dogen/cpp/types/view_models/exception_view_model.hpp"
#include "dogen/cpp/types/view_models/registrar_view_model.hpp"
#include "dogen/sml/types/category_types.hpp"
#include "dogen/sml/types/meta_types.hpp"

namespace dogen {
namespace cpp {
namespace view_models {

class file_view_model final {
public:
    file_view_model(const file_view_model&) = default;
    ~file_view_model() = default;

public:
    file_view_model();

public:
    file_view_model(file_view_model&& rhs);

public:
    file_view_model(
        const dogen::config::cpp_facet_types& facet_type,
        const dogen::cpp::file_types& file_type,
        const dogen::cpp::cpp_aspect_types& aspect_type,
        const dogen::sml::category_types& category_type,
        const dogen::sml::meta_types& meta_type,
        const boost::optional<dogen::cpp::view_models::class_view_model>& class_vm,
        const boost::optional<dogen::cpp::view_models::enumeration_view_model>& enumeration_vm,
        const boost::optional<dogen::cpp::view_models::exception_view_model>& exception_vm,
        const boost::optional<dogen::cpp::view_models::registrar_view_model>& registrar_vm,
        const std::string& header_guard,
        const std::list<std::string>& system_includes,
        const std::list<std::string>& user_includes,
        const boost::filesystem::path& file_path);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const file_view_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, file_view_model& v, unsigned int version);

public:
    dogen::config::cpp_facet_types facet_type() const;
    void facet_type(const dogen::config::cpp_facet_types& v);

    dogen::cpp::file_types file_type() const;
    void file_type(const dogen::cpp::file_types& v);

    dogen::cpp::cpp_aspect_types aspect_type() const;
    void aspect_type(const dogen::cpp::cpp_aspect_types& v);

    dogen::sml::category_types category_type() const;
    void category_type(const dogen::sml::category_types& v);

    dogen::sml::meta_types meta_type() const;
    void meta_type(const dogen::sml::meta_types& v);

    const boost::optional<dogen::cpp::view_models::class_view_model>& class_vm() const;
    boost::optional<dogen::cpp::view_models::class_view_model>& class_vm();
    void class_vm(const boost::optional<dogen::cpp::view_models::class_view_model>& v);
    void class_vm(const boost::optional<dogen::cpp::view_models::class_view_model>&& v);

    const boost::optional<dogen::cpp::view_models::enumeration_view_model>& enumeration_vm() const;
    boost::optional<dogen::cpp::view_models::enumeration_view_model>& enumeration_vm();
    void enumeration_vm(const boost::optional<dogen::cpp::view_models::enumeration_view_model>& v);
    void enumeration_vm(const boost::optional<dogen::cpp::view_models::enumeration_view_model>&& v);

    const boost::optional<dogen::cpp::view_models::exception_view_model>& exception_vm() const;
    boost::optional<dogen::cpp::view_models::exception_view_model>& exception_vm();
    void exception_vm(const boost::optional<dogen::cpp::view_models::exception_view_model>& v);
    void exception_vm(const boost::optional<dogen::cpp::view_models::exception_view_model>&& v);

    const boost::optional<dogen::cpp::view_models::registrar_view_model>& registrar_vm() const;
    boost::optional<dogen::cpp::view_models::registrar_view_model>& registrar_vm();
    void registrar_vm(const boost::optional<dogen::cpp::view_models::registrar_view_model>& v);
    void registrar_vm(const boost::optional<dogen::cpp::view_models::registrar_view_model>&& v);

    const std::string& header_guard() const;
    std::string& header_guard();
    void header_guard(const std::string& v);
    void header_guard(const std::string&& v);

    const std::list<std::string>& system_includes() const;
    std::list<std::string>& system_includes();
    void system_includes(const std::list<std::string>& v);
    void system_includes(const std::list<std::string>&& v);

    const std::list<std::string>& user_includes() const;
    std::list<std::string>& user_includes();
    void user_includes(const std::list<std::string>& v);
    void user_includes(const std::list<std::string>&& v);

    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);

public:
    bool operator==(const file_view_model& rhs) const;
    bool operator!=(const file_view_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(file_view_model& other) noexcept;
    file_view_model& operator=(file_view_model other);

private:
    dogen::config::cpp_facet_types facet_type_;
    dogen::cpp::file_types file_type_;
    dogen::cpp::cpp_aspect_types aspect_type_;
    dogen::sml::category_types category_type_;
    dogen::sml::meta_types meta_type_;
    boost::optional<dogen::cpp::view_models::class_view_model> class_vm_;
    boost::optional<dogen::cpp::view_models::enumeration_view_model> enumeration_vm_;
    boost::optional<dogen::cpp::view_models::exception_view_model> exception_vm_;
    boost::optional<dogen::cpp::view_models::registrar_view_model> registrar_vm_;
    std::string header_guard_;
    std::list<std::string> system_includes_;
    std::list<std::string> user_includes_;
    boost::filesystem::path file_path_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::view_models::file_view_model& lhs,
    dogen::cpp::view_models::file_view_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
