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
#include "dogen/yarn.dia/types/context.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::meta_model::module>& lhs,
const boost::shared_ptr<dogen::yarn::meta_model::module>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace yarn {
namespace dia {

context::context(
    const std::unordered_map<std::string, std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >& dia_id_to_module,
    const std::unordered_map<std::string, std::list<dogen::yarn::meta_model::name> >& child_dia_id_to_parent_names)
    : dia_id_to_module_(dia_id_to_module),
      child_dia_id_to_parent_names_(child_dia_id_to_parent_names) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(dia_id_to_module_, other.dia_id_to_module_);
    swap(child_dia_id_to_parent_names_, other.child_dia_id_to_parent_names_);
}

bool context::operator==(const context& rhs) const {
    return dia_id_to_module_ == rhs.dia_id_to_module_ &&
        child_dia_id_to_parent_names_ == rhs.child_dia_id_to_parent_names_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >& context::dia_id_to_module() const {
    return dia_id_to_module_;
}

std::unordered_map<std::string, std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >& context::dia_id_to_module() {
    return dia_id_to_module_;
}

void context::dia_id_to_module(const std::unordered_map<std::string, std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >& v) {
    dia_id_to_module_ = v;
}

void context::dia_id_to_module(const std::unordered_map<std::string, std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >&& v) {
    dia_id_to_module_ = std::move(v);
}

const std::unordered_map<std::string, std::list<dogen::yarn::meta_model::name> >& context::child_dia_id_to_parent_names() const {
    return child_dia_id_to_parent_names_;
}

std::unordered_map<std::string, std::list<dogen::yarn::meta_model::name> >& context::child_dia_id_to_parent_names() {
    return child_dia_id_to_parent_names_;
}

void context::child_dia_id_to_parent_names(const std::unordered_map<std::string, std::list<dogen::yarn::meta_model::name> >& v) {
    child_dia_id_to_parent_names_ = v;
}

void context::child_dia_id_to_parent_names(const std::unordered_map<std::string, std::list<dogen::yarn::meta_model::name> >&& v) {
    child_dia_id_to_parent_names_ = std::move(v);
}

} } }
