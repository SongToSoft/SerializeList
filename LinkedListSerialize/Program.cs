using System;
using System.IO;

namespace LinkedListSerialize
{
  class Program
  {
    static private string path = "serializedList.txt";

    static void Main(string[] args)
    {
      ListRand list = new ListRand();
      list.Add("first");
      list.Add("second");
      list.Add("third");
      list.Add("fourth");
      list.Add("fifth");
      list.AddRandomLink(0, 3);
      list.AddRandomLink(1, 1);
      list.AddRandomLink(2, 4);
      list.Print();

      using (StreamWriter writer = new StreamWriter(path, false))
      {
        list.Serialize(writer);
      }

      ListRand newList = new ListRand();
      using (StreamReader reader = new StreamReader(path))
      {
        newList.Deserialize(reader);
      }
      newList.Print();
    }
  }
}
