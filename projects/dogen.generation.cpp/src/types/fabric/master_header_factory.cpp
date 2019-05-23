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
#include <memory>
#include <forward_list>
#include <boost/make_shared.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.assets/types/helpers/building_error.hpp"
#include "dogen.assets/io/meta_model/name_io.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/meta_model/structural/module.hpp"
#include "dogen.assets/types/meta_model/structural/visitor.hpp"
#include "dogen.assets/types/meta_model/structural/exception.hpp"
#include "dogen.assets/types/meta_model/structural/enumeration.hpp"
#include "dogen.assets/types/meta_model/structural/object_template.hpp"
#include "dogen.assets/types/meta_model/element_visitor.hpp"
#include "dogen.assets/types/helpers/name_factory.hpp"
#include "dogen.assets/types/meta_model/elements_traversal.hpp"
#include "dogen.generation.cpp/types/fabric/master_header.hpp"
#include "dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "dogen.generation.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen.generation.cpp/types/fabric/master_header_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("generation.cpp.fabric.master_header_factory"));

const std::string master_header_name("all");
const std::string formatter_not_found_for_type(
    "Formatter not found for type: ");

}

namespace dogen::generation::cpp::fabric {

using assets::meta_model::origin_types;
using assets::meta_model::technical_space;

namespace {

class generator final : public assets::meta_model::element_visitor {
public:
    generator(const assets::meta_model::name& model_name,
        const formatters::repository& rp)
        : result_(create_master_header(model_name)),
          file_formatters_by_meta_name_(
              filter_file_formatters_by_meta_name(rp)) {}

private:
    boost::shared_ptr<master_header>
    create_master_header(const assets::meta_model::name& model_name);

    std::forward_list<std::shared_ptr<formatters::artefact_formatter_interface>>
    filter_formatters(const std::forward_list<
        std::shared_ptr<formatters::artefact_formatter_interface>>&
        formatters) const;

    std::unordered_map<
        std::string,
        std::forward_list<
            std::shared_ptr<formatters::artefact_formatter_interface>>>
    filter_file_formatters_by_meta_name(const formatters::repository& rp) const;

    void process_element(const assets::meta_model::element& e);

public:
    using assets::meta_model::element_visitor::visit;
    void visit(const assets::meta_model::structural::visitor& v) { process_element(v); }
    void visit(const assets::meta_model::structural::enumeration& e) {
        process_element(e);
    }
    void visit(const assets::meta_model::structural::primitive& p) {
        process_element(p);
    }
    void visit(const assets::meta_model::structural::object& o) { process_element(o); }
    void visit(const assets::meta_model::structural::exception& e) {
        process_element(e);
    }
    void visit(const assets::meta_model::structural::module& m) { process_element(m); }

public:
    boost::shared_ptr<master_header> result() { return result_; }

private:
    boost::shared_ptr<master_header> result_;
    const std::unordered_map<
        std::string,
        std::forward_list<
            std::shared_ptr<formatters::artefact_formatter_interface>>>
    file_formatters_by_meta_name_;

};

boost::shared_ptr<master_header>
generator::create_master_header(const assets::meta_model::name& model_name) {
    auto r(boost::make_shared<master_header>());
    assets::helpers::name_factory f;
    r->name(f.build_element_in_model(model_name, master_header_name));
    r->meta_name(meta_name_factory::make_master_header_name());
    r->origin_type(origin_types::target);
    r->intrinsic_technical_space(technical_space::cpp);
    r->configuration(
        boost::make_shared<variability::meta_model::configuration>());
    r->configuration()->name().simple(r->name().simple());
    r->configuration()->name().qualified(r->name().qualified().dot());
    return r;
}

std::forward_list<std::shared_ptr<formatters::artefact_formatter_interface>>
generator::filter_formatters(const std::forward_list<std::shared_ptr<
    formatters::artefact_formatter_interface>>& formatters) const {
    std::forward_list<std::shared_ptr<formatters::artefact_formatter_interface>>
        r;

    /*
     * We are only interested in formatters that generate
     * header files.
     */
    using formatters::inclusion_support_types;
    static const auto ns(inclusion_support_types::not_supported);
    for (const auto& fmt : formatters) {
        if (fmt->inclusion_support_type() != ns)
            r.push_front(fmt);
    }
    return r;
}

std::unordered_map<
    std::string,
    std::forward_list<
        std::shared_ptr<formatters::artefact_formatter_interface>>>
generator::filter_file_formatters_by_meta_name(
    const formatters::repository& rp) const {
    std::unordered_map<
        std::string,
        std::forward_list<
            std::shared_ptr<formatters::artefact_formatter_interface>>> r;

    for (const auto& pair : rp.stock_artefact_formatters_by_meta_name()) {
        const auto& mt(pair.first);
        const auto& fmts(pair.second);
        r[mt] = filter_formatters(fmts);
    }
    return r;
}

void generator::process_element(const assets::meta_model::element& e) {
    if (e.origin_type() != origin_types::target)
        return;

    BOOST_LOG_SEV(lg, debug) << "Processing element: "
                             << e.name().qualified().dot();
    const auto mt(e.meta_name().qualified().dot());
    const auto i(file_formatters_by_meta_name_.find(mt));
    if (i == file_formatters_by_meta_name_.end()) {
        const auto id(e.name().qualified().dot());
        BOOST_LOG_SEV(lg, error) << formatter_not_found_for_type << id;
        BOOST_THROW_EXCEPTION(
            assets::helpers::building_error(formatter_not_found_for_type + id));
    }

    for (const auto& fmt : i->second) {
        const auto fct(fmt->archetype_location().facet());
        const auto arch(fmt->archetype_location().archetype());
        result_->inclusion_by_facet()[fct][arch].push_back(e.name());
        BOOST_LOG_SEV(lg, debug) << "Added name. Facet: "
                                 << fct << " Archetype: " << arch;
    }
}

}

boost::shared_ptr<assets::meta_model::element>
master_header_factory::make(const formatters::repository& frp,
    const generation::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Generating the master header.";

    generator g(m.name(), frp);
    for(auto& ptr : m.elements()) {
        const auto& e(*ptr);
        e.accept(g);
    }
    const auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Generated the master header.";
    return r;
}

}
