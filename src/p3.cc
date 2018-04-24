#include <cstdlib>
#include <iostream>

#include "database.h"
#include "timer.h"

int main() {
  using namespace algdb;

 // Timer timer;
  Database db;
  db.LoadData("../data", 10000, 10000, 100000);
  db.RandomizeGraph(1000000);
  std::cout << "Building graph completed.\n";

  /*timer.Start();
  db.member_id_hash_index[3]->PathToMemberIDDFS(6);
  auto time = timer.End();

  std::cout << "Time to find path to member " << time << "\n";*/
}
