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
#ifndef DOGEN_FORMATTERS_TYPES_GENERAL_SETTINGS_HANDLER_HPP
#define DOGEN_FORMATTERS_TYPES_GENERAL_SETTINGS_HANDLER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include "dogen/sml/types/consumer_interface.hpp"
#include "dogen/formatters/types/general_settings.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Generates a map of general settings for qnames, taking into
 * account the general settings heuristics.
 */
class general_settings_handler : public sml::consumer_interface {
public:
    std::string id() const override;
    unsigned int required_passes() const override;
    bool consume_last() const override;
    void consume(const sml::model& model, const unsigned int pass,
        const sml::concept& target) const override;
    void consume(const sml::model& model, const unsigned int pass,
        const sml::module& target) const override;
    void consume(const sml::model& model, const unsigned int pass,
        const sml::enumeration& target) const override;
    void consume(const sml::model& model, const unsigned int pass,
        const sml::primitive& target) const override;
    void consume(const sml::model& model, const unsigned int pass,
        const sml::object& target) const override;

public:
    /**
     * @brief Returns the general settings by qname container, built
     * from an SML model.
     */
    const std::unordered_map<sml::qname, general_settings>&
    general_settings_by_qname() const;

private:
    std::unordered_map<sml::qname, general_settings> general_settings_by_qname_;
};

} }

#endif
