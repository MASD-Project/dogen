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
#include "dogen/cpp/types/formattables/entity_visitor.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Responsible for dispatching the entity to the appropriate
 * formatters.
 */
class dispatcher : public formattables::entity_visitor {
public:
    dispatcher(const container& c, const settings::settings& s);
    ~dispatcher() noexcept { }

public:
    using entity_visitor::visit;
    void visit(const formattables::class_info& c) override;
    void visit(const formattables::enum_info& e) override;
    void visit(const formattables::exception_info& e) override;
    void visit(const formattables::registrar_info& r) override;
    void visit(const formattables::namespace_info& n) override;
    void visit(const formattables::visitor_info& v) override;
    void visit(const formattables::new_class_info& c) override;
    void visit(const formattables::concept_info& c) override;
    void visit(const formattables::primitive_info& p) override;

public:
    /**
     * @brief Converts the supplied entity into all supported
     * representations.
     */
    std::forward_list<dogen::formatters::file>
    format(const formattables::entity& e);

private:
    const container& container_;
    const settings::settings& settings_;
    std::forward_list<dogen::formatters::file> files_;
};

dispatcher::dispatcher(const container& c, const settings::settings& s)
    : container_(c), settings_(s) { }

void dispatcher::visit(const formattables::class_info& c) {
    for (const auto f : container_.class_formatters())
        files_.push_front(f->format(settings_, c));
}

void dispatcher::visit(const formattables::enum_info& /*e*/) {
}

void dispatcher::visit(const formattables::exception_info& /*e*/) {
}

void dispatcher::visit(const formattables::registrar_info& /*r*/) {
}

void dispatcher::visit(const formattables::namespace_info& /*n*/) {
}

void dispatcher::visit(const formattables::visitor_info& /*v*/) {
}

void dispatcher::visit(const formattables::new_class_info& /*c*/) {
}

void dispatcher::visit(const formattables::concept_info& /*c*/) {
}

void dispatcher::visit(const formattables::primitive_info& /*p*/) {
}

std::forward_list<dogen::formatters::file>
dispatcher::format(const formattables::entity& e) {
    e.accept(*this);
    return files_;
}

workflow::workflow(const container& c, const settings::settings& s)
    : container_(c), settings_(s) { }

std::forward_list<dogen::formatters::file>
workflow::format(const formattables::entity& e) const {
    dispatcher d(container_, settings_);
    return d.format(e);
}

} } }
