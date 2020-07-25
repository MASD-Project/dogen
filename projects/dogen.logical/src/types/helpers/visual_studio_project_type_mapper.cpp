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
#include <boost/lexical_cast.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/lexical_cast/entities/technical_space_lc.hpp"
#include "dogen.logical/types/helpers/mapping_error.hpp"
#include "dogen.logical/types/helpers/visual_studio_project_type_mapper.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("visual_studio_project_type_mapper"));

const std::string unsupported_technical_space(
    "Invalid or unsupported technical space: ");

/*
 * GUIDs for project types.
 * Source: https://www.codeproject.com/Reference/720512/List-of-Visual-Studio-Project-Type-GUIDs
 */
const std::string asp_net_5_project_guid(
    "8BB2217D-0F2D-49D1-97BC-3654ED321F3B");
const std::string asp_net_mvc_1_project_guid(
    "603C0E0B-DB56-11DC-BE95-000D561079B0");
const std::string asp_net_mvc_2_project_guid(
    "F85E285D-A4E0-4152-9332-AB1D724D3325");
const std::string asp_net_mvc_3_project_guid(
    "E53F8FEA-EAE0-44A6-8774-FFD645390401");
const std::string asp_net_mvc_4_project_guid(
    "E3E379DF-F4C6-4180-9B81-6769533ABE47");
const std::string asp_net_mvc_5_project_guid(
    "349C5851-65DF-11DA-9384-00065B846F21");
const std::string csharp_project_guid("FAE04EC0-301F-11D3-BF4B-00C04F79EFBC");
const std::string cpp_project_guid("8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942");
const std::string database_project_guid("A9ACE9BB-CECE-4E62-9AA4-C7E7C5BD2124");
const std::string database_other_project_types_project_guid(
    "4F174C21-8C12-11D0-8340-0000F80270F8");
const std::string deployment_cab_project_guid(
    "3EA9E505-35AC-4774-B492-AD1749C4943A");
const std::string deployment_merge_module_project_guid(
    "06A35CCD-C46D-44D5-987B-CF40FF872267");
const std::string deployment_setup_project_guid(
    "978C614F-708E-4E1A-B201-565925725DBA");
const std::string deployment_smart_device_cab_project_guid(
    "AB322303-2255-48EF-A496-5904EB18DA55");
const std::string distributed_system_project_guid(
    "F135691A-BF7E-435D-8960-F99683D2D49C");
const std::string dynamics_2012_ax_csharp_in_aot_project_guid(
    "BF6F8E12-879D-49E7-ADF0-5503146B24B8");
const std::string fsharp_project_guid("F2A71F9B-5D33-465A-A702-920D77279786");
const std::string jsharp_project_guid("E6FDF86B-F3D1-11D4-8576-0002A516ECE8");
const std::string legacy_2003_smart_device_csharp_project_guid(
    "20D4826A-C6FA-45DB-90F4-C717570B9F32");
const std::string legacy_2003_smart_device_vb_net_project_guid(
    "CB4CE8C6-1BDB-4DC7-A4D3-65A1999772F8");
const std::string micro_framework_project_guid(
    "b69e3092-b931-443c-abe7-7e7b65f2a37f");
const std::string model_view_controller_v2_mvc_2_project_guid(
    "F85E285D-A4E0-4152-9332-AB1D724D3325");
const std::string model_view_controller_v3_mvc_3_project_guid(
    "E53F8FEA-EAE0-44A6-8774-FFD645390401");
const std::string model_view_controller_v4_mvc_4_project_guid(
    "E3E379DF-F4C6-4180-9B81-6769533ABE47");
const std::string model_view_controller_v5_mvc_5_project_guid(
    "349C5851-65DF-11DA-9384-00065B846F21");
const std::string mono_for_android_project_guid(
    "EFBA0AD7-5A72-4C68-AF49-83D382785DCF");
const std::string monotouch_project_guid(
    "6BC8ED88-2882-458C-8E55-DFD12B67127B");
const std::string monotouch_binding_project_guid(
    "F5B4F3BC-B597-4E2B-B552-EF5D8A32436F");
const std::string portable_class_library_project_guid(
    "786C830F-07A1-408B-BD7F-6EE04809D6DB");
const std::string project_folders_project_guid(
    "66A26720-8FB5-11D2-AA7E-00C04F688DDE");
const std::string sharepoint_csharp_project_guid(
    "593B0543-81F6-4436-BA1E-4747859CAAE2");
const std::string sharepoint_vb_net_project_guid(
    "EC05E597-79D4-47f3-ADA0-324C4F7C7484");
