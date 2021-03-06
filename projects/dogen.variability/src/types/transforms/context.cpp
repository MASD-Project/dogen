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
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.variability/types/transforms/context.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::tracing::tracer>& lhs,
const boost::shared_ptr<dogen::tracing::tracer>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::variability::transforms {

context::context()
    : compatibility_mode_(static_cast<bool>(0)) { }

context::context(
    const bool compatibility_mode,
    const std::unordered_map<std::string, std::vector<std::string> >& template_instantiation_domains,
    const boost::shared_ptr<dogen::tracing::tracer>& tracer)
    : compatibility_mode_(compatibility_mode),
      template_instantiation_domains_(template_instantiation_domains),
      tracer_(tracer) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(compatibility_mode_, other.compatibility_mode_);
    swap(template_instantiation_domains_, other.template_instantiation_domains_);
    swap(tracer_, other.tracer_);
}

bool context::operator==(const context& rhs) const {
    return compatibility_mode_ == rhs.compatibility_mode_ &&
        template_instantiation_domains_ == rhs.template_instantiation_domains_ &&
        tracer_ == rhs.tracer_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool context::compatibility_mode() const {
    return compatibility_mode_;
}

void context::compatibility_mode(const bool v) {
    compatibility_mode_ = v;
}

const std::unordered_map<std::string, std::vector<std::string> >& context::template_instantiation_domains() const {
    return template_instantiation_domains_;
}

std::unordered_map<std::string, std::vector<std::string> >& context::template_instantiation_domains() {
    return template_instantiation_domains_;
}

void context::template_instantiation_domains(const std::unordered_map<std::string, std::vector<std::string> >& v) {
    template_instantiation_domains_ = v;
}

void context::template_instantiation_domains(const std::unordered_map<std::string, std::vector<std::string> >&& v) {
    template_instantiation_domains_ = std::move(v);
}

const boost::shared_ptr<dogen::tracing::tracer>& context::tracer() const {
    return tracer_;
}

boost::shared_ptr<dogen::tracing::tracer>& context::tracer() {
    return tracer_;
}

void context::tracer(const boost::shared_ptr<dogen::tracing::tracer>& v) {
    tracer_ = v;
}

void context::tracer(const boost::shared_ptr<dogen::tracing::tracer>&& v) {
    tracer_ = std::move(v);
}

}
