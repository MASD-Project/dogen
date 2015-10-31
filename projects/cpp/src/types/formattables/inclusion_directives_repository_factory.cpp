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
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/all_model_items_traversal.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/io/formattables/inclusion_directives_repository_io.hpp"
#include "dogen/cpp/types/settings/inclusion_directives_settings_factory.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_factory.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formattables.inclusion_directives_repository_factory"));

const std::string registrar_name("registrar");
const std::string duplicate_name("Duplicate name: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

namespace {

/**
 * @brief Generates all inclusion directives.
 */
class generator {
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
    void operator()(const dogen::yarn::object& o) { generate(o); }
    void operator()(const dogen::yarn::enumeration& e) { generate(e); }
    void operator()(const dogen::yarn::primitive& p) { generate(p); }
    void operator()(const dogen::yarn::module& m) { generate(m); }
    void operator()(const dogen::yarn::concept& c) { generate(c); }

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
    const yarn::intermediate_model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Making inclusion directives repository.";

    const inclusion_directives_factory f(srp, fc, pdrp);
    generator g(f);
    yarn::all_model_items_traversal(m, g);

    yarn::name n;
    n.simple(registrar_name);
    n.location().original_model_name(m.name().location().original_model_name());
    n.location().external_module_path(
        m.name().location().external_module_path());
    const auto o = dynamic::object();
    g.generate(o, n);

    for (const auto& pair : m.references()) {
        const auto origin_type(pair.second);
        if (origin_type == yarn::origin_types::system)
            continue;

        const auto ref(pair.first);
        yarn::name n;
        n.location().original_model_name(ref.location().original_model_name());
        n.simple(registrar_name);
        n.location().external_module_path(
            ref.location().external_module_path());
        g.generate(o, n);
    }
    const auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Finished inclusion directives repository:"
                             << r;
    return r;
}

} } }
