using System;

namespace Phi
{
    /// <summary>
    /// Generates sequences of CollectionTestType.
    /// </summary>
    public static class CollectionTestTypeDumper
    {
        static internal void Dump(AssistantDumper assistant, CollectionTestType value, bool withSeparator = false)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("Phi.CollectionTestType", true/*withSeparator*/);
            if (value == null)
            {
                assistant.Add("data", "<null>");
                assistant.AddEndObject();
                return;
            }

            assistant.AddKey("data");
            assistant.AddPairSeparator();
            assistant.AddStartObject();
            assistant.AddKey("BinariesTest");
            assistant.AddPairSeparator();
            System.Collections.Generic.ListDumper.Dump(assistant, value.BinariesTest);
            assistant.AddEndObject(); // data
            assistant.AddEndObject(); // main object
            assistant.HandleMemberSeparator(withSeparator);

            assistant.DecrementDepth();
        }

        public static string Dump(CollectionTestType value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.ToString();
        }
    }
}
