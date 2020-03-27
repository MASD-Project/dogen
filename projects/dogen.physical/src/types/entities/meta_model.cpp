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
#include "dogen.physical/types/entities/meta_model.hpp"

namespace dogen::physical::entities {

meta_model::meta_model(
    const std::unordered_map<std::string, dogen::physical::entities::kernel>& kernels,
    const std::unordered_map<std::string, dogen::physical::entities::enablement_flags>& enablement_flags,
    const std::unordered_map<std::string, std::vector<std::string> >& template_instantiation_domains)
    : kernels_(kernels),
      enablement_flags_(enablement_flags),
      template_instantiation_domains_(template_instantiation_domains) { }

void meta_model::swap(meta_model& other) noexcept {
    using std::swap;
    swap(kernels_, other.kernels_);
    swap(enablement_flags_, other.enablement_flags_);
    swap(template_instantiation_domains_, other.template_instantiation_domains_);
}

bool meta_model::operator==(const meta_model& rhs) const {
    return kernels_ == rhs.kernels_ &&
        enablement_flags_ == rhs.enablement_flags_ &&
        template_instantiation_domains_ == rhs.template_instantiation_domains_;
}

meta_model& meta_model::operator=(meta_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::physical::entities::kernel>& meta_model::kernels() const {
    return kernels_;
}

std::unordered_map<std::string, dogen::physical::entities::kernel>& meta_model::kernels() {
    return kernels_;
}

void meta_model::kernels(const std::unordered_map<std::string, dogen::physical::entities::kernel>& v) {
    kernels_ = v;
}

void meta_model::kernels(const std::unordered_map<std::string, dogen::physical::entities::kernel>&& v) {
    kernels_ = std::move(v);
}

const std::unordered_map<std::string, dogen::physical::entities::enablement_flags>& meta_model::enablement_flags() const {
    return enablement_flags_;
}

std::unordered_map<std::string, dogen::physical::entities::enablement_flags>& meta_model::enablement_flags() {
    return enablement_flags_;
}

void meta_model::enablement_flags(const std::unordered_map<std::string, dogen::physical::entities::enablement_flags>& v) {
    enablement_flags_ = v;
}

void meta_model::enablement_flags(const std::unordered_map<std::string, dogen::physical::entities::enablement_flags>&& v) {
    enablement_flags_ = std::move(v);
}

const std::unordered_map<std::string, std::vector<std::string> >& meta_model::template_instantiation_domains() const {
    return template_instantiation_domains_;
}

std::unordered_map<std::string, std::vector<std::string> >& meta_model::template_instantiation_domains() {
    return template_instantiation_domains_;
}

void meta_model::template_instantiation_domains(const std::unordered_map<std::string, std::vector<std::string> >& v) {
    template_instantiation_domains_ = v;
}

void meta_model::template_instantiation_domains(const std::unordered_map<std::string, std::vector<std::string> >&& v) {
    template_instantiation_domains_ = std::move(v);
}

}
