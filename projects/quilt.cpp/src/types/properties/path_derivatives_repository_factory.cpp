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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/quilt.cpp/types/properties/building_error.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/io/properties/path_derivatives_repository_io.hpp"
#include "dogen/quilt.cpp/types/properties/path_derivatives_factory.hpp"
#include "dogen/quilt.cpp/types/properties/path_derivatives_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.properties.path_derivatives_repository_factory"));

const std::string duplicate_name("Duplicate name: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

namespace {

/**
 * @brief Generates all path derivatives.
 */
class generator final : public fabric::element_visitor {
public:
    generator(const path_derivatives_factory& f) : factory_(f) { }

private:
    /**
     * @brief Generates all of the path derivatives for the formatters
     * and qualified name.
     */
    void generate(const yarn::name& n);

public:
    using fabric::element_visitor::visit;
    void visit(const yarn::module& m) override { generate(m.name()); }
    void visit(const yarn::concept& c) override { generate(c.name()); }
    void visit(const yarn::primitive& p) override { generate(p.name()); }
    void visit(const yarn::enumeration& e) override { generate(e.name()); }
    void visit(const yarn::object& o) override { generate(o.name()); }
    void visit(const yarn::exception& e) override { generate(e.name()); }
    void visit(const yarn::visitor& v) override { generate(v.name()); }
    void visit(const fabric::registrar& rg) override { generate(rg.name()); }
    void visit(const fabric::master_header& mh) override {
        generate(mh.name());
    }

public:
    const path_derivatives_repository & result() const { return result_; }

private:
    const path_derivatives_factory& factory_;
    path_derivatives_repository result_;
};

void generator::generate(const yarn::name& n) {
    BOOST_LOG_SEV(lg, debug) << "Processing name: " << n;
    auto& pd(result_.by_name());
    const auto pair(pd.insert(std::make_pair(n, factory_.make(n))));
    const bool inserted(pair.second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_name << n.id();
        BOOST_THROW_EXCEPTION(building_error(duplicate_name + n.id()));
    }
}

}

path_derivatives_repository path_derivatives_repository_factory::make(
    const config::cpp_options& opts,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const yarn::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Starting workflow.";
    const path_derivatives_factory f(opts, m, ps);
    generator g(f);
    for (const auto& pair : m.elements()) {
        const auto& e(*pair.second);
        e.accept(g);
    }
    const auto r(g.result());
    BOOST_LOG_SEV(lg, debug) << "Finished workflow. Result: " << r;

    return r;
}

} } } }