const std::string sharepoint_workflow_project_guid(
    "F8810EC1-6754-47FC-A15F-DFABD2E3FA90");
const std::string silverlight_project_guid(
    "A1591282-1198-4647-A2B1-27E5FF5F6F3B");
const std::string smart_device_csharp_project_guid(
    "4D628B5B-2FBC-4AA6-8C16-197242AEB884");
const std::string smart_device_vb_net_project_guid(
    "68B1623D-7FB9-47D8-8664-7ECEA3297D4F");
const std::string solution_folder_project_guid(
    "2150E333-8FDC-42A3-9474-1A3956D46DE8");
const std::string test_project_guid("3AC096D0-A1C2-E12C-1390-A8335801FDAB");
const std::string universal_windows_class_library_project_guid(
    "A5A43C5B-DE2A-4C0C-9213-0A381AF9435A");
const std::string vb_net_project_guid("F184B08F-C81C-45F6-A57F-5ABD9991F28F");
const std::string visual_database_tools_project_guid(
    "C252FEB5-A946-4202-B1D4-9916A0590387");
const std::string visual_studio_2015_installer_project_extension_project_guid(
    "54435603-DBB4-11D2-8724-00A0C9A8B90C");
const std::string visual_studio_tools_for_applications_vsta_project_guid(
    "A860303F-1F3F-4691-B57E-529FC101A107");
const std::string visual_studio_tools_for_office_vsto_project_guid(
    "BAA0C2D2-18E2-41B9-852F-F413020CAA33");
const std::string web_application_project_guid(
    "349C5851-65DF-11DA-9384-00065B846F21");
const std::string web_site_project_guid("E24C65DC-7377-472B-9ABA-BC803B73C61A");
const std::string windows_csharp_project_guid(
    "FAE04EC0-301F-11D3-BF4B-00C04F79EFBC");
const std::string windows_vb_net_project_guid(
    "F184B08F-C81C-45F6-A57F-5ABD9991F28F");
const std::string windows_visual_csharp_project_guid(
    "8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942");
const std::string windows_communication_foundation_wcf_project_guid(
    "3D9AD99F-2412-4246-B90B-4EAA41C64699");
const std::string windows_phone_8_8_1_blank_hub_webview_app_project_guid(
"76f1466a-8b6d-4e39-a767-685a06062a3const std::string 9");
const std::string windows_phone_8_8_1_app_csharp_project_guid(
    "C089C8C0-30E0-4E22-80C0-CE093F111A43");
const std::string windows_phone_8_8_1_app_vb_net_project_guid(
    "DB03555F-0C8B-43BE-9FF9-57896B3C5E56");
const std::string windows_presentation_foundation_wpf_project_guid(
    "60DC8134-EBA5-43B8-BCC9-BB4BC16C2548");
const std::string windows_store_metro_apps_and_components_project_guid(
    "BC8A1FFA-BEE3-4634-8014-F334798102B3");
const std::string workflow_csharp_project_guid(
    "14822709-B5A1-4724-98CA-57A101D1B079");
const std::string workflow_vb_net_project_guid(
    "D59BE175-2ED0-4C54-BE3D-CDAA9F3214C8");
const std::string workflow_foundation_project_guid(
    "32F31D43-81CC-4C15-9DE6-3FC5453562B6");
const std::string xamarin_android_project_guid(
    "EFBA0AD7-5A72-4C68-AF49-83D382785DCF");
const std::string xamarin_ios_project_guid(
    "6BC8ED88-2882-458C-8E55-DFD12B67127B");
const std::string xna_windows_project_guid(
    "6D335F3A-9D43-41b4-9D22-F6F17C4BE596");
const std::string xna_xbox_project_guid("2DF5C3F4-5A5F-47a9-8E94-23B4456F55E2");
const std::string xna_zune_project_guid("D399B71A-8929-442a-A9AC-8BEC78BB2433");

}

namespace dogen::logical::helpers {

std::string visual_studio_project_type_mapper::
from_technical_space(const identification::entities::technical_space ts) {
    using identification::entities::technical_space;
    switch(ts) {
    case technical_space::cpp: return cpp_project_guid;
    case technical_space::csharp: return csharp_project_guid;
    default:
        const auto s(boost::lexical_cast<std::string>(ts));
        BOOST_LOG_SEV(lg, error) << unsupported_technical_space << s;
        BOOST_THROW_EXCEPTION(mapping_error(unsupported_technical_space + s));
    }
}

}
