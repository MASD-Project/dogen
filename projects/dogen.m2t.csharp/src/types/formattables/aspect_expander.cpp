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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.m2t.csharp/types/formattables/aspect_properties.hpp"
#include "dogen.m2t.csharp/types/formatters/model_to_text_transform.hpp"
#include "dogen.m2t.csharp/types/formattables/expansion_error.hpp"
#include "dogen.m2t.csharp/types/formattables/aspect_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("m2t.csharp.formattables.aspect_expander"));

}

namespace dogen::m2t::csharp::formattables {

class aspect_properties_generator : public logical::entities::element_visitor {
private:
    struct feature_group {
        variability::entities::feature requires_static_reference_equals;
    };

    feature_group make_feature_group(
        const variability::entities::feature_model& feature_model) const;

public:
    explicit aspect_properties_generator(
        const variability::entities::feature_model& feature_model);

private:
    void handle_aspect_properties(
        const variability::entities::configuration& cfg,
        const std::string& id, const bool is_floating_point = false);

public:
    using logical::entities::element_visitor::visit;
    void visit(const logical::entities::structural::enumeration& e);
    void visit(const logical::entities::structural::exception& e);
    void visit(const logical::entities::structural::object& o);
    void visit(const logical::entities::structural::builtin& p);

public:
    const std::unordered_map<std::string, formattables::aspect_properties>&
    result() const;

private:
    feature_group feature_group_;
    std::unordered_map<std::string, formattables::aspect_properties> result_;
};


aspect_properties_generator::aspect_properties_generator(
    const variability::entities::feature_model& feature_model)
    : feature_group_(make_feature_group(feature_model)) {}

aspect_properties_generator::feature_group
aspect_properties_generator::make_feature_group(
    const variability::entities::feature_model& feature_model) const {

    feature_group r;
    const variability::helpers::feature_selector s(feature_model);
    const auto rsrq(traits::csharp::aspect::requires_static_reference_equals());
    r.requires_static_reference_equals = s.get_by_name(rsrq);

    return r;
}

void aspect_properties_generator::handle_aspect_properties(
    const variability::entities::configuration& cfg, const std::string& id,
    const bool is_floating_point) {
    const variability::helpers::configuration_selector s(cfg);

    /*
     * FIXME: It would be nice to make this container sparse rather
     * than dense. However, because we now default "require static
     * reference equals" to true, sparseness becomes a bit
     * confusing. This needs some rethinking.
     */
    aspect_properties ap;
    const auto& rsrq(feature_group_.requires_static_reference_equals);
    ap.requires_static_reference_equals(s.get_boolean_content_or_default(rsrq));
    ap.is_floating_point(is_floating_point);

    result_[id] = ap;
}

void aspect_properties_generator::
visit(const logical::entities::structural::enumeration& e) {
    handle_aspect_properties(*e.configuration(), e.name().qualified().dot());
}

void aspect_properties_generator::
visit(const logical::entities::structural::exception& e) {
    handle_aspect_properties(*e.configuration(), e.name().qualified().dot());
}

void aspect_properties_generator::visit(const logical::entities::structural::object& o) {
    handle_aspect_properties(*o.configuration(), o.name().qualified().dot());
}

void aspect_properties_generator::visit(const logical::entities::structural::builtin& p) {
    handle_aspect_properties(*p.configuration(), p.name().qualified().dot());
}

const std::unordered_map<std::string, formattables::aspect_properties>&
aspect_properties_generator::result() const {
    return result_;
}

void aspect_expander::
expand(const variability::entities::feature_model& feature_model,
    model& fm) const {
    aspect_properties_generator g(feature_model);
    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);
        const auto& e(*formattable.element());
        e.accept(g);
    }
    fm.aspect_properties(g.result());
}

}
