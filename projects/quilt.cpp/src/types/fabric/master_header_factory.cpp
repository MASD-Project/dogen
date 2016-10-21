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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/visitor.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/quilt.cpp/types/fabric/master_header.hpp"
#include "dogen/quilt.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/fabric/master_header_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("quilt.cpp.fabric.master_header_factory"));

const std::string master_header_name("all");
const std::string formatter_not_found_for_type(
    "Formatter not found for type: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

namespace {

class generator final {
public:
    generator(const yarn::name& model_name, const formatters::repository& rp)
        : result_(create_master_header(model_name)),
          file_formatters_by_type_index_(
              filter_file_formatters_by_type_index(rp)) {}

private:
    boost::shared_ptr<master_header>
    create_master_header(const yarn::name& model_name);

    std::forward_list<std::shared_ptr<formatters::artefact_formatter_interface>>
    filter_formatters(const std::forward_list<
        std::shared_ptr<formatters::artefact_formatter_interface>>&
        formatters) const;

    std::unordered_map<
        std::type_index,
        std::forward_list<
            std::shared_ptr<formatters::artefact_formatter_interface>>>
    filter_file_formatters_by_type_index(const formatters::repository& rp) const;

    void process_element(const yarn::element& e);

public:
    void operator()(const yarn::concept&) {}
    void operator()(const yarn::primitive&) {}
    void operator()(const dogen::yarn::visitor& v) { process_element(v); }
    void operator()(const yarn::enumeration& e) { process_element(e); }
    void operator()(const yarn::object& o) { process_element(o); }
    void operator()(const yarn::exception& e) { process_element(e); }
    void operator()(const yarn::module& m) { process_element(m); }

public:
    boost::shared_ptr<master_header> result() { return result_; }

private:
    boost::shared_ptr<master_header> result_;
    const std::unordered_map<
        std::type_index,
        std::forward_list<
            std::shared_ptr<formatters::artefact_formatter_interface>>>
    file_formatters_by_type_index_;

};

boost::shared_ptr<master_header>
generator::create_master_header(const yarn::name& model_name) {
    auto r(boost::make_shared<master_header>());
    yarn::name_factory f;
    r->name(f.build_element_in_model(model_name, master_header_name));
    r->origin_type(yarn::origin_types::target);
    return r;
}

std::forward_list<std::shared_ptr<formatters::artefact_formatter_interface>>
generator::filter_formatters(const std::forward_list<std::shared_ptr<
    formatters::artefact_formatter_interface>>& formatters) const {
    std::forward_list<std::shared_ptr<formatters::artefact_formatter_interface>> r;

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
    std::type_index,
    std::forward_list<
        std::shared_ptr<formatters::artefact_formatter_interface>>>
generator::filter_file_formatters_by_type_index(
    const formatters::repository& rp) const {
    std::unordered_map<
        std::type_index,
        std::forward_list<
            std::shared_ptr<formatters::artefact_formatter_interface>>> r;

    for (const auto& pair : rp.stock_artefact_formatters_by_type_index()) {
        const auto& ti(pair.first);
        const auto& fmts(pair.second);
        r[ti] = filter_formatters(fmts);
    }
    return r;
}

void generator::process_element(const yarn::element& e) {
    if (e.origin_type() != yarn::origin_types::target)
        return;

    const auto ti(std::type_index(typeid(e)));
    const auto i(file_formatters_by_type_index_.find(ti));
    if (i == file_formatters_by_type_index_.end()) {
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, error) << formatter_not_found_for_type << id;
        BOOST_THROW_EXCEPTION(
            yarn::building_error(formatter_not_found_for_type + id));
    }

    for (const auto& fmt : i->second) {
        const auto fct(fmt->archetype_location().facet());
        const auto arch(fmt->archetype_location().archetype());
        result_->inclusion_by_facet()[fct][arch].push_back(e.name());
        BOOST_LOG_SEV(lg, debug) << "Added name. Id: " << e.name()
                                 << " Facet: " << fct << " Archetype: " << arch;
    }
}

}

boost::shared_ptr<yarn::element>
master_header_factory::build(const formatters::repository& frp,
    const yarn::intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Generating the master header.";

    generator g(im.name(), frp);
    yarn::elements_traversal(im, g);
    const auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Generated the master header.";
    return r;
}

} } } }
