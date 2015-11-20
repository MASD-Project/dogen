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
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/all_model_items_traversal.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/io/formattables/path_derivatives_repository_io.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_factory.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formattables.path_derivatives_repository_factory"));

const std::string registrar_name("registrar");
const std::string duplicate_name("Duplicate name: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

namespace {

/**
 * @brief Generates all path derivatives.
 */
class generator {
public:
    generator(const path_derivatives_factory& f) : factory_(f) { }

public:
    /**
     * @brief Generates all of the path derivatives for the formatters
     * and qualified name.
     */
    void generate(const yarn::name& n);

public:
    void operator()(const dogen::yarn::object& o) { generate(o.name()); }
    void operator()(const dogen::yarn::enumeration& e) { generate(e.name()); }
    void operator()(const dogen::yarn::primitive& p) { generate(p.name()); }
    void operator()(const dogen::yarn::module& m) { generate(m.name()); }
    void operator()(const dogen::yarn::concept& c) { generate(c.name()); }

public:
    const path_derivatives_repository & result() const { return result_; }

private:
    const path_derivatives_factory& factory_;
    path_derivatives_repository result_;
};

void generator::generate(const yarn::name& n) {
    BOOST_LOG_SEV(lg, debug) << "Processing name: " << n;
    auto& pd(result_.path_derivatives_by_name());
    const auto pair(pd.insert(std::make_pair(n, factory_.make(n))));
    const bool inserted(pair.second);
    if (!inserted) {
        const auto qn(n.simple());
        BOOST_LOG_SEV(lg, error) << duplicate_name << qn;
        BOOST_THROW_EXCEPTION(building_error(duplicate_name + qn));
    }
}

}

path_derivatives_repository path_derivatives_repository_factory::make(
    const config::cpp_options& opts,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const yarn::intermediate_model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Starting workflow.";
    const path_derivatives_factory f(opts, m, ps);
    generator g(f);
    yarn::all_model_items_traversal(m, g);

    yarn::name_factory nf;
    const auto n(nf.build_element_in_model(m.name(), registrar_name));
    g.generate(n);

    for (const auto& pair : m.references()) {
        const auto origin_type(pair.second);
        if (origin_type == yarn::origin_types::system)
            continue;

        const auto ref(pair.first);
        const auto n(nf.build_element_in_model(ref, registrar_name));
        g.generate(n);
    }

    const auto r(g.result());
    BOOST_LOG_SEV(lg, debug) << "Finished workflow. Result: " << r;

    return r;
}

} } }
