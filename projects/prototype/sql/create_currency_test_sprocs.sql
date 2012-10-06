/* -*- sql-product: postgres; tab-width: 4; indent-tabs-mode: nil -*-
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
set client_min_messages = ERROR;

/**
 * @brief Create all countries defined in ISO 4217.
 */
create or replace function kitanda.test_currency_complete_generator()
returns void as
$body$
begin
    perform kitanda.currency_save(784, 'United Arab Emirates dirham', 'AED', 2, 0);
    perform kitanda.currency_save(971, 'Afghani', 'AFN', 2, 0);
    perform kitanda.currency_save(8, 'Lek', 'ALL', 2, 0);
    perform kitanda.currency_save(51, 'Armenian dram', 'AMD', 0, 0);
    perform kitanda.currency_save(532, 'Netherlands Antillean guilder', 'ANG', 2, 0);
    perform kitanda.currency_save(973, 'Kwanza', 'AOA', 1, 0);
    perform kitanda.currency_save(32, 'Argentine peso', 'ARS', 2, 0);
    perform kitanda.currency_save(36, 'Australian dollar', 'AUD', 2, 0);
    perform kitanda.currency_save(533, 'Aruban guilder', 'AWG', 2, 0);
    perform kitanda.currency_save(944, 'Azerbaijanian manat', 'AZN', 2, 0);
    perform kitanda.currency_save(977, 'Convertible marks', 'BAM', 2, 0);
    perform kitanda.currency_save(52, 'Barbados dollar', 'BBD', 2, 0);
    perform kitanda.currency_save(50, 'Bangladeshi taka', 'BDT', 2, 0);
    perform kitanda.currency_save(975, 'Bulgarian lev', 'BGN', 2, 0);
    perform kitanda.currency_save(48, 'Bahraini dinar', 'BHD', 3, 0);
    perform kitanda.currency_save(108, 'Burundian franc', 'BIF', 0, 0);
    perform kitanda.currency_save(60, 'Bermudian dollar (customarily known as Bermuda dollar)', 'BMD', 2, 0);
    perform kitanda.currency_save(96, 'Brunei dollar', 'BND', 2, 0);
    perform kitanda.currency_save(68, 'Boliviano', 'BOB', 2, 0);
    perform kitanda.currency_save(984, 'Bolivian Mvdol (funds code)', 'BOV', 2, 0);
    perform kitanda.currency_save(986, 'Brazilian real', 'BRL', 2, 0);
    perform kitanda.currency_save(44, 'Bahamian dollar', 'BSD', 2, 0);
    perform kitanda.currency_save(64, 'Ngultrum', 'BTN', 2, 0);
    perform kitanda.currency_save(72, 'Pula', 'BWP', 2, 0);
    perform kitanda.currency_save(974, 'Belarusian ruble', 'BYR', 0, 0);
    perform kitanda.currency_save(84, 'Belize dollar', 'BZD', 2, 0);
    perform kitanda.currency_save(124, 'Canadian dollar', 'CAD', 2, 0);
    perform kitanda.currency_save(976, 'Franc Congolais', 'CDF', 2, 0);
    perform kitanda.currency_save(947, 'WIR euro (complementary currency)', 'CHE', 2, 0);
    perform kitanda.currency_save(756, 'Swiss franc', 'CHF', 2, 0);
    perform kitanda.currency_save(948, 'WIR franc (complementary currency)', 'CHW', 2, 0);
    perform kitanda.currency_save(990, 'Unidad de Fomento (funds code)', 'CLF', 0, 0);
    perform kitanda.currency_save(152, 'Chilean peso', 'CLP', 0, 0);
    perform kitanda.currency_save(156, 'Chinese Yuan', 'CNY', 1, 0);
    perform kitanda.currency_save(170, 'Colombian peso', 'COP', 0, 0);
    perform kitanda.currency_save(970, 'Unidad de Valor Real', 'COU', 2, 0);
    perform kitanda.currency_save(188, 'Costa Rican colon', 'CRC', 2, 0);
    perform kitanda.currency_save(931, 'Cuban convertible peso', 'CUC', 2, 0);
    perform kitanda.currency_save(192, 'Cuban peso', 'CUP', 2, 0);
    perform kitanda.currency_save(132, 'Cape Verde escudo', 'CVE', 2, 0);
    perform kitanda.currency_save(203, 'Czech Koruna', 'CZK', 2, 0);
    perform kitanda.currency_save(262, 'Djibouti franc', 'DJF', 0, 0);
    perform kitanda.currency_save(208, 'Danish krone', 'DKK', 2, 0);
    perform kitanda.currency_save(214, 'Dominican peso', 'DOP', 2, 0);
    perform kitanda.currency_save(12, 'Algerian dinar', 'DZD', 2, 0);
    perform kitanda.currency_save(233, 'Kroon', 'EEK', 2, 0);
    perform kitanda.currency_save(818, 'Egyptian pound', 'EGP', 2, 0);
    perform kitanda.currency_save(232, 'Nakfa', 'ERN', 2, 0);
    perform kitanda.currency_save(230, 'Ethiopian birr', 'ETB', 2, 0);
    perform kitanda.currency_save(978, 'euro', 'EUR', 2, 0);
    perform kitanda.currency_save(242, 'Fiji dollar', 'FJD', 2, 0);
    perform kitanda.currency_save(238, 'Falkland Islands pound', 'FKP', 2, 0);
    perform kitanda.currency_save(826, 'Pound sterling', 'GBP', 2, 0);
    perform kitanda.currency_save(981, 'Lari', 'GEL', 2, 0);
    perform kitanda.currency_save(936, 'Cedi', 'GHS', 2, 0);
    perform kitanda.currency_save(292, 'Gibraltar pound', 'GIP', 2, 0);
    perform kitanda.currency_save(270, 'Dalasi', 'GMD', 2, 0);
    perform kitanda.currency_save(324, 'Guinea franc', 'GNF', 0, 0);
    perform kitanda.currency_save(320, 'Quetzal', 'GTQ', 2, 0);
    perform kitanda.currency_save(328, 'Guyana dollar', 'GYD', 2, 0);
    perform kitanda.currency_save(344, 'Hong Kong dollar', 'HKD', 2, 0);
    perform kitanda.currency_save(340, 'Lempira', 'HNL', 2, 0);
    perform kitanda.currency_save(191, 'Croatian kuna', 'HRK', 2, 0);
    perform kitanda.currency_save(332, 'Haiti gourde', 'HTG', 2, 0);
    perform kitanda.currency_save(348, 'Forint', 'HUF', 2, 0);
    perform kitanda.currency_save(360, 'Rupiah', 'IDR', 0, 0);
    perform kitanda.currency_save(376, 'Israeli new sheqel', 'ILS', 2, 0);
    perform kitanda.currency_save(356, 'Indian rupee', 'INR', 2, 0);
    perform kitanda.currency_save(368, 'Iraqi dinar', 'IQD', 0, 0);
    perform kitanda.currency_save(364, 'Iranian rial', 'IRR', 0, 0);
    perform kitanda.currency_save(352, 'Iceland krona', 'ISK', 0, 0);
    perform kitanda.currency_save(388, 'Jamaican dollar', 'JMD', 2, 0);
    perform kitanda.currency_save(400, 'Jordanian dinar', 'JOD', 3, 0);
    perform kitanda.currency_save(392, 'Japanese yen', 'JPY', 0, 0);
    perform kitanda.currency_save(404, 'Kenyan shilling', 'KES', 2, 0);
    perform kitanda.currency_save(417, 'Som', 'KGS', 2, 0);
    perform kitanda.currency_save(116, 'Riel', 'KHR', 0, 0);
    perform kitanda.currency_save(174, 'Comoro franc', 'KMF', 0, 0);
    perform kitanda.currency_save(408, 'North Korean won', 'KPW', 0, 0);
    perform kitanda.currency_save(410, 'South Korean won', 'KRW', 0, 0);
    perform kitanda.currency_save(414, 'Kuwaiti dinar', 'KWD', 3, 0);
    perform kitanda.currency_save(136, 'Cayman Islands dollar', 'KYD', 2, 0);
    perform kitanda.currency_save(398, 'Tenge', 'KZT', 2, 0);
    perform kitanda.currency_save(418, 'Kip', 'LAK', 0, 0);
    perform kitanda.currency_save(422, 'Lebanese pound', 'LBP', 0, 0);
    perform kitanda.currency_save(144, 'Sri Lanka rupee', 'LKR', 2, 0);
    perform kitanda.currency_save(430, 'Liberian dollar', 'LRD', 2, 0);
    perform kitanda.currency_save(426, 'Lesotho loti', 'LSL', 2, 0);
    perform kitanda.currency_save(440, 'Lithuanian litas', 'LTL', 2, 0);
    perform kitanda.currency_save(428, 'Latvian lats', 'LVL', 2, 0);
    perform kitanda.currency_save(434, 'Libyan dinar', 'LYD', 3, 0);
    perform kitanda.currency_save(504, 'Moroccan dirham', 'MAD', 2, 0);
    perform kitanda.currency_save(498, 'Moldovan leu', 'MDL', 2, 0);
    perform kitanda.currency_save(969, 'Malagasy ariary', 'MGA', 0, 0);
    perform kitanda.currency_save(807, 'Denar', 'MKD', 2, 0);
    perform kitanda.currency_save(104, 'Kyat', 'MMK', 0, 0);
    perform kitanda.currency_save(496, 'Tugrik', 'MNT', 2, 0);
    perform kitanda.currency_save(446, 'Pataca', 'MOP', 1, 0);
    perform kitanda.currency_save(478, 'Ouguiya', 'MRO', 0, 0);
    perform kitanda.currency_save(480, 'Mauritius rupee', 'MUR', 2, 0);
    perform kitanda.currency_save(462, 'Rufiyaa', 'MVR', 2, 0);
    perform kitanda.currency_save(454, 'Kwacha', 'MWK', 2, 0);
    perform kitanda.currency_save(484, 'Mexican peso', 'MXN', 2, 0);
    perform kitanda.currency_save(979, 'Mexican Unidad de Inversion (UDI) (funds code)', 'MXV', 2, 0);
    perform kitanda.currency_save(458, 'Malaysian ringgit', 'MYR', 2, 0);
    perform kitanda.currency_save(943, 'Metical', 'MZN', 2, 0);
    perform kitanda.currency_save(516, 'Namibian dollar', 'NAD', 2, 0);
    perform kitanda.currency_save(566, 'Naira', 'NGN', 2, 0);
    perform kitanda.currency_save(558, 'Cordoba oro', 'NIO', 2, 0);
    perform kitanda.currency_save(578, 'Norwegian krone', 'NOK', 2, 0);
    perform kitanda.currency_save(524, 'Nepalese rupee', 'NPR', 2, 0);
    perform kitanda.currency_save(554, 'New Zealand dollar', 'NZD', 2, 0);
    perform kitanda.currency_save(512, 'Rial Omani', 'OMR', 3, 0);
    perform kitanda.currency_save(590, 'Balboa', 'PAB', 2, 0);
    perform kitanda.currency_save(604, 'Nuevo sol', 'PEN', 2, 0);
    perform kitanda.currency_save(598, 'Kina', 'PGK', 2, 0);
    perform kitanda.currency_save(608, 'Philippine peso', 'PHP', 2, 0);
    perform kitanda.currency_save(586, 'Pakistan rupee', 'PKR', 2, 0);
    perform kitanda.currency_save(985, 'Złoty', 'PLN', 2, 0);
    perform kitanda.currency_save(600, 'Guarani', 'PYG', 0, 0);
    perform kitanda.currency_save(634, 'Qatari rial', 'QAR', 2, 0);
    perform kitanda.currency_save(946, 'Romanian new leu', 'RON', 2, 0);
    perform kitanda.currency_save(941, 'Serbian dinar', 'RSD', 2, 0);
    perform kitanda.currency_save(643, 'Russian rouble', 'RUB', 2, 0);
    perform kitanda.currency_save(646, 'Rwanda franc', 'RWF', 0, 0);
    perform kitanda.currency_save(682, 'Saudi riyal', 'SAR', 2, 0);
    perform kitanda.currency_save(90, 'Solomon Islands dollar', 'SBD', 2, 0);
    perform kitanda.currency_save(690, 'Seychelles rupee', 'SCR', 2, 0);
    perform kitanda.currency_save(938, 'Sudanese pound', 'SDG', 2, 0);
    perform kitanda.currency_save(752, 'Swedish krona/kronor', 'SEK', 2, 0);
    perform kitanda.currency_save(702, 'Singapore dollar', 'SGD', 2, 0);
    perform kitanda.currency_save(654, 'Saint Helena pound', 'SHP', 2, 0);
    perform kitanda.currency_save(694, 'Leone', 'SLL', 0, 0);
    perform kitanda.currency_save(706, 'Somali shilling', 'SOS', 2, 0);
    perform kitanda.currency_save(968, 'Surinam dollar', 'SRD', 2, 0);
    perform kitanda.currency_save(678, 'Dobra', 'STD', 0, 0);
    perform kitanda.currency_save(760, 'Syrian pound', 'SYP', 2, 0);
    perform kitanda.currency_save(748, 'Lilangeni', 'SZL', 2, 0);
    perform kitanda.currency_save(764, 'Baht', 'THB', 2, 0);
    perform kitanda.currency_save(972, 'Somoni', 'TJS', 2, 0);
    perform kitanda.currency_save(934, 'Manat', 'TMT', 2, 0);
    perform kitanda.currency_save(788, 'Tunisian dinar', 'TND', 3, 0);
    perform kitanda.currency_save(776, 'Pa''anga', 'TOP', 2, 0);
    perform kitanda.currency_save(949, 'Turkish lira', 'TRY', 2, 0);
    perform kitanda.currency_save(780, 'Trinidad and Tobago dollar', 'TTD', 2, 0);
    perform kitanda.currency_save(901, 'New Taiwan dollar', 'TWD', 1, 0);
    perform kitanda.currency_save(834, 'Tanzanian shilling', 'TZS', 2, 0);
    perform kitanda.currency_save(980, 'Hryvnia', 'UAH', 2, 0);
    perform kitanda.currency_save(800, 'Uganda shilling', 'UGX', 0, 0);
    perform kitanda.currency_save(840, 'US dollar', 'USD', 2, 0);
    perform kitanda.currency_save(997, 'United States dollar (next day) (funds code)', 'USN', 2, 0);
    perform kitanda.currency_save(998, 'United States dollar (same day) (funds code)', 'USS', 2, 0);
    perform kitanda.currency_save(858, 'Peso Uruguayo', 'UYU', 2, 0);
    perform kitanda.currency_save(860, 'Uzbekistan som', 'UZS', 2, 0);
    perform kitanda.currency_save(937, 'Venezuelan bolívar fuerte', 'VEF', 2, 0);
    perform kitanda.currency_save(704, 'Vietnamese đồng', 'VND', 0, 0);
    perform kitanda.currency_save(548, 'Vatu', 'VUV', 0, 0);
    perform kitanda.currency_save(882, 'Samoan tala', 'WST', 2, 0);
    perform kitanda.currency_save(950, 'CFA franc BEAC', 'XAF', 0, 0);
    perform kitanda.currency_save(961, 'Silver (one troy ounce)', 'XAG', 0, 0);
    perform kitanda.currency_save(959, 'Gold (one troy ounce)', 'XAU', 0, 0);
    perform kitanda.currency_save(955, 'European Composite Unit (EURCO) (bond market unit)', 'XBA', 0, 0);
    perform kitanda.currency_save(956, 'European Monetary Unit (E.M.U.-6) (bond market unit)', 'XBB', 0, 0);
    perform kitanda.currency_save(957, 'European Unit of Account 9 (E.U.A.-9) (bond market unit)', 'XBC', 0, 0);
    perform kitanda.currency_save(958, 'European Unit of Account 17 (E.U.A.-17) (bond market unit)', 'XBD', 0, 0);
    perform kitanda.currency_save(951, 'East Caribbean dollar', 'XCD', 2, 0);
    perform kitanda.currency_save(960, 'Special Drawing Rights', 'XDR', 0, 0);
    perform kitanda.currency_save(0, 'UIC franc (special settlement currency)', 'XFU', 0, 0);
    perform kitanda.currency_save(952, 'CFA Franc BCEAO', 'XOF', 0, 0);
    perform kitanda.currency_save(964, 'Palladium (one troy ounce)', 'XPD', 0, 0);
    perform kitanda.currency_save(953, 'CFP franc', 'XPF', 0, 0);
    perform kitanda.currency_save(962, 'Platinum (one troy ounce)', 'XPT', 0, 0);
    perform kitanda.currency_save(963, 'Code reserved for testing purposes', 'XTS', 0, 0);
    perform kitanda.currency_save(999, 'No currency', 'XXX', 0, 0);
    perform kitanda.currency_save(886, 'Yemeni rial', 'YER', 0, 0);
    perform kitanda.currency_save(710, 'South African rand', 'ZAR', 2, 0);
    perform kitanda.currency_save(894, 'Kwacha', 'ZMK', 0, 0);
    perform kitanda.currency_save(932, 'Zimbabwe dollar', 'ZWL', 2, 0);
