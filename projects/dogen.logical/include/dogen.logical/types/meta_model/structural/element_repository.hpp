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
#ifndef DOGEN_LOGICAL_TYPES_META_MODEL_STRUCTURAL_ELEMENT_REPOSITORY_HPP
#define DOGEN_LOGICAL_TYPES_META_MODEL_STRUCTURAL_ELEMENT_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/meta_model/structural/module_fwd.hpp"
#include "dogen.logical/types/meta_model/structural/object_fwd.hpp"
#include "dogen.logical/types/meta_model/structural/builtin_fwd.hpp"
#include "dogen.logical/types/meta_model/structural/visitor_fwd.hpp"
#include "dogen.logical/types/meta_model/structural/assistant_fwd.hpp"
#include "dogen.logical/types/meta_model/structural/exception_fwd.hpp"
#include "dogen.logical/types/meta_model/structural/primitive_fwd.hpp"
#include "dogen.logical/types/meta_model/structural/entry_point_fwd.hpp"
#include "dogen.logical/types/meta_model/structural/enumeration_fwd.hpp"
#include "dogen.logical/types/meta_model/structural/object_template_fwd.hpp"

namespace dogen::logical::meta_model::structural {

class element_repository final {
public:
    element_repository() = default;
    element_repository(const element_repository&) = default;
    element_repository(element_repository&&) = default;
    ~element_repository() = default;

public:
    element_repository(
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::module> >& modules,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::object_template> >& object_templates,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::builtin> >& builtins,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::enumeration> >& enumerations,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::primitive> >& primitives,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::object> >& objects,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::exception> >& exceptions,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::visitor> >& visitors,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::entry_point> >& entry_points,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::assistant> >& assistants);

public:
    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::module> >& modules() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::module> >& modules();
    void modules(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::module> >& v);
    void modules(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::module> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::object_template> >& object_templates() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::object_template> >& object_templates();
    void object_templates(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::object_template> >& v);
    void object_templates(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::object_template> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::builtin> >& builtins() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::builtin> >& builtins();
    void builtins(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::builtin> >& v);
    void builtins(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::builtin> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::enumeration> >& enumerations() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::enumeration> >& enumerations();
    void enumerations(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::enumeration> >& v);
    void enumerations(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::enumeration> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::primitive> >& primitives() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::primitive> >& primitives();
    void primitives(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::primitive> >& v);
    void primitives(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::primitive> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::object> >& objects() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::object> >& objects();
    void objects(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::object> >& v);
    void objects(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::object> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::exception> >& exceptions() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::exception> >& exceptions();
    void exceptions(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::exception> >& v);
    void exceptions(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::exception> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::visitor> >& visitors() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::visitor> >& visitors();
    void visitors(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::visitor> >& v);
    void visitors(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::visitor> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::entry_point> >& entry_points() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::entry_point> >& entry_points();
    void entry_points(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::entry_point> >& v);
    void entry_points(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::entry_point> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::assistant> >& assistants() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::assistant> >& assistants();
    void assistants(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::assistant> >& v);
    void assistants(const std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::assistant> >&& v);

public:
    bool operator==(const element_repository& rhs) const;
    bool operator!=(const element_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_repository& other) noexcept;
    element_repository& operator=(element_repository other);

private:
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::module> > modules_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::object_template> > object_templates_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::builtin> > builtins_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::enumeration> > enumerations_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::primitive> > primitives_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::object> > objects_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::exception> > exceptions_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::visitor> > visitors_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::entry_point> > entry_points_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::logical::meta_model::structural::assistant> > assistants_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::meta_model::structural::element_repository& lhs,
    dogen::logical::meta_model::structural::element_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
