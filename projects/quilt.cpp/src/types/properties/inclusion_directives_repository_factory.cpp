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
#include "dogen/quilt.cpp/types/annotations/inclusion_directive_annotations_factory.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_directives_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.properties.inclusion_directives_repository_factory"));

const std::string double_quote("\"");
const std::string duplicate_name("Duplicate name: ");
const std::string empty_include_directive("Include directive is empty.");

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
    generator(const container& c, const locator& l,
        const annotations::inclusion_directive_annotations_factory& f)
        : container_(obtain_relevant_providers(c)), locator_(l), factory_(f) { }

private:
    /**
     * @brief Filter out providers that do not support inclusion
     * paths.
     *
     * Not all formatters support inclusion path. We are only
     * interested in those which do.
     */
    container obtain_relevant_providers(const container& c) const;

    /**
     * @brief Inserts the inclusion directive.
     */
    void insert_inclusion_directive(const std::string& id,
        const std::string& formatter_name, const std::string& directive);

    /**
     * @brief Converts a relative path to an inclusion directive.
     */
    std::string to_inclusion_directive(const boost::filesystem::path& p) const;

private:
    template<typename YarnEntity>
    void generate(const std::forward_list<
        boost::shared_ptr<provider_interface<YarnEntity>>>& providers,
        const YarnEntity& e) {

        const auto& n(e.name());
        const auto id(n.id());

        /*
         * First we extract the configuration for the generation of
         * include directives for this element. Note that we generate
         * this setting for _all elements_ even if the user did not
         * specify any meta-data (we do so via defaults).
         *
         * The question we are asking is: "does this element require
         * any inclusion directives at all, across all facets?". Not
         * all elements do; for example bool, int and so on don't
         * require any inclusions at all across all facets. If the
         * user did not override this, we default it to true because
         * normally elements require inclusion.
         */
        const auto& o(e.extensions());
        const bool required(factory_.make_top_level_inclusion_required(o));
        if (!required) {
            BOOST_LOG_SEV(lg, debug) << "Inclusion not required for element.";
            return;
        }

        if (providers.empty()) {
            BOOST_LOG_SEV(lg, debug) << "No providers found.";
            return;
        }

        /*
         * Now we start working at the formatter level.
         */
        for (const auto& p : providers) {
            const auto fmt_n(p->formatter_name());
            BOOST_LOG_SEV(lg, debug) << "Formatter: " << fmt_n;

            /*
             * Does the type require an inclusion directive for this
             * specific formatter? Some types require inclusion
             * directives for some formatters, but not for others. For
             * example, we may need an include for serialising a
             * std::list, but in test data we make use of helpers and
             * thus do not require an include.
             *
             * Again, we default this to true.
             */
            const auto s(factory_.make_inclusion_directive_annotations(fmt_n, o));
            if (!s.inclusion_required()) {
                BOOST_LOG_SEV(lg, debug) << "Inclusion directive not required "
                                         << " for formatter: " << fmt_n;
                continue;
            }

            /*
             * Do the annotations provide a "hard-coded" inclusion directive?
             * That is, the type had an hard-coded incantation for its
             * include. This is the case for system models such as boost, std
             * etc where we can't compute the inclusion directive.
             */
            std::string directive;
            if (s.inclusion_directive())
                directive = *s.inclusion_directive();
            else {
                /*
                 * Finally, we have no alternative but to compute the
                 * inclusion directive.
                 */
                const auto path(p->provide_inclusion_path(locator_, n));
                directive = to_inclusion_directive(path);
            }

            BOOST_LOG_SEV(lg, debug) << "Inclusion directive: " << directive;
            insert_inclusion_directive(id, fmt_n, directive);

            /*
             * If the provider is also the default for this facet and
             * element, we need to register it against the facet
             * too. Note that, for a given element type on a given
             * facet, there can only be one default - or else we'll
             * throw.
             */
            const auto def(inclusion_path_support::is_default);
            const auto fct_n(p->facet_name());
            if (p->inclusion_path_support() == def) {
                BOOST_LOG_SEV(lg, debug) << "Inserting default for: " << fct_n;
                insert_inclusion_directive(id, fct_n, directive);
            }
        }
    }

