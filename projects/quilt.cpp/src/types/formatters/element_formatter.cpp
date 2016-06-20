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
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/element_formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quit.cpp.formatters.workflow"));

const std::string formatter_properties_not_found(
    "Could not find properties for formatter: ");
const std::string bundle_not_found(
    "Could not find settings bundle for: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

namespace {

class dispatcher : public yarn::element_visitor  {
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

        files_.push_front(file);
        if (!file.overwrite()) {
            BOOST_LOG_SEV(lg, debug) << "Filename: "
                                     << file.path().generic_string();
            BOOST_LOG_SEV(lg, debug) << "Content: "
                                     << (file.content().empty() ? "<empty>" :
                                         file.content());
            BOOST_LOG_SEV(lg, debug) << "Finished formatting: '" << id << "'";
        } else {
            BOOST_LOG_SEV(lg, debug) << "Not dumping file contents to log "
                                     << "(overwrite is false).";
        }
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
    using yarn::element_visitor::visit;
    void visit(const dogen::yarn::module& m) override {
        if (m.documentation().empty())
            return;

        format(container_.namespace_formatters(), m);
    }
    void visit(const dogen::yarn::concept& /*c*/) override {}
    void visit(const dogen::yarn::primitive& /*p*/) override {}
    void visit(const dogen::yarn::enumeration& e) override {
        format(container_.enum_formatters(), e);
    }
    void visit(const dogen::yarn::object& /*o*/) override {}
    void visit(const dogen::yarn::exception& e) override {
        format(container_.exception_formatters(), e);
    }
    void visit(const dogen::yarn::visitor& v) override {
        format(container_.visitor_formatters(), v);
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
