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
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/element_formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quit.cpp.formatters.element_formatter"));

const std::string formatter_properties_not_found(
    "Could not find properties for formatter: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

namespace {

class dispatcher : public fabric::element_visitor  {
public:
    dispatcher(const context_factory& f, const container& c) :
        factory_(f), container_(c) {}

public:
    std::forward_list<dogen::formatters::file> files() {
        return files_;
    }

private:
    template<typename Formatter, typename YarnElement>
    void format(const Formatter& f, const YarnElement& e) {

        const auto id(e.name().id());
        const auto fn(f.ownership_hierarchy().formatter_name());
        BOOST_LOG_SEV(lg, debug) << "Formatting: '" << id << "' with '"
                                 << fn << "'";

        const auto ctx(factory_.make(e.name().id()));
        const auto fp(ctx.element_properties().formatter_properties());
        const auto i(fp.find(fn));
        if (i == fp.end()) {
            BOOST_LOG_SEV(lg, error) << formatter_properties_not_found << fn;
            BOOST_THROW_EXCEPTION(
                workflow_error(formatter_properties_not_found + fn));
        }

        const auto is_formatter_enabled(i->second.enabled());
        if (!is_formatter_enabled) {
            BOOST_LOG_SEV(lg, debug) << "Formatter not enabled for type.";
            return;
        }

        auto file(f.format(ctx, e));

        // FIXME: hack to handle services
        if (e.generation_type() == yarn::generation_types::partial_generation) {
            BOOST_LOG_SEV(lg, debug) << "Emptying out content.";
            file.content().clear();
        }

        files_.push_front(file);
        BOOST_LOG_SEV(lg, debug) << "Finished formatting: '" << id << "'";
    }

    template<typename Formatter, typename Formattable>
    void format(const std::forward_list<std::shared_ptr<Formatter>>& fc,
        const Formattable& e) {
        for (const auto f : fc)
            format(*f, e);
    }

public:
    /**
     * @brief Converts the supplied entity into all supported
     * representations.
     */
    void format(const yarn::element& e) {
        e.accept(*this);
    }

public:
    using fabric::element_visitor::visit;
    void visit(const dogen::yarn::module& m) override {
        // FIXME: hack. We should remove these from the pipeline
        // earlier or make the return optional.
        if (m.documentation().empty())
            return;

        format(container_.module_formatters(), m);
    }
    void visit(const yarn::enumeration& e) override {
        format(container_.enumeration_formatters(), e);
    }
    void visit(const yarn::object& o) override {
        format(container_.object_formatters(), o);
    }
    void visit(const yarn::exception& e) override {
        format(container_.exception_formatters(), e);
    }
    void visit(const yarn::visitor& v) override {
        format(container_.visitor_formatters(), v);
    }
    void visit(const fabric::registrar& rg) override {
        format(container_.registrar_formatters(), rg);
    }
    void visit(const fabric::master_header& mh) override {
        format(container_.master_header_formatters(), mh);
    }
    void visit(const fabric::forward_declarations& fd) override {
        format(container_.forward_declarations_formatters(), fd);
    }
    void visit(const fabric::cmakelists& c) override {
        format(container_.cmakelists_formatters(), c);
    }
    void visit(const fabric::odb_options& o) override {
        format(container_.odb_options_formatters(), o);
    }

private:
    const context_factory factory_;
    const container& container_;
    std::forward_list<dogen::formatters::file> files_;
};

}

element_formatter::
element_formatter(const context_factory& f, const container& c)
    : factory_(f), container_(c) { }

std::forward_list<dogen::formatters::file> element_formatter::
format(const yarn::element& e) const {
    dispatcher d(factory_, container_);
    d.format(e);
    return d.files();
}

} } } }
