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
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/visitor.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/quilt.cpp/types/fabric/master_header.hpp"
#include "dogen/quilt.cpp/types/fabric/master_header_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("quilt.cpp.fabric.master_header_factory"));

const std::string master_header_name("all");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

namespace {

class generator final {
private:
    struct header_formatters_container {
        std::forward_list<std::shared_ptr<formatters::file_formatter_interface>>
        object_formatters;
        std::forward_list<std::shared_ptr<formatters::file_formatter_interface>>
        enumeration_formatters;
        std::forward_list<std::shared_ptr<formatters::file_formatter_interface>>
        exception_formatters;
        std::forward_list<std::shared_ptr<formatters::file_formatter_interface>>
        module_formatters;
        std::forward_list<std::shared_ptr<formatters::file_formatter_interface>>
        visitor_formatters;
    };

public:
    generator(const yarn::name& model_name, const formatters::container& fc)
        : result_(create_master_header(model_name)),
          container_(create_container(fc)) {}

private:
    boost::shared_ptr<master_header>
    create_master_header(const yarn::name& model_name) {
        auto r(boost::make_shared<master_header>());
        yarn::name_factory f;
        r->name(f.build_element_in_model(model_name, master_header_name));
        return r;
    }

    template<typename Formatter>
    std::forward_list<std::shared_ptr<Formatter>> filter_formatters(
        const std::forward_list<std::shared_ptr<Formatter>>& formatters) const {
        std::forward_list<std::shared_ptr<Formatter>> r;

        /*
         * We are only interested in formatters that generate
         * header files.
         */
        for (const auto& f : formatters)
            if (f->file_type() == formatters::file_types::cpp_header)
                r.push_front(f);
        return r;
    }

    header_formatters_container
    create_container(const formatters::container& fc) {
        header_formatters_container r;
        r.object_formatters = filter_formatters(fc.object_formatters());
        r.enumeration_formatters = filter_formatters(
            fc.enumeration_formatters());
        r.exception_formatters = filter_formatters(fc.exception_formatters());
        r.module_formatters = filter_formatters(fc.module_formatters());
        r.visitor_formatters = filter_formatters(fc.visitor_formatters());
        return r;
    }

    template<typename Formatter, typename Element>
    void process_element(
        const std::forward_list<std::shared_ptr<Formatter>>& formatters,
        const Element& e) {

        for (const auto& f : formatters) {
            const auto fn(f->ownership_hierarchy().facet_name());
            const auto fmtn(f->ownership_hierarchy().formatter_name());
            result_->inclusion_by_facet()[fn][fmtn].push_back(e.name());
        }
    }

public:
    void operator()(const yarn::concept&) {}
    void operator()(const yarn::primitive&) {}
    void operator()(const dogen::yarn::visitor& v) {
        if (v.generation_type() != yarn::generation_types::no_generation)
            process_element(container_.visitor_formatters, v);
    }

    void operator()(const yarn::enumeration& e) {
        if (e.generation_type() != yarn::generation_types::no_generation)
            process_element(container_.enumeration_formatters, e);
    }

    void operator()(const yarn::object& o) {
        // FIXME: ignore services?
        // FIXME: o.object_type() != yarn::object_types::user_defined_service
        if (o.generation_type() != yarn::generation_types::no_generation)
            process_element(container_.object_formatters, o);
    }

    void operator()(const yarn::exception& e) {
        if (e.generation_type() != yarn::generation_types::no_generation)
            process_element(container_.exception_formatters, e);
    }

    void operator()(const yarn::module& m) {
        if (m.generation_type() != yarn::generation_types::no_generation &&
            !m.documentation().empty())
            process_element(container_.module_formatters, m);
    }

public:
    boost::shared_ptr<master_header> result() { return result_; }

private:
    boost::shared_ptr<master_header> result_;
    const header_formatters_container container_;
};

}

boost::shared_ptr<yarn::element>
master_header_factory::build(const formatters::container& fc,
    const yarn::intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Generating the master header.";

    generator g(im.name(), fc);
    yarn::elements_traversal(im, g);
    const auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Generated the master header.";
    return r;
}

} } } }
