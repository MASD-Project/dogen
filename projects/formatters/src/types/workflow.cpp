/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/formatters/types/file_formatter_interface.hpp"
#include "dogen/formatters/types/transformer_interface.hpp"
#include "dogen/formatters/types/workflow.hpp"

namespace dogen {
namespace formatters {

void workflow::register_interface(file_formatter_type ff) {
    repository().file_formatters().push_back(ff);
}

void workflow::register_interface(transformer_type t) {
    repository().transformers().push_back(t);
}

formatters::repository& workflow::repository() {
    static formatters::repository repository_;
    return repository_;
}

std::list<file> workflow::execute(const entities_type& entities) {
    std::list<file> r;
    for (const auto& e : entities) {
        for (const auto& f : repository().file_formatters()) {
            const auto of(f->format(*e));
            if (of)
                r.push_back(*of);
        }
    }
    return r;
}

std::list<file> workflow::execute(const sml::model& m) {
    std::list<file> r;
    for (const auto& t : repository().transformers()) {
        const auto& entities(t->transform(m));
        for (const auto& e : entities) {
            for (const auto& f : repository().file_formatters()) {
                const auto of(f->format(*e));
                if (of)
                    r.push_back(*of);
            }
        }
    }
    return r;
}


} }
