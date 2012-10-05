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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/prototype/test_data/currency_td.hpp"

namespace dogen {
namespace prototype {
namespace detail {

complete_currency_generator::value_type
complete_currency_generator::next_term(const unsigned int position) {
    // manual process atm. see GH-24
    using dogen::prototype::versioned_key;

    using dogen::prototype::currency;
    switch(position) {
    case 0: return(currency("United Arab Emirates dirham", "AED", 2, 784, versioned_key(784, 0)));
    case 1: return(currency("Afghani", "AFN", 2, 971, versioned_key(971, 0)));
    case 2: return(currency("Lek", "ALL", 2, 8, versioned_key(8, 0)));
    case 3: return(currency("Armenian dram", "AMD", 0, 51, versioned_key(51, 0)));
    case 4: return(currency("Netherlands Antillean guilder", "ANG", 2, 532, versioned_key(532, 0)));
    case 5: return(currency("Kwanza", "AOA", 1, 973, versioned_key(973, 0)));
    case 6: return(currency("Argentine peso", "ARS", 2, 32, versioned_key(32, 0)));
    case 7: return(currency("Australian dollar", "AUD", 2, 36, versioned_key(36, 0)));
    case 8: return(currency("Aruban guilder", "AWG", 2, 533, versioned_key(533, 0)));
    case 9: return(currency("Azerbaijanian manat", "AZN", 2, 944, versioned_key(944, 0)));
    case 10: return(currency("Convertible marks", "BAM", 2, 977, versioned_key(977, 0)));
    case 11: return(currency("Barbados dollar", "BBD", 2, 52, versioned_key(52, 0)));
    case 12: return(currency("Bangladeshi taka", "BDT", 2, 50, versioned_key(50, 0)));
    case 13: return(currency("Bulgarian lev", "BGN", 2, 975, versioned_key(975, 0)));
    case 14: return(currency("Bahraini dinar", "BHD", 3, 48, versioned_key(48, 0)));
    case 15: return(currency("Burundian franc", "BIF", 0, 108, versioned_key(108, 0)));
    case 16: return(currency("Bermudian dollar (customarily known as Bermuda dollar)", "BMD", 2, 60, versioned_key(60, 0)));
    case 17: return(currency("Brunei dollar", "BND", 2, 96, versioned_key(96, 0)));
    case 18: return(currency("Boliviano", "BOB", 2, 68, versioned_key(68, 0)));
    case 19: return(currency("Bolivian Mvdol (funds code)", "BOV", 2, 984, versioned_key(984, 0)));
    case 20: return(currency("Brazilian real", "BRL", 2, 986, versioned_key(986, 0)));
    case 21: return(currency("Bahamian dollar", "BSD", 2, 44, versioned_key(44, 0)));
    case 22: return(currency("Ngultrum", "BTN", 2, 64, versioned_key(64, 0)));
    case 23: return(currency("Pula", "BWP", 2, 72, versioned_key(72, 0)));
    case 24: return(currency("Belarusian ruble", "BYR", 0, 974, versioned_key(974, 0)));
    case 25: return(currency("Belize dollar", "BZD", 2, 84, versioned_key(84, 0)));
    case 26: return(currency("Canadian dollar", "CAD", 2, 124, versioned_key(124, 0)));
    case 27: return(currency("Franc Congolais", "CDF", 2, 976, versioned_key(976, 0)));
    case 28: return(currency("WIR euro (complementary currency)", "CHE", 2, 947, versioned_key(947, 0)));
    case 29: return(currency("Swiss franc", "CHF", 2, 756, versioned_key(756, 0)));
    case 30: return(currency("WIR franc (complementary currency)", "CHW", 2, 948, versioned_key(948, 0)));
    case 31: return(currency("Unidad de Fomento (funds code)", "CLF", 0, 990, versioned_key(990, 0)));
    case 32: return(currency("Chilean peso", "CLP", 0, 152, versioned_key(152, 0)));
    case 33: return(currency("Chinese Yuan", "CNY", 1, 156, versioned_key(156, 0)));
    case 34: return(currency("Colombian peso", "COP", 0, 170, versioned_key(170, 0)));
    case 35: return(currency("Unidad de Valor Real", "COU", 2, 970, versioned_key(970, 0)));
    case 36: return(currency("Costa Rican colon", "CRC", 2, 188, versioned_key(188, 0)));
    case 37: return(currency("Cuban convertible peso", "CUC", 2, 931, versioned_key(931, 0)));
    case 38: return(currency("Cuban peso", "CUP", 2, 192, versioned_key(192, 0)));
    case 39: return(currency("Cape Verde escudo", "CVE", 2, 132, versioned_key(132, 0)));
    case 40: return(currency("Czech Koruna", "CZK", 2, 203, versioned_key(203, 0)));
    case 41: return(currency("Djibouti franc", "DJF", 0, 262, versioned_key(262, 0)));
    case 42: return(currency("Danish krone", "DKK", 2, 208, versioned_key(208, 0)));
    case 43: return(currency("Dominican peso", "DOP", 2, 214, versioned_key(214, 0)));
    case 44: return(currency("Algerian dinar", "DZD", 2, 12, versioned_key(12, 0)));
    case 45: return(currency("Kroon", "EEK", 2, 233, versioned_key(233, 0)));
    case 46: return(currency("Egyptian pound", "EGP", 2, 818, versioned_key(818, 0)));
    case 47: return(currency("Nakfa", "ERN", 2, 232, versioned_key(232, 0)));
    case 48: return(currency("Ethiopian birr", "ETB", 2, 230, versioned_key(230, 0)));
    case 49: return(currency("euro", "EUR", 2, 978, versioned_key(978, 0)));
    case 50: return(currency("Fiji dollar", "FJD", 2, 242, versioned_key(242, 0)));
    case 51: return(currency("Falkland Islands pound", "FKP", 2, 238, versioned_key(238, 0)));
    case 52: return(currency("Pound sterling", "GBP", 2, 826, versioned_key(826, 0)));
    case 53: return(currency("Lari", "GEL", 2, 981, versioned_key(981, 0)));
    case 54: return(currency("Cedi", "GHS", 2, 936, versioned_key(936, 0)));
    case 55: return(currency("Gibraltar pound", "GIP", 2, 292, versioned_key(292, 0)));
    case 56: return(currency("Dalasi", "GMD", 2, 270, versioned_key(270, 0)));
    case 57: return(currency("Guinea franc", "GNF", 0, 324, versioned_key(324, 0)));
    case 58: return(currency("Quetzal", "GTQ", 2, 320, versioned_key(320, 0)));
    case 59: return(currency("Guyana dollar", "GYD", 2, 328, versioned_key(328, 0)));
    case 60: return(currency("Hong Kong dollar", "HKD", 2, 344, versioned_key(344, 0)));
    case 61: return(currency("Lempira", "HNL", 2, 340, versioned_key(340, 0)));
    case 62: return(currency("Croatian kuna", "HRK", 2, 191, versioned_key(191, 0)));
    case 63: return(currency("Haiti gourde", "HTG", 2, 332, versioned_key(332, 0)));
    case 64: return(currency("Forint", "HUF", 2, 348, versioned_key(348, 0)));
    case 65: return(currency("Rupiah", "IDR", 0, 360, versioned_key(360, 0)));
    case 66: return(currency("Israeli new sheqel", "ILS", 2, 376, versioned_key(376, 0)));
    case 67: return(currency("Indian rupee", "INR", 2, 356, versioned_key(356, 0)));
    case 68: return(currency("Iraqi dinar", "IQD", 0, 368, versioned_key(368, 0)));
    case 69: return(currency("Iranian rial", "IRR", 0, 364, versioned_key(364, 0)));
    case 70: return(currency("Iceland krona", "ISK", 0, 352, versioned_key(352, 0)));
    case 71: return(currency("Jamaican dollar", "JMD", 2, 388, versioned_key(388, 0)));
    case 72: return(currency("Jordanian dinar", "JOD", 3, 400, versioned_key(400, 0)));
    case 73: return(currency("Japanese yen", "JPY", 0, 392, versioned_key(392, 0)));
    case 74: return(currency("Kenyan shilling", "KES", 2, 404, versioned_key(404, 0)));
    case 75: return(currency("Som", "KGS", 2, 417, versioned_key(417, 0)));
    case 76: return(currency("Riel", "KHR", 0, 116, versioned_key(116, 0)));
    case 77: return(currency("Comoro franc", "KMF", 0, 174, versioned_key(174, 0)));
    case 78: return(currency("North Korean won", "KPW", 0, 408, versioned_key(408, 0)));
    case 79: return(currency("South Korean won", "KRW", 0, 410, versioned_key(410, 0)));
    case 80: return(currency("Kuwaiti dinar", "KWD", 3, 414, versioned_key(414, 0)));
    case 81: return(currency("Cayman Islands dollar", "KYD", 2, 136, versioned_key(136, 0)));
    case 82: return(currency("Tenge", "KZT", 2, 398, versioned_key(398, 0)));
    case 83: return(currency("Kip", "LAK", 0, 418, versioned_key(418, 0)));
    case 84: return(currency("Lebanese pound", "LBP", 0, 422, versioned_key(422, 0)));
    case 85: return(currency("Sri Lanka rupee", "LKR", 2, 144, versioned_key(144, 0)));
    case 86: return(currency("Liberian dollar", "LRD", 2, 430, versioned_key(430, 0)));
    case 87: return(currency("Lesotho loti", "LSL", 2, 426, versioned_key(426, 0)));
    case 88: return(currency("Lithuanian litas", "LTL", 2, 440, versioned_key(440, 0)));
    case 89: return(currency("Latvian lats", "LVL", 2, 428, versioned_key(428, 0)));
    case 90: return(currency("Libyan dinar", "LYD", 3, 434, versioned_key(434, 0)));
    case 91: return(currency("Moroccan dirham", "MAD", 2, 504, versioned_key(504, 0)));
    case 92: return(currency("Moldovan leu", "MDL", 2, 498, versioned_key(498, 0)));
    case 93: return(currency("Malagasy ariary", "MGA", 0, 969, versioned_key(969, 0))); // FIXME: 0.7
    case 94: return(currency("Denar", "MKD", 2, 807, versioned_key(807, 0)));
    case 95: return(currency("Kyat", "MMK", 0, 104, versioned_key(104, 0)));
    case 96: return(currency("Tugrik", "MNT", 2, 496, versioned_key(496, 0)));
    case 97: return(currency("Pataca", "MOP", 1, 446, versioned_key(446, 0)));
    case 98: return(currency("Ouguiya", "MRO", 0, 478, versioned_key(478, 0))); // FIXME: 0.7
    case 99: return(currency("Mauritius rupee", "MUR", 2, 480, versioned_key(480, 0)));
    case 100: return(currency("Rufiyaa", "MVR", 2, 462, versioned_key(462, 0)));
    case 101: return(currency("Kwacha", "MWK", 2, 454, versioned_key(454, 0)));
    case 102: return(currency("Mexican peso", "MXN", 2, 484, versioned_key(484, 0)));
    case 103: return(currency("Mexican Unidad de Inversion (UDI) (funds code)", "MXV", 2, 979, versioned_key(979, 0)));
    case 104: return(currency("Malaysian ringgit", "MYR", 2, 458, versioned_key(458, 0)));
    case 105: return(currency("Metical", "MZN", 2, 943, versioned_key(943, 0)));
    case 106: return(currency("Namibian dollar", "NAD", 2, 516, versioned_key(516, 0)));
    case 107: return(currency("Naira", "NGN", 2, 566, versioned_key(566, 0)));
    case 108: return(currency("Cordoba oro", "NIO", 2, 558, versioned_key(558, 0)));
    case 109: return(currency("Norwegian krone", "NOK", 2, 578, versioned_key(578, 0)));
    case 110: return(currency("Nepalese rupee", "NPR", 2, 524, versioned_key(524, 0)));
    case 111: return(currency("New Zealand dollar", "NZD", 2, 554, versioned_key(554, 0)));
    case 112: return(currency("Rial Omani", "OMR", 3, 512, versioned_key(512, 0)));
    case 113: return(currency("Balboa", "PAB", 2, 590, versioned_key(590, 0)));
    case 114: return(currency("Nuevo sol", "PEN", 2, 604, versioned_key(604, 0)));
    case 115: return(currency("Kina", "PGK", 2, 598, versioned_key(598, 0)));
    case 116: return(currency("Philippine peso", "PHP", 2, 608, versioned_key(608, 0)));
    case 117: return(currency("Pakistan rupee", "PKR", 2, 586, versioned_key(586, 0)));
    case 118: return(currency("Złoty", "PLN", 2, 985, versioned_key(985, 0)));
    case 119: return(currency("Guarani", "PYG", 0, 600, versioned_key(600, 0)));
    case 120: return(currency("Qatari rial", "QAR", 2, 634, versioned_key(634, 0)));
    case 121: return(currency("Romanian new leu", "RON", 2, 946, versioned_key(946, 0)));
    case 122: return(currency("Serbian dinar", "RSD", 2, 941, versioned_key(941, 0)));
    case 123: return(currency("Russian rouble", "RUB", 2, 643, versioned_key(643, 0)));
    case 124: return(currency("Rwanda franc", "RWF", 0, 646, versioned_key(646, 0)));
    case 125: return(currency("Saudi riyal", "SAR", 2, 682, versioned_key(682, 0)));
    case 126: return(currency("Solomon Islands dollar", "SBD", 2, 90, versioned_key(90, 0)));
    case 127: return(currency("Seychelles rupee", "SCR", 2, 690, versioned_key(690, 0)));
    case 128: return(currency("Sudanese pound", "SDG", 2, 938, versioned_key(938, 0)));
    case 129: return(currency("Swedish krona/kronor", "SEK", 2, 752, versioned_key(752, 0)));
    case 130: return(currency("Singapore dollar", "SGD", 2, 702, versioned_key(702, 0)));
    case 131: return(currency("Saint Helena pound", "SHP", 2, 654, versioned_key(654, 0)));
    case 132: return(currency("Leone", "SLL", 0, 694, versioned_key(694, 0)));
    case 133: return(currency("Somali shilling", "SOS", 2, 706, versioned_key(706, 0)));
    case 134: return(currency("Surinam dollar", "SRD", 2, 968, versioned_key(968, 0)));
    case 135: return(currency("Dobra", "STD", 0, 678, versioned_key(678, 0)));
    case 136: return(currency("Syrian pound", "SYP", 2, 760, versioned_key(760, 0)));
    case 137: return(currency("Lilangeni", "SZL", 2, 748, versioned_key(748, 0)));
    case 138: return(currency("Baht", "THB", 2, 764, versioned_key(764, 0)));
    case 139: return(currency("Somoni", "TJS", 2, 972, versioned_key(972, 0)));
    case 140: return(currency("Manat", "TMT", 2, 934, versioned_key(934, 0)));
    case 141: return(currency("Tunisian dinar", "TND", 3, 788, versioned_key(788, 0)));
    case 142: return(currency("Pa'anga", "TOP", 2, 776, versioned_key(776, 0)));
    case 143: return(currency("Turkish lira", "TRY", 2, 949, versioned_key(949, 0)));
    case 144: return(currency("Trinidad and Tobago dollar", "TTD", 2, 780, versioned_key(780, 0)));
    case 145: return(currency("New Taiwan dollar", "TWD", 1, 901, versioned_key(901, 0)));
    case 146: return(currency("Tanzanian shilling", "TZS", 2, 834, versioned_key(834, 0)));
    case 147: return(currency("Hryvnia", "UAH", 2, 980, versioned_key(980, 0)));
    case 148: return(currency("Uganda shilling", "UGX", 0, 800, versioned_key(800, 0)));
    case 149: return(currency("US dollar", "USD", 2, 840, versioned_key(840, 0)));
    case 150: return(currency("United States dollar (next day) (funds code)", "USN", 2, 997, versioned_key(997, 0)));
    case 151: return(currency("United States dollar (same day) (funds code) (one source[who?] claims it is no longer used, but it is still on the ISO 4217-MA list)", "USS", 2, 998, versioned_key(998, 0)));
    case 152: return(currency("Peso Uruguayo", "UYU", 2, 858, versioned_key(858, 0)));
    case 153: return(currency("Uzbekistan som", "UZS", 2, 860, versioned_key(860, 0)));
    case 154: return(currency("Venezuelan bolívar fuerte", "VEF", 2, 937, versioned_key(937, 0)));
    case 155: return(currency("Vietnamese đồng", "VND", 0, 704, versioned_key(704, 0)));
    case 156: return(currency("Vatu", "VUV", 0, 548, versioned_key(548, 0)));
    case 157: return(currency("Samoan tala", "WST", 2, 882, versioned_key(882, 0)));
    case 158: return(currency("CFA franc BEAC", "XAF", 0, 950, versioned_key(950, 0)));
    case 159: return(currency("Silver (one troy ounce)", "XAG", 0, 961, versioned_key(961, 0)));
    case 160: return(currency("Gold (one troy ounce)", "XAU", 0, 959, versioned_key(959, 0)));
    case 161: return(currency("European Composite Unit (EURCO) (bond market unit)", "XBA", 0, 955, versioned_key(955, 0)));
    case 162: return(currency("European Monetary Unit (E.M.U.-6) (bond market unit)", "XBB", 0, 956, versioned_key(956, 0)));
    case 163: return(currency("European Unit of Account 9 (E.U.A.-9) (bond market unit)", "XBC", 0, 957, versioned_key(957, 0)));
    case 164: return(currency("European Unit of Account 17 (E.U.A.-17) (bond market unit)", "XBD", 0, 958, versioned_key(958, 0)));
    case 165: return(currency("East Caribbean dollar", "XCD", 2, 951, versioned_key(951, 0)));
    case 166: return(currency("Special Drawing Rights", "XDR", 0, 960, versioned_key(960, 0)));
    case 167: return(currency("UIC franc (special settlement currency)", "XFU", 0, 0, versioned_key(0, 0)));
    case 168: return(currency("CFA Franc BCEAO", "XOF", 0, 952, versioned_key(952, 0)));
    case 169: return(currency("Palladium (one troy ounce)", "XPD", 0, 964, versioned_key(964, 0)));
    case 170: return(currency("CFP franc", "XPF", 0, 953, versioned_key(953, 0)));
    case 171: return(currency("Platinum (one troy ounce)", "XPT", 0, 962, versioned_key(962, 0)));
    case 172: return(currency("Code reserved for testing purposes", "XTS", 0, 963, versioned_key(963, 0)));
    case 173: return(currency("No currency", "XXX", 0, 999, versioned_key(999, 0)));
    case 174: return(currency("Yemeni rial", "YER", 0, 886, versioned_key(886, 0)));
    case 175: return(currency("South African rand", "ZAR", 2, 710, versioned_key(710, 0)));
    case 176: return(currency("Kwacha", "ZMK", 0, 894, versioned_key(894, 0)));
    case 177: return(currency("Zimbabwe dollar", "ZWL", 2, 932, versioned_key(932, 0)));
    default:
        // keep gcc happy
        BOOST_THROW_EXCEPTION(
            dogen::utility::test_data::sequence_exhausted());
    }
}

majors_currency_generator::value_type
majors_currency_generator::next_term(const unsigned int position) {
    const dogen::prototype::versioned_key vk;

    using dogen::prototype::currency;
    switch(position) {
    case 0: return(currency("US dollar", "USD", 2, 840, versioned_key(840, 0)));
    case 1: return(currency("euro", "EUR", 2, 978, versioned_key(978, 0)));
    case 2: return(currency("Japanese yen", "JPY", 0, 392, versioned_key(392, 0)));
    case 3: return(currency("Pound sterling", "GBP", 2, 826, versioned_key(826, 0)));
    case 4: return(currency("Swiss franc", "CHF", 2, 756, versioned_key(756, 0)));
    case 5: return(currency("Canadian dollar", "CAD", 2, 124, versioned_key(124, 0)));
    case 6: return(currency("Australian dollar", "AUD", 2, 36, versioned_key(36, 0)));
    case 7: return(currency("Hong Kong dollar", "HKD", 2, 344, versioned_key(344, 0)));
    default:
        // keep gcc happy
        BOOST_THROW_EXCEPTION(
            dogen::utility::test_data::sequence_exhausted());
    }
}

unrealistic_currency_generator::value_type
unrealistic_currency_generator::next_term(const unsigned int position) {
    unsigned int iterator(position);
    const unsigned int base(26);
    unsigned int remainder;

    // convert position to a base 26 number.
    std::ostringstream stream;
    unsigned int missing_digits(3);
    while (iterator > 0) {
        remainder = iterator % base;
        iterator = iterator / base;
        stream << ((char)(remainder + 65));
        --missing_digits;
    }

    // add leading A's to make up a three letter code.
    const std::string prefix(missing_digits, 'A');
    std::string code(prefix + stream.str());

    const std::string name("test_currency_" +
                           boost::lexical_cast<std::string>(position));

    const dogen::prototype::versioned_key vk;
    return(dogen::prototype::currency(name, code, 2, position, versioned_key(position, 0)));
}

} } }
