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
#include <unordered_set>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/visitor.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/io/formattables/helper_dependencies_repository_io.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_dependencies_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.helper_properties_repository_factory"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

namespace {

/**
 * @brief Generates all helper dependencies.
 */
class generator final : public yarn::element_visitor {
public:
    explicit generator(const helper_properties_repository& hprp)
        : properties_(hprp) { }

private:
    std::list<std::string>
        to_list(const std::unordered_set<std::string>& set) const;
    
    void generate(const yarn::nested_name& nn,
        std::unordered_set<std::string>& deps) const;
    
    template<typename YarnStateful>
    void generate(const YarnStateful& s) {
        if (s.generation_type() == yarn::generation_types::no_generation)
            return;
        
        std::unordered_set<std::string> deps;
        for (const auto& p : s.local_properties()) {
            generate(p.type(), deps);
        }

        const auto qn(s.name().qualified());
        result_.helper_dependencies_by_name()[qn] = to_list(deps);
    }

public:
    using yarn::element_visitor::visit;
    void visit(const dogen::yarn::concept& c) { generate(c); }
    void visit(const dogen::yarn::object& o) { generate(o); }

public:
    const helper_properties_repository& properties_;
    const helper_dependencies_repository& result() const { return result_; }

private:
    helper_dependencies_repository result_;
};

std::list<std::string>
generator::to_list(const std::unordered_set<std::string>& set) const {
    std::list<std::string> r;
    for (const auto& s : set) {
        r.push_back(s);
    }
    return r;
}

void generator::generate(const yarn::nested_name& nn,
    std::unordered_set<std::string>& deps) const {
    const auto& hp(properties_.helper_properties_by_name());
    const auto i(hp.find(nn.parent().qualified()));
    if (i != hp.end())
        deps.insert(i->second);

    for (const auto& c : nn.children())
        generate(c, deps);
}

}

helper_dependencies_repository helper_dependencies_repository_factory::
make(const helper_properties_repository& hprp, const yarn::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started computing helper dependencies.";
    generator g(hprp);
    for (const auto& pair : m.elements()) {
        const auto& e(*pair.second);
        e.accept(g);
    }
    auto r(g.result());
    BOOST_LOG_SEV(lg, debug) << "Finished computing helper dependencies" << r;
    return r;    
}    

} } } }
