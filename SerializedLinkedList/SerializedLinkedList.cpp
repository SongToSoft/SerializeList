#include "ListRand.h"

int main()
{
  const std::string path = "serializedList.txt";
  ListRand list;
  list.Add("first");
  list.Add("second");
  list.Add("third");
  list.Add("fourth");
  list.Add("fifth");
  list.AddRandomLink(0, 3);
  list.AddRandomLink(1, 1);
  list.AddRandomLink(2, 4);
  list.Print();

  std::ofstream out;
  out.open(path);
  if (out.is_open()) {
    list.Serialize(out);
  }

  ListRand desList;
  std::ifstream in;
  in.open(path);
  if (in.is_open()) {
    desList.Deserialize(in);
  }
  desList.Print();

  return 0;
}