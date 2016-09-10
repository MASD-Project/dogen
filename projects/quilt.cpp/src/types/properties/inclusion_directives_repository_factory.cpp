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
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/pair_io.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/properties/building_error.hpp"
#include "dogen/quilt.cpp/io/properties/inclusion_directives_repository_io.hpp"
#include "dogen/quilt.cpp/types/settings/inclusion_directives_settings_factory.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_directives_factory.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_directives_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.properties.inclusion_directives_repository_factory"));

const std::string duplicate_name("Duplicate name: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

namespace {

/**
 * @brief Generates all inclusion directives.
 */
class generator final : public fabric::element_visitor {
public:
    generator(const inclusion_directives_factory& f) : factory_(f) { }

private:
    void generate(const dynamic::object& o, const yarn::name& n) {
        const auto id(factory_.make(o, n));
        if (!id)
            return;

        auto& id_n(result_.by_name());
        const auto pair(id_n.insert(std::make_pair(n, *id)));
        if (pair.second)
            return;

        BOOST_LOG_SEV(lg, error) << duplicate_name << n.id();
        BOOST_THROW_EXCEPTION(building_error(duplicate_name + n.id()));
    }

private:
    /**
     * @brief Generates all of the inclusion dependencies for the
     * formatters and name.
     */
    template<typename ExtensibleAndNameable>
    void generate(const ExtensibleAndNameable& e) {
        generate(e.extensions(), e.name());
    }

public:
    using fabric::element_visitor::visit;
    void visit(const yarn::module& m) override { generate(m); }
    void visit(const yarn::concept& c) override { generate(c); }
    void visit(const yarn::primitive& p) override { generate(p); }
    void visit(const yarn::enumeration& e) override { generate(e); }
    void visit(const yarn::object& o) override { generate(o); }
    void visit(const yarn::exception& e) override { generate(e); }
    void visit(const yarn::visitor& v) override { generate(v); }
    void visit(const fabric::registrar& rg) override { generate(rg); }
    void visit(const fabric::master_header& mh) override { generate(mh); }

public:
    const inclusion_directives_repository& result() const { return result_; }

private:
    const inclusion_directives_factory& factory_;
    inclusion_directives_repository result_;
};

}

inclusion_directives_repository inclusion_directives_repository_factory::make(
    const dynamic::repository& srp,
    const formatters::container& fc,
    const path_derivatives_repository& pdrp,
    const yarn::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Making inclusion directives repository.";

    const inclusion_directives_factory f(srp, fc, pdrp);
    generator g(f);
    for (const auto& pair : m.elements()) {
        const auto& e(*pair.second);
        e.accept(g);
    }

    const auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Finished inclusion directives repository:"
                             << r;
    return r;
}

} } } }
