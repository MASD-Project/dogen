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

namespace Dogen.TestModels.CSharpModel.Tests
{
    [TestFixture]
    class TypesTests
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof(TypesTests));
        private static readonly string FixtureName = typeof(TypesTests).Name;

        static LogConfigurator LogConfigurator
        {
            get
            {
                return new LogConfigurator(FixtureName);
            }
        }

        [Test]
        public void GeneratingComplexBuiltinsResultsInExpectedDump()
        {
            using (var lc = LogConfigurator)
            {
                var seq = ComplexBuiltinsSequenceGenerator.Sequence();
                var c = seq.GetEnumerator().Current;
                Log.DebugFormat("JSON: {0}", ComplexBuiltinsDumper.Dump(c));
            }
        }

        [Test]
        public void GeneratingPrimitiveBuiltinsResultsInExpectedDump()
        {
            using (var lc = LogConfigurator)
            {
                var seq = PrimitiveBuiltinsSequenceGenerator.Sequence();
                var c = seq.GetEnumerator().Current;
                Log.DebugFormat("JSON: {0}", PrimitiveBuiltinsDumper.Dump(c));
            }
        }

        [Test]
        public void GeneratingOnePropertyResultsInExpectedDump()
        {
            using (var lc = LogConfigurator)
            {
                var seq = OnePropertySequenceGenerator.Sequence();
                var c = seq.GetEnumerator().Current;
                Log.DebugFormat("JSON: {0}", OnePropertyDumper.Dump(c));
            }
        }

        [Test]
        public void GeneratingNoPropertiesResultsInExpectedDump()
        {
            using (var lc = LogConfigurator)
            {
                var seq = NoPropertiesSequenceGenerator.Sequence();
                var c = seq.GetEnumerator().Current;
                Log.DebugFormat("JSON: {0}", NoPropertiesDumper.Dump(c));
            }
        }
    }
}