public:
    using fabric::element_visitor::visit;
    void visit(const yarn::module& m) override {
        BOOST_LOG_SEV(lg, debug) << "Generating inclusion directive for: "
                                 << m.name().id() << " (module)";
        generate(container_.module_providers(), m);
    }

    void visit(const yarn::concept& c) override {
        BOOST_LOG_SEV(lg, debug) << "Generating inclusion directive for: "
                                 << c.name().id() << " (concept)";
        generate(container_.concept_providers(), c);
    }

    void visit(const yarn::primitive& p) override {
        BOOST_LOG_SEV(lg, debug) << "Generating inclusion directive for: "
                                 << p.name().id() << " (primitive)";
        generate(container_.primitive_providers(), p);
    }

    void visit(const yarn::enumeration& e) override {
        BOOST_LOG_SEV(lg, debug) << "Generating inclusion directive for: "
                                 << e.name().id() << " (enumeration)";
        generate(container_.enumeration_providers(), e);
    }

    void visit(const yarn::object& o) override {
        BOOST_LOG_SEV(lg, debug) << "Generating inclusion directive for: "
                                 << o.name().id() << " (object)";
        generate(container_.object_providers(), o);
    }

    void visit(const yarn::exception& e) override {
        BOOST_LOG_SEV(lg, debug) << "Generating inclusion directive for: "
                                 << e.name().id() << " (exception)";
        generate(container_.exception_providers(), e);
    }

    void visit(const yarn::visitor& v) override {
        BOOST_LOG_SEV(lg, debug) << "Generating inclusion directive for: "
                                 << v.name().id() << " (visitor)";
        generate(container_.visitor_providers(), v);
    }

    void visit(const fabric::registrar& rg) override {
        BOOST_LOG_SEV(lg, debug) << "Generating inclusion directive for: "
                                 << rg.name().id() << " (registrar)";
        generate(container_.registrar_providers(), rg);
    }

    void visit(const fabric::master_header& mh) override {
        BOOST_LOG_SEV(lg, debug) << "Generating inclusion directive for: "
                                 << mh.name().id() << " (master header)";
        generate(container_.master_header_providers(), mh);
    }

    void visit(const fabric::forward_declarations& fd) override {
        BOOST_LOG_SEV(lg, debug) << "Generating inclusion directive for: "
                                 << fd.name().id() << " (forward declarations)";
        generate(container_.forward_declarations_providers(), fd);
    }

public:
    const inclusion_directives_repository& result() const { return result_; }

private:
    const container container_;
    const locator& locator_;
    const annotations::inclusion_directive_annotations_factory factory_;
    inclusion_directives_repository result_;
};

container generator::obtain_relevant_providers(const container& c) const {
    container r;

    const auto ns(inclusion_path_support::not_supported);

    for (auto p : c.module_providers()) {
        if (p->inclusion_path_support() == ns)
            continue;
        r.module_providers().push_front(p);
    }

    for (auto p : c.concept_providers()) {
        if (p->inclusion_path_support() == ns)
            continue;
        r.concept_providers().push_front(p);
    }

    for (auto p : c.primitive_providers()) {
        if (p->inclusion_path_support() == ns)
            continue;
        r.primitive_providers().push_front(p);
    }

    for (auto p : c.object_providers()) {
        if (p->inclusion_path_support() == ns)
            continue;
        r.object_providers().push_front(p);
    }

    for (auto p : c.enumeration_providers()) {
        if (p->inclusion_path_support() == ns)
            continue;
        r.enumeration_providers().push_front(p);
    }

    for (auto p : c.exception_providers()) {
        if (p->inclusion_path_support() == ns)
            continue;
        r.exception_providers().push_front(p);
    }

    for (auto p : c.visitor_providers()) {
        if (p->inclusion_path_support() == ns)
            continue;
        r.visitor_providers().push_front(p);
    }

    for (auto p : c.registrar_providers()) {
        if (p->inclusion_path_support() == ns)
            continue;
        r.registrar_providers().push_front(p);
    }

    for (auto p : c.master_header_providers()) {
        if (p->inclusion_path_support() == ns)
            continue;
        r.master_header_providers().push_front(p);
    }

    for (auto p : c.forward_declarations_providers()) {
        if (p->inclusion_path_support() == ns)
            continue;
        r.forward_declarations_providers().push_front(p);
    }

    return r;
}

void generator::insert_inclusion_directive(const std::string& id,
    const std::string& formatter_name, const std::string& directive) {

    if (directive.empty()) {
        std::ostringstream s;
        s << empty_include_directive << formatter_name << " for type: " << id;

        const auto msg(s.str());
        BOOST_LOG_SEV(lg, error) << msg;
        BOOST_THROW_EXCEPTION(building_error(msg));
    }

    const auto fn_dir(std::make_pair(formatter_name, directive));
    const auto pair(result_.by_name()[id].insert(fn_dir));
    if (pair.second)
        return;

    BOOST_LOG_SEV(lg, error) << duplicate_name << id;
    BOOST_THROW_EXCEPTION(building_error(duplicate_name + id));
}

std::string generator::
to_inclusion_directive(const boost::filesystem::path& p) const {
    std::ostringstream ss;
    ss << double_quote << p.generic_string() << double_quote;
    return ss.str();
}

}

inclusion_directives_repository inclusion_directives_repository_factory::make(
    const dynamic::repository& drp,
    const formatters::container& fc,
    const registrar& rg, const locator& l,
    const yarn::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Making inclusion directives repository.";

    const annotations::inclusion_directive_annotations_factory f(drp, fc);
    generator g(rg.container(), l, f);
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        e.accept(g);
    }
    const auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Finished inclusion directives repository:"
                             << r;
    return r;
}

} } } }
