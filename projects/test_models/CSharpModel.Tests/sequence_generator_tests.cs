// -*- mode: csharp; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
//
// Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.
//
using log4net;
using NUnit.Framework;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;

namespace Dogen.TestModels.CSharpModel.Tests
{
    [TestFixture]
    // Analysis disable once InconsistentNaming
    public class sequence_generator_tests
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof(equality_tests));
        private static readonly string FixtureName = typeof(sequence_generator_tests).Name;

        static bool ValidateJson(string jsonString)
        {
            try
            {
                JToken.Parse(jsonString);
                return true;
            }
            catch (JsonReaderException ex)
            {
                Log.ErrorFormat("String is not valid JSON: {0}", ex);
                return false;
            }
        }

        [Test]
        // Analysis disable once InconsistentNaming
        public void sequence_dumper_produces_valid_json()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                var a = ComplexBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                var jsonA = ComplexBuiltinsDumper.Dump(a);
                Log.DebugFormat("JSON: {0}", jsonA);
                Assert.That(ValidateJson(jsonA), Is.True);

                var b = PrimitiveBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                var jsonB = PrimitiveBuiltinsDumper.Dump(b);
                Log.DebugFormat("JSON: {0}", jsonB);
                Assert.That(ValidateJson(jsonB), Is.True);

                var c = OnePropertySequenceGenerator.Sequence().GetEnumerator().Current;
                var jsonC = OnePropertyDumper.Dump(c);
                Log.DebugFormat("JSON: {0}", jsonC);
                Assert.That(ValidateJson(jsonC), Is.True);

                var d = NoPropertiesSequenceGenerator.Sequence().GetEnumerator().Current;
                var jsonD = NoPropertiesDumper.Dump(d);
                Log.DebugFormat("JSON: {0}", jsonD);
                Assert.That(ValidateJson(jsonD), Is.True);

                var en = BookTypesSequenceGenerator.Sequence().GetEnumerator();
                var e = en.Current;
                var jsonE = BookTypesDumper.Dump(e);
                Log.DebugFormat("JSON: {0}", jsonE);
                Assert.That(ValidateJson(jsonE), Is.True);

                en.MoveNext();
                e = en.Current;
                jsonE = BookTypesDumper.Dump(e);
                Log.DebugFormat("JSON: {0}", jsonE);
                Assert.That(ValidateJson(jsonE), Is.True);
            }
        }
    }
}
