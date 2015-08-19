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
#include "dogen/utility/log/logger.hpp"
#include "dogen/tack/types/references_expander.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("tack.references_expander"));

}

namespace dogen {
namespace tack {

void references_expander::
expand_model_references(const tack::nested_name& nn, model& m) const {
    const auto nn_omn(nn.type().location().original_model_name());
    const auto m_omn(m.name().location().original_model_name());
    const bool is_current_model(nn_omn == m_omn);

  if (!nn_omn.empty() && !is_current_model) {
      tack::name n;
      n.location().original_model_name(nn_omn);
      const auto p(std::make_pair(n, tack::origin_types::unknown));
      m.references().insert(p);

      BOOST_LOG_SEV(lg, debug) << "Adding model dependency: "
                               << nn_omn << ". Current model: " << m_omn;
  }

  for (const auto c : nn.children())
      expand_model_references(c, m);
}

void references_expander::expand(model& m) const {
    for (auto& pair : m.objects()) {
        auto& o(pair.second);
        for (auto& p : o.local_properties())
            expand_model_references(p.type(), m);
    }

    for (auto& pair : m.concepts()) {
        auto& c(pair.second);
        for (auto& p : c.local_properties())
            expand_model_references(p.type(), m);
    }
}

} }
