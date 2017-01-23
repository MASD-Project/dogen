using System;

namespace Zeta
{
    /// <summary>
    /// Generates sequences of ExternalModelTest.
    /// </summary>
    public static class ExternalModelTestDumper
    {
        static internal void Dump(AssistantDumper assistant, ExternalModelTest value, bool withSeparator = false)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("Zeta.ExternalModelTest", true/*withSeparator*/);
            if (value == null)
            {
                assistant.Add("data", "<null>");
                assistant.AddEndObject();
                return;
            }

            assistant.AddKey("data");
            assistant.AddPairSeparator();
            assistant.AddStartObject();
            assistant.AddKey("DateTest");
            assistant.AddPairSeparator();
            Phi.DateDumper.Dump(assistant, value.DateTest, true/*withSeparator*/);
            assistant.AddKey("BinariesTest");
            assistant.AddPairSeparator();
            System.Collections.Generic.ListDumper.Dump(assistant, value.BinariesTest, true/*withSeparator*/);
            assistant.AddKey("CollectionOfCollectionTest");
            assistant.AddPairSeparator();
            System.Collections.Generic.ListDumper.Dump(assistant, value.CollectionOfCollectionTest, true/*withSeparator*/);
            assistant.AddKey("CollectionOfCollectionOfCollectionTest");
            assistant.AddPairSeparator();
            System.Collections.Generic.ListDumper.Dump(assistant, value.CollectionOfCollectionOfCollectionTest);
            assistant.AddEndObject(); // data
            assistant.AddEndObject(); // main object
            assistant.HandleMemberSeparator(withSeparator);

            assistant.DecrementDepth();
        }

        public static string Dump(ExternalModelTest value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.ToString();
        }
    }
}
