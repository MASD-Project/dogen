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
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/types/properties/building_error.hpp"
#include "dogen/quilt.cpp/io/properties/inclusion_directives_repository_io.hpp"
#include "dogen/quilt.cpp/types/settings/inclusion_directives_settings_factory.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_directives_factory.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_directives_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.properties.inclusion_directives_repository_factory"));

const std::string registrar_name("registrar");
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
class generator final : public yarn::element_visitor {
public:
    generator(const inclusion_directives_factory& f) : factory_(f) { }

public:
    void generate(const dynamic::object& o, const yarn::name& n) {
        const auto id(factory_.make(o, n));
        if (!id)
            return;

        auto& id_n(result_.inclusion_directives_by_name());
        const auto pair(id_n.insert(std::make_pair(n, *id)));
        if (pair.second)
            return;

        const auto qn(n.qualified());
        BOOST_LOG_SEV(lg, error) << duplicate_name << qn;
        BOOST_THROW_EXCEPTION(building_error(duplicate_name + qn));
    }

private:
    /**
     * @brief Generates all of the inclusion dependencies for the
     * formatters and qualified name.
     */
    template<typename ExtensibleAndNameable>
    void generate(const ExtensibleAndNameable& e) {
        generate(e.extensions(), e.name());
    }

public:
    using yarn::element_visitor::visit;
    void visit(const dogen::yarn::module& m) { generate(m); }
    void visit(const dogen::yarn::concept& c) { generate(c); }
    void visit(const dogen::yarn::primitive& p) { generate(p); }
    void visit(const dogen::yarn::enumeration& e) { generate(e); }
    void visit(const dogen::yarn::object& o) { generate(o); }
    void visit(const dogen::yarn::exception& e) { generate(e); }
    void visit(const dogen::yarn::visitor& v) { generate(v); }

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

    yarn::name_factory nf;
    const auto n(nf.build_element_in_model(m.name(), registrar_name));
    const auto o = dynamic::object();
    g.generate(o, n);

    for (const auto& pair : m.references()) {
        const auto origin_type(pair.second);
        if (origin_type == yarn::origin_types::system)
            continue;

        const auto ref(pair.first);
        const auto n(nf.build_element_in_model(ref, registrar_name));
        g.generate(o, n);
    }
    const auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Finished inclusion directives repository:"
                             << r;
    return r;
}

} } } }
