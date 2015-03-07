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
#ifndef DOGEN_DYNAMIC_SCHEMA_TEST_MOCK_WORKFLOW_FACTORY_HPP
#define DOGEN_DYNAMIC_SCHEMA_TEST_MOCK_WORKFLOW_FACTORY_HPP

#include "dogen/dynamic/schema/types/workflow.hpp"

namespace dogen {
namespace dynamic {
namespace schema {
namespace test {

/**
 * @brief Generates "mock" workflows. In reality these are just
 * instances of the workflow used for testing.
 */
class mock_workflow_factory {
public:
    /**
     * @brief Creates a workflow that does not throw if field
     * instances do not have a corresponding field definition.
     *
     * This behaviour is useful when we do not have all of the c++
     * field definitions and so on and it safe to ignore those.
     */
    static const workflow& non_validating_workflow();
};

} } } }

#endif
