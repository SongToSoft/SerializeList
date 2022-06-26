using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace LinkedListSerialize
{
  class ListRand
  {
    public ListNode Head;
    public ListNode Tail;
    public int Count = 0;

    public void Serialize(StreamWriter writer)
    {
      Dictionary<ListNode, int> dictionaryNodes = new Dictionary<ListNode, int>();
      var counter = 0;
      var pointer = Head;
      while (pointer != null)
      {
        dictionaryNodes[pointer] = counter;
        ++counter;
        pointer = pointer.Next;
      }
      pointer = Head;
      while (pointer != null)
      {
        writer.WriteLine(pointer.Data);
        if (pointer.Rand != null)
        {
          writer.WriteLine(dictionaryNodes[pointer.Rand]);
        }
        else
        {
          writer.WriteLine(-1);
        }
        pointer = pointer.Next;
      }
    }

    public void Deserialize(StreamReader reader)
    {
      Dictionary<ListNode, int> dictionaryNodes = new Dictionary<ListNode, int>();
      string line;
      while ((line = reader.ReadLine()) != null)
      {
        var node = Add(line);
        line = reader.ReadLine();
        dictionaryNodes[node] = Int32.Parse(line);
      }
      var pointer = Head;
      while (pointer != null)
      {
        if (dictionaryNodes[pointer] != (-1))
        {
          pointer.Rand = dictionaryNodes.ElementAt(dictionaryNodes[pointer]).Key;
        }
        pointer = pointer.Next;
      }
    }

    public ListNode Add(string value)
    {
      ListNode node = new ListNode();
      node.Data = value;
      if (Tail != null)
      {
        Tail.Next = node;
      }

      node.Prev = Tail;
      node.Rand = null;

      Tail = node;
      if (Head == null)
      {
        Head = node;
      }
      ++Count;
      return node;
    }

    public void AddRandomLink(int indexNode, int indexTarget)
    {
      if (((indexNode < 0) || (indexNode > Count)) ||
          ((indexTarget < 0) || (indexTarget > Count)))
      {
        System.Console.WriteLine("Index out of bounds list");
        return;
      }

      ListNode pointerNode = null;
      ListNode pointerTarget = null;
      var pointer = Head;
      int counter = 0;
      while (pointer != null)
      {
        if (indexNode == counter)
        {
          pointerNode = pointer;
        }
        if (indexTarget == counter)
        {
          pointerTarget = pointer;
        }
        if ((pointerNode != null) && (pointerTarget != null))
        {
          break;
        }
        pointer = pointer.Next;
        ++counter;
      }
      pointerNode.Rand = pointerTarget;
    }

    public void Print()
    {
      var node = Head;
      while (node != null)
      {
        System.Console.Write(node.Data + " ");
        if (node.Rand != null)
        {
          System.Console.Write("-(" + node.Rand.Data + ") ");
        }
        node = node.Next;
      }
      System.Console.WriteLine();
    }
  }
}
