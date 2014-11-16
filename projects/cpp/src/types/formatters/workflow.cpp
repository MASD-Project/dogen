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
#include "dogen/cpp/types/entity_visitor.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class dispatcher : public entity_visitor {
public:
    dispatcher(const std::forward_list<workflow::facet>& f);
    ~dispatcher() noexcept { }

public:
    using entity_visitor::visit;
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
    std::forward_list<dogen::formatters::file> format(const entity& e);

private:
    const std::forward_list<workflow::facet>& facets_;
    std::forward_list<dogen::formatters::file> files_;
};

dispatcher::dispatcher(const std::forward_list<workflow::facet>& f)
    : facets_(f) { }

void dispatcher::visit(const dogen::cpp::class_info& c) {
    for (const auto& fct : facets_)
        for (const auto fmt : fct.container.class_formatters())
            files_.push_front(fmt->format(fct.bundle, c));
}

void dispatcher::visit(const dogen::cpp::enum_info& /*e*/) {
}

void dispatcher::visit(const dogen::cpp::exception_info& /*e*/) {
}

void dispatcher::visit(const dogen::cpp::registrar_info& /*r*/) {
}

void dispatcher::visit(const dogen::cpp::namespace_info& /*n*/) {
}

void dispatcher::visit(const dogen::cpp::visitor_info& /*v*/) {
}

void dispatcher::visit(const dogen::cpp::new_class_info& /*c*/) {
}

void dispatcher::visit(const dogen::cpp::concept_info& /*c*/) {
}

void dispatcher::visit(const dogen::cpp::primitive_info& /*p*/) {
}

std::forward_list<dogen::formatters::file> dispatcher::format(const entity& e) {
    e.accept(*this);
    return files_;
}

workflow::workflow(
    const std::unordered_map<std::string, container>& formatters_by_facet,
    const std::unordered_map<std::string, settings_bundle>&
    settings_bundle_for_facet)
    : facets_(build_facets(formatters_by_facet, settings_bundle_for_facet)) { }

std::forward_list<workflow::facet> workflow::
build_facets(const std::unordered_map<std::string, container>&
    formatters_by_facet,
    const std::unordered_map<std::string, settings_bundle>&
    settings_bundle_for_facet) const {

    std::unordered_map<std::string, facet> facet_by_id;
    for (const auto pair : formatters_by_facet)
        facet_by_id[pair.first].container = pair.second;

    for (auto pair : settings_bundle_for_facet)
        facet_by_id[pair.first].bundle = pair.second;

    std::forward_list<workflow::facet> r;
    for (const auto& pair : facet_by_id) {
        auto f(pair.second);
        f.id = pair.first;
        r.push_front(f);
    }

    return r;
}

std::forward_list<dogen::formatters::file>
workflow::format(const entity& e) const {
    dispatcher d(facets_);
    return d.format(e);
}

} } }