end
$body$
language 'plpgsql';

/**
 * @brief Create major countries.
 */
create or replace function kitanda.test_currency_majors_generator()
returns void as
$body$
begin
    perform kitanda.currency_save(840, 'US dollar', 'USD', 2, 0);
    perform kitanda.currency_save(978, 'euro', 'EUR', 2, 0);
    perform kitanda.currency_save(392, 'Japanese yen', 'JPY', 0, 0);
    perform kitanda.currency_save(826, 'Pound sterling', 'GBP', 2, 0);
    perform kitanda.currency_save(756, 'Swiss franc', 'CHF', 2, 0);
    perform kitanda.currency_save(124, 'Canadian dollar', 'CAD', 2, 0);
    perform kitanda.currency_save(36, 'Australian dollar', 'AUD', 2, 0);
    perform kitanda.currency_save(344, 'Hong Kong dollar', 'HKD', 2, 0);
end
$body$
language 'plpgsql';

/**
 * @brief Create "random" test data.
 */
create or replace function kitanda.test_currency_unrealistic_generator(number_of_rows int)
returns void as
$body$
declare
    currency_name_prefix kitanda.currency.name%type;
    currency_name kitanda.currency.name%type;
    alpha_code kitanda.currency.alpha_code%type;

    iterator int;
    remainder int;
    missing_digits int;
    max_value constant int := 26 * 26 * 26;
