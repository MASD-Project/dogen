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
#ifndef DOGEN_CPP_TYPES_FORMATTER_DISPATCHER_HPP
#define DOGEN_CPP_TYPES_FORMATTER_DISPATCHER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen/cpp/types/registrar.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/cpp/types/entity_visitor.hpp"
#include "dogen/cpp/types/settings_bundle.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Responsible for disp
 */

class formatter_dispatcher : public entity_visitor {
public:
    formatter_dispatcher(const registrar& r, const settings_bundle& s);

public:
    void visit(const dogen::cpp::class_info& c) override;
    void visit(const dogen::cpp::enum_info& e) override;
    void visit(const dogen::cpp::exception_info& e) override;
    void visit(const dogen::cpp::registrar_info& r) override;
    void visit(const dogen::cpp::namespace_info& n) override;
    void visit(const dogen::cpp::visitor_info& v) override;
    void visit(const dogen::cpp::new_class_info& c) override;
    void visit(const dogen::cpp::concept_info& c) override;
    void visit(const dogen::cpp::primitive_info& p) override;

public:
    /**
     * @brief Converts the supplied entity into all supported
     * representations.
     */
    std::list<dogen::formatters::file> format(const entity& e);

private:
    const registrar& registrar_;
    const settings_bundle settings_bundle_;
    std::list<dogen::formatters::file> files_;
};

} }

#endif
