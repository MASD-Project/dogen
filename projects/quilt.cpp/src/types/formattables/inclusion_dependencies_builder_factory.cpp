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
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_builder_factory.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class factory_impl {
public:
    virtual ~factory_impl() {}

public:
    virtual inclusion_dependencies_builder make() const = 0;
};

class legacy_impl final : public factory_impl {
public:
    legacy_impl(const enablement_repository& erp,
        const inclusion_directives_repository& idrp);

public:
    inclusion_dependencies_builder make() const;

private:
    const enablement_repository& enablement_repository_;
    const inclusion_directives_repository& directives_repository_;
};

legacy_impl::legacy_impl(const enablement_repository& erp,
    const inclusion_directives_repository& idrp)
    : enablement_repository_(erp), directives_repository_(idrp) {}

inclusion_dependencies_builder legacy_impl::make() const {
    return inclusion_dependencies_builder(
        enablement_repository_, directives_repository_);
}

class new_impl final : public factory_impl {
public:
    new_impl(const std::unordered_map<
        std::string,
        std::unordered_map<std::string, std::string>
        >& inclusion_directives,
        const std::unordered_map<std::string, formattable>& formattables);

public:
    inclusion_dependencies_builder make() const;

private:
    const std::unordered_map<
    std::string,
    std::unordered_map<std::string, std::string>
    >& inclusion_directives_;
    const std::unordered_map<std::string, formattable>& formattables_;
};

new_impl::new_impl(const std::unordered_map<
    std::string,
    std::unordered_map<std::string, std::string>
    >& inclusion_directives,
    const std::unordered_map<std::string, formattable>& formattables) :
    inclusion_directives_(inclusion_directives),
    formattables_(formattables) {}

inclusion_dependencies_builder new_impl::make() const {
    return inclusion_dependencies_builder(inclusion_directives_, formattables_);
}

inclusion_dependencies_builder_factory::inclusion_dependencies_builder_factory(
    const enablement_repository& erp,
    const inclusion_directives_repository& idrp)
    : impl_(new legacy_impl(erp, idrp)) {}

inclusion_dependencies_builder_factory::inclusion_dependencies_builder_factory(
    const std::unordered_map<std::string,
    std::unordered_map<std::string, std::string>
    >& inclusion_directives,
    const std::unordered_map<std::string, formattable>& formattables)
    : impl_(new new_impl(inclusion_directives, formattables)) {}

inclusion_dependencies_builder inclusion_dependencies_builder_factory::
make() const {
    return impl_->make();
}

} } } }