begin
    if number_of_rows >= max_value then
        raise exception 'The requested number of rows (%) is greater than allowed (%).',
            number_of_rows, max_value;
    end if;

    currency_name_prefix := 'TEST_DATA_';
    for i in 0 .. number_of_rows loop
        currency_name := currency_name_prefix || i;

        missing_digits := 3;
        iterator := i;
        alpha_code := '';
        while iterator > 0 loop
            remainder := iterator % 26;
            iterator := iterator / 26;
            alpha_code := chr(remainder + 65) || alpha_code;
            missing_digits := missing_digits - 1;
        end loop;

        while missing_digits > 0 loop
            alpha_code := chr(65) || alpha_code;
            missing_digits := missing_digits - 1;
        end loop;
        perform kitanda.currency_save(i, currency_name, alpha_code, 2, 0);
    end loop;
end
$body$
language 'plpgsql';

/**
 * @brief Unit Test currency's sprocs.
 *
 * NOTE: all rows in currency table will be deleted by running
 * NOTE: this test.
 */
create or replace function kitanda.test_currency()
returns void as
$body$
declare
    exception_flag boolean := false;
    number_of_records int;
    euro kitanda.currency%rowtype;
    number_of_currencies_in_iso_4217 constant int := 178;
    euro_numeric_code constant int := 978;
