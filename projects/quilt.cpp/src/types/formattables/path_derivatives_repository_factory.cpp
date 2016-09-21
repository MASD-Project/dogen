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
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/quilt.cpp/types/formattables/building_error.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/io/formattables/path_derivatives_io.hpp"
#include "dogen/quilt.cpp/io/formattables/path_derivatives_repository_io.hpp"
#include "dogen/quilt.cpp/types/formattables/path_derivatives_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.path_derivatives_repository_factory"));

const std::string empty;
const std::string underscore("_");
const std::string double_quote("\"");
const std::string dot(".");
const std::string separator("_");

const std::string duplicate_name("Duplicate name: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

namespace {

/**
 * @brief Generates all path derivatives.
 */
class generator final : public fabric::element_visitor {
public:
    generator(const container& c, const locator& l)
        : container_(c), locator_(l) { }

private:
    /**
     * @brief Converts a relative path to a header file into a C++
     * header guard name.
     */
    std::string to_header_guard_name(const boost::filesystem::path& p) const;

    /**
     * @brief Generates all of the path derivatives for the formatters
     * and qualified name.
     */
    template<typename YarnEntity>
    void generate(const std::forward_list<
        boost::shared_ptr<provider_interface<YarnEntity>>>& providers,
        const yarn::name& n) {

        BOOST_LOG_SEV(lg, debug) << "Processing name: " << n;
        auto& map(result_.by_name()[n]);
        for (const auto& p : providers) {
            BOOST_LOG_SEV(lg, debug) << "Provider: "
                                     << p->formatter_name();

            path_derivatives pd;
            pd.file_path(p->provide_full_path(locator_, n));
            const auto ns(inclusion_path_support::not_supported);
            if (p->inclusion_path_support() != ns) {
                const auto ip(p->provide_inclusion_path(locator_, n));
                pd.header_guard(to_header_guard_name(ip));
            }
            BOOST_LOG_SEV(lg, debug) << "New Path derivatives: " << pd;
            const auto pair(std::make_pair(p->formatter_name(), pd));
            const auto result(map.insert(pair));
            const bool inserted(result.second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_name << n.id()
                                         << " formatter: "
                                         << p->formatter_name();
                BOOST_THROW_EXCEPTION(building_error(duplicate_name + n.id()));
            }
        }
    }

public:
    using fabric::element_visitor::visit;
    void visit(const yarn::module& m) override {
        generate(container_.module_providers(), m.name());
    }

    void visit(const yarn::concept& c) override {
        generate(container_.concept_providers(), c.name());
    }

    void visit(const yarn::primitive& p) override {
        generate(container_.primitive_providers(), p.name());
    }

    void visit(const yarn::enumeration& e) override {
        generate(container_.enumeration_providers(), e.name());
    }

    void visit(const yarn::object& o) override {
        generate(container_.object_providers(), o.name());
    }

    void visit(const yarn::exception& e) override {
        generate(container_.exception_providers(), e.name());
    }

    void visit(const yarn::visitor& v) override {
        generate(container_.visitor_providers(), v.name());
    }

    void visit(const fabric::registrar& rg) override {
        generate(container_.registrar_providers(), rg.name());
    }

    void visit(const fabric::master_header& mh) override {
        generate(container_.master_header_providers(), mh.name());
    }

    void visit(const fabric::forward_declarations& fd) override {
        generate(container_.forward_declarations_providers(), fd.name());
    }

    void visit(const fabric::cmakelists& c) override {
        generate(container_.cmakelists_providers(), c.name());
    }

    void visit(const fabric::odb_options& o) override {
        generate(container_.odb_options_providers(), o.name());
    }

public:
    const path_derivatives_repository & result() const { return result_; }

private:
    const container& container_;
    const locator& locator_;
    path_derivatives_repository result_;
};

std::string generator::
to_header_guard_name(const boost::filesystem::path& p) const {
    bool is_first(true);
    std::ostringstream ss;
    for (const auto& token : p) {
        std::string s(token.string());
        boost::replace_all(s, dot, separator);
        boost::to_upper(s);
        ss << (is_first ? empty : separator) << s;
        is_first = false;
    }
    return ss.str();
}

}

path_derivatives_repository path_derivatives_repository_factory::make(
    const registrar& rg, const locator& l, const yarn::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Generating path derivatives repository.";
    generator g(rg.container(), l);
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        e.accept(g);
    }
    const auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Finished generating path derivatives"
                             << " repository. Result: " << r;
    return r;
}

} } } }