begin
    raise notice 'test_currency: starting test run.';

    --
    -- create all the required test data
    --
    delete from kitanda.currency;
    perform kitanda.test_currency_complete_generator();

    --
    -- test currency_save
    --
    select into number_of_records count(1) from kitanda.currency;
    if (number_of_records != number_of_currencies_in_iso_4217) then
        raise exception 'currency_save: failed to create all currencies.';
    end if;

    select into number_of_records count(1)
    from kitanda.currency
    where numeric_code = euro_numeric_code and name = 'euro' and
        alpha_code = 'EUR' and decimal_places = 2 and
        snapshot = 1 and latest = true;

    if (number_of_records != 1) then
       raise exception 'currency_save: failed to create EUR correctly.';
    end if;

    -- save multiple versions
    perform kitanda.currency_save(978, 'euro', 'EUR', 2, 1);
    perform kitanda.currency_save(978, 'euro', 'EUR', 2, 2);
    begin
        perform kitanda.currency_save(978, 'euro', 'EUR', 2, 2);
    exception
        when raise_exception then
            exception_flag := true;
            raise notice 'currency_save: correctly failed to save duplicate.';
    end;

    if exception_flag = false then
        raise notice 'currency_save: failed to detect duplicate save.';
    end if;

    --
    -- test currency_load
    --

    -- although we have two extra entries for EUR, the total
    -- number should not change.
    select into number_of_records count(1) from kitanda.currency_load(null);
    if (number_of_records != number_of_currencies_in_iso_4217) then
        raise exception 'currency_load: did not load the expected currencies.';
    end if;

    select into number_of_records count(1)
    from kitanda.currency_load(euro_numeric_code)
    where numeric_code = euro_numeric_code and name = 'euro' and
        alpha_code = 'EUR' and decimal_places = 2;

    if (number_of_records != 1) then
       raise exception 'currency_load: failed to load EUR correctly.';
    end if;

    --
    -- test currency_delete
    --

    -- delete non-existent currency.
    perform kitanda.currency_delete(1000);

    select into number_of_records count(1) from kitanda.currency;
    -- take into account the two new EUR versions
    if (number_of_records != (number_of_currencies_in_iso_4217 + 2)) then
        raise exception 'currency_delete: error deleting nonexistent record.';
    end if;

    -- delete existing currency
    perform kitanda.currency_delete(euro_numeric_code);

    select into number_of_records count(1)
    from kitanda.currency_load(euro_numeric_code)
    where numeric_code = euro_numeric_code and name = 'euro' and
        alpha_code = 'EUR' and decimal_places = 2 and
        snapshot = 1 and latest = true;

    if (number_of_records != 0) then
       raise exception 'currency_delete: failed to delete EUR correctly.';
    end if;

    -- delete all existing currencies
    perform kitanda.currency_delete(null);

    select into number_of_records count(1) from kitanda.currency_load(null);
    if (number_of_records != 0) then
       raise exception 'currency_delete: failed to delete all currencies correctly.';
    end if;

    raise notice 'test_currency: all tests passed.';
    return;
end
$body$
language 'plpgsql';
